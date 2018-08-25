
// Template_ControlDlg.h : 头文件
//

#pragma once
#include "Jogdlg.h"
#include "Homedlg.h"
#include "Devicedlg.h"
#include "Errdlg.h"
#include "ListBoxHm.h"
#include "InputCommandDlg.h"
#include "afxwin.h"
#include <vector>
#include "afxdtctl.h"
#include <Gdiplus.h>

using namespace std;
using namespace Gdiplus;

#pragma comment(lib, "Gdiplus.lib")

#define  WM_RECVDATA WM_USER+1

#define MR13COUNT 2
#define AXISCOUNT 2

#define XAXISPULNUM 3200
#define YAXISPULNUM 3200
#define XAXISSCREWVALUE 10
#define YAXISSCREWVALUE 5
#define EPOCHFILETIME   (116444736000000000UL) // time start

struct RECVPARAM
{
	SOCKET sock;//已创建的套接字
	HWND hwnd;//对话框句柄
};

struct CONTROLPARAM		//电控平台控制参数
{
	JOG_INFO jogInfo[2];
	HOME_INFO homeInfo[2];
};

class CLogFile
{
public:
	CStdioFile mFile;
	float dist[2];
	int axisMoving[2];

	CLogFile();
	~CLogFile();

	void WriteLog(int moveMode);
	int SplitToLong(CString strL, char cMark, long* dataProc, int begin, int num);
};

