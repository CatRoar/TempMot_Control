#pragma once


class CRealMr13Socket
{
public:
	CRealMr13Socket();
	~CRealMr13Socket();
	void	setHwnd(HWND hWnd);
	void	InitData();//初始化数据
	bool	StartWinSock();//引用winsock dll
	bool	OpenSocket(int iWaitTime);//打开socket口
	bool	ConnectbyIP(unsigned char * IPAddr, int portnum);//连接网络
	bool	NetOnOff(bool fOn, int iWaitTime);//网络开关1-开 0-实时连接无提示
	bool    IsNetOpen();//是否通信打开，true正常
	bool	SendAllData(int DeviceNum, int totalNum);//发送数据,地址，数目
	bool	ReadAllData(int TableStart, int totalNum);//读取数据,地址，数目

private:
	char	ConvertHexChar(char ch);
	int		String2Hex(CString str, CByteArray &senddata);
	bool	ReadMr13Data(int Idevice, int Ichannel, int Iaddress, int& value, int Idatalen = 0);
	bool	WriteMr13Data(int Idevice, int Ichannel, int address, int Idatalen, int Ivalue);

public:
	HWND	m_hWnd;//发送消息窗口句柄
	CString	m_cStrIP;//当前连接IP地址
	BYTE    m_byModAddr, m_byID;//从站地址,当前网络ID

private:
	SOCKET	m_iSocket;//连接网口变量
};

