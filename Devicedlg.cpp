// Devicedlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Template_Control.h"
#include "Devicedlg.h"
#include "afxdialogex.h"


// CDevicedlg �Ի���

IMPLEMENT_DYNAMIC(CDevicedlg, CDialogEx)

CDevicedlg::CDevicedlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDevicedlg::IDD, pParent)
{
	
}

CDevicedlg::~CDevicedlg()
{
}

void CDevicedlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DEVICE_COMBO1, m_Dtemperature);
	DDX_Control(pDX, IDC_DEVICE_LIST1, m_Listbox);
}


BEGIN_MESSAGE_MAP(CDevicedlg, CDialogEx)
	ON_BN_CLICKED(IDC_DEVICE_BUTTON2, &CDevicedlg::OnBnClickedDeviceButton2)
	ON_BN_CLICKED(IDC_DEVICE_BUTTON1, &CDevicedlg::OnBnClickedDeviceButton1)
	ON_LBN_SELCHANGE(IDC_DEVICE_LIST1, &CDevicedlg::OnLbnSelchangeDeviceList1)
	ON_BN_CLICKED(IDC_DEVICE_BUTTON3, &CDevicedlg::OnBnClickedDeviceButton3)
END_MESSAGE_MAP()


// CDevicedlg ��Ϣ�������


BOOL CDevicedlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_Dtemperature.SetCurSel(0);
	CString strTmp;
	strTmp.Format("%0.1f", m_Setsv[0]);
	SetDlgItemText(IDC_DEVICE_EDIT1, strTmp);
	for (int i = 0; i < 11; i++)
	{
		strTmp.Format("���µ�%d SV�趨ֵ: %0.1f��", i + 1, m_Setsv[i]);
		m_Listbox.SetItemHeight(i, 20);
		m_Listbox.InsertString(i, strTmp);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CDevicedlg::OnBnClickedDeviceButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strName, strValue, strTmp;
	for (int i = 0; i < 11; i++)
	{
		strName.Format("PT100SV_%d", i);
		strValue.Format("%0.1f", m_Setsv[i]);
		::WritePrivateProfileString("MR13Info", strName, strValue, "C:\\Windows\\Template_Control.ini");
	}
	CDialogEx::OnOK();
}


void CDevicedlg::OnBnClickedDeviceButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int nCurSel = m_Dtemperature.GetCurSel();
	CString cTmpstr,cShowstr;
	GetDlgItemText(IDC_DEVICE_EDIT1, cTmpstr);
	float fTmpval = atof(cTmpstr.GetBuffer());
	m_Setsv[nCurSel] = fTmpval;
	cShowstr.Format("���µ�%d SV�趨ֵ: %0.1f��", nCurSel + 1, fTmpval);
	m_Listbox.DeleteString(nCurSel);
	m_Listbox.InsertString(nCurSel, cShowstr);
}


void CDevicedlg::OnLbnSelchangeDeviceList1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int nCurSel;
	nCurSel = m_Listbox.GetCurSel();  // ��ȡ��ǰѡ���б���
	m_Dtemperature.SetCurSel(nCurSel);
	CString cTmpstr;
	float fValue = m_Setsv[nCurSel];
	cTmpstr.Format("%0.1f", fValue);
	SetDlgItemText(IDC_DEVICE_EDIT1, cTmpstr);
}


void CDevicedlg::OnBnClickedDeviceButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