// CTemplate_ControlDlg 对话框
class CTemplate_ControlDlg : public CDialogEx
{
// 构造
public:
	CTemplate_ControlDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CTemplate_ControlDlg();

// 对话框数据
	enum { IDD = IDD_TEMPLATE_CONTROL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON		m_hIcon;
	CJogdlg		m_JogDlg;		//点动参数对象
	CHomedlg	m_HomeDlg;		//回零参数对象
	CDevicedlg	m_DeviceDlg;	//温控仪参数对象
	CErrdlg		m_ErrDlg;		//错误说明对象
	CListBoxHm  m_ListCommand;	//列表框对象
	CMenu       m_menu;			//定义一个菜单类对象

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton13();
	LRESULT afx_msg OnRecvData(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLbnDblclkList1();
	afx_msg LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnInsertCommand();
	afx_msg void OnDeleteCommand();
	DECLARE_MESSAGE_MAP()
public:
	BOOL InitSocket();
	//static void SplitString(const CString& s, vector<string> v, const char* c);
	void InitElecPlatePara();
	void InitElecPlateDevicePara();
	void InitControlCard();
	static DWORD WINAPI RecvProc(LPVOID lpParameter);
	static int String2Hex(CString str, CByteArray &senddata);
	static char ConvertHexChar(char ch);
	static BOOL ReadMr13Data(SOCKET socket, int Idevice, int Ichannel, int Iaddress, int& value, int Idatalen = 0);
	static BOOL WriteMr13Data(SOCKET socket, int Idevice, int Ichannel, int address, int Idatalen, int Ivalue);
	void DistMove(int axis, int dir, long dist);
	void func1();
	void func2();
	void func3();
	void FlushList();
private:
	SOCKET m_socket;
	bool m_homeFlag;
	bool m_jogFlag;
	long m_curpos[6];
	long m_curpos_t[6];
	unsigned short m_gin[32];
	unsigned short m_gin_t[32];
	int m_countNum[2];
	float m_Setsv[11];
	float m_Getpv[11];
	float m_Getpv_pro[11];
	CONTROLPARAM m_controlPara;
	DEVICE_INFO m_devicePara[2];
	CFG_INFO m_cfg[6];
	
	vector<CInputCommandDlg::CCommandPack> mCommandPack;
public:
	CEdit m_edit1;
	CEdit m_edit2;
	CEdit m_edit3;
	CEdit m_edit4;
	CEdit m_edit5;
	CEdit m_edit6;
	CEdit m_edit7;
	CEdit m_edit8;
	CEdit m_edit9;
	CEdit m_edit10;
	CEdit m_edit11;
	CEdit m_edit12;
	CEdit m_edit13;
	CEdit m_edit14;
	CEdit m_edit15;
	CEdit m_edit16;
	CEdit m_edit17;
	CEdit m_edit18;
	CEdit m_edit19;
	CEdit* m_editCrl[19];
	CEdit m_editCrlPV1;
	CEdit m_editCrlPV2;
	CEdit m_editCrlPV3;
	CEdit m_editCrlPV4;
	CEdit m_editCrlPV5;
	CEdit m_editCrlPV6;
	CEdit m_editCrlPV7;
	CEdit m_editCrlPV8;
	CEdit m_editCrlPV9;
	CEdit m_editCrlPV10;
	CEdit m_editCrlPV11;
	CEdit* m_editCrlPV[11];
	HANDLE m_hThread;
	BOOL m_operFlags;
	CStatic m_picCtl1;
	CStatic m_picCtl2;
	CStatic m_picCtl3;
	CStatic m_picCtl4;
	CStatic m_picCtl5;
	CStatic m_picCtl6;
	CStatic m_picCtl7;
	CStatic m_picCtl8;
	CStatic m_picCtl9;
	CStatic m_picCtl10;
	CStatic m_picCtl11;
	CStatic* m_picCtlArray[11];
	CBitmap m_bmplog1;
	CBitmap m_bmplog2;
	CDC m_dcCompatibleRed;
	CDC m_dcCompatibleGreen;
	CRect m_rectPho;
	BITMAP m_bmp1;
	IMC_HANDLE m_handle;	//设备句柄
	CBrush m_checkBrush;	//检查框字体画刷工具
	COLORREF colorRef[12];

	int mThreadMultiStepFlag;
	HANDLE hThreadMultiStep;
	unsigned uiThread1ID;
	static unsigned _stdcall Thread_0(void* pThis);
	int th_CommandExecutor();
	int mThreadFlag_1;
	HANDLE hThread_1;
	unsigned uiThread1ID_1;
	static unsigned _stdcall Thread_1(void* pThis);
	void HomeControl(int axis);
	int mThreadFlag_2;
	HANDLE hThread_2;
	unsigned uiThread1ID_2;
	static unsigned _stdcall Thread_2(void* pThis);

	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int m_ShowSignal[11];

	// temperature paint related para-------------------
	float *mCurTemperPtr; // input temperature data
	HANDLE hThread;
	unsigned int uiThreadID_2;
	CDC* pDC;
	bool mThreadFlag_2DC;

	CRect staticRect;
	CPoint oriPnt;
	CPoint mPntPosX;
	CPoint mPntPosT;
	CPoint mPnt1[120];
	CPoint mPnt2[11][120];
	CPoint m_TagPos[4];

	CString m_Tag[8];
	//CString m_TagPre[8];

	float mTmpPosX;
	float mTmpPosY;

	long mCurStartIndex; // 待显示数据的起始index
	long mCurEndIndex;   // 待显示数据的结束index
	long mCurStoreNum;   // 已储存数据的数量

	CPen mPenAxis;
	CPen mPenPos;
	CBrush mBrushPos;
	CPen mPenAxisMoving;
	CPen mPenAxisError;
	CBrush mBrushAxisError;

	unsigned int uiThreadID;
	bool mThreadFlag;
	bool m_ThreadFlag1;
	bool m_ThreadFlag2;
	bool m_ScanMaxMinFlag;
	bool m_ThreadFlag_3;

	int m_ThreadFlag_2DC;
	float m_Scale; // scale = temperature date / T axis height; not used for now
	unsigned m_MinIndex;
	float m_CurMin;
	unsigned m_MaxIndex;
	float m_CurMax;
	BOOL m_RescaleFlag;
	float m_Temp;
	CPen m_Pen[12];
	vector<float> m_vecTempData[11];
	vector<time_t> m_vecTempTimeStamp;
	bool m_ValidFlag[11];

	ULONG_PTR m_pGdiToken;
	Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;

	CEdit m_TimeStartCtr;
	CEdit m_TimeEndCtr;

	CButton m_TempCheck1;
	CButton m_TempCheck2;
	CButton m_TempCheck3;
	CButton m_TempCheck4;
	CButton m_TempCheck5;
	CButton m_TempCheck6;
	CButton m_TempCheck7;
	CButton m_TempCheck8;
	CButton m_TempCheck9;
	CButton m_TempCheck10;
	CButton m_TempCheck11;

	// temperature paint related func-------------------
	static unsigned int _stdcall Thread_Paint(void* pThis);
	int m_DataTransferToGraaph();
	void m_DrawGraph(CDC *pDC);
	afx_msg void OnBnClickedButton1();
	
	BOOL StringToSysTime(CString strTimeStart, SYSTEMTIME *lpSystemTime);
	BOOL StringToData1(CString strTime, time_t *time1, time_t *time2, CString *FileName);
	BOOL StringToData2(CString strSrc, time_t *timet, float *time1, float *t2, float *t3,
		float *t4, float *t5, float *t6, float *t7, float *t8, float *t9,
		float *t10, float *t11);
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedCheck8();
	afx_msg void OnBnClickedCheck9();
	afx_msg void OnBnClickedCheck10();
	afx_msg void OnBnClickedCheck11();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnReadMoveRecord();
	afx_msg void OnClose();
};