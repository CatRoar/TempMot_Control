#pragma once
#include "afxwin.h"


// CJogdlg 对话框

class CJogdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CJogdlg)

public:
	CJogdlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CJogdlg();

// 对话框数据
	enum { IDD = IDD_DLG_JOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedJogButton1();
	CEdit m_edit1;
	CEdit m_edit2;
	CEdit m_edit3;
	CEdit m_edit4;
	CEdit m_edit5;
	CEdit m_edit6;
	CEdit* m_editArray[6];
	JOG_INFO m_jogInfo[2];
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedJogButton2();
};
