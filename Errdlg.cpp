// Errdlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Template_Control.h"
#include "Errdlg.h"
#include "afxdialogex.h"


// CErrdlg �Ի���

IMPLEMENT_DYNAMIC(CErrdlg, CDialogEx)

CErrdlg::CErrdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CErrdlg::IDD, pParent)
{
	memset(m_err, -1, sizeof(WORD) * 16);
	memset(m_showIo, -1, sizeof(WORD) * 2 * 6);
	m_pImageList = NULL;
}

CErrdlg::~CErrdlg()
{
	if (!m_pImageList)
	{
		delete m_pImageList;
		m_pImageList = NULL;
	}
}

void CErrdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtl);
}


BEGIN_MESSAGE_MAP(CErrdlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CErrdlg ��Ϣ�������


BOOL CErrdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	memset(m_err, -1, sizeof(WORD) * 16);
	memset(m_showIo, -1, sizeof(WORD) * 2 * 6);
	/*CString str = _T("�������ͣ�\
								\r\nPLim��Ӳ������λ\t\tNLim��Ӳ������λ\t\tStop����ͣ����\
					 			\r\nPOSLIM��λ������\tINSERR��ָ�����\t\tVELLIM���ٶȳ���\
								\r\nACCLIM�����ٶȳ���\t\tDELPOS��ָ��λ���쳣\tORG:ԭ�㵽λ\
								\r���б����ȫ��0ʱ����ʾû�д���\
								\r���б���ж�Ӧ������1���������Ӧ�Ĵ�������");*/
	CString str = _T("�������ͣ�\r\nPLim��Ӳ������λ\t\tNLim��Ӳ������λ\t\tPSOF��������λ\t\tNSOF������λ\t\tStop����ͣ����\
	ALM���ŷ�����\t\tPOSLIM��λ������\tTGPOSOV��Ŀ��λ��Խ��\tPOSOV��ָ��λ��Խ��\t\tINSERR��ָ�����\
	VELLIM���ٶȳ���\t\tACCLIM�����ٶȳ���\t\tDELPOS��ָ��λ���쳣\tORG:ԭ�㵽λ\n\n\r\
���б����ȫ��0ʱ����ʾû�д���\r\n\
���б���ж�Ӧ������1���������Ӧ�Ĵ�������");
	SetDlgItemText(IDC_STATIC_TEXT, str);
	InitListCtrl();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CErrdlg::InitListCtrl()
{
	int i = 0;
	DWORD dwStyle = GetWindowLong(m_listCtl.m_hWnd, GWL_STYLE);
	dwStyle &= ~LVS_TYPEMASK;   //�����ʾ��ʽλ 
	dwStyle |= LVS_REPORT; //LVS_LIST;//���ñ�����
	dwStyle |= LVS_SHOWSELALWAYS; ///ʼ�ո�����ѡ�еı���
	//��ԭ����ʽ�Ļ����ϣ����LVS_REPORT��չ��ʽ
	SetWindowLong(m_listCtl.m_hWnd, GWL_STYLE, dwStyle);
	//��ȡ���е���չ��ʽ
	DWORD dwStyles = m_listCtl.GetExStyle();
	//ȡ����ѡ����ʽ
	dwStyles &= ~LVS_EX_CHECKBOXES;
	dwStyles |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES;
	//�������ѡ��ͱ������չ��ʽ
	m_listCtl.SetExtendedStyle(dwStyles);

	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP3);
	m_pImageList = new CImageList();
	m_pImageList->Create(17, 16, TRUE, 2, 2);
	m_pImageList->Add(&bitmap, RGB(0, 0, 0));
	m_listCtl.SetImageList(m_pImageList, LVSIL_SMALL);

	CHeaderCtrl* pHeaderCtrl = (CHeaderCtrl*)m_listCtl.GetHeaderCtrl();
	pHeaderCtrl->EnableWindow(FALSE);
	//������
	CString str;
	CRect rc;
	//**********************************************************************
	m_listCtl.GetClientRect(&rc);
	int width = rc.Width() - 32;
	m_listCtl.InsertColumn(0, _T("��"), LVCFMT_CENTER, 30);
	m_listCtl.InsertColumn(1, _T("PLim"), LVCFMT_CENTER, 50);
	m_listCtl.InsertColumn(2, _T("NLim"), LVCFMT_CENTER, 50);
	m_listCtl.InsertColumn(3, _T("PSOF"), LVCFMT_CENTER, 50);
	m_listCtl.InsertColumn(4, _T("NSOF"), LVCFMT_CENTER, 50);
	m_listCtl.InsertColumn(5, _T("Stop"), LVCFMT_CENTER, 50);
	m_listCtl.InsertColumn(6, _T("ALM"), LVCFMT_CENTER, 50);
	m_listCtl.InsertColumn(7, _T("POSLIM"), LVCFMT_CENTER, 50);
	m_listCtl.InsertColumn(8, _T("TGPOSOV"), LVCFMT_CENTER, 70);
	m_listCtl.InsertColumn(9, _T("POSOV"), LVCFMT_CENTER, 50);
	m_listCtl.InsertColumn(10, _T("INSERR"), LVCFMT_CENTER, 50);
	m_listCtl.InsertColumn(11, _T("VELLIM"), LVCFMT_CENTER, 50);
	m_listCtl.InsertColumn(12, _T("ACCLIM"), LVCFMT_CENTER, 50);
	m_listCtl.InsertColumn(13, _T("DELPOS"), LVCFMT_CENTER, 50);
	m_listCtl.InsertColumn(14, _T("ORG"), LVCFMT_CENTER, 50);
	//*********************************************************************

	LVCOLUMN col;
	col.mask = LVCF_FMT;
	col.fmt = LVCFMT_CENTER;
	m_listCtl.SetColumn(0, &col);
}


void CErrdlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO:  �ڴ˴������Ϣ����������
	CString str;
	if (bShow)
	{
		memset(m_err, -1, sizeof(WORD) * 16);
		memset(m_showIo, -1, sizeof(WORD) * 2 * 6);
		m_listCtl.DeleteAllItems();
		for (int i = 0; i < 2; i++)
		{
			m_listCtl.InsertItem(i, _T(""), -1);
			switch (i)
			{
			case 0:
				str = _T("X");
				break;
			case 1:
				str = _T("Y");
				break;
			default:
				break;
			}

			m_listCtl.SetItemText(i, 0, str);
		}
		SetTimer(3, 40, NULL);
	}
	else
		KillTimer(3);
}

/*
error�Ĵ�����bit�ĺ���
bit0:	����Ӳ����Խ��
bit1:	����Ӳ����Խ��
bit2:	��������Խ��
bit3:	��������Խ��
bit4:	ֹͣλ
bit5:	��
bit6:	�ŷ�����
bit7:	λ������
bit8:	��
bit9:	Ŀ��λ��Խ��
bit10:	ָ��λ��Խ��
bit11:	��
bit12:	ָ�����
bit13:	�ٶȳ���
bit14:	���ٶȳ���
bit15:	ָ��λ���쳣
*/

void CErrdlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	WORD err[16];
	WORD tmp_Io[6][6];
	int i, k, n;
	switch (nIDEvent)
	{
	case 3:
		int st = PKG_IMC_GetErrorReg(m_handle, err, 6);
		if (st)
		{
			for (i = 0; i < 2; i++)
			{
				if (err[i] != m_err[i])
				{
					m_err[i] = err[i];
					for (k = 0; k < 5; k++)
					{
						if (m_err[i] & (1 << k))
							m_listCtl.SetItem(i, 1 + k, LVIF_TEXT | LVIF_IMAGE, _T(""), 0, NULL, NULL, 0); //
						else
							m_listCtl.SetItem(i, 1 + k, LVIF_TEXT | LVIF_IMAGE, _T(""), 1, NULL, NULL, 0); //
					}
					n = k;
					for (k = 6; k < 8; k++)
					{
						if (m_err[i] & (1 << k))
							m_listCtl.SetItem(i, 1 + n, LVIF_TEXT | LVIF_IMAGE, _T(""), 0, NULL, NULL, 0); //
						else
							m_listCtl.SetItem(i, 1 + n, LVIF_TEXT | LVIF_IMAGE, _T(""), 1, NULL, NULL, 0); //
						n++;
					}
					for (k = 9; k < 11; k++)
					{
						if (m_err[i] & (1 << k))
							m_listCtl.SetItem(i, 1 + n, LVIF_TEXT | LVIF_IMAGE, _T(""), 0, NULL, NULL, 0); //
						else
							m_listCtl.SetItem(i, 1 + n, LVIF_TEXT | LVIF_IMAGE, _T(""), 1, NULL, NULL, 0); //
						n++;
					}
					for (k = 12; k < 16; k++)
					{
						if (m_err[i] & (1 << k))
							m_listCtl.SetItem(i, 1 + n, LVIF_TEXT | LVIF_IMAGE, _T(""), 0, NULL, NULL, 0); //
						else
							m_listCtl.SetItem(i, 1 + n, LVIF_TEXT | LVIF_IMAGE, _T(""), 1, NULL, NULL, 0); //
						n++;
					}
				}
			}
		}
		st = PKG_IMC_GetAin(m_handle, tmp_Io, 6);
		if (st)
		{
			int i;
			int j = 2;
			for (i = 0; i < 2; i++)
			{
				if (m_showIo[i][j] != tmp_Io[i][j])
				{
					if (!tmp_Io[i][j])
					{
						m_listCtl.SetItem(i, 14, LVIF_TEXT | LVIF_IMAGE, _T(""), 0, NULL, NULL, 0);
					}
					else
						m_listCtl.SetItem(i, 14, LVIF_TEXT | LVIF_IMAGE, _T(""), 1, NULL, NULL, 0);
					m_showIo[i][j] = tmp_Io[i][j];
				}
			}
		}
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}
