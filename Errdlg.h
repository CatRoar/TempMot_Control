#pragma once
#include "afxcmn.h"


// CErrdlg �Ի���

class CErrdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CErrdlg)

public:
	CErrdlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CErrdlg();

// �Ի�������
	enum { IDD = IDD_DLG_ERROR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	IMC_HANDLE m_handle;	//�豸���
};
