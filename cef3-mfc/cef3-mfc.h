
// cef3-mfc.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Ccef3mfcApp: 
// �йش����ʵ�֣������ cef3-mfc.cpp
//

class Ccef3mfcApp : public CWinApp
{
public:
	Ccef3mfcApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Ccef3mfcApp theApp;