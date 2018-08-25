#pragma once


// CListBoxHm

class CListBoxHm : public CListBox
{
	DECLARE_DYNAMIC(CListBoxHm)

public:
	CListBoxHm();
	virtual ~CListBoxHm();

	// 覆盖该方法以便添加水平滚动条
	int AddString(LPCTSTR lpszItem);
	int InsertString(int nIndex, LPCTSTR lpszItem);
	// 计算水平滚动条宽度
	void RefushHorizontalScrollBar(void);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};


