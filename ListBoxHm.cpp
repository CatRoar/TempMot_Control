// ListBoxHm.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Template_Control.h"
#include "ListBoxHm.h"


// CListBoxHm

IMPLEMENT_DYNAMIC(CListBoxHm, CListBox)

CListBoxHm::CListBoxHm()
{

}

CListBoxHm::~CListBoxHm()
{
}


BEGIN_MESSAGE_MAP(CListBoxHm, CListBox)
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


// CListBoxHm ��Ϣ�������


void CListBoxHm::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	POINT   pt;
	GetCursorPos(&pt);
	int nCount = GetCount();
	ScreenToClient(&pt);
	//ʵ���Ҽ����ѡ��Ŀ��
	for (int i = 0; i < nCount; i++)
	{
		CRect rc;

		GetItemRect(i, &rc);
		if (rc.PtInRect(pt))
		{
			SetCurSel(i);
			CMenu temp, *ptr;
			temp.LoadMenu(IDR_MENU1);
			ptr = temp.GetSubMenu(0);
			ClientToScreen(&pt);
			ptr->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, GetParent());

			break;
		}
	}
	CListBox::OnRButtonUp(nFlags, point);
}


int CListBoxHm::AddString(LPCTSTR lpszItem)
{
	int nResult = CListBox::AddString(lpszItem);
	RefushHorizontalScrollBar();
	return nResult;
}


int CListBoxHm::InsertString(int nIndex, LPCTSTR lpszItem)
{
	int nResult = CListBox::InsertString(nIndex, lpszItem);
	RefushHorizontalScrollBar();
	return nResult;
}


void CListBoxHm::RefushHorizontalScrollBar(void)
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
