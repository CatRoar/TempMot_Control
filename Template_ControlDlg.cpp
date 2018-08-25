
// Template_ControlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Template_Control.h"
#include "Template_ControlDlg.h"
#include "afxdialogex.h"
#include "GraphShowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTemplate_ControlDlg 对话框

CRITICAL_SECTION  m_csReadWriteTable;//临界区
int EmStopFlag = 0;
double g_absRecord_In[2] = { 0, 0 };
double g_absRecord_Out[2] = { 0, 0 };

CTemplate_ControlDlg::CTemplate_ControlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTemplate_ControlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_operFlags = FALSE;
	m_hThread = NULL;
	m_handle = NULL;
	::InitializeCriticalSection(&m_csReadWriteTable);
	Gdiplus::GdiplusStartup(&m_pGdiToken, &m_gdiplusStartupInput, NULL);
	m_jogFlag = false;
	m_countNum[0] = 0;
	m_countNum[1] = 0;
}

CTemplate_ControlDlg::~CTemplate_ControlDlg()
{
	
	
	Gdiplus::GdiplusShutdown(m_pGdiToken);
	::DeleteCriticalSection(&m_csReadWriteTable);	
}

void CTemplate_ControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT3, m_edit3);
	DDX_Control(pDX, IDC_EDIT4, m_edit4);
	DDX_Control(pDX, IDC_EDIT5, m_edit5);
	DDX_Control(pDX, IDC_EDIT6, m_edit6);
	DDX_Control(pDX, IDC_EDIT13, m_edit7);
	DDX_Control(pDX, IDC_EDIT14, m_edit8);
	DDX_Control(pDX, IDC_EDIT15, m_edit9);
	DDX_Control(pDX, IDC_EDIT16, m_edit10);
	DDX_Control(pDX, IDC_EDIT17, m_edit11);
	DDX_Control(pDX, IDC_EDIT7, m_editCrlPV1);
	DDX_Control(pDX, IDC_EDIT8, m_editCrlPV2);
	DDX_Control(pDX, IDC_EDIT9, m_editCrlPV3);
	DDX_Control(pDX, IDC_EDIT10, m_editCrlPV4);
	DDX_Control(pDX, IDC_EDIT11, m_editCrlPV5);
	DDX_Control(pDX, IDC_EDIT12, m_editCrlPV6);
	DDX_Control(pDX, IDC_EDIT18, m_editCrlPV7);
	DDX_Control(pDX, IDC_EDIT19, m_editCrlPV8);
	DDX_Control(pDX, IDC_EDIT20, m_editCrlPV9);
	DDX_Control(pDX, IDC_EDIT21, m_editCrlPV10);
	DDX_Control(pDX, IDC_EDIT22, m_editCrlPV11);
	DDX_Control(pDX, IDC_ALARMPIC1, m_picCtl1);
	DDX_Control(pDX, IDC_ALARMPIC2, m_picCtl2);
	DDX_Control(pDX, IDC_ALARMPIC3, m_picCtl3);
	DDX_Control(pDX, IDC_ALARMPIC4, m_picCtl4);
	DDX_Control(pDX, IDC_ALARMPIC5, m_picCtl5);
	DDX_Control(pDX, IDC_ALARMPIC6, m_picCtl6);
	DDX_Control(pDX, IDC_ALARMPIC7, m_picCtl7);
	DDX_Control(pDX, IDC_ALARMPIC8, m_picCtl8);
	DDX_Control(pDX, IDC_ALARMPIC9, m_picCtl9);
	DDX_Control(pDX, IDC_ALARMPIC10, m_picCtl10);
	DDX_Control(pDX, IDC_ALARMPIC11, m_picCtl11);
	DDX_Control(pDX, IDC_LIST1, m_ListCommand);
	DDX_Control(pDX, IDC_EDIT23, m_edit12);
	DDX_Control(pDX, IDC_EDIT24, m_edit13);
	DDX_Control(pDX, IDC_EDIT25, m_edit14);
	DDX_Control(pDX, IDC_EDIT26, m_edit15);
	DDX_Control(pDX, IDC_EDIT27, m_edit16);
	DDX_Control(pDX, IDC_EDIT28, m_edit17);
	DDX_Control(pDX, IDC_EDIT29, m_edit18);
	DDX_Control(pDX, IDC_EDIT30, m_edit19);
	//DDX_Control(pDX, IDC_EDIT35, m_TimeStartCtr);
	//DDX_Control(pDX, IDC_EDIT36, m_TimeEndCtr);
	DDX_Control(pDX, IDC_CHECK1, m_TempCheck1);
	DDX_Control(pDX, IDC_CHECK2, m_TempCheck2);
	DDX_Control(pDX, IDC_CHECK3, m_TempCheck3);
	DDX_Control(pDX, IDC_CHECK4, m_TempCheck4);
	DDX_Control(pDX, IDC_CHECK5, m_TempCheck5);
	DDX_Control(pDX, IDC_CHECK6, m_TempCheck6);
	DDX_Control(pDX, IDC_CHECK7, m_TempCheck7);
	DDX_Control(pDX, IDC_CHECK8, m_TempCheck8);
	DDX_Control(pDX, IDC_CHECK9, m_TempCheck9);
	DDX_Control(pDX, IDC_CHECK10, m_TempCheck10);
	DDX_Control(pDX, IDC_CHECK11, m_TempCheck11);
}

BEGIN_MESSAGE_MAP(CTemplate_ControlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON9, &CTemplate_ControlDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON3, &CTemplate_ControlDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTemplate_ControlDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CTemplate_ControlDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON13, &CTemplate_ControlDlg::OnBnClickedButton13)
	ON_MESSAGE(WM_RECVDATA, &CTemplate_ControlDlg::OnRecvData)
	ON_WM_TIMER()
	ON_LBN_DBLCLK(IDC_LIST1, &CTemplate_ControlDlg::OnLbnDblclkList1)
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_32771, &CTemplate_ControlDlg::OnInsertCommand)
	ON_COMMAND(ID_32772, &CTemplate_ControlDlg::OnDeleteCommand)
	ON_REGISTERED_MESSAGE(WM_MY_MESSAGE, &CTemplate_ControlDlg::OnMyMessage)
	ON_BN_CLICKED(IDC_BUTTON14, &CTemplate_ControlDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON16, &CTemplate_ControlDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON15, &CTemplate_ControlDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON5, &CTemplate_ControlDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTemplate_ControlDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CTemplate_ControlDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CTemplate_ControlDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON10, &CTemplate_ControlDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CTemplate_ControlDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CTemplate_ControlDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON1, &CTemplate_ControlDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CTemplate_ControlDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CTemplate_ControlDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CTemplate_ControlDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CTemplate_ControlDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CTemplate_ControlDlg::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK6, &CTemplate_ControlDlg::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK7, &CTemplate_ControlDlg::OnBnClickedCheck7)
	ON_BN_CLICKED(IDC_CHECK8, &CTemplate_ControlDlg::OnBnClickedCheck8)
	ON_BN_CLICKED(IDC_CHECK9, &CTemplate_ControlDlg::OnBnClickedCheck9)
	ON_BN_CLICKED(IDC_CHECK10, &CTemplate_ControlDlg::OnBnClickedCheck10)
	ON_BN_CLICKED(IDC_CHECK11, &CTemplate_ControlDlg::OnBnClickedCheck11)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_32773, &CTemplate_ControlDlg::OnReadMoveRecord)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CTemplate_ControlDlg 消息处理程序

