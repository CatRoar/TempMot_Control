#pragma once

#include "afxwin.h"
#include <vector>
#include <Gdiplus.h>
#include "afxdtctl.h"

using namespace std;
using namespace Gdiplus;

// CGraphShowDlg 对话框

class CGraphShowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGraphShowDlg)

public:
	CGraphShowDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGraphShowDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	HICON		m_hIcon;
	ULONG_PTR m_pGdiToken;
	Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;
	CButton m_TempCheck1;
	CButton m_TempCheck2;
	CButton m_TempCheck3;
	CButton m_TempCheck4;
	CButton m_TempCheck5;
	CButton m_TempCheck6;
	CButton m_TempCheck7;
	CButton m_TempCheck8;
	CButton m_TempCheck9;
	CButton m_TempCheck10;
	CButton m_TempCheck11;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg BOOL OnInitDialog();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	bool m_ValidFlag[11];
	bool m_PaintFlag;
	Gdiplus::Rect m_Rect;
	Gdiplus::Rect m_RectBmp;
	Gdiplus::Bitmap *bitmap;
	RECT staticRect;
	RECT windowRect;
	CDC *pDC;

	afx_msg void OnBnClickedButton1();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedCheck8();
	afx_msg void OnBnClickedCheck9();
	afx_msg void OnBnClickedCheck10();
	afx_msg void OnBnClickedCheck11();

	BOOL StringToSysTime(CString strTimeStart, SYSTEMTIME *lpSystemTime);
	BOOL StringToData1(CString strTime, time_t *time1, time_t *time2, CString *FileName);
	BOOL StringToData2(CString strSrc, time_t *timet, float *time1, float *t2, float *t3,
		float *t4, float *t5, float *t6, float *t7, float *t8, float *t9,
		float *t10, float *t11);
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	int RePaint(Gdiplus::Bitmap *bitmap);
	CEdit m_TimeStartCtr;
	CEdit m_TimeEndCtr;
	CDateTimeCtrl m_TimeStart;
	CDateTimeCtrl m_DateStart;
	CDateTimeCtrl m_DateEnd;
	CDateTimeCtrl m_TimeEnd;
};
