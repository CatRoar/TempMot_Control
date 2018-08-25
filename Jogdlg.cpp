// Jogdlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Template_Control.h"
#include "Jogdlg.h"
#include "afxdialogex.h"


// CJogdlg �Ի���

IMPLEMENT_DYNAMIC(CJogdlg, CDialogEx)

CJogdlg::CJogdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJogdlg::IDD, pParent)
{

}

CJogdlg::~CJogdlg()
{
}

void CJogdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_JOG_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_JOG_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_JOG_EDIT3, m_edit3);
	DDX_Control(pDX, IDC_JOG_EDIT4, m_edit4);
	DDX_Control(pDX, IDC_JOG_EDIT5, m_edit5);
	DDX_Control(pDX, IDC_JOG_EDIT6, m_edit6);
}


BEGIN_MESSAGE_MAP(CJogdlg, CDialogEx)
	ON_BN_CLICKED(IDC_JOG_BUTTON1, &CJogdlg::OnBnClickedJogButton1)
	ON_BN_CLICKED(IDC_JOG_BUTTON2, &CJogdlg::OnBnClickedJogButton2)
END_MESSAGE_MAP()


// CJogdlg ��Ϣ�������

BOOL CJogdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_editArray[0] = &m_edit1;
	m_editArray[1] = &m_edit2;
	m_editArray[2] = &m_edit3;
	m_editArray[3] = &m_edit4;
	m_editArray[4] = &m_edit5;
	m_editArray[5] = &m_edit6;

	CString strValue;
	for (int i = 0; i < 2;i++)
	{
		strValue.Format("%0.1f", m_jogInfo[i].startvel);
		m_editArray[0 + i * 3]->SetWindowText(strValue);
		strValue.Format("%0.1f", m_jogInfo[i].tagvel);
		m_editArray[1 + i * 3]->SetWindowText(strValue);
		strValue.Format("%0.1f", m_jogInfo[i].accvel);
		m_editArray[2 + i * 3]->SetWindowText(strValue);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CJogdlg::OnBnClickedJogButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strtmp, strTitle;
	for (int i = 0; i < 2; i++)
	{
		m_editArray[ 0 + i*3]->GetWindowText(strtmp);
		m_jogInfo[i].startvel = atof(strtmp);
		strTitle.Format("StartVel_%d", i);
		::WritePrivateProfileString("JogInfo", strTitle, strtmp, "C:\\Windows\\Template_Control.ini");

		m_editArray[1 + i*3]->GetWindowText(strtmp);
		m_jogInfo[i].tagvel = atof(strtmp);
		strTitle.Format("TagVel_%d", i);
		::WritePrivateProfileString("JogInfo", strTitle, strtmp, "C:\\Windows\\Template_Control.ini");

		m_editArray[2 + i*3]->GetWindowText(strtmp);
		m_jogInfo[i].accvel = atof(strtmp);
		strTitle.Format("AccVel_%d", i);
		::WritePrivateProfileString("JogInfo", strTitle, strtmp, "C:\\Windows\\Template_Control.ini");
	}
	MessageBox(_T("��������ɹ�"), _T("��ʾ"));
	CDialogEx::OnOK();
}

void CJogdlg::OnBnClickedJogButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