BOOL CTemplate_ControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	// initial paint for temperature data input----------------------------------
	//COLORREF colorRef[12];
	float height = 0;

	CWnd *pWnd = NULL;
	pWnd = GetDlgItem(IDC_STATIC_TEMP);//获取控件句柄  
	pWnd->GetClientRect(&staticRect);//获取句柄指向控件区域的大小  
	oriPnt.x = staticRect.Width()*0.1;
	oriPnt.y = staticRect.Height()*0.95;
	mPntPosX.x = oriPnt.x + staticRect.Width()*0.85;
	mPntPosX.y = oriPnt.y;
	mPntPosT.x = oriPnt.x;
	mPntPosT.y = oriPnt.y - staticRect.Height()*0.9;
	pDC = NULL;
	pDC = pWnd->GetDC();//获取picture的DC  
	float step = (mPntPosX.x - oriPnt.x - 4) / 15;

	hThread = NULL;
	m_CurMin = 100;
	m_MinIndex = 120;
	m_CurMax = -20;
	m_MaxIndex = 120;
	m_RescaleFlag = 1;
	mThreadFlag = 0;
	m_ThreadFlag1 = 1;
	m_ThreadFlag2 = 1;
	m_ScanMaxMinFlag = 0;

	for (int i = 15; i > -1; i--)
	{
		mPnt1[i].x = oriPnt.x + step * i + 4;
		mPnt1[i].y = oriPnt.y - 4;
		for (int j = 0; j < 11; j++)
		{
			mPnt2[j][i] = mPnt1[i];
			m_ValidFlag[j] = false;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		m_Tag[i] = "0";
	}

	colorRef[0] = RGB(255, 0, 0);
	colorRef[1] = RGB(191, 63, 0);
	colorRef[2] = RGB(128, 128, 0);
	colorRef[3] = RGB(63, 191, 0);
	colorRef[4] = RGB(0, 255, 0);
	colorRef[5] = RGB(0, 191, 63);
	colorRef[6] = RGB(0, 128, 128);
	colorRef[7] = RGB(0, 63, 191);
	colorRef[8] = RGB(0, 0, 255);
	colorRef[9] = RGB(63, 0, 191);
	colorRef[10] = RGB(128, 0, 128);
	colorRef[11] = RGB(0, 0, 0);

	for (int i = 0; i < 12; i++)
	{
		m_Pen[i].CreatePen(PS_SOLID, 1, colorRef[i]);
	}

	height = oriPnt.y - mPntPosT.y - 4;
	m_TagPos[0].x = oriPnt.x - 40;
	m_TagPos[0].y = oriPnt.y - 4 - 6;
	m_TagPos[1].x = oriPnt.x - 40;
	m_TagPos[1].y = oriPnt.y - 4 - 6 - height / 3.0;
	m_TagPos[2].x = oriPnt.x - 40;
	m_TagPos[2].y = oriPnt.y - 4 - 6 - 2.0 * height / 3.0;
	m_TagPos[3].x = oriPnt.x - 40;
	m_TagPos[3].y = oriPnt.y - 4 - 6 - height;
	//-------------------------------------------

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	///////////////////////////////////
	m_menu.LoadMenu(IDR_MENU2);
	SetMenu(&m_menu);

	m_ListCommand.AddString(_T(""));

	m_editCrl[0] = &m_edit1;
	m_editCrl[1] = &m_edit2;
	m_editCrl[2] = &m_edit3;
	m_editCrl[3] = &m_edit4;
	m_editCrl[4] = &m_edit5;
	m_editCrl[5] = &m_edit6;
	m_editCrl[6] = &m_edit7;
	m_editCrl[7] = &m_edit8;
	m_editCrl[8] = &m_edit9;
	m_editCrl[9] = &m_edit10;
	m_editCrl[10] = &m_edit11;
	m_editCrl[11] = &m_edit12;
	m_editCrl[12] = &m_edit13;
	m_editCrl[13] = &m_edit14;
	m_editCrl[14] = &m_edit15;
	m_editCrl[15] = &m_edit16;
	m_editCrl[16] = &m_edit17;
	m_editCrl[17] = &m_edit18;
	m_editCrl[18] = &m_edit19;

	m_editCrlPV[0] = &m_editCrlPV1;
	m_editCrlPV[1] = &m_editCrlPV2;
	m_editCrlPV[2] = &m_editCrlPV3;
	m_editCrlPV[3] = &m_editCrlPV4;
	m_editCrlPV[4] = &m_editCrlPV5;
	m_editCrlPV[5] = &m_editCrlPV6;
	m_editCrlPV[6] = &m_editCrlPV7;
	m_editCrlPV[7] = &m_editCrlPV8;
	m_editCrlPV[8] = &m_editCrlPV9;
	m_editCrlPV[9] = &m_editCrlPV10;
	m_editCrlPV[10] = &m_editCrlPV11;

	m_picCtlArray[0] = &m_picCtl1;
	m_picCtlArray[1] = &m_picCtl2;
	m_picCtlArray[2] = &m_picCtl3;
	m_picCtlArray[3] = &m_picCtl4;
	m_picCtlArray[4] = &m_picCtl5;
	m_picCtlArray[5] = &m_picCtl6;
	m_picCtlArray[6] = &m_picCtl7;
	m_picCtlArray[7] = &m_picCtl8;
	m_picCtlArray[8] = &m_picCtl9;
	m_picCtlArray[9] = &m_picCtl10;
	m_picCtlArray[10] = &m_picCtl11;

	///////////////////////////////////
	CFile deviceIni;	//查找是否存在ini文件，若不存在，则生成一个新的默认设置的ini文件
	deviceIni.Open("Template_Control.ini", CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);
	CString strName, strValue, strTmp;

	for (int i = 0; i < 11; i++)
	{
		strName.Format("PT100SV_%d", i);
		::GetPrivateProfileString("MR13Info", strName, "0", strValue.GetBuffer(MAX_PATH), MAX_PATH, "C:\\Windows\\Template_Control.ini");
		strName.ReleaseBuffer();
		m_Setsv[i] = atof(strValue);//初始化m_Setsv[i]、m_Getpv[i]两个数组
		strTmp.Format("%0.1f℃", m_Setsv[i]);
		m_editCrl[i]->SetWindowTextA(strTmp);
		m_Getpv[i] = 0;
		
	}

	CFile absPosIni;	//查找是否存在ini文件，若不存在，则生成一个新的默认设置的ini文件
	absPosIni.Open("AbsPos_Record.ini", CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);

	for (int i = 0; i < 2;i++)
	{
		strName.Format("AbsPos_%d", i);
		::GetPrivateProfileString("PosInfo", strName, "0", strValue.GetBuffer(MAX_PATH), MAX_PATH, "C:\\Windows\\AbsPos_Record.ini");
		strName.ReleaseBuffer();
		g_absRecord_In[i] = atof(strValue);
	}

	//加载报警图标
	m_bmplog1.LoadBitmap(IDB_BITMAP1);
	m_bmplog2.LoadBitmap(IDB_BITMAP2);
	CPaintDC dcLog(this);
	m_dcCompatibleRed.CreateCompatibleDC(&dcLog);
	m_dcCompatibleRed.SelectObject(&m_bmplog1);
	m_dcCompatibleGreen.CreateCompatibleDC(&dcLog);
	m_dcCompatibleGreen.SelectObject(&m_bmplog2);
	CStatic* pPHoto1 = (CStatic*)GetDlgItem(IDC_ALARMPIC1);//IDC_ALARMPIC1为指定的Picture控件
	pPHoto1->GetClientRect(&m_rectPho);
	m_bmplog1.GetBitmap(&m_bmp1);

	m_checkBrush.CreateSolidBrush(GetSysColor(COLOR_3DFACE));//初始化画刷,用GetSysColor返回对话框背景色

	//程序初始化时搜索PC中的网卡
	char info[16][256];
	int num;
	CString str;
	if (PKG_IMC_FindNetCard(info, &num))
	{
		for (int i = 0; i < num; i++)
		{
			((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(info[i]);
		}
		((CComboBox*)GetDlgItem(IDC_COMBO3))->SetCurSel(0);
	}

	InitElecPlatePara();		//初始化运动参数
	InitElecPlateDevicePara();	//初始化平台参数

	uiThread1ID = 0;
	uiThread1ID_1 = 0;
	uiThread1ID_2 = 0;

	hThreadMultiStep = NULL;
	hThread_1 = NULL;
	hThread_2 = NULL;

	m_socket = NULL;
	for (int i = 0; i < 6;i++)
	{
		m_curpos[i] = 0;
		m_curpos_t[i] = 0;
	}

	for (int i = 0; i < 32;i++)
	{
		m_gin[i] = 2;
		m_gin_t[i] = 2;
	}

	for (int i = 0; i < 11;i++)
	{
		m_Getpv_pro[i] = 0;
		m_ShowSignal[i] = -1;//红色为0，绿色为1
	}

	SetTimer(2, 100, NULL);
	SetTimer(3, 100, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTemplate_ControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTemplate_ControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	/*
	//绘制报警图标
	for (int i = 0; i < 11; i++)
	{
		if (m_Getpv[i]<m_Setsv[i])
		{
			m_picCtlArray[i]->GetDC()->StretchBlt(m_rectPho.left, m_rectPho.top, m_rectPho.Width(), m_rectPho.Height(), &m_dcCompatibleRed, 0, 0, m_bmp1.bmWidth, m_bmp1.bmHeight, SRCCOPY);
		}
		else
		{
			m_picCtlArray[i]->GetDC()->StretchBlt(m_rectPho.left, m_rectPho.top, m_rectPho.Width(), m_rectPho.Height(), &m_dcCompatibleGreen, 0, 0, m_bmp1.bmWidth, m_bmp1.bmHeight, SRCCOPY);
		}
	}*/

	// paint for temperature data input----------------------------------------
	//mThreadFlag = 0;
	m_ThreadFlag_2DC = 0;
	Sleep(64);

	pDC->SetROP2(R2_COPYPEN);

	pDC->SelectStockObject(BLACK_BRUSH);
	pDC->SelectStockObject(BLACK_PEN);

	pDC->Rectangle(staticRect);
	pDC->SelectObject(mPenAxis);

	//pDC->SelectStockObject(WHITE_BRUSH);
	pDC->SelectStockObject(WHITE_PEN);

	pDC->MoveTo(oriPnt);
	pDC->LineTo(CPoint((int)mPntPosX.x, (int)mPntPosX.y));
	pDC->MoveTo(oriPnt);
	pDC->LineTo(CPoint((int)mPntPosT.x, (int)mPntPosT.y));

	mThreadFlag = 1;
	m_RescaleFlag = 1;
	if (hThread == NULL)
	{
		hThread = (HANDLE)_beginthreadex(NULL, 0, CTemplate_ControlDlg::Thread_Paint, this, 0, &uiThreadID);
		if (hThread == 0)
		{
			MessageBox(_T("线程创建失败"));
			return;
		}
	}
}

unsigned int CTemplate_ControlDlg::Thread_Paint(void* pThis)
{
	CTemplate_ControlDlg* pThread = (CTemplate_ControlDlg*)pThis;

	pThread->m_DataTransferToGraaph();

	return 1;
}

int CTemplate_ControlDlg::m_DataTransferToGraaph()
{
	vector<float>::iterator iter_begin, iter_end;
	vector<time_t>::iterator iter_begin_time, iter_end_time;
	unsigned uVecSize = 0;
	int iFlagTmp = 0, iFlagSave = 0;
	unsigned __int64 i64Tmp = 0;
	CString strFN, strTemp;

	time_t timep[2] = { 0 };
	time_t timet, timetemp = 0;
	FILETIME ft, ftl;
	ULARGE_INTEGER uli;
	SYSTEMTIME SystemTime;

	FILE *pf = NULL, *pf2 =NULL;
	CStdioFile  mf1, mf2;
	CDC* pmDC = NULL;
	if (pmDC != NULL)
	{
		ReleaseDC(pmDC);
		pmDC = NULL;
	}
	CWnd *pWnd = NULL;
	pWnd = GetDlgItem(IDC_STATIC_TEMP);//获取控件句柄  

	pmDC = NULL;
	pmDC = pWnd->GetDC();//获取picture的DC  

	if ((uVecSize = m_vecTempData[0].size()) < 120)
	{
		for (int i = 0; i < 120 - uVecSize; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				if (m_Getpv[j] > 150)
				{
					m_vecTempData[j].push_back(150);
				}
				else if (m_Getpv[j] < -150)
				{
					m_vecTempData[j].push_back(-150);
				}
				else
				{
					m_vecTempData[j].push_back(m_Getpv[j]);
				}
			}
		}
		for (int i = 0; i < 120 - uVecSize; i++)
		{
			m_vecTempTimeStamp.push_back(0);
		}
	}

	GetSystemTimeAsFileTime(&ft);
	FileTimeToLocalFileTime(&ft, &ftl);
	uli.HighPart = ftl.dwHighDateTime;
	uli.LowPart = ftl.dwLowDateTime;
	timet = (double)uli.QuadPart / 10000.0;
	FileTimeToSystemTime(&ftl, &SystemTime);
	
	
	strFN.Format("temp_%d-%d-%d_%d-%d-%d.txt", SystemTime.wYear, SystemTime.wMonth,
		SystemTime.wDay, (SystemTime.wHour), SystemTime.wMinute, SystemTime.wSecond);
	if (mf1.Open(strFN.GetString(), CStdioFile::modeCreate | CStdioFile::modeWrite | CStdioFile::modeNoTruncate) == false)
	{
		MessageBox("无法打开文件");
		return 0;
	}

	m_ThreadFlag2 = 0;

	while (mThreadFlag == 1)
	{
		if (abs((timep[1] - timep[0])) < 500 && mThreadFlag)
		{
			Sleep(500 - (timep[1] - timep[0]));
		}

		GetSystemTimeAsFileTime(&ft);
		FileTimeToLocalFileTime(&ft, &ftl);
		uli.HighPart = ftl.dwHighDateTime;
		uli.LowPart = ftl.dwLowDateTime;
		timep[0] = (double)uli.QuadPart / 10000.0;
		FileTimeToSystemTime(&ftl, &SystemTime);
		
		if (m_vecTempData[0].size() >= 128)
		{
			m_RescaleFlag = 1;
			iFlagSave = 0;
			for (int i = 0; i < 8; i++)
			{
				strTemp.Format("%I64u:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f\t获取时间:%d:%d:%d_%d:%d:%d\n",
					m_vecTempTimeStamp.at(i),
					m_vecTempData[0].at(i),
					m_vecTempData[1].at(i),
					m_vecTempData[2].at(i),
					m_vecTempData[3].at(i),
					m_vecTempData[4].at(i),
					m_vecTempData[5].at(i),
					m_vecTempData[6].at(i),
					m_vecTempData[7].at(i),
					m_vecTempData[8].at(i),
					m_vecTempData[9].at(i),
					m_vecTempData[10].at(i),
					SystemTime.wYear, 
					SystemTime.wMonth,
					SystemTime.wDay, 
					SystemTime.wHour, 
					SystemTime.wMinute, 
					SystemTime.wSecond);
				mf1.WriteString(strTemp);
			}
		}
		else
		{
			iFlagSave = 0;
			if (timep[0] - timet > 3600000)
			{
				iFlagSave = 1;
				if (mf1.m_hFile != CFile::hFileNull)
				{
					for (int i = 0; i < m_vecTempData[0].size(); i++)
					{
						strTemp.Format("%I64u:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f\t获取时间:%d:%d:%d_%d:%d:%d\n",
							m_vecTempTimeStamp.at(i),
							m_vecTempData[0].at(i),
							m_vecTempData[1].at(i),
							m_vecTempData[2].at(i),
							m_vecTempData[3].at(i),
							m_vecTempData[4].at(i),
							m_vecTempData[5].at(i),
							m_vecTempData[6].at(i),
							m_vecTempData[7].at(i),
							m_vecTempData[8].at(i),
							m_vecTempData[9].at(i),
							m_vecTempData[10].at(i),
							SystemTime.wYear,
							SystemTime.wMonth,
							SystemTime.wDay,
							SystemTime.wHour,
							SystemTime.wMinute,
							SystemTime.wSecond);
						mf1.WriteString(strTemp);
					}

					mf1.Close();
				}


				mf2.Open(_T("FileRecord.txt"), CStdioFile::modeCreate | CStdioFile::modeWrite | CStdioFile::modeNoTruncate);

				strTemp.Format("%I664u:%I64u:", timet, timep[0]);
				strTemp += (strFN + "\n");
				mf2.SeekToEnd();
				mf2.WriteString(strTemp);
				mf2.Close();

				GetSystemTimeAsFileTime(&ft);
				FileTimeToLocalFileTime(&ft, &ftl);
				uli.HighPart = ftl.dwHighDateTime;
				uli.LowPart = ftl.dwLowDateTime;
				FileTimeToSystemTime(&ftl, &SystemTime);

				strFN.Format("temp_%d-%d-%d_%d-%d-%d.txt", SystemTime.wYear, SystemTime.wMonth,
					SystemTime.wDay, (SystemTime.wHour), SystemTime.wMinute, SystemTime.wSecond);
				if (mf1.Open(strFN, CFile::modeNoTruncate | CStdioFile::modeWrite | CFile::modeCreate) == false)
				{
					MessageBox("无法打开文件");
					return 0;
				}

				timet = timep[0];
			}
		}

		for (int i = 0; i < 11; i++)
		{
			iter_begin = m_vecTempData[i].begin();
			if (m_vecTempData[i].size() >= 128)
			{
				m_vecTempData[i].erase(iter_begin, iter_begin + 8);
			}
			if (m_Getpv[i] > 150)
			{
				m_vecTempData[i].push_back(150);
			}
			else if (m_Getpv[i] < -150)
			{
				m_vecTempData[i].push_back(-150);
			}
			else
			{
				m_vecTempData[i].push_back(m_Getpv[i]);
			}
		}

		iter_begin_time = m_vecTempTimeStamp.begin();
		if (m_vecTempTimeStamp.size() >= 128)
		{
			m_vecTempTimeStamp.erase(iter_begin_time, iter_begin_time + 8);
		}
		m_vecTempTimeStamp.push_back(timep[0]);

		

		// check if it is necessary to update max and min value to show -------
		if (m_MaxIndex > 119 || m_ScanMaxMinFlag == 1)
		{
			m_CurMax = -999;
			m_RescaleFlag = 1;
			for (int i = 0; i < 11; i++)
			{
				if (m_ValidFlag[i] == true)
				{
					iter_end = m_vecTempData[i].end() - 1;
					for (int j = 0; j < 120; j++)
					{
						if (m_CurMax < *(iter_end))
						{
							m_CurMax = *(iter_end);
							m_MaxIndex = j;
						}
						iter_end--;
					}
				}
			}
		}
		else
		{
			
			for (int i = 0; i < 11; i++)
			{
				if (m_ValidFlag[i] == true)
				{
					if (*(m_vecTempData[i].end() - 1) > m_CurMax)
					{
						m_RescaleFlag = 1;
						m_CurMax = *(m_vecTempData[i].end() - 1);
						m_MaxIndex = 0;
					}
				}
			}
		}
		if (m_MinIndex > 119 || m_ScanMaxMinFlag == 1)
		{
			m_CurMin = 999;
			m_RescaleFlag = 1;
			for (int i = 0; i < 11; i++)
			{
				if (m_ValidFlag[i] == true)
				{
					iter_end = m_vecTempData[i].end() - 1;
					for (int j = 0; j < 120; j++)
					{
						if (m_CurMin > *(iter_end))
						{
							m_CurMin = *(iter_end);
							m_MinIndex = j;
						}
						iter_end--;
					}
				}
			}
			m_ScanMaxMinFlag = 0;
		}
		else
		{
			
			for (int i = 0; i < 11; i++)
			{
				if (m_ValidFlag[i] == true)
				{
					if (*(m_vecTempData[i].end() - 1) < m_CurMin)
					{
						m_RescaleFlag = 1;
						m_CurMin = *(m_vecTempData[i].end() - 1);
						m_MinIndex = 0;
					}
				}
			}
		}
		if (fabs(m_CurMax - m_CurMin) < 0.1)
		{
			m_CurMax += 0.05;
			m_CurMin -= 0.05;
		}
		// ------------------------------------------------------------

		/*if (m_CurMin > 30)
		{
		m_CurMin = 30;
		}
		if (m_CurMax < 120)
		{
		m_CurMax = 120;
		}*/

		if (mThreadFlag == 1 && m_ThreadFlag1 == 1)
		{
			m_DrawGraph(pmDC);
			m_MinIndex++;
			m_MaxIndex++;
		}
		
		GetSystemTimeAsFileTime(&ft);
		FileTimeToLocalFileTime(&ft, &ftl);
		uli.HighPart = ftl.dwHighDateTime;
		uli.LowPart = ftl.dwLowDateTime;
		timep[1] = (double)uli.QuadPart / 10000.0;
	}

	if (mf2.Open(_T("FileRecord.txt"), CStdioFile::modeCreate | CStdioFile::modeWrite | CStdioFile::modeNoTruncate) == false)
	{
		MessageBox("无法打开文件");
		return 0;
	}

	timetemp = timep[0];
	strTemp.Format("%I64u:%I64u:", timet, timetemp);
	strTemp += (strFN + "\n");
	mf2.SeekToEnd();
	mf2.WriteString(strTemp);

	GetSystemTimeAsFileTime(&ft);
	FileTimeToSystemTime(&ftl, &SystemTime);

	if (mf1.m_hFile != CFile::hFileNull)
	{
		if (iFlagSave == 0)
		{
			for (int i = 0; i < m_vecTempData[0].size(); i++)
			{
				strTemp.Format("%I64u:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f:%f\t获取时间:%d:%d:%d_%d:%d:%d\n",
					m_vecTempTimeStamp.at(i),
					m_vecTempData[0].at(i),
					m_vecTempData[1].at(i),
					m_vecTempData[2].at(i),
					m_vecTempData[3].at(i),
					m_vecTempData[4].at(i),
					m_vecTempData[5].at(i),
					m_vecTempData[6].at(i),
					m_vecTempData[7].at(i),
					m_vecTempData[8].at(i),
					m_vecTempData[9].at(i),
					m_vecTempData[10].at(i),
					SystemTime.wYear,
					SystemTime.wMonth,
					SystemTime.wDay,
					SystemTime.wHour,
					SystemTime.wMinute,
					SystemTime.wSecond);
				mf1.WriteString(strTemp);
			}
		}

		mf1.Close();
	}
	m_ThreadFlag2 = 1;
	hThread = 0;
	return 1;
}

void CTemplate_ControlDlg::m_DrawGraph(CDC *pDC)
{
	vector<float>::iterator iter_begin[11], iter_end[11];
	CRect rect;
	CRect rect4Draw;

	float height = oriPnt.y - mPntPosT.y - 4;
	float step = (double)(mPntPosX.x - oriPnt.x - 4) / 119.0;
	float mScale = height / (m_CurMax - m_CurMin);

	for (int i = 119; i > -1; i--)
	{
		mPnt1[i].x = oriPnt.x + step * i + 4;
		mPnt1[i].y = oriPnt.y - 4;
	}
	if (m_CurMax < m_CurMin)
	{
		m_Tag[0] = "";
		m_Tag[1] = "";
		m_Tag[2] = "";
		m_Tag[3] = "";
	}
	else
	{
		m_Tag[0].Format("%3.1f", m_CurMin);
		m_Tag[1].Format("%3.1f", m_CurMin + (m_CurMax - m_CurMin) / 3);
		m_Tag[2].Format("%3.1f", m_CurMin + 2 * (m_CurMax - m_CurMin) / 3);
		m_Tag[3].Format("%3.1f", m_CurMax);
	}

	//COLORREF colorRef_1;

	//获取Picture Control控件的大小  
	GetDlgItem(IDC_STATIC_TEMP)->GetWindowRect(&rect);
	oriPnt;
	mPntPosX;
	mPntPosT;
	// 去除上一帧
	for (int i = 0; i < 11; i++)
	{
		pDC->SelectObject(m_Pen[11]);
		for (int j = 0; j < 120; j++)
		{
			if (j == 0)
			{
				pDC->MoveTo(mPnt2[i][j]);
			}
			pDC->LineTo(mPnt2[i][j]);
		}
	}
	if (m_RescaleFlag == 1)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->TextOutA(m_TagPos[0].x, m_TagPos[0].y, m_Tag[4]);
		pDC->TextOutA(m_TagPos[1].x, m_TagPos[1].y, m_Tag[5]);
		pDC->TextOutA(m_TagPos[2].x, m_TagPos[2].y, m_Tag[6]);
		pDC->TextOutA(m_TagPos[3].x, m_TagPos[3].y, m_Tag[7]);
	}

	if (m_RescaleFlag == 1)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->TextOutA(m_TagPos[0].x, m_TagPos[0].y, m_Tag[0]);
		pDC->TextOutA(m_TagPos[1].x, m_TagPos[1].y, m_Tag[1]);
		pDC->TextOutA(m_TagPos[2].x, m_TagPos[2].y, m_Tag[2]);
		pDC->TextOutA(m_TagPos[3].x, m_TagPos[3].y, m_Tag[3]);
		m_Tag[4] = m_Tag[0];
		m_Tag[5] = m_Tag[1];
		m_Tag[6] = m_Tag[2];
		m_Tag[7] = m_Tag[3];
		m_RescaleFlag = 0;
	}

	//绘制下一帧
	for (int i = 0; i < 11; i++)
	{
		iter_begin[i] = m_vecTempData[i].begin();
		iter_end[i] = m_vecTempData[i].end() - 1;
		pDC->SelectObject(m_Pen[i]);
		if (m_ValidFlag[i] == true)
		{
			for (int j = 0; j < 120; j++)
			{

				mPnt1[j].y = oriPnt.y - 4 - (LONG)(mScale * (*(iter_end[i] - j) - m_CurMin));
				if (j == 0)
				{
					pDC->MoveTo(mPnt1[j]);
				}
				pDC->LineTo(mPnt1[j]);

				mPnt2[i][j] = mPnt1[j];
			}
		}

		//Sleep(10000);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTemplate_ControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTemplate_ControlDlg::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类
	if (m_operFlags)
	{
		MessageBox("请断开设备连接后再关闭控制程序！");
		return;
	}
	m_hThread = NULL;
	m_ThreadFlag_3 = 0;

	CString strtmp, strTitle;
	for (int i = 0; i < 2; i++)
	{
		strtmp.Format("%.3lf", g_absRecord_Out[i]);
		strTitle.Format("AbsPos_%d", i);
		::WritePrivateProfileString("PosInfo", strTitle, strtmp, "C:\\Windows\\AbsPos_Record.ini");
	}

	CDialogEx::OnCancel();
}


void CTemplate_ControlDlg::OnBnClickedButton9()
{
	// TODO:  在此添加控件通知处理程序代码
	for (int i = 0; i < 2;i++)
	{
		m_JogDlg.m_jogInfo[i].startvel = m_controlPara.jogInfo[i].startvel;
		m_JogDlg.m_jogInfo[i].tagvel = m_controlPara.jogInfo[i].tagvel;
		m_JogDlg.m_jogInfo[i].accvel = m_controlPara.jogInfo[i].accvel;
	}

	if (IDOK == m_JogDlg.DoModal())
	{
		for (int i = 0; i < 2; i++)
		{
			m_controlPara.jogInfo[i].startvel = m_JogDlg.m_jogInfo[i].startvel;
			m_controlPara.jogInfo[i].tagvel = m_JogDlg.m_jogInfo[i].tagvel;
			m_controlPara.jogInfo[i].accvel = m_JogDlg.m_jogInfo[i].accvel;
		}
	}
}

int CTemplate_ControlDlg::String2Hex(CString str, CByteArray &senddata)
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

char CTemplate_ControlDlg::ConvertHexChar(char ch)
{
	if ((ch >= '0') && (ch <= '9'))
		return ch - 0x30;
	else if ((ch >= 'A') && (ch <= 'F'))
		return ch - 'A' + 10;
	else if ((ch >= 'a') && (ch <= 'f'))
		return ch - 'a' + 10;
	else return (-1);
}

BOOL CTemplate_ControlDlg::ReadMr13Data(SOCKET socket, int Idevice, int Ichannel, int Iaddress,int& value, int Idatalen)
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
	send(socket, cSendmsg.GetBuffer(), len, 0);
	recv(socket, buf, 100, 0);

	int n = 0;
	int temp = 0;
	if (buf[5] == '0'&&buf[6] == '0')
	{
		for (int i = 8; i < 12;i++)
		{
			if (buf[i] >= 'A'&&buf[i] <= 'F')//十六进制还要判断他是不是在A-F或者a-f之间a=10。。
				n = buf[i] - 'A' + 10;
			else if (buf[i] >= 'a'&&buf[i] <= 'f')
				n = buf[i] - 'a' + 10;
			else n = buf[i] - '0';
			temp = temp * 16 + n;
		}
		value = temp;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
BOOL CTemplate_ControlDlg::WriteMr13Data(SOCKET socket, int Idevice, int Ichannel, int Iaddress, int Idatalen, int Ivalue)
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
	for (int i = 0; i < strtmp.GetLength();i++)
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
	send(socket, cSendmsg.GetBuffer(), len, 0);
	recv(socket, buf, 20, 0);
	
	if (buf[5]=='0'&&buf[6]=='0')
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

void CTemplate_ControlDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_handle==NULL)
	{
		MessageBox("温控仪未连接！");
		return;
	}
	for (int i = 0; i < 11;i++)
	{
		m_DeviceDlg.m_Setsv[i] = m_Setsv[i];
	}

	if (IDOK == m_DeviceDlg.DoModal())
	{
		for (int i = 0; i < 11; i++)
		{
			m_Setsv[i] = m_DeviceDlg.m_Setsv[i];
		}
	}

	CString strtmp;
	int Idevnum;

	EnterCriticalSection(&m_csReadWriteTable);
	for (int i = 0; i < 6; i++)//修改
	{
		int svValue = m_Setsv[i] * 10;
		Idevnum = i / 3 + 1;
		int ch = i % 3 + 1;
		BOOL res;
		res = WriteMr13Data(m_socket, Idevnum, ch, 0x0300, 0, svValue);
		if (!res)
		{
			Sleep(5);
			res = WriteMr13Data(m_socket, Idevnum, ch, 0x0300, 0, svValue);
		}
		if (res)
		{
			strtmp.Format("%0.1f℃", m_Setsv[i]);
			m_editCrl[i]->SetWindowTextA(strtmp);
		}
		else
		{
			strtmp.Format("测温点%d设置SV值失败!", i + 1);
			MessageBox(strtmp);
		}	
	}
	LeaveCriticalSection(&m_csReadWriteTable);

}


