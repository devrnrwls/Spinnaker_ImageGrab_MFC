
// Spinnaker_ImageGrab_MFCDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Spinnaker_ImageGrab_MFC.h"
#include "Spinnaker_ImageGrab_MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSpinnaker_ImageGrab_MFCDlg 대화 상자



CSpinnaker_ImageGrab_MFCDlg::CSpinnaker_ImageGrab_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SPINNAKER_IMAGEGRAB_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSpinnaker_ImageGrab_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSpinnaker_ImageGrab_MFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON1, &CSpinnaker_ImageGrab_MFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON1, &CSpinnaker_ImageGrab_MFCDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CSpinnaker_ImageGrab_MFCDlg 메시지 처리기

BOOL CSpinnaker_ImageGrab_MFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSpinnaker_ImageGrab_MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSpinnaker_ImageGrab_MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSpinnaker_ImageGrab_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


UINT CSpinnaker_ImageGrab_MFCDlg::threadGrab(LPVOID pParam)
{
	CSpinnaker_ImageGrab_MFCDlg* pDlg = ((CSpinnaker_ImageGrab_MFCDlg*)pParam);
	UINT Retval = pDlg->GrabLoop();
	SetEvent(pDlg->m_heventThreadDone); // 이벤트를Set 함
	return Retval;
}

UINT CSpinnaker_ImageGrab_MFCDlg::GrabLoop(void)
{
	//unsigned int SerialNumber=111111;
	// 카메라 GUID 획득
	m_camera = m_camList.GetByIndex(0);
	//serialnumber
	//m_error=m_BusManager.GetCameraFromSerialNumber(SerialNumber,&m_Guid);
	// 카메라 연결
	m_camera->Init();

	// 영상 획득 시작
	m_camera->BeginAcquisition();

	m_pDC = GetDC();
	m_pDC->SetStretchBltMode(COLORONCOLOR);
	m_bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_bitmapInfo.bmiHeader.biPlanes = 1;
	m_bitmapInfo.bmiHeader.biCompression = BI_RGB;
	m_bitmapInfo.bmiHeader.biXPelsPerMeter = 100;
	m_bitmapInfo.bmiHeader.biYPelsPerMeter = 100;
	m_bitmapInfo.bmiHeader.biClrUsed = 0;
	m_bitmapInfo.bmiHeader.biClrImportant = 0;
	m_bitmapInfo.bmiHeader.biBitCount = 24;
	m_bitmapInfo.bmiHeader.biSizeImage = 0;


	while (m_ThreadContinue)
	{
		try
		{

			ImagePtr pResultImage = m_camera->GetNextImage(1000);
			if (pResultImage->IsIncomplete())
			{
				// Retrieve and print the image status description
				cout << "Image incomplete: " << Image::GetImageStatusDescription(pResultImage->GetImageStatus())
					<< "..." << endl
					<< endl;
			}
			else
			{
				ImagePtr convertedImage = pResultImage->Convert(PixelFormat_BGR8, HQ_LINEAR);
				m_bitmapInfo.bmiHeader.biWidth = (int)convertedImage->GetWidth();
				m_bitmapInfo.bmiHeader.biHeight = -(int)convertedImage->GetHeight();
				StretchDIBits(m_pDC->GetSafeHdc(), 10, 10, 320, 240, 0, 0, convertedImage->GetWidth(), convertedImage->GetHeight(), convertedImage->GetData(), &m_bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
				pResultImage->Release();
			}
		}
		catch (Spinnaker::Exception &e)
		{
			cout << "Error: " << e.what() << endl;
		}
		

	}

	ReleaseDC(m_pDC);

	SetEvent(m_heventThreadDone);

	return 0;
}

void CSpinnaker_ImageGrab_MFCDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ptrSystem = System::GetInstance();
	m_camList = ptrSystem->GetCameras();
	m_ThreadContinue = true;
	CWinThread *pThread = ::AfxBeginThread(threadGrab, this); // thread 생성
}


void CSpinnaker_ImageGrab_MFCDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_ThreadContinue = false;

	DWORD dwRet = WaitForSingleObject(m_heventThreadDone, 3000);

	if (m_camera != nullptr)
	{
		if (m_camera->IsInitialized())
		{
			m_camera->EndAcquisition();
			m_camera->DeInit();
		}
		try
		{
			m_camera = NULL;
			m_camList.Clear();

			ptrSystem->ReleaseInstance();
		}
		catch (Spinnaker::Exception &e)
		{
			cout << "Error: " << e.what() << endl;
		}
	}

	CloseHandle(m_heventThreadDone); // 핸들종료

	CDialogEx::OnClose();
}
