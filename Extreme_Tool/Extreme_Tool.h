
// Extreme_Tool.h : Extreme_Tool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CExtreme_ToolApp:
// �� Ŭ������ ������ ���ؼ��� Extreme_Tool.cpp�� �����Ͻʽÿ�.
//

class CExtreme_ToolApp : public CWinApp
{
public:
	CExtreme_ToolApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	//UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnIdle(LONG lCount);
};

extern CExtreme_ToolApp theApp;