void CTemplate_ControlDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	m_ErrDlg.m_handle = m_handle;
	m_ErrDlg.DoModal();
}

BOOL CTemplate_ControlDlg::InitSocket()
{
	if (m_socket != 0)
	{
		closesocket(m_socket);
		m_socket = NULL;
	}
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == m_socket)
	{
		return FALSE;
	}
	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(4197);
	addrSrv.sin_addr.S_un.S_addr = inet_addr("192.168.1.200");

	timeval tm;
	fd_set set;
	unsigned long ul = 1;
	int len = 0;
	bool ret = false;
	char error = 0;
	ioctlsocket(m_socket, FIONBIO, &ul); //设置为非阻塞模式 

	int result = connect(m_socket, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//如何让堵塞函数超时自动退出
	if (result == -1)
	{
		tm.tv_sec = 1.5;//超时时间3秒
		tm.tv_usec = 0;
		FD_ZERO(&set);
		FD_SET(m_socket, &set);

		if (select(m_socket+1, NULL, &set, NULL, &tm) > 0)
		{
			getsockopt(m_socket, SOL_SOCKET, SO_ERROR, &error, &len);
			if (error == 0)
			{
				ret = true;
			}
			else
			{
				ret = false;
			}
		}
		else
		{
			ret = false;
		}
	}
	else
	{
		ret = true;
	}
	ul = 0;
	ioctlsocket(m_socket, FIONBIO, &ul); //设置为阻塞模式  
	if (!ret)
	{
		closesocket(m_socket);
		MessageBox("温控仪TCP连接超时");
		return FALSE;
	}
	return TRUE;
}

