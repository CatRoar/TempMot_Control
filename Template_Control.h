
// Template_Control.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTemplate_ControlApp: 
// �йش����ʵ�֣������ Template_Control.cpp
//
#define INVALID_TEMP 3276.7

class CTemplate_ControlApp : public CWinApp
{
public:
	CTemplate_ControlApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTemplate_ControlApp theApp;