
// Spinnaker_ImageGrab_MFC.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CSpinnaker_ImageGrab_MFCApp:
// �� Ŭ������ ������ ���ؼ��� Spinnaker_ImageGrab_MFC.cpp�� �����Ͻʽÿ�.
//

class CSpinnaker_ImageGrab_MFCApp : public CWinApp
{
public:
	CSpinnaker_ImageGrab_MFCApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CSpinnaker_ImageGrab_MFCApp theApp;