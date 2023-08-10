
// Spinnaker_ImageGrab_MFCDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Spinnaker_ImageGrab_MFC.h"
#include "Spinnaker_ImageGrab_MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CSpinnaker_ImageGrab_MFCDlg ��ȭ ����



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


// CSpinnaker_ImageGrab_MFCDlg �޽��� ó����

BOOL CSpinnaker_ImageGrab_MFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CSpinnaker_ImageGrab_MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CSpinnaker_ImageGrab_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


UINT CSpinnaker_ImageGrab_MFCDlg::threadGrab(LPVOID pParam)
{
	CSpinnaker_ImageGrab_MFCDlg* pDlg = ((CSpinnaker_ImageGrab_MFCDlg*)pParam);
	UINT Retval = pDlg->GrabLoop();
	SetEvent(pDlg->m_heventThreadDone); // �̺�Ʈ��Set ��
	return Retval;
}

UINT CSpinnaker_ImageGrab_MFCDlg::GrabLoop(void)
{
	//unsigned int SerialNumber=111111;
	// ī�޶� GUID ȹ��
	m_camera = m_camList.GetByIndex(0);
	//serialnumber
	//m_error=m_BusManager.GetCameraFromSerialNumber(SerialNumber,&m_Guid);
	// ī�޶� ����
	m_camera->Init();

	// ���� ȹ�� ����
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	ptrSystem = System::GetInstance();
	m_camList = ptrSystem->GetCameras();
	m_ThreadContinue = true;
	CWinThread *pThread = ::AfxBeginThread(threadGrab, this); // thread ����
}


void CSpinnaker_ImageGrab_MFCDlg::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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

	CloseHandle(m_heventThreadDone); // �ڵ�����

	CDialogEx::OnClose();
}
