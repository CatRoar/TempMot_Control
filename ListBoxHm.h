#pragma once


// CListBoxHm

class CListBoxHm : public CListBox
{
	DECLARE_DYNAMIC(CListBoxHm)

public:
	CListBoxHm();
	virtual ~CListBoxHm();

	// ���Ǹ÷����Ա����ˮƽ������
	int AddString(LPCTSTR lpszItem);
	int InsertString(int nIndex, LPCTSTR lpszItem);
	// ����ˮƽ���������
	void RefushHorizontalScrollBar(void);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};


