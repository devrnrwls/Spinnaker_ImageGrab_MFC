
// Spinnaker_ImageGrab_MFCDlg.h : 헤더 파일
//

#pragma once

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"
//#include <opencv2/opencv.hpp>
//#include <opencv2/core/types_c.h>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgcodecs.hpp>
#include "afxwin.h"
#include "afxcmn.h"
#include "stdafx.h"

#include "../../opencv/build/include/opencv2/opencv.hpp"      
#include "../../opencv/build/include/opencv2/highgui/highgui.hpp"      
#include "../../opencv/build/include/opencv2/core/core.hpp"
#include "../../opencv/build/include/opencv2/imgproc/imgproc.hpp"
#pragma comment(lib, "../../opencv/build/x86/vc11/lib/opencv_ts300.lib")
#pragma comment(lib, "../../opencv/build/x86/vc11/lib/opencv_world300.lib")


using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;
using namespace cv;

// CSpinnaker_ImageGrab_MFCDlg 대화 상자
class CSpinnaker_ImageGrab_MFCDlg : public CDialogEx
{
// 생성입니다.
public:
	CSpinnaker_ImageGrab_MFCDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPINNAKER_IMAGEGRAB_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
	int resolution_factor;
	int interval;
	int min_grid;
	int hsv_limit;

	bool m_ThreadContinue;
	HANDLE m_heventThreadDone;
	static UINT threadGrab(LPVOID pParam);
	UINT GrabLoop(void);
	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton2();
	CEdit m_resolution;
	CEdit m_interval;
	CEdit m_min_grid;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CEdit m_hsv_limit;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_sldTest;
	CEdit m_edTest;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditTest();	
};
