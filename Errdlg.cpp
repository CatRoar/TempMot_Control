// Errdlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Template_Control.h"
#include "Errdlg.h"
#include "afxdialogex.h"


// CErrdlg 对话框

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


// CErrdlg 消息处理程序


BOOL CErrdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	memset(m_err, -1, sizeof(WORD) * 16);
	memset(m_showIo, -1, sizeof(WORD) * 2 * 6);
	/*CString str = _T("错误类型：\
								\r\nPLim：硬件正限位\t\tNLim：硬件负限位\t\tStop：急停触发\
					 			\r\nPOSLIM：位置误差超限\tINSERR：指令错误\t\tVELLIM：速度超限\
								\r\nACCLIM：加速度超限\t\tDELPOS：指令位置异常\tORG:原点到位\
								\r当列表框中全是0时，表示没有错误。\
								\r当列表框中对应的列置1，则表明对应的错误发生。");*/
	CString str = _T("错误类型：\r\nPLim：硬件正限位\t\tNLim：硬件负限位\t\tPSOF：软正限位\t\tNSOF：软负限位\t\tStop：急停触发\
	ALM：伺服报警\t\tPOSLIM：位置误差超限\tTGPOSOV：目标位置越界\tPOSOV：指令位置越界\t\tINSERR：指令错误\
	VELLIM：速度超限\t\tACCLIM：加速度超限\t\tDELPOS：指令位置异常\tORG:原点到位\n\n\r\
当列表框中全是0时，表示没有错误。\r\n\
当列表框中对应的列置1，则表明对应的错误发生。");
	SetDlgItemText(IDC_STATIC_TEXT, str);
	InitListCtrl();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CErrdlg::InitListCtrl()
{
	int i = 0;
	DWORD dwStyle = GetWindowLong(m_listCtl.m_hWnd, GWL_STYLE);
	dwStyle &= ~LVS_TYPEMASK;   //清除显示方式位 
	dwStyle |= LVS_REPORT; //LVS_LIST;//设置报表风格
	dwStyle |= LVS_SHOWSELALWAYS; ///始终高亮被选中的表项
	//在原有样式的基本上，添加LVS_REPORT扩展样式
	SetWindowLong(m_listCtl.m_hWnd, GWL_STYLE, dwStyle);
	//获取已有的扩展样式
	DWORD dwStyles = m_listCtl.GetExStyle();
	//取消复选框样式
	dwStyles &= ~LVS_EX_CHECKBOXES;
	dwStyles |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES;
	//添加整行选择和表格线扩展样式
	m_listCtl.SetExtendedStyle(dwStyles);

	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP3);
	m_pImageList = new CImageList();
	m_pImageList->Create(17, 16, TRUE, 2, 2);
	m_pImageList->Add(&bitmap, RGB(0, 0, 0));
	m_listCtl.SetImageList(m_pImageList, LVSIL_SMALL);

	CHeaderCtrl* pHeaderCtrl = (CHeaderCtrl*)m_listCtl.GetHeaderCtrl();
	pHeaderCtrl->EnableWindow(FALSE);
	//设置列
	CString str;
	CRect rc;
	//**********************************************************************
	m_listCtl.GetClientRect(&rc);
	int width = rc.Width() - 32;
	m_listCtl.InsertColumn(0, _T("轴"), LVCFMT_CENTER, 30);
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

	// TODO:  在此处添加消息处理程序代码
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
error寄存器各bit的含义
bit0:	正向硬极限越界
bit1:	负向硬极限越界
bit2:	正向软极限越界
bit3:	负向软极限越界
bit4:	停止位
bit5:	无
bit6:	伺服报警
bit7:	位置误差超限
bit8:	无
bit9:	目标位置越界
bit10:	指令位置越界
bit11:	无
bit12:	指令错误
bit13:	速度超限
bit14:	加速度超限
bit15:	指令位置异常
*/

void CErrdlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
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
