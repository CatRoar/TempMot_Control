// InputCommandDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Template_Control.h"
#include "InputCommandDlg.h"
#include "afxdialogex.h"


// CInputCommandDlg 对话框

IMPLEMENT_DYNAMIC(CInputCommandDlg, CDialogEx)

CInputCommandDlg::CInputCommandDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInputCommandDlg::IDD, pParent)
{

}

CInputCommandDlg::~CInputCommandDlg()
{
}

void CInputCommandDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INPUT_EDIT1, m_editDistX);
	DDX_Control(pDX, IDC_INPUT_EDIT2, m_editSpeedX);
	DDX_Control(pDX, IDC_INPUT_EDIT3, m_editAccX);
	DDX_Control(pDX, IDC_INPUT_EDIT4, m_editDistY);
	DDX_Control(pDX, IDC_INPUT_EDIT5, m_editSpeedY);
	DDX_Control(pDX, IDC_INPUT_EDIT6, m_editAccY);
	DDX_Control(pDX, IDC_INPUT_EDIT7, m_editWaitTime);
	DDX_Control(pDX, IDC_INPUT_EDIT8, m_editCycles);
	DDX_Control(pDX, IDC_CHECK1, m_checkX);
	DDX_Control(pDX, IDC_CHECK2, m_checkY);
	DDX_Control(pDX, IDC_INPUTDLGLIST, m_nInputDlgList);
}


BEGIN_MESSAGE_MAP(CInputCommandDlg, CDialogEx)
	ON_BN_CLICKED(IDC_INPUT_BUTTON1, &CInputCommandDlg::OnBnClickedInputButton1)
	ON_BN_CLICKED(IDC_INPUT_BUTTON2, &CInputCommandDlg::OnBnClickedInputButton2)
	ON_BN_CLICKED(IDC_CHECK1, &CInputCommandDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CInputCommandDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_BUTTON1, &CInputCommandDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CInputCommandDlg 消息处理程序



BOOL CInputCommandDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_pEditArray[0] = &m_editDistX;
	m_pEditArray[1] = &m_editSpeedX;
	m_pEditArray[2] = &m_editAccX;
	m_pEditArray[3] = &m_editDistY;
	m_pEditArray[4] = &m_editSpeedY;
	m_pEditArray[5] = &m_editAccY;

	for (int i = 0; i < 6; i++)
	{
		m_pEditArray[i]->EnableWindow(FALSE);
	}
	m_editWaitTime.SetWindowTextA("0.5");
	m_editCycles.SetWindowTextA("1");
	m_nCommadnArray.clear();

	m_hwnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CInputCommandDlg::OnBnClickedInputButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	CString str;
	if (!(m_checkX.GetCheck()) && !(m_checkY.GetCheck()))
	{
		MessageBox("请选择移动平台!");
		return;
	}

	int numOfCycle = 0;
	double waitTime = 0;
	double axisPara[6] = { 0, 0, 0, 0, 0, 0 };
	double dist[2] = { 0, 0};

	if (m_checkX.GetCheck())
	{
		for (int i = 0; i < 3;i++)
		{
			m_pEditArray[i]->GetWindowTextA(str);
			axisPara[i] = atof(str);
		}
	}
	if (m_checkY.GetCheck())
	{
		for (int i = 3; i < 6; i++)
		{
			m_pEditArray[i]->GetWindowTextA(str);
			axisPara[i] = atof(str);
		}
	}
	m_editWaitTime.GetWindowTextA(str);
	waitTime = atof(str) * 1000;

	commandPack = CCommandPack();
	commandPack.setValue(waitTime, axisPara, dist);

	m_nCommadnArray.push_back(commandPack);

	CString strTmp;
	strTmp.Format("X:(%0.3fmm, %0.2fmm/s, %0.2fmm/s2),  Y:(%0.3fmm, %0.2fmm/s, %0.2fmm/s2)", commandPack.axisPara[0], commandPack.axisPara[1],
		commandPack.axisPara[2], commandPack.axisPara[3], commandPack.axisPara[4], commandPack.axisPara[5]);
	int cnt = m_nCommadnArray.size() - 1;
	m_nInputDlgList.InsertString(cnt, strTmp);


	//::PostMessage(m_hwnd, WM_MY_MESSAGE, 0, (LPARAM)&commandPack);
}


void CInputCommandDlg::OnBnClickedInputButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	CString str;
	int numOfCycle;
	commandPackInfo = CommandPackInfo();
	m_editCycles.GetWindowTextA(str);
	numOfCycle = atoi(str);
	commandPackInfo.numOfCycle = numOfCycle;
	for (int i = 0; i < m_nCommadnArray.size();i++)
	{
		commandPackInfo.CommandPack.push_back(m_nCommadnArray[i]);
	}
	
	::PostMessage(m_hwnd, WM_MY_MESSAGE, 0, (LPARAM)&commandPackInfo);

	//CDialogEx::OnOK();
}


void CInputCommandDlg::CCommandPack::setValue(float waitTime, double* axis, double* dst)
{
	//numOfCycle = numCycle;
	waitTime = waitTime;
	for (int i = 0; i < 6;i++)
	{
		axisPara[i] = axis[i];
	}
}


CInputCommandDlg::CCommandPack::CCommandPack()
{
	//numOfCycle = 0;
	waitTime = 0;
	for (int i = 0; i < 6;i++)
	{
		axisPara[i] = 0;
	}
}


CInputCommandDlg::CommandPackInfo::CommandPackInfo()
{
	numOfCycle = 0;
	CommandPack.clear();
}


void CInputCommandDlg::OnBnClickedCheck1()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_checkX.GetCheck())
	{
		for (int i = 0; i < 3; i++)
		{
			m_pEditArray[i]->EnableWindow(TRUE);
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			m_pEditArray[i]->EnableWindow(FALSE);
		}
	}
}


void CInputCommandDlg::OnBnClickedCheck2()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_checkY.GetCheck())
	{
		for (int i = 3; i < 6; i++)
		{
			m_pEditArray[i]->EnableWindow(TRUE);
		}
	}
	else
	{
		for (int i = 3; i < 6; i++)
		{
			m_pEditArray[i]->EnableWindow(FALSE);
		}
	}
}


void CInputCommandDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	vector<CCommandPack>::iterator tempIterator;
	tempIterator = m_nCommadnArray.begin();

	int nCurSel = m_nInputDlgList.GetCurSel();
	if (nCurSel != LB_ERR)
	{
		m_nCommadnArray.erase(tempIterator + nCurSel);
		m_nInputDlgList.DeleteString(nCurSel);
	}
	else
	{
		MessageBox("请选择需要删除的命令行!");
	}
}
