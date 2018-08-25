// Homedlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Template_Control.h"
#include "Homedlg.h"
#include "afxdialogex.h"


// CHomedlg 对话框

IMPLEMENT_DYNAMIC(CHomedlg, CDialogEx)

CHomedlg::CHomedlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHomedlg::IDD, pParent)
{

}

CHomedlg::~CHomedlg()
{
}

void CHomedlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HOME_COMBO1, m_comBox1);
	DDX_Control(pDX, IDC_HOME_COMBO2, m_comBox2);
	DDX_Control(pDX, IDC_HOME_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_HOME_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_HOME_EDIT3, m_edit3);
	DDX_Control(pDX, IDC_HOME_EDIT4, m_edit4);
	DDX_Control(pDX, IDC_HOME_EDIT5, m_edit5);
	DDX_Control(pDX, IDC_HOME_EDIT6, m_edit6);
}


BEGIN_MESSAGE_MAP(CHomedlg, CDialogEx)
	ON_BN_CLICKED(IDC_HOME_BUTTON1, &CHomedlg::OnBnClickedHomeButton1)
	ON_BN_CLICKED(IDC_HOME_BUTTON2, &CHomedlg::OnBnClickedHomeButton2)
END_MESSAGE_MAP()


// CHomedlg 消息处理程序


BOOL CHomedlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_comBoxArray[0] = &m_comBox1;
	m_comBoxArray[1] = &m_comBox2;
	m_editArray[0] = &m_edit1;
	m_editArray[1] = &m_edit2;
	m_editArray[2] = &m_edit3;
	m_editArray[3] = &m_edit4;
	m_editArray[4] = &m_edit5;
	m_editArray[5] = &m_edit6;

	CString strValue;
	for (int i = 0; i < 2; i++)
	{
		m_comBoxArray[i]->SetCurSel(m_homeInfo[i].dir);

		strValue.Format("%0.1f", m_homeInfo[i].tagvel);
		m_editArray[0 + i * 3]->SetWindowText(strValue);
		strValue.Format("%0.1f", m_homeInfo[i].accvel);
		m_editArray[1 + i * 3]->SetWindowText(strValue);
		strValue.Format("%0.1f", m_homeInfo[i].compatevel);
		m_editArray[2 + i * 3]->SetWindowText(strValue);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CHomedlg::OnBnClickedHomeButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strtmp, strTitle;
	for (int i = 0; i < 2; i++)
	{
		m_homeInfo[i].dir = m_comBoxArray[i]->GetCurSel();
		strtmp.Format("%d", m_homeInfo[i].dir);
		strTitle.Format("Direction_%d", i);
		::WritePrivateProfileString("HomeInfo", strTitle, strtmp, "C:\\Windows\\Template_Control.ini");

		m_editArray[0 + i * 3]->GetWindowText(strtmp);
		m_homeInfo[i].tagvel = abs(atof(strtmp));
		strTitle.Format("TagVel_%d", i);
		::WritePrivateProfileString("HomeInfo", strTitle, strtmp, "C:\\Windows\\Template_Control.ini");

		m_editArray[1 + i * 3]->GetWindowText(strtmp);
		m_homeInfo[i].accvel = abs(atof(strtmp));
		strTitle.Format("Accvel_%d", i);
		::WritePrivateProfileString("HomeInfo", strTitle, strtmp, "C:\\Windows\\Template_Control.ini");

		m_editArray[2 + i * 3]->GetWindowText(strtmp);
		m_homeInfo[i].compatevel = abs(atof(strtmp));
		strTitle.Format("CmpateVel_%d", i);
		::WritePrivateProfileString("HomeInfo", strTitle, strtmp, "C:\\Windows\\Template_Control.ini");
	}
	MessageBox(_T("参数保存成功"), _T("提示"));

	CDialogEx::OnOK();
}

void CHomedlg::OnBnClickedHomeButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
