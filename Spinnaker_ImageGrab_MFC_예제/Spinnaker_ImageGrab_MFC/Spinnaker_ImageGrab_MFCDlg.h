
// Spinnaker_ImageGrab_MFCDlg.h : ��� ����
//

#pragma once

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;

// CSpinnaker_ImageGrab_MFCDlg ��ȭ ����
class CSpinnaker_ImageGrab_MFCDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CSpinnaker_ImageGrab_MFCDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPINNAKER_IMAGEGRAB_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	BITMAPINFO m_bitmapInfo;
	CDC* m_pDC;

	SystemPtr ptrSystem;
	CameraPtr m_camera;
	CameraList m_camList;
	CWinThread* m_pProcessThread;
	bool m_bProcessThread;

	bool m_ThreadContinue;
	HANDLE m_heventThreadDone;
	static UINT threadGrab(LPVOID pParam);
	UINT GrabLoop(void);
	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
};
