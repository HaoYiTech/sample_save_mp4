
// sample_save_mp4.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Csample_save_mp4App:
// �йش����ʵ�֣������ sample_save_mp4.cpp
//

class Csample_save_mp4App : public CWinApp
{
public:
	Csample_save_mp4App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Csample_save_mp4App theApp;