#pragma once
#include "afxwin.h"
class ClistBoxEx : public CListBox
{
public:
	ClistBoxEx();
	~ClistBoxEx();

	// 覆盖该方法以便添加水平滚动条
	int AddString(LPCTSTR lpszItem);
	int InsertString(int nIndex, LPCTSTR lpszItem);
	// 计算水平滚动条宽度
	void RefushHorizontalScrollBar(void);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

