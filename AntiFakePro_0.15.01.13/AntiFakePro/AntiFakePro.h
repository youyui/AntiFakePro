
// AntiFakePro.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAntiFakeProApp:
// �йش����ʵ�֣������ AntiFakePro.cpp
//

class CAntiFakeProApp : public CWinApp
{
public:
	CAntiFakeProApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAntiFakeProApp theApp;