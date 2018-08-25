#pragma once
#include "afxwin.h"


// CDevicedlg 对话框

class CDevicedlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDevicedlg)

public:
	CDevicedlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDevicedlg();

// 对话框数据
	enum { IDD = IDD_DLG_DEVICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedDeviceButton2();
	afx_msg void OnBnClickedDeviceButton1();
	afx_msg void OnLbnSelchangeDeviceList1();
	afx_msg void OnBnClickedDeviceButton3();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_Dtemperature;
	CListBox m_Listbox;
	float m_Setsv[11];
};