void CTemplate_ControlDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	//温控仪socket连接
	if (!m_operFlags)
	{
		int netid = ((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCurSel();
		m_handle = PKG_IMC_Open(netid, 0);
		if (m_handle != NULL)
		{
			int i = PKG_IMC_InitCfg(m_handle);
			if (i == 0)
			{
				const char* err = PKG_IMC_GetFunErrStr();
				MessageBox(err);
			}
			InitControlCard();
			SetTimer(1, 100, NULL);
			TRACE("运动控制卡连接成功！");
		}
		else
		{
			MessageBox("请检查网卡和控制卡ID是否选择正确！", "警告");
			return;
		}

		//////////////////////////////////////////////////////////////
		
		if (FALSE == InitSocket())
		{
			return;
		}
		else
		{
			EnterCriticalSection(&m_csReadWriteTable);
			BOOL res;

			for (int i = 1; i < 3; i++)//修改
			{
				res = WriteMr13Data(m_socket, i, 1, 0x018C, 0, 1);
				if (!res)
				{
					Sleep(5);
					WriteMr13Data(m_socket, i, 1, 0x018C, 0, 1);
				}
			}
			LeaveCriticalSection(&m_csReadWriteTable);
		}

		//RECVPARAM* pRecvParam = new RECVPARAM;
		//pRecvParam->sock = m_socket;
		//pRecvParam->hwnd = m_hWnd;
		//创建接受线程
		if (m_hThread==NULL)
		{
			m_ThreadFlag_3 = 1;
			m_hThread = CreateThread(NULL, 0, RecvProc, this, 0, NULL);
		}
		GetDlgItem(IDC_BUTTON2)->SetWindowTextA("关闭");
		m_operFlags = TRUE;	
		m_homeFlag = false;
		MessageBox("温控设备打开！");

	}
	else
	{
		EnterCriticalSection(&m_csReadWriteTable);
		m_ThreadFlag_3 = 0;
		m_hThread = NULL;
		LeaveCriticalSection(&m_csReadWriteTable);

		closesocket(m_socket);
		m_socket = NULL;
		GetDlgItem(IDC_BUTTON2)->SetWindowTextA("连接");
		m_operFlags = FALSE;

		PKG_IMC_Close(m_handle);
		m_handle = NULL;
		//MessageBox("温控设备关闭！");
	}
}

DWORD WINAPI CTemplate_ControlDlg::RecvProc(LPVOID lpParameter)
{
	//获得主线程传递的套接字和窗口句柄
	//SOCKET sock = ((RECVPARAM*)lpParameter)->sock;
	//HWND hwnd = ((RECVPARAM*)lpParameter)->hwnd;
	//delete lpParameter;

	CTemplate_ControlDlg* pThread = (CTemplate_ControlDlg*)lpParameter;
	SOCKET sock = pThread->m_socket;

	int Idevnum, ch, value;

	while (1)
	{
		if (pThread->m_ThreadFlag_3 == 0)
		{
			return 0;
		}
		Idevnum = ch = 0;

		EnterCriticalSection(&m_csReadWriteTable);	
		for (int i = 0; i < 6; i++)//修改
		{
			Idevnum = i / 3 + 1;
			ch = i % 3 + 1;
			value = 0;
			BOOL res;
			res = ReadMr13Data(sock, Idevnum, ch, 0x0100, value, 0);
			if (!res)
			{
				Sleep(10);
				ReadMr13Data(sock, Idevnum, ch, 0x0100, value, 0);
			}
			pThread->m_Getpv[i] = value / 10.0;
		}
		LeaveCriticalSection(&m_csReadWriteTable);
		Sleep(100);
	}
	return 0;
}

LRESULT CTemplate_ControlDlg::OnRecvData(WPARAM wParam, LPARAM lParam)
{
	const char* source = (char*)lParam;
	CStringArray m_destTemp;

	//SplitString(source, m_destTemp, " ");
	int len = m_destTemp.GetSize();
	for (int i = 0; i < len;i++)
	{
		CString str = m_destTemp[i];
		m_editCrlPV[i]->SetWindowText(str);
		m_Getpv[i] = atof(str);

		if (m_Getpv[i] <= m_Setsv[i])
		{
			m_picCtlArray[i]->GetDC()->StretchBlt(m_rectPho.left, m_rectPho.top, m_rectPho.Width(), m_rectPho.Height(), &m_dcCompatibleRed, 0, 0, m_bmp1.bmWidth, m_bmp1.bmHeight, SRCCOPY);
		}
		else if (m_Getpv[i]>m_Setsv[i])
		{
			m_picCtlArray[i]->GetDC()->StretchBlt(m_rectPho.left, m_rectPho.top, m_rectPho.Width(), m_rectPho.Height(), &m_dcCompatibleGreen, 0, 0, m_bmp1.bmWidth, m_bmp1.bmHeight, SRCCOPY);
		}
		else;
	}

	return TRUE;
}

/*
void CTemplate_ControlDlg::SplitString(const CString& s, vector<string> v, const char* c)
{
	unsigned int pos1, pos2;
	pos2 = s.Find(c);
	pos1 = 0;
	while (-1 != pos2)
	{
		v.Add(s.Mid(pos1, pos2 - pos1));
		pos1 = pos2 + strlen(c);
		pos2 = s.Find(c, pos1);
	}
	if (pos1 != s.GetLength())
		v.Add(s.Mid(pos1));
}*/

void CTemplate_ControlDlg::OnBnClickedButton13()
{
	// TODO:  在此添加控件通知处理程序代码
	for (int i = 0; i < 2; i++)
	{
		m_HomeDlg.m_homeInfo[i].dir = m_controlPara.homeInfo[i].dir;
		m_HomeDlg.m_homeInfo[i].tagvel = m_controlPara.homeInfo[i].tagvel;
		m_HomeDlg.m_homeInfo[i].accvel = m_controlPara.homeInfo[i].accvel;
		m_HomeDlg.m_homeInfo[i].compatevel = m_controlPara.homeInfo[i].compatevel;
	}

	if (IDOK == m_HomeDlg.DoModal())
	{
		for (int i = 0; i < 2; i++)
		{
			m_controlPara.homeInfo[i].dir = m_HomeDlg.m_homeInfo[i].dir;
			m_controlPara.homeInfo[i].tagvel = m_HomeDlg.m_homeInfo[i].tagvel;
			m_controlPara.homeInfo[i].accvel = m_HomeDlg.m_homeInfo[i].accvel;
			m_controlPara.homeInfo[i].compatevel = m_HomeDlg.m_homeInfo[i].compatevel;
		}
	}
}

void CTemplate_ControlDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 1:
		// 如果收到ID为1的定时器的消息则调用func1函数  
		if (m_handle == NULL)
			break;
		func1();
		break;
	case 2:
		if (m_handle == NULL)
			break;
		func2();
		break;
	case 3:
		//if (m_handle == NULL)
			//break;
		func3();
		break;
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CTemplate_ControlDlg::func1()
{
	CString str;
	long deltaPos;
	double curVel;

	if (PKG_IMC_GetCurpos(m_handle, m_curpos, 6))//获得当前位置
	{
		for (int i = 0; i < 2;i++)
		{
			deltaPos = m_curpos[i] - m_curpos_t[i];
			if (deltaPos != 0)
			{
				curVel = abs(deltaPos * 10 / m_devicePara[i].Scale);
				str.Format(_T("%3.2f"), curVel);
				m_editCrl[11 + i * 4]->SetWindowText(str);  // 显示运动速度

				str.Format("%.3lf", (double)(m_curpos_t[i] / m_devicePara[i].Scale));
				m_editCrl[12 + i * 4]->SetWindowText(str);	//显示目标位置

				g_absRecord_Out[i] = m_curpos_t[i] / m_devicePara[i].Scale + g_absRecord_In[i];
				str.Format("%.3lf", g_absRecord_Out[i]);
				m_editCrl[14 + i * 4]->SetWindowText(str);	//显示绝对位置
				m_countNum[i] = 0;
			}
			else if (deltaPos == 0 && m_countNum[i] == 0)
			{
				curVel = abs(deltaPos * 10 / m_devicePara[i].Scale);
				str.Format(_T("%3.2f"), curVel);
				m_editCrl[11 + i * 4]->SetWindowText(str);  // 显示运动速度

				str.Format("%.3lf", (double)(m_curpos_t[i] / m_devicePara[i].Scale));
				m_editCrl[12 + i * 4]->SetWindowText(str);	//显示目标位置

				g_absRecord_Out[i] = m_curpos_t[i] / m_devicePara[i].Scale + g_absRecord_In[i];
				str.Format("%.3lf", g_absRecord_Out[i]);
				m_editCrl[14 + i * 4]->SetWindowText(str);	//显示绝对位置
				m_countNum[i]++;
			}
			else;
			m_curpos_t[i] = m_curpos[i];
		}
	}
}


void CTemplate_ControlDlg::func2()
{
	//负限位作零点，反向补偿一定距离
	int tmp1;
	short data;

	if (m_homeFlag && m_jogFlag == false)
	{
		for (int i = 0; i < 2; i++)
		{
			PKG_IMC_GetParam16(m_handle, aiolatLoc, &data, i);
			tmp1 = (data & (1 << 1)) ? 1 : 0;
			if (tmp1)
			{
				int st = PKG_IMC_HomeStop(m_handle, i);
				if (st)
				{
					double high = m_controlPara.homeInfo[i].tagvel * m_devicePara[i].Scale * 0.001;
					PKG_IMC_MoveDist(m_handle, m_controlPara.homeInfo[i].compatevel*m_devicePara[i].Scale, high, high, 1, i);
					PKG_IMC_ExitWait();
				}
			}
		}
	}

	//监测急停输入信号，如果急停按钮按下控制卡执行暂停，按钮回复暂停结束
	PKG_IMC_GetGin(m_handle, m_gin);
	if (m_gin[0]==0 && m_gin[0]!=m_gin_t[0])
	{
		PKG_IMC_Pause(m_handle, 1);
		SuspendThread(hThreadMultiStep);
	}
	else if (m_gin[0] == 1 && m_gin[0] != m_gin_t[0])
	{
		PKG_IMC_Pause(m_handle, 0);
		ResumeThread(hThreadMultiStep);
	}
	else;
	m_gin_t[0] = m_gin[0];
}


void CTemplate_ControlDlg::func3()
{
	CString str;
	for (int i = 0; i < 11;i++)
	{
		if (m_Getpv_pro[i] != m_Getpv[i])
		{
			str.Format("%0.1f", m_Getpv[i]);
			m_editCrlPV[i]->SetWindowText(str);
		}
		m_Getpv_pro[i] = m_Getpv[i];
		
		if (m_Getpv[i] <= m_Setsv[i])
		{
			if (m_ShowSignal[i] == 1 || m_ShowSignal[i] == -1)
			{
				//红色报警信号
				m_picCtlArray[i]->GetDC()->StretchBlt(m_rectPho.left, m_rectPho.top, m_rectPho.Width(), m_rectPho.Height(), &m_dcCompatibleRed, 0, 0, m_bmp1.bmWidth, m_bmp1.bmHeight, SRCCOPY);
				m_ShowSignal[i] = 0;
			}
		}
		else
		{
			if (m_ShowSignal[i] == 0 || m_ShowSignal[i] == -1)
			{
				//绿色报警信号
				m_picCtlArray[i]->GetDC()->StretchBlt(m_rectPho.left, m_rectPho.top, m_rectPho.Width(), m_rectPho.Height(), &m_dcCompatibleGreen, 0, 0, m_bmp1.bmWidth, m_bmp1.bmHeight, SRCCOPY);
				m_ShowSignal[i] = 1;
			}	
		}
	}
}


void CTemplate_ControlDlg::InitControlCard()
{
	//读取控制卡配置信息
	int st;
	const char *err;
	memset(m_cfg, 0, sizeof(CFG_INFO) * 6);
	for (int i = 0; i < 6; i++)
	{
		st = PKG_IMC_GetConfig(m_handle, &m_cfg[i].steptime, &m_cfg[i].pulpolar, &m_cfg[i].dirpolar,
			&m_cfg[i].encpena, &m_cfg[i].encpmode, &m_cfg[i].encpdir, &m_cfg[i].encpfactor,
			&m_cfg[i].vellim, &m_cfg[i].acclim, &m_cfg[i].ena, &m_cfg[i].plimitena, &m_cfg[i].plimitpolar, &m_cfg[i].nlimitena, &m_cfg[i].nlimitpolar,
			&m_cfg[i].almena, &m_cfg[i].almpolar, &m_cfg[i].INPena, &m_cfg[i].INPpolar, i);
		if (st == 0)
		{
			err = PKG_IMC_GetFunErrStr();
			MessageBox(err);
			break;
		}
	}
	//配置控制卡设备参数
	st = PKG_IMC_ClearIMC(m_handle);
	for (int i = 0; i < 6; i++)
	{
		st = PKG_IMC_ClearAxis(m_handle, i);
		if (st == 0)
			break;
		st = PKG_IMC_SetStopfilt(m_handle, 1, i);
		if (st == 0)
			break;
		st = PKG_IMC_SetExitfilt(m_handle, 0, i);
		if (st == 0)
			break;
		st = PKG_IMC_SetPulWidth(m_handle, m_cfg[i].steptime, i);
		if (st == 0)
			break;
		st = PKG_IMC_SetPulPolar(m_handle, m_cfg[i].pulpolar, m_cfg[i].dirpolar, i);
		if (st == 0)
			break;
		st = PKG_IMC_SetEncpEna(m_handle, m_cfg[i].encpena, i);
		if (st == 0)
			break;
		st = PKG_IMC_SetEncpMode(m_handle, m_cfg[i].encpmode, m_cfg[i].encpdir, i);
		if (st == 0)
			break;
		st = PKG_IMC_SetEncpRate(m_handle, m_cfg[i].encpfactor, i);
		if (st == 0)
			break;
		st = PKG_IMC_SetVelAccLim(m_handle, m_cfg[i].vellim, m_cfg[i].acclim, i);
		if (st == 0)
			break;
		st = PKG_IMC_Setlimit(m_handle, m_cfg[i].plimitena, m_cfg[i].plimitpolar, m_cfg[i].nlimitena, m_cfg[i].nlimitpolar, i);
		if (st == 0)
			break;
		st = PKG_IMC_SetEna(m_handle, m_cfg[i].ena, i);//使能驱动器放在最后
		if (st == 0)
			break;
	}
}


void CTemplate_ControlDlg::InitElecPlatePara()
{
	CString strtmp, strTitle;
	for (int i = 0; i < 2;i++)
	{
		//读取点动参数
		strTitle.Format("StartVel_%d", i);
		::GetPrivateProfileString("JogInfo", strTitle, _T("0"), strtmp.GetBuffer(MAX_PATH), MAX_PATH, "C:\\Windows\\Template_Control.ini");
		strTitle.ReleaseBuffer();
		m_controlPara.jogInfo[i].startvel = atof(strtmp);

		strTitle.Format("TagVel_%d", i);
		::GetPrivateProfileString("JogInfo", strTitle, _T("0"), strtmp.GetBuffer(MAX_PATH), MAX_PATH, "C:\\Windows\\Template_Control.ini");
		strTitle.ReleaseBuffer();
		m_controlPara.jogInfo[i].tagvel = atof(strtmp);

		strTitle.Format("AccVel_%d", i);
		::GetPrivateProfileString("JogInfo", strTitle, _T("0"), strtmp.GetBuffer(MAX_PATH), MAX_PATH, "C:\\Windows\\Template_Control.ini");
		strTitle.ReleaseBuffer();
		m_controlPara.jogInfo[i].accvel = atof(strtmp);

		//读取回零参数
		strTitle.Format("Direction_%d", i);
		::GetPrivateProfileString("HomeInfo", strTitle, _T("0"), strtmp.GetBuffer(MAX_PATH), MAX_PATH, "C:\\Windows\\Template_Control.ini");
		strTitle.ReleaseBuffer();
		m_controlPara.homeInfo[i].dir = atoi(strtmp);

		strTitle.Format("TagVel_%d", i);
		::GetPrivateProfileString("HomeInfo", strTitle, _T("0"), strtmp.GetBuffer(MAX_PATH), MAX_PATH, "C:\\Windows\\Template_Control.ini");
		strTitle.ReleaseBuffer();
		m_controlPara.homeInfo[i].tagvel = atof(strtmp);

		strTitle.Format("Accvel_%d", i);
		::GetPrivateProfileString("HomeInfo", strTitle, _T("0"), strtmp.GetBuffer(MAX_PATH), MAX_PATH, "C:\\Windows\\Template_Control.ini");
		strTitle.ReleaseBuffer();
		m_controlPara.homeInfo[i].accvel = atof(strtmp);

		strTitle.Format("CmpateVel_%d", i);
		::GetPrivateProfileString("HomeInfo", strTitle, _T("0"), strtmp.GetBuffer(MAX_PATH), MAX_PATH, "C:\\Windows\\Template_Control.ini");
		strTitle.ReleaseBuffer();
		m_controlPara.homeInfo[i].compatevel = atof(strtmp);
	}

}


void CTemplate_ControlDlg::InitElecPlateDevicePara()
{
	m_devicePara[0].PULnum = XAXISPULNUM;
	m_devicePara[0].ScrewValue = XAXISSCREWVALUE;
	m_devicePara[0].Scale = m_devicePara[0].PULnum / m_devicePara[0].ScrewValue;
	m_devicePara[0].ReduceValue = 0;

	m_devicePara[1].PULnum = YAXISPULNUM;
	m_devicePara[1].ScrewValue = YAXISSCREWVALUE;
	m_devicePara[1].Scale = m_devicePara[1].PULnum / m_devicePara[1].ScrewValue;
	m_devicePara[1].ReduceValue = 0;
}

void CTemplate_ControlDlg::OnLbnDblclkList1()
{
	// TODO:  在此添加控件通知处理程序代码
	POINT   pt;
	GetCursorPos(&pt);
	int nCount = m_ListCommand.GetCount();
	m_ListCommand.ScreenToClient(&pt);

	for (int i = 0; i < nCount; i++)
	{
		CRect rc;

		m_ListCommand.GetItemRect(i, &rc);
		if (rc.PtInRect(pt))
		{
			CInputCommandDlg inputDlg(this);
			inputDlg.DoModal();
		}
	}
}


void CTemplate_ControlDlg::OnInsertCommand()
{
	// TODO:  在此添加命令处理程序代码
	CInputCommandDlg inputDlg(this);
	inputDlg.DoModal();
}


void CTemplate_ControlDlg::OnDeleteCommand()
{
	// TODO:  在此添加命令处理程序代码
	if (m_ListCommand.GetCount() == 1)
	{
		return;
	}
	/*if (m_ListCommand.GetCurSel() == m_ListCommand.GetCount() - 1)
	{
		return;
	}*/

	// 记录所选的项
	int nCount = m_ListCommand.GetSelCount();
	int* buffer = new int[nCount];
	memset(buffer, -1, sizeof(int) * nCount);
	m_ListCommand.GetSelItems(nCount, buffer);

	int list_index;
	list_index = m_ListCommand.GetCurSel();
	if (list_index == CB_ERR)
	{
		MessageBox("请选中一个记录");
	}
	else
	{
		//删除listbox 中的记录
		//m_ListCommand.DeleteString(list_index);
		//mCommandPack.erase(mCommandPack.begin() + list_index);
		for (int i = nCount - 1; i >= 0;i--)
		{
			int tmp = m_ListCommand.GetCount() - 1;
			if (buffer[i] < tmp)
			{
				m_ListCommand.DeleteString(buffer[i]);
				mCommandPack.erase(mCommandPack.begin() + buffer[i]);
			}		
		}
	}
	FlushList();
}


void CTemplate_ControlDlg::FlushList()
{
	int count = m_ListCommand.GetCount();
	int pos_1, pos_2, length;
	CString strTmp, strTmp_1, strTmp_2;

	for (int i = 0; i < count - 1; i++)
	{
		m_ListCommand.GetText(i, strTmp_1);
		if ((pos_1 = strTmp_1.Find('<')) >= 0)
		{
			pos_2 = strTmp_1.Find('>');
			length = pos_2 - pos_1 + 2;
			strTmp_1 = strTmp_1.Mid(pos_2 + 2, strTmp_1.GetLength() - length);
		}

		strTmp_2.Format(_T("<%d> "), i + 1);
		strTmp = strTmp_2 + strTmp_1;
		m_ListCommand.InsertString(i, strTmp);
		if (i < m_ListCommand.GetCount() - 2)
			m_ListCommand.DeleteString(i + 1);
	}
}


afx_msg LRESULT CTemplate_ControlDlg::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
	CInputCommandDlg::CommandPackInfo* pCommand = (CInputCommandDlg::CommandPackInfo*)lParam;

	int index;
	CString strTmp;
	int size = 0;
	CInputCommandDlg::CCommandPack tmpCPack;
	index = m_ListCommand.GetCount() - 1;//获得指令选中的索引位置（从0开始）
	int adnum = 0;
	for (int i = 0; i < pCommand->numOfCycle; i++)
	{
		size = (*pCommand).CommandPack.size();
		for (int j = 0; j < size;j++)
		{
			tmpCPack = (*pCommand).CommandPack[j];
			mCommandPack.insert(mCommandPack.begin() + index + adnum, tmpCPack);
			strTmp.Format("X:(%0.3fmm, %0.2fmm/s, %0.2fmm/s2),  Y:(%0.3fmm, %0.2fmm/s, %0.2fmm/s2)", tmpCPack.axisPara[0], tmpCPack.axisPara[1],
				tmpCPack.axisPara[2], tmpCPack.axisPara[3], tmpCPack.axisPara[4], tmpCPack.axisPara[5]);
			m_ListCommand.InsertString(index + adnum, strTmp);
			adnum++;
		}
		/*
		tmpCPack = (*pCommand).CommandPack;
		mCommandPack.insert(mCommandPack.begin() + index + i, tmpCPack);

		strTmp.Format("X:(%0.3fmm, %0.2fmm/s, %0.2fmm/s2),  Y:(%0.3fmm, %0.2fmm/s, %0.2fmm/s2)", tmpCPack.axisPara[0], tmpCPack.axisPara[1],
			tmpCPack.axisPara[2], tmpCPack.axisPara[3], tmpCPack.axisPara[4], tmpCPack.axisPara[5]);
		m_ListCommand.InsertString(index + i, strTmp);*/

	}
	FlushList();
	return 0;
}

