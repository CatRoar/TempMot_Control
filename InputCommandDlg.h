#pragma once
#include "afxwin.h"
#include <vector>
using namespace std;


// CInputCommandDlg 对话框
static UINT WM_MY_MESSAGE = RegisterWindowMessage(_T("User"));

class CInputCommandDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInputCommandDlg)

public:
	CInputCommandDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInputCommandDlg();

// 对话框数据
	enum { IDD = IDD_DLG_INPUTCOMMAND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editDistX;
	CEdit m_editSpeedX;
	CEdit m_editAccX;
	CEdit m_editDistY;
	CEdit m_editSpeedY;
	CEdit m_editAccY;
	CEdit m_editWaitTime;
	CEdit m_editCycles;
	CEdit* m_pEditArray[6];
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedInputButton1();
	afx_msg void OnBnClickedInputButton2();
	afx_msg void OnBnClickedInputRadio1();
	afx_msg void OnBnClickedInputRadio2();

	class CCommandPack
	{
	public:
		//int numOfCycle;
		double waitTime;
		double axisPara[6];

		CCommandPack();
		void setValue(float waitTime, double* axis, double* dst);
	}commandPack;

	class CommandPackInfo
	{
	public:
		vector<CCommandPack> CommandPack;
		int numOfCycle;

		CommandPackInfo();
	}commandPackInfo;

	vector<CCommandPack> m_nCommadnArray;
	HWND m_hwnd;
	CButton m_checkX;
	CButton m_checkY;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	CListBox m_nInputDlgList;
	afx_msg void OnBnClickedButton1();
};
