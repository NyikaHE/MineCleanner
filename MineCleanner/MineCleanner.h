
// MineCleanner.h : MineCleanner Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMineCleannerApp:
// �йش����ʵ�֣������ MineCleanner.cpp
//

class CMineCleannerApp : public CWinApp
{
public:
	CMineCleannerApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMineCleannerApp theApp;
