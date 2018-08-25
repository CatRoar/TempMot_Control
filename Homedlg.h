#pragma once
#include "afxwin.h"


// CHomedlg 对话框

class CHomedlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHomedlg)

public:
	CHomedlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHomedlg();

// 对话框数据
	enum { IDD = IDD_DLG_HOME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedHomeButton1();
	virtual BOOL OnInitDialog();
	CComboBox m_comBox1;
	CComboBox m_comBox2;
	CComboBox* m_comBoxArray[2];
	CEdit m_edit1;
	CEdit m_edit2;
	CEdit m_edit3;
	CEdit m_edit4;
	CEdit m_edit5;
	CEdit m_edit6;
	CEdit* m_editArray[6];
	HOME_INFO m_homeInfo[2];
	afx_msg void OnBnClickedHomeButton2();
};
