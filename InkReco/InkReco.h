
// InkReco.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CInkRecoApp: 
// �йش����ʵ�֣������ InkReco.cpp
//

class CInkRecoApp : public CWinApp
{
public:
	CInkRecoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CInkRecoApp theApp;