void CTemplate_ControlDlg::OnBnClickedButton14()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_handle == NULL)
	{
		MessageBox("设备没有打开！");
		return;
	}

	mThreadMultiStepFlag = 1;
	hThreadMultiStep = (HANDLE)_beginthreadex(NULL,         // security
		0,            // stack size
		CTemplate_ControlDlg::Thread_0,
		this,           // arg list
		0,  // 立即执行不要挂起
		&uiThread1ID);
}


unsigned _stdcall CTemplate_ControlDlg::Thread_0(void* pThis)
{
	CTemplate_ControlDlg* pThreadThis = (CTemplate_ControlDlg*)pThis;

	pThreadThis->th_CommandExecutor();
	return 1;
}


int CTemplate_ControlDlg::th_CommandExecutor()
{
	int numComm = mCommandPack.size();
	if (numComm == 0)
		return 1;
	int mNumOfCyc;//运动指令循环次数
	int mWaitTime;
	long mDist;
	double mVel;
	double mAcc[2] = { 0, 0 };
	int st;
	const char * err;
	unsigned short mAxisMStatus[6];
	unsigned short mStatus;
	CLogFile mf;

	//清空急停
	st = PKG_IMC_Emstop(m_handle, 0);
	int count = m_ListCommand.GetCount();
	m_ListCommand.SetSel(count - 1, 0);

	for (int i = 0; i < numComm;i++)
	{
		m_ListCommand.SetSel(i, 1);
		mWaitTime = mCommandPack[i].waitTime;
		mAcc[0] = mCommandPack[i].axisPara[2] * m_devicePara[0].Scale * 0.001* 0.001;
		mAcc[1] = mCommandPack[i].axisPara[5] * m_devicePara[1].Scale * 0.001* 0.001;

		for (int j = 0; j < 2; j++)
		{
			mf.dist[j] = mCommandPack[i].axisPara[j * 3];
		}

		for (int j = 0; j < 2;j++)
		{
			PKG_IMC_SetAccel(m_handle, mAcc[j], mAcc[j], j);
		}

		for (int j = 0; j < 2;j++)
		{
			if (mCommandPack[i].axisPara[j * 3] != 0)
			{
				mDist = mCommandPack[i].axisPara[j * 3] * m_devicePara[j].Scale;
				mVel = mCommandPack[i].axisPara[j * 3 + 1] * m_devicePara[j].Scale * 0.001;
				PKG_IMC_SetEna(m_handle, 1, j);
				st = PKG_IMC_MoveDist(m_handle, mDist, mVel, mVel, 0, j);
				if (st == 0)
				{
					err = PKG_IMC_GetFunErrStr();
				}
				mf.WriteLog(1);
			}
		}

		//循环等待指令完成
		do
		{
			PKG_IMC_GetMoving(m_handle, mAxisMStatus, 6);
			mStatus = 0;
			for (int j = 0; j < 2; j++)
			{
				mStatus += mAxisMStatus[j];
			}
			Sleep(100);

			if (mStatus == 0)
			{
				PKG_IMC_GetMoving(m_handle, mAxisMStatus, 6);
				mStatus = 0;
				for (int j = 0; j < 2; j++)
				{
					mStatus += mAxisMStatus[j];
				}
				Sleep(20);
			}
			if (mStatus == 0)
			{
				PKG_IMC_GetMoving(m_handle, mAxisMStatus, 6);
				mStatus = 0;
				for (int j = 0; j < 2; j++)
				{
					mStatus += mAxisMStatus[j];
				}
			}
		} while (mStatus != 0);

		if (mWaitTime != 0)
			Sleep(mWaitTime);
		m_ListCommand.SetSel(i, 0);
		//线程结束指令判断
		if (mThreadMultiStepFlag == 0)
		{
			return 0;
		}
	}
	return 0;
}


