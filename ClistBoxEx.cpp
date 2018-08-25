#include "stdafx.h"
#include "ClistBoxEx.h"
#include "Resource.h"

ClistBoxEx::ClistBoxEx()
{
}


ClistBoxEx::~ClistBoxEx()
{
}


BEGIN_MESSAGE_MAP(ClistBoxEx, CListBox)
	ON_WM_MBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


void ClistBoxEx::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	
}


int ClistBoxEx::AddString(LPCTSTR lpszItem)
{
	int nResult = CListBox::AddString(lpszItem);
	RefushHorizontalScrollBar();
	return nResult;
}

int ClistBoxEx::InsertString(int nIndex, LPCTSTR lpszItem)
{
	int nResult = CListBox::InsertString(nIndex, lpszItem);
	RefushHorizontalScrollBar();
	return nResult;
}


void ClistBoxEx::RefushHorizontalScrollBar(void)
{
	CDC *pDC = this->GetDC();
	if (NULL == pDC)
	{
		return;
	}
	int nCount = this->GetCount();
	if (nCount < 1)
	{
		this->SetHorizontalExtent(0);
		return;
	}
	int nMaxExtent = 0;
	CString szText;
	for (int i = 0; i < nCount; ++i)
	{
		this->GetText(i, szText);
		CSize &cs = pDC->GetTextExtent(szText);
		if (cs.cx > nMaxExtent)
		{
			nMaxExtent = cs.cx;
		}
	}
	this->SetHorizontalExtent(nMaxExtent);
}


void ClistBoxEx::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CListBox::OnRButtonDown(nFlags, point);
}
