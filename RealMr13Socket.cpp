#include "stdafx.h"
#include "RealMr13Socket.h"


CRealMr13Socket::CRealMr13Socket()
{
	m_hWnd = NULL;
}


CRealMr13Socket::~CRealMr13Socket()
{
}


void CRealMr13Socket::setHwnd(HWND hWnd)
{
	m_hWnd = hWnd;
}


void CRealMr13Socket::InitData()
{
	m_hWnd = NULL;
	m_cStrIP = "192.168.1.201";
	m_iSocket = NULL;
}


bool CRealMr13Socket::StartWinSock()
{
	//add by ZYN for use windows socket.
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(wVersionRequested, &wsaData))
	{
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		return false;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		WSACleanup();
		return false;
	}

	/* The WinSock DLL is acceptable. Proceed. */
	return true;
}


bool CRealMr13Socket::OpenSocket(int iWaitTime)
{
	int err, timeout = iWaitTime;//单位m秒
	m_iSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_iSocket == NULL) return false;
	err = setsockopt(m_iSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
	if (err != NO_ERROR)
	{
		closesocket(m_iSocket);
		m_iSocket = NULL;
		return false;
	}
	return true;
}


bool CRealMr13Socket::ConnectbyIP(unsigned char * IPAddr, int portnum)
{
	struct sockaddr_in sa;		//holds IP address and protocol port

	//store remote host's IP address, server's port number, protocal type into sa structure
	memcpy((char*)&sa.sin_addr, IPAddr, 4);
	sa.sin_port = htons(portnum);
	sa.sin_family = AF_INET;

	if (connect(m_iSocket, (sockaddr *)&sa, sizeof(sa)) < 0)		//connect to remote server
	{
		return false;
	}
	return true;
}


bool CRealMr13Socket::NetOnOff(bool fOn, int iWaitTime)
{
	unsigned char IPAddr[4];
	int a, i; 
	CString cStrIP = m_cStrIP;
	a=atoi(cStrIP);
	//a = _wtoi(cStrIP);
	IPAddr[0] = (unsigned char)a;
	i = cStrIP.Find('.');
	cStrIP = cStrIP.Mid(i + 1);
	a=atoi(cStrIP);
	//a = _wtoi(cStrIP);
	IPAddr[1] = (unsigned char)a;
	i = cStrIP.Find('.');
	cStrIP = cStrIP.Mid(i + 1);
	a=atoi(cStrIP);
	//a = _wtoi(cStrIP);
	IPAddr[2] = (unsigned char)a;
	i = cStrIP.Find('.');
	cStrIP = cStrIP.Mid(i + 1);
	a=atoi(cStrIP);
	//a = _wtoi(cStrIP);
	IPAddr[3] = (unsigned char)a;
	if (m_iSocket != NULL)
	{
		closesocket(m_iSocket);
		m_iSocket = NULL;
	}
	if (fOn)
	{
		if (!StartWinSock())
		{
			AfxMessageBox(_T("网络文本版本太低，请升级"));
			return false;
		}
	}
	if (!OpenSocket(iWaitTime))
	{
		AfxMessageBox(_T("控制器连接不能正常设置"));
		return false;
	}
	if (!ConnectbyIP(IPAddr, 502 + (m_byID - 1) * 10))//502/512
	{
		closesocket(m_iSocket);
		m_iSocket = NULL;
		return false;
	}
	return true;
}


bool CRealMr13Socket::IsNetOpen()
{
	if (m_iSocket) return true;
	else return false;
}


