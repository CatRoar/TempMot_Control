#pragma once
#include "afxwin.h"
class ClistBoxEx : public CListBox
{
public:
	ClistBoxEx();
	~ClistBoxEx();

	// ���Ǹ÷����Ա����ˮƽ������
	int AddString(LPCTSTR lpszItem);
	int InsertString(int nIndex, LPCTSTR lpszItem);
	// ����ˮƽ���������
	void RefushHorizontalScrollBar(void);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