void CTemplate_ControlDlg::OnBnClickedButton16()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_handle == NULL)
	{
		MessageBox("设备没有打开！");
		return;
	}

	if (PKG_IMC_Emstop(m_handle, 1))
	{
		EmStopFlag = 1;
		PKG_IMC_ExitWait();
	}
	m_homeFlag = false;
	mThreadMultiStepFlag = 0;
	mThreadFlag_1 = 0;
	mThreadFlag_2 = 0;

}


void CTemplate_ControlDlg::OnBnClickedButton15()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_handle == NULL)
	{
		MessageBox("设备没有打开！");
		return;
	}
	m_homeFlag = false;
	mThreadMultiStepFlag = 0;
}


void CTemplate_ControlDlg::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_handle == NULL)
	{
		MessageBox("设备没有打开！");
		return;
	}
	CString strValue;
	GetDlgItemText(IDC_EDIT31, strValue);
	int dist = atof(strValue)*m_devicePara[0].Scale;
	DistMove(0, 1, dist);
}


//点动控制接口
void CTemplate_ControlDlg::DistMove(int axis, int dir, long dist)
{
	int st;
	double acc, startvel, tgvel;
	const char * err;

	m_jogFlag = true;

	acc = m_controlPara.jogInfo[axis].accvel * m_devicePara[axis].Scale * 0.001;
	startvel = m_controlPara.jogInfo[axis].startvel * m_devicePara[axis].Scale * 0.001;
	tgvel = m_controlPara.jogInfo[axis].tagvel * m_devicePara[axis].Scale * 0.001;

	//清空急停
	st = PKG_IMC_Emstop(m_handle, 0);
	//使能驱动器
	st = PKG_IMC_SetEna(m_handle, 1, axis);

	if (st)
	{
		st = PKG_IMC_SetAccel(m_handle, acc, acc, axis);
	}
	if (st)
	{
		st = PKG_IMC_MoveDist(m_handle, dist * dir, startvel, tgvel, 0, axis);
		if (!st)
		{
			err = PKG_IMC_GetFunErrStr();
			MessageBox(err);
		}
	}
	else
	{
		err = PKG_IMC_GetFunErrStr();
		MessageBox(err);
	}

	//17.2 ADD MoveRecord.txt ---------------------------------
	CLogFile mf;
	for (int i = 0; i < 2; i++)
	{
		mf.dist[i] = 0;
	}
	mf.dist[axis] = (float)dist * dir / m_devicePara[axis].Scale;
	mf.WriteLog(1);
}

void CTemplate_ControlDlg::OnBnClickedButton6()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_handle == NULL)
	{
		MessageBox("设备没有打开！");
		return;
	}
	CString strValue;
	GetDlgItemText(IDC_EDIT32, strValue);
	int dist = atof(strValue)*m_devicePara[0].Scale;
	DistMove(0, -1, dist);
}


void CTemplate_ControlDlg::OnBnClickedButton7()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_handle == NULL)
	{
		MessageBox("设备没有打开！");
		return;
	}
	CString strValue;
	GetDlgItemText(IDC_EDIT33, strValue);
	int dist = atof(strValue)*m_devicePara[1].Scale;
	DistMove(1, 1, dist);
}


void CTemplate_ControlDlg::OnBnClickedButton8()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_handle == NULL)
	{
		MessageBox("设备没有打开！");
		return;
	}
	CString strValue;
	GetDlgItemText(IDC_EDIT34, strValue);
	int dist = atof(strValue)*m_devicePara[1].Scale;
	DistMove(1, -1, dist);
}


void CTemplate_ControlDlg::OnBnClickedButton10()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_handle == NULL)
	{
		MessageBox(_T("设备没有打开！"));
		return;
	}
	mThreadFlag_1 = 1;
	hThread_1 = (HANDLE)_beginthreadex(NULL,         // security
		0,            // stack size
		CTemplate_ControlDlg::Thread_1,
		this,           // arg list
		0,  // 立即执行不要挂起
		&uiThread1ID_1);
	CLogFile mf;
	mf.axisMoving[0] = 1;
	mf.WriteLog(9);
}


unsigned _stdcall CTemplate_ControlDlg::Thread_1(void* pThis)
{
	CTemplate_ControlDlg* pThreadThis = (CTemplate_ControlDlg*)pThis;

	pThreadThis->HomeControl(0);

	return 1;
}


//回零控制接口
void CTemplate_ControlDlg::HomeControl(int axis)
{
	int st, flag;
	const char* err;
	CString str;
	EmStopFlag = 0;
	m_jogFlag = false;
	m_homeFlag = true;

	//清空急停
	st = PKG_IMC_Emstop(m_handle, 0);
	//使能驱动器
	st = PKG_IMC_SetEna(m_handle, 1, axis);


	//设置搜零轴的加减速度
	double acc = m_controlPara.homeInfo[axis].accvel * m_devicePara[axis].Scale * 0.001;
	st = PKG_IMC_SetAccel(m_handle, acc, acc, axis);
	if (st == 0)
	{
		err = PKG_IMC_GetFunErrStr();
		MessageBox(err);
		return;
	}
	//设置搜零轴的搜零速度
	double high = m_controlPara.homeInfo[axis].tagvel * m_devicePara[axis].Scale * 0.001;

	st = PKG_IMC_SetHomeVel(m_handle, high, high, axis);
	if (st == 0)
	{
		err = PKG_IMC_GetFunErrStr();
		MessageBox(err);
		return;
	}
	int mode = 0;
	int dir = m_controlPara.homeInfo[axis].dir;
	int riseEdge = 0;
	int pos = 0;
	int stpos = m_controlPara.homeInfo[axis].compatevel * m_devicePara[axis].Scale;
	double vel = 0;

	switch (mode)
	{
	case 0:
	{
		st = PKG_IMC_HomeSwitch1(m_handle, dir, riseEdge, pos, stpos, vel, 1, axis);
		break;
	}
	case 1:
	{
		st = PKG_IMC_HomeSwitchIndex1(m_handle, dir, riseEdge, pos, stpos, vel, 1, axis);
		break;
	}
	case 2:
	{
		st = PKG_IMC_HomeIndex(m_handle, dir, pos, stpos, vel, 1, axis);
		break;
	}
	}

	if (st == 0)
	{
		err = PKG_IMC_GetFunErrStr();
		MessageBox(err);
		return;
	}
	else if (st!=0 && EmStopFlag==0)
	{
		PKG_IMC_SetPos(m_handle, 0, axis);
		g_absRecord_In[axis] = 0;
	}
	
}

void CTemplate_ControlDlg::OnBnClickedButton11()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_handle == NULL)
	{
		MessageBox(_T("设备没有打开！"));
		return;
	}
	mThreadFlag_2 = 1;
	hThread_2 = (HANDLE)_beginthreadex(NULL,         // security
		0,            // stack size
		CTemplate_ControlDlg::Thread_2,
		this,           // arg list
		0,  // 立即执行不要挂起
		&uiThread1ID_2);
	CLogFile mf;
	mf.axisMoving[1] = 1;
	mf.WriteLog(9);
}


unsigned _stdcall CTemplate_ControlDlg::Thread_2(void* pThis)
{
	CTemplate_ControlDlg* pThreadThis = (CTemplate_ControlDlg*)pThis;

	pThreadThis->HomeControl(1);
	return 1;
}


void CTemplate_ControlDlg::OnBnClickedButton12()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_handle == NULL)
	{
		MessageBox(_T("设备没有打开！"));
		return;
	}

	mThreadFlag_1 = 1;
	hThread_1 = (HANDLE)_beginthreadex(NULL,         // security
		0,            // stack size
		CTemplate_ControlDlg::Thread_1,
		this,           // arg list
		0,  // 立即执行不要挂起
		&uiThread1ID_1);

	mThreadFlag_2 = 1;
	hThread_2 = (HANDLE)_beginthreadex(NULL,         // security
		0,            // stack size
		CTemplate_ControlDlg::Thread_2,
		this,           // arg list
		0,  // 立即执行不要挂起
		&uiThread1ID_2);

	CLogFile mf;
	for (int i = 0; i < 2;i++)
	{
		mf.axisMoving[i] = 1;
	}
	mf.WriteLog(9);
}