bool CRealMr13Socket::ReadMr13Data(int Idevice, int Ichannel, int Iaddress, int& value, int Idatalen)
{
	CString device, channel, address, datalen;
	device.Format("%02d", Idevice);
	channel.Format("%d", Ichannel);
	address.Format("%04X", Iaddress);
	datalen.Format("%d", Idatalen);

	CString cSendtmp, strtmp, cSendmsg, cSendmsgHex, cReciveMsg;
	cSendmsgHex = "02";
	strtmp = device + channel + "R" + address + datalen;
	for (int i = 0; i < strtmp.GetLength(); i++)
	{
		cSendtmp.Format("%X", strtmp[i]);
		cSendmsgHex += cSendtmp;
	}
	cSendmsgHex += "030D";

	strtmp.Empty();
	char buf[100];
	memset(buf, 0, 100);
	CByteArray hexData;
	int len = String2Hex(cSendmsgHex, hexData);
	for (int i = 0; i < hexData.GetSize(); i++)
	{
		BYTE bt = hexData[i];
		strtmp.Format("%c", bt); //将字符送入临时变量strtemp存放
		cSendmsg += strtmp;
	}
	send(m_iSocket, cSendmsg.GetBuffer(), len, 0);
	recv(m_iSocket, buf, 100, 0);

	int n = 0;
	int temp = 0;
	if (buf[5] == '0'&&buf[6] == '0')
	{
		for (int i = 8; i < 12; i++)
		{
			if (buf[i] >= 'A'&&buf[i] <= 'F')//十六进制还要判断他是不是在A-F或者a-f之间a=10。。
				n = buf[i] - 'A' + 10;
			else if (buf[i] >= 'a'&&buf[i] <= 'f')
				n = buf[i] - 'a' + 10;
			else n = buf[i] - '0';
			temp = temp * 16 + n;
		}
		value = temp;
		return true;
	}
	else
	{
		return false;
	}
}


int CRealMr13Socket::String2Hex(CString str, CByteArray &senddata)
{
	int hexdata, lowhexdata;
	int hexdatalen = 0;
	int len = str.GetLength();
	//if len is odd number,the system will 
	// add '0' front of the variable "str";
	// else not 
	if (len % 2 == 0)
		senddata.SetSize(len / 2);
	else
	{
		str = operator+('0', str);
		senddata.SetSize(len / 2 + 1);
		len++;
	}


	for (int i = 0; i < len;)
	{
		char lstr, hstr = str[i];
		if (hstr == ' ')
		{
			i++;
			continue;
		}
		i++;
		if (i >= len)
			break;
		lstr = str[i];
		hexdata = ConvertHexChar(hstr);
		lowhexdata = ConvertHexChar(lstr);
		if ((hexdata == 16) || (lowhexdata == 16))
			break;
		else
			hexdata = hexdata * 16 + lowhexdata;
		i++;
		senddata[hexdatalen] = (char)hexdata;
		hexdatalen++;
	}

	senddata.SetSize(hexdatalen);
	return hexdatalen;
}


char CRealMr13Socket::ConvertHexChar(char ch)
{
	if ((ch >= '0') && (ch <= '9'))
		return ch - 0x30;
	else if ((ch >= 'A') && (ch <= 'F'))
		return ch - 'A' + 10;
	else if ((ch >= 'a') && (ch <= 'f'))
		return ch - 'a' + 10;
	else return (-1);
}


bool CRealMr13Socket::WriteMr13Data(int Idevice, int Ichannel, int Iaddress, int Idatalen, int Ivalue)
{
	CString device, channel, address, datalen, value;
	device.Format("%02d", Idevice);
	channel.Format("%d", Ichannel);
	address.Format("%04X", Iaddress);
	datalen.Format("%d", Idatalen);
	value.Format("%04X", Ivalue);

	CString cSendtmp, strtmp, cSendmsg, cSendmsgHex, cReciveMsg;
	cSendmsgHex = "02";
	strtmp = device + channel + "W" + address + datalen + "," + value;
	for (int i = 0; i < strtmp.GetLength(); i++)
	{
		cSendtmp.Format("%X", strtmp[i]);
		cSendmsgHex += cSendtmp;
	}
	cSendmsgHex += "030D";

	strtmp.Empty();
	char buf[20];
	memset(buf, 0, 20);
	CByteArray hexData;
	int len = String2Hex(cSendmsgHex, hexData);
	for (int i = 0; i < hexData.GetSize(); i++)
	{
		BYTE bt = hexData[i];
		strtmp.Format("%c", bt); //将字符送入临时变量strtemp存放
		cSendmsg += strtmp;
	}
	send(m_iSocket, cSendmsg.GetBuffer(), len, 0);
	recv(m_iSocket, buf, 20, 0);

	if (buf[5] == '0'&&buf[6] == '0')
	{
		return true;
	}
	else
	{
		return false;
	}
}