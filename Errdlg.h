#pragma once
#include "afxcmn.h"


// CErrdlg 对话框

class CErrdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CErrdlg)

public:
	CErrdlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CErrdlg();

// 对话框数据
	enum { IDD = IDD_DLG_ERROR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	void InitListCtrl();
	CListCtrl m_listCtl;
	CImageList* m_pImageList;
	WORD m_err[16];
	WORD m_showIo[2][6];
	IMC_HANDLE m_handle;	//设备句柄
};