BOOL CTemplate_ControlDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
			return TRUE;
		case VK_ESCAPE:
			return TRUE;
		default:
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CTemplate_ControlDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	// 停止绘图区域刷新
	//m_ThreadFlag1 = 0;

	//int dataLength = 0, height = 260, width = 0, heightY = 260 - 20 - 8, widthX = 0;
	//bool flagF = false;
	//float temp[11];
	//float curMax = -1000, curMin = 1000;
	//double step = 10.0, stepX = 100.0, stepY = 77;
	//double scaleX = 1.0;
	//double scaleY = 1.0;
	//CString strTimeStart, strTimeEnd, strLog, strFN, strTag;
	//time_t timec = 0, timep[2] = { 0 }, times[2] = { 0 };
	//FILETIME ft;
	//ULARGE_INTEGER uli;
	//SYSTEMTIME lpSystemTime[2], lpSystemTimeTag;
	//CStdioFile mf;
	//vector<CString> vecFN;
	//vector<time_t> vecTime;
	//vector<float> vecData[11];

	//m_TimeStartCtr.GetWindowTextA(strTimeStart);
	//m_TimeEndCtr.GetWindowTextA(strTimeEnd);
	//
	//StringToSysTime(strTimeStart, &lpSystemTime[0]);
	//StringToSysTime(strTimeEnd, &lpSystemTime[1]);	

	//if ((SystemTimeToFileTime(&lpSystemTime[0], &ft)) == false)
	//{
	//	MessageBox("无效起始时间");
	//	return;
	//}
	//uli.HighPart = ft.dwHighDateTime;
	//uli.LowPart = ft.dwLowDateTime;
	//times[0] = (double)uli.QuadPart / 10000.0;

	//if ((SystemTimeToFileTime(&lpSystemTime[1], &ft)) == false)
	//{
	//	MessageBox("无效起始时间");
	//	return;
	//}
	//uli.HighPart = ft.dwHighDateTime;
	//uli.LowPart = ft.dwLowDateTime;
	//times[1] = (double)uli.QuadPart / 10000.0;
	//

	//// 加载文件
	//if (mf.Open(_T("FileRecord.txt"), CFile::modeRead) != true)
	//{
	//	MessageBox("FileRecord无法加载");
	//	return;
	//}
	//
	//while (false != mf.ReadString(strLog))
	//{
	//	if (StringToData1(strLog, &timep[0], &timep[1], &strFN) == false)
	//	{
	//		MessageBox("FileRecord无法加载");
	//		return;
	//	}
	//	if (timep[0] < times[0] && timep[1] > times[0])
	//	{
	//		vecFN.push_back(strFN);
	//		flagF = true;
	//	}
	//	if (timep[0] < times[1] && timep[1] > times[1])
	//	{
	//		flagF = false;
	//		mf.Close();
	//		break;
	//	}
	//	if (flagF == true)
	//	{
	//		if (timep[0] < times[1] && timep[1] > times[1])
	//		{
	//			vecFN.push_back(strFN);
	//			mf.Close();
	//			break;
	//		}
	//	}
	//}
	//if (mf.m_hFile != CFile::hFileNull)
	//{
	//	mf.Close();
	//}
	//if (vecFN.size() == 0)
	//{
	//	MessageBox("没有相关数据");
	//	return;
	//}

	//dataLength = (double)(timep[1] - timep[0]) / (double)500;

	//if (dataLength > 500)
	//{
	//	step = 5000.0 / (double)dataLength;
	//	stepX = 10.0 * 5000.0 / (double)dataLength;
	//}

	//width = dataLength * step + 0.000001;

	//// 为GDI 绘图创建文件流 --------------------------------
	//IStream *pStrmBmp;
	//BITMAPFILEHEADER fileHeader;
	//BITMAPINFOHEADER bitmapHeader;

	//CreateStreamOnHGlobal(NULL, TRUE, &pStrmBmp);

	////Create Bitmap File Header
	//fileHeader.bfType = 0x4D42;
	//fileHeader.bfSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+width*height * 3;
	//fileHeader.bfReserved1 = 0;
	//fileHeader.bfReserved2 = 0;
	//fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);

	////Create Bitmap Info Header
	//bitmapHeader.biSize = sizeof(BITMAPINFOHEADER);
	//bitmapHeader.biWidth = width;
	//bitmapHeader.biHeight = height;
	//bitmapHeader.biPlanes = 1;
	//bitmapHeader.biBitCount = 24;
	//bitmapHeader.biCompression = 0;		//BI_RGB
	//bitmapHeader.biSizeImage = width*height * 3;

	////write data, white color
	//BYTE *data = new BYTE[width * height * 3]();
	//for (int i = 0; i < width * height * 3; ++i)
	//{
	//	data[i] = 0;
	//}

	//pStrmBmp->Write(&fileHeader, sizeof(BITMAPFILEHEADER), NULL);
	//pStrmBmp->Write(&bitmapHeader, sizeof(BITMAPINFOHEADER), NULL);
	//pStrmBmp->Write(data, width * height * 3, NULL);

	////-----------------------------------------------------

	//Gdiplus::Bitmap bitmap(pStrmBmp);

	//Gdiplus::Graphics g(&bitmap);

	//Gdiplus::Point pntAxis[3];
	//Gdiplus::Point pntData[11];
	//Gdiplus::PointF pntTag[2];
	//Gdiplus::Point pntDataPre[11];
	//Gdiplus::Point pntDataSeg[2];

	//Gdiplus::Color cData[11] = { Color(255, 0, 0), Color(191, 63, 0), Color(128, 128, 0),
	//	Color(63, 191, 0), Color(0, 255, 0), Color(0, 191, 63), Color(0, 128, 128),
	//	Color(0, 63, 191), Color(0, 0, 255), Color(63, 0, 191), Color(128, 0, 128) };

	//Gdiplus::Pen penAxis(Color(255, 255, 255), 2);
	//Gdiplus::Pen penData0(Color(0, 0, 0), 1);
	//SolidBrush  brushText(Color(255, 255, 255));
	///*Gdiplus::Pen penData1(Color(255, 0, 0), 1);
	//Gdiplus::Pen penData2(Color(191, 63, 0), 1);
	//Gdiplus::Pen penData3(Color(128, 128, 0), 1);
	//Gdiplus::Pen penData4(Color(63, 191, 0), 1);
	//Gdiplus::Pen penData5(Color(0, 255, 0), 1);
	//Gdiplus::Pen penData6(Color(0, 191, 63), 1);
	//Gdiplus::Pen penData7(Color(0, 128, 128), 1);
	//Gdiplus::Pen penData8(Color(0, 63, 191), 1);
	//Gdiplus::Pen penData9(Color(0, 0, 255), 1);
	//Gdiplus::Pen penData10(Color(63, 0, 191), 1);
	//Gdiplus::Pen penData11(Color(128, 0, 128), 1);
	//Gdiplus::Pen penData(Color(128, 0, 128), 1)[11];*/
	//FontFamily fontFamily(L"幼圆");
	//Gdiplus::Font font(&fontFamily, 12, FontStyleRegular, UnitPixel);

	//Gdiplus::Status gStatus;

	////bitmap.create;
	//pntAxis[0].X = 40;
	//pntAxis[0].Y = 4;
	//pntAxis[1].X = 40;
	//pntAxis[1].Y = height - 20;
	//pntAxis[2].X = width - 10;
	//pntAxis[2].Y = height - 20;
	//widthX = width - 50 - 8;

	//gStatus = g.DrawLines(&penAxis, pntAxis, 3);
	//penAxis.SetWidth(1);
	//for (int i = 0; i < vecFN.size(); i++)
	//{
	//	if (mf.Open(vecFN.at(i), CFile::modeRead) == false)
	//	{
	//		MessageBox("无法读取温度数据");
	//		return;
	//	}

	//	while (mf.ReadString(strLog))
	//	{
	//		if (strLog == "")
	//		{
	//			continue;
	//		}
	//		if (StringToData2(strLog, &timec, &temp[0], &temp[1], &temp[2], &temp[3],
	//			&temp[4], &temp[5], &temp[6], &temp[7], &temp[8], &temp[9], &temp[10]) == false)
	//		{
	//			MessageBox("FileRecord无法加载");
	//			return;
	//		}
	//		if (timec != 0)
	//		{
	//			vecTime.push_back(timec);
	//			for (int j = 0; j < 11; j++)
	//			{
	//				vecData[j].push_back(temp[j]);
	//				if (temp[j] == INVALID_TEMP)
	//				{
	//					break;
	//				}
	//				if (temp[j] > curMax)
	//				{
	//					curMax = temp[j];
	//				}
	//				if (temp[j] < curMin)
	//				{
	//					curMin = temp[j];
	//				}
	//			}
	//		}
	//	}
	//	mf.Close();
	//}

	//scaleX = (double)widthX / (double)dataLength;
	//scaleY = (double)heightY / (double)(curMax - curMin);

	//for (int i = 0; i < 4; i++)
	//{
	//	pntTag[0].Y = pntAxis[0].Y + stepY * i;
	//	pntTag[0].X = pntAxis[0].X - 40;
	//	strTag.Format("%5.1f", curMax - i * (curMax - curMin) / 3.0);
	//	g.DrawString(strTag.AllocSysString(), strTag.GetLength(), &font, pntTag[0], &brushText);
	//	pntTag[0].X = pntAxis[0].X - 4;
	//	pntTag[1].X = pntTag[0].X + widthX + 4;
	//	pntTag[1].Y = pntTag[0].Y;
	//	g.DrawLine(&penAxis, pntTag[0], pntTag[1]);
	//}

	//pntData[0].X = pntAxis[1].X + 4;
	//pntData[0].Y = pntAxis[1].Y - (vecData[0].at(0) - curMin) * scaleY - 4;
	//pntData[1].X = pntAxis[1].X + 4;
	//pntData[1].Y = pntAxis[1].Y - (vecData[1].at(0) - curMin) * scaleY - 4;
	//pntData[2].X = pntAxis[1].X + 4;
	//pntData[2].Y = pntAxis[1].Y - (vecData[2].at(0) - curMin) * scaleY - 4;
	//pntData[3].X = pntAxis[1].X + 4;
	//pntData[3].Y = pntAxis[1].Y - (vecData[3].at(0) - curMin) * scaleY - 4;
	//pntData[4].X = pntAxis[1].X + 4;
	//pntData[4].Y = pntAxis[1].Y - (vecData[4].at(0) - curMin) * scaleY - 4;
	//pntData[5].X = pntAxis[1].X + 4;
	//pntData[5].Y = pntAxis[1].Y - (vecData[5].at(0) - curMin) * scaleY - 4;
	//pntData[6].X = pntAxis[1].X + 4;
	//pntData[6].Y = pntAxis[1].Y - (vecData[6].at(0) - curMin) * scaleY - 4;
	//pntData[7].X = pntAxis[1].X + 4;
	//pntData[7].Y = pntAxis[1].Y - (vecData[7].at(0) - curMin) * scaleY - 4;
	//pntData[8].X = pntAxis[1].X + 4;
	//pntData[8].Y = pntAxis[1].Y - (vecData[8].at(0) - curMin) * scaleY - 4;
	//pntData[9].X = pntAxis[1].X + 4;
	//pntData[9].Y = pntAxis[1].Y - (vecData[9].at(0) - curMin) * scaleY - 4;
	//pntData[10].X = pntAxis[1].X + 4;
	//pntData[10].Y = pntAxis[1].Y - (vecData[10].at(0) - curMin) * scaleY - 4;
	//
	//for (int i = 0; i < 11; i++)
	//{
	//	pntDataPre[i] = pntData[i];
	//}
	//// 逐点绘制
	//penData0.SetWidth(1);
	//for (int i = 1; i < vecTime.size(); i++)
	//{
	//	for (int j = 0; j < 11; j++)
	//	{
	//		if (fabs(vecData[j].at(i) - INVALID_TEMP) < 0.000001)
	//		{
	//			pntData[j].Y = pntAxis[1].Y;
	//			continue;
	//		}
	//		pntData[j].Y = pntAxis[1].Y - (vecData[j].at(i) - curMin) * scaleY - 4;
	//		pntData[j].X = pntAxis[1].X + 4 + scaleX * (double)(vecTime.at(i) - vecTime.at(0)) / (double)500;
	//	}
	//	if (abs(pntData[0].X - pntDataPre[0].X) < 2)
	//	{
	//		continue;
	//	}
	//	for (int j = 0; j < 11; j++)
	//	{
	//		if (m_ValidFlag[j] == true)
	//		{
	//			pntDataSeg[0] = pntDataPre[j];
	//			pntDataSeg[1] = pntData[j];
	//			penData0.SetColor(cData[j]);
	//			gStatus = g.DrawLines(&penData0, pntDataSeg, 2);
	//		}
	//	}
	//	if (i % 10 == 0)
	//	{
	//		pntTag[1].Y = pntAxis[1].Y + 4;
	//		pntTag[1].X = pntData[0].X;
	//		strTag.Format("%5.1f", (double)(vecTime.at(i) - vecTime.at(0)) / 1000.0);
	//		g.DrawString(strTag.AllocSysString(), strTag.GetLength(), &font, pntTag[1], &brushText);
	//		pntTag[0].X = pntTag[1].X;
	//		pntTag[0].Y = pntTag[1].Y - heightY - 8;
	//		g.DrawLine(&penAxis, pntTag[0], pntTag[1]);
	//	}
	//	for (int i = 0; i < 11; i++)
	//	{
	//		pntDataPre[i] = pntData[i];
	//	}
	//}

	////g.DrawImage(&bitmap, &r, 0, 0, 1024, 512);
	//string strFN2;
	//CLSID pngClsid;
	//WCHAR  *wcX;
	//GetEncoderClsid(L"image/bmp", &pngClsid);
	//strFN.Format("profile_%d-%d-%d_%d-%d-%dto%d-%d-%d_%d-%d-%d.bmp", lpSystemTime[0].wYear,
	//	lpSystemTime[0].wMonth, lpSystemTime[0].wDay, lpSystemTime[0].wHour, lpSystemTime[0].wMinute,
	//	lpSystemTime[0].wSecond, lpSystemTime[1].wYear, lpSystemTime[1].wMonth, lpSystemTime[1].wDay,
	//	lpSystemTime[1].wHour, lpSystemTime[1].wMinute, lpSystemTime[1].wSecond);
	//wcX = strFN.AllocSysString();
	//gStatus = bitmap.Save(wcX, &pngClsid, nullptr);

	//if (data)
	//{
	//	delete data;
	//	data = NULL;
	//}
	CGraphShowDlg mGraphDlg;
	mGraphDlg.DoModal();
}

int CTemplate_ControlDlg::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)

{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;
	GetImageEncodersSize(&num, &size);

	if (size == 0)
		return -1;  // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}


	free(pImageCodecInfo);
	return -1;  // Failure
}

