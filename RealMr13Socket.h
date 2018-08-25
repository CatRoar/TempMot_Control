#pragma once


class CRealMr13Socket
{
public:
	CRealMr13Socket();
	~CRealMr13Socket();
	void	setHwnd(HWND hWnd);
	void	InitData();//��ʼ������
	bool	StartWinSock();//����winsock dll
	bool	OpenSocket(int iWaitTime);//��socket��
	bool	ConnectbyIP(unsigned char * IPAddr, int portnum);//��������
	bool	NetOnOff(bool fOn, int iWaitTime);//���翪��1-�� 0-ʵʱ��������ʾ
	bool    IsNetOpen();//�Ƿ�ͨ�Ŵ򿪣�true����
	bool	SendAllData(int DeviceNum, int totalNum);//��������,��ַ����Ŀ
	bool	ReadAllData(int TableStart, int totalNum);//��ȡ����,��ַ����Ŀ

private:
	char	ConvertHexChar(char ch);
	int		String2Hex(CString str, CByteArray &senddata);
	bool	ReadMr13Data(int Idevice, int Ichannel, int Iaddress, int& value, int Idatalen = 0);
	bool	WriteMr13Data(int Idevice, int Ichannel, int address, int Idatalen, int Ivalue);

public:
	HWND	m_hWnd;//������Ϣ���ھ��
	CString	m_cStrIP;//��ǰ����IP��ַ
	BYTE    m_byModAddr, m_byID;//��վ��ַ,��ǰ����ID

private:
	SOCKET	m_iSocket;//�������ڱ���
};