BOOL CTemplate_ControlDlg::StringToSysTime(CString strTime, SYSTEMTIME *lSystemTime)
{
	int index[2] = { 0 };
	int temp = 0;
	CString strTemp;

	for (int i = 0; i < strTime.GetLength(); i++)
	{
		if (strTime[i] < 48 || strTime[i] > 58)
		{
			return false;
		}
	}
	lSystemTime->wDayOfWeek = 0;
	lSystemTime->wMilliseconds = 0;
	// year
	index[1] = strTime.Find(":", index[0]);
	if (index[1] < 0)
	{
		return false;
	}
	strTemp = strTime.Mid(index[0], index[1]);
	if (strTemp == "")
	{
		return false;
	}
	temp = _ttoi(strTemp);
	if (temp < 1900 || temp > 2100)
	{
		return false;
	}
	lSystemTime->wYear = (WORD)temp;
	index[0] = index[1] + 1;

	//month
	index[1] = strTime.Find(":", index[0]);
	if (index[1] < 0)
	{
		return false;
	}
	strTemp = strTime.Mid(index[0], index[1]);
	if (strTemp == "")
	{
		return false;
	}
	temp = _ttoi(strTemp);
	if (temp < 1 || temp > 12)
	{
		return false;
	}
	lSystemTime->wMonth = (WORD)temp;
	index[0] = index[1] + 1;

	//date
	index[1] = strTime.Find(":", index[0]);
	if (index[1] < 0)
	{
		return false;
	}
	strTemp = strTime.Mid(index[0], index[1]);
	if (strTemp == "")
	{
		return false;
	}
	temp = _ttoi(strTemp);
	if (temp < 1 || temp > 31)
	{
		return false;
	}
	lSystemTime->wDay = (WORD)temp;
	index[0] = index[1] + 1;

	// hour
	index[1] = strTime.Find(":", index[0]);
	if (index[1] < 0)
	{
		return false;
	}
	strTemp = strTime.Mid(index[0], index[1]);
	if (strTemp == "")
	{
		return false;
	}
	temp = _ttoi(strTemp);
	if (temp < 0 || temp > 23)
	{
		return false;
	}
	lSystemTime->wHour = (WORD)temp;

	index[0] = index[1] + 1;

	// minute
	index[1] = strTime.Find(":", index[0]);
	if (index[1] < 0)
	{
		return false;
	}
	strTemp = strTime.Mid(index[0], index[1]);
	if (strTemp == "")
	{
		return false;
	}
	temp = _ttoi(strTemp);
	if (temp < 0 || temp > 59)
	{
		return false;
	}
	lSystemTime->wMinute = (WORD)temp;
	index[0] = index[1] + 1;

	// second
	strTemp = strTime.Mid(index[0], strTime.GetLength());;
	if (strTemp == "")
	{
		return false;
	}
	temp = _ttoi(strTemp);
	if (temp < 0 || temp > 59)
	{
		return false;
	}
	lSystemTime->wSecond= (WORD)temp;



	return true;
}

BOOL CTemplate_ControlDlg::StringToData1(CString strTime, time_t *time1, time_t *time2, CString *FileName)
{
	int index = 0, indexNext = 0;
	CString strTemp;
	if ((indexNext = strTime.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strTime.Mid(index, indexNext);
	*time1 = _ttoll(strTemp);
	index = indexNext + 1;

	if ((indexNext = strTime.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strTime.Mid(index, indexNext);
	*time2 = _ttoll(strTemp);
	index = indexNext + 1;

	*FileName = strTime.Mid(index, strTime.GetLength());
	m_ThreadFlag1 = 1;
	return true;
}

BOOL CTemplate_ControlDlg::StringToData2(CString strSrc, time_t *timet, float *t1, float *t2, float *t3,
	float *t4, float *t5, float *t6, float *t7, float *t8, float *t9,
	float *t10, float *t11)
{
	int index = 0, indexNext = 0;
	CString strTemp;
	if ((indexNext = strSrc.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strSrc.Mid(index, indexNext);
	*timet = _ttoll(strTemp);
	index = indexNext + 1;

	if ((indexNext = strSrc.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strSrc.Mid(index, indexNext);
	*t1 = _ttof(strTemp);
	index = indexNext + 1;

	if ((indexNext = strSrc.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strSrc.Mid(index, indexNext);
	*t2 = _ttof(strTemp);
	index = indexNext + 1;

	if ((indexNext = strSrc.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strSrc.Mid(index, indexNext);
	*t3 = _ttof(strTemp);
	index = indexNext + 1;

	if ((indexNext = strSrc.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strSrc.Mid(index, indexNext);
	*t4 = _ttof(strTemp);
	index = indexNext + 1;

	if ((indexNext = strSrc.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strSrc.Mid(index, indexNext);
	*t5 = _ttof(strTemp);
	index = indexNext + 1;

	if ((indexNext = strSrc.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strSrc.Mid(index, indexNext);
	*t6 = _ttof(strTemp);
	index = indexNext + 1;

	if ((indexNext = strSrc.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strSrc.Mid(index, indexNext);
	*t7 = _ttof(strTemp);
	index = indexNext + 1;

	if ((indexNext = strSrc.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strSrc.Mid(index, indexNext);
	*t8 = _ttof(strTemp);
	index = indexNext + 1;

	if ((indexNext = strSrc.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strSrc.Mid(index, indexNext);
	*t9 = _ttof(strTemp);
	index = indexNext + 1;

	if ((indexNext = strSrc.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strSrc.Mid(index, indexNext);
	*t10 = _ttof(strTemp);
	index = indexNext + 1;

	strTemp = strSrc.Mid(index, strSrc.GetLength());
	*t11 = _ttof(strTemp);
	
	return true;
}

void CTemplate_ControlDlg::OnBnClickedCheck1()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_TempCheck1.GetCheck())
	{
		m_ValidFlag[0] = true;
	}
	else
	{
		m_ValidFlag[0] = false;
	}
	m_ScanMaxMinFlag = 1;
}


void CTemplate_ControlDlg::OnBnClickedCheck2()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_TempCheck2.GetCheck())
	{
		m_ValidFlag[1] = true;
	}
	else
	{
		m_ValidFlag[1] = false;
	}
	m_ScanMaxMinFlag = 1;
}


void CTemplate_ControlDlg::OnBnClickedCheck3()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_TempCheck3.GetCheck())
	{
		m_ValidFlag[2] = true;
	}
	else
	{
		m_ValidFlag[2] = false;
	}
	m_ScanMaxMinFlag = 1;
}


void CTemplate_ControlDlg::OnBnClickedCheck4()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_TempCheck4.GetCheck())
	{
		m_ValidFlag[3] = true;
	}
	else
	{
		m_ValidFlag[3] = false;
	}
	m_ScanMaxMinFlag = 1;
}


void CTemplate_ControlDlg::OnBnClickedCheck5()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_TempCheck5.GetCheck())
	{
		m_ValidFlag[4] = true;
	}
	else
	{
		m_ValidFlag[4] = false;
	}
	m_ScanMaxMinFlag = 1;
}


void CTemplate_ControlDlg::OnBnClickedCheck6()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_TempCheck6.GetCheck())
	{
		m_ValidFlag[5] = true;
	}
	else
	{
		m_ValidFlag[5] = false;
	}
	m_ScanMaxMinFlag = 1;
}


void CTemplate_ControlDlg::OnBnClickedCheck7()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_TempCheck7.GetCheck())
	{
		m_ValidFlag[6] = true;
	}
	else
	{
		m_ValidFlag[6] = false;
	}
	m_ScanMaxMinFlag = 1;
}


void CTemplate_ControlDlg::OnBnClickedCheck8()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_TempCheck8.GetCheck())
	{
		m_ValidFlag[7] = true;
	}
	else
	{
		m_ValidFlag[7] = false;
	}
	m_ScanMaxMinFlag = 1;
}


void CTemplate_ControlDlg::OnBnClickedCheck9()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_TempCheck9.GetCheck())
	{
		m_ValidFlag[8] = true;
	}
	else
	{
		m_ValidFlag[8] = false;
	}
	m_ScanMaxMinFlag = 1;
}


void CTemplate_ControlDlg::OnBnClickedCheck10()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_TempCheck10.GetCheck())
	{
		m_ValidFlag[9] = true;
	}
	else
	{
		m_ValidFlag[9] = false;
	}
	m_ScanMaxMinFlag = 1;
}


void CTemplate_ControlDlg::OnBnClickedCheck11()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_TempCheck11.GetCheck())
	{
		m_ValidFlag[10] = true;
	}
	else
	{
		m_ValidFlag[10] = false;
	}
	m_ScanMaxMinFlag = 1;
}


HBRUSH CTemplate_ControlDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	for (int i = 0; i < 11; i++)
	{
		if (pWnd->GetDlgCtrlID() == IDC_CHECK1 + i && nCtlColor == CTLCOLOR_STATIC)//特定的某一个检查框，IDC_CHECK1为标签控件ID
		{
			pDC->SetBkMode(BKMODE_LAST);//透明
			pDC->SetTextColor(colorRef[i]); //文字颜色  
		}
	}

	return (HBRUSH)m_checkBrush.GetSafeHandle();
}


CLogFile::CLogFile()
{}

CLogFile::~CLogFile()
{}

void CLogFile::WriteLog(int moveMode)
{
	mFile.Open("MovingRecord.txt", CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
	mFile.SeekToEnd();
	time_t t = time(0);
	tm tInfo;
	char tmp[64];
	localtime_s(&tInfo, &t);
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X %A", &tInfo);
	CString strTmp(tmp);
	mFile.Write(tmp, strlen(tmp));
	mFile.Write("\t", 1);

	switch (moveMode)
	{
	case 1:
	{
		mFile.Write("点位运动(mm/d): ", 16);
		break;
	}
	case 2:
	{
		mFile.Write("点位运动(p/p): ", 15);
		break;
	}
	case 3:
	{
		mFile.Write("点位运动(mm/p): ", 16);
		break;
	}
	case 4:
	{
		mFile.Write("点位运动(p/d): ", 15);
		break;
	}
	case 5:
	{
		mFile.Write("插补运动(mm/d): ", 16);
		break;
	}
	case 6:
	{
		mFile.Write("插补运动(p/p): ", 15);
		break;
	}
	case 7:
	{
		mFile.Write("插补运动(mm/p): ", 16);
		break;
	}
	case 8:
	{
		mFile.Write("插补运动(p/d): ", 15);
		break;
	}
	case 9:
	{
		mFile.Write("回零运动: ", 10);
		break;
	}
	case 10:
	{
		mFile.Write("连续运动: ", 10);
		break;
	}
	}

	if (moveMode == 10 || moveMode == 9)
	{
		for (int i = 0; i < 2; i++)
		{
			if (axisMoving[i] == 1)
			{
				switch (i)
				{
				case 0:
					mFile.Write("  X", 3);
					break;
				case 1:
					mFile.Write("  Y", 3);
					break;
				case 2:
					mFile.Write("  Z", 3);
					break;
				case 3:
					mFile.Write("  T1", 4);
					break;
				case 4:
					mFile.Write("  T2", 4);
					break;
				case 5:
					mFile.Write("  T3", 4);
					break;
				default:
					break;
				}
			}
		}
		mFile.Write("\r\n", 2);
		mFile.Close();
		return;
	}
	for (int i = 0; i < 2; i++)
	{
		strTmp.Format("%f", dist[i]);
		mFile.WriteString(strTmp);
		if (i < 1)
			mFile.Write("\t", 1);
		else
			mFile.Write(";", 1);
	}
	mFile.Write("\r\n", 2);
	mFile.Close();
}


int CLogFile::SplitToLong(CString strL, char cMark, long* dataProc, int begin, int num)
{
	int curPos = 0,
		c = 0,
		i = 0,
		k = 0,
		count;
	CString temp;

	while ((curPos = strL.Find(cMark, curPos + 1)) != -1)
	{
		if (i == (begin + num - 1))
			break;
		if (strL.Mid(curPos + 1, 1) != cMark)
		{
			count = curPos - c;
			if (i >= begin)
			{
				temp = strL.Mid(c, count);
				dataProc[k] = (long)_ttoi(temp);
				k++;
			}
			c = curPos;
			i++;
		}
	}
	if (curPos == -1)
		temp = strL.Mid(c + 1, strL.GetLength() - c - 1);
	else
		temp = strL.Mid(c + 1, curPos - c - 1);
	dataProc[k] = _ttoi(temp);
	return i + 1;
}


void CTemplate_ControlDlg::OnReadMoveRecord()
{
	// TODO:  在此添加命令处理程序代码
	CFileDialog fd(TRUE, "*.txt", NULL, 0, "文本文件(*.txt)|*.txt|所有文件|*.*||", theApp.GetMainWnd()->GetWindow(GW_HWNDPREV));
	if (IDCANCEL == fd.DoModal())
	{
		return;
	}
	CString szFile = fd.GetPathName();
	ShellExecute(NULL, "open", szFile, NULL, NULL, SW_SHOW);
	this->SetFocus();
}


void CTemplate_ControlDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	mThreadFlag = 0;
	m_ThreadFlag1 = 0;
	while (m_ThreadFlag2 == 0)
	{
		Sleep(250);
	}
	Sleep(250);
	CDialogEx::OnClose();
}
