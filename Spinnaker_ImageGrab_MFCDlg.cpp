
// Spinnaker_ImageGrab_MFCDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Spinnaker_ImageGrab_MFC.h"
#include "Spinnaker_ImageGrab_MFCDlg.h"
#include "afxdialogex.h"
#include <time.h>
#include <string>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")




int m_hCurDevice;
struct usb_relay_device_info *m_pDeviceList;

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
	DDX_Control(pDX, IDC_EDIT1, m_resolution);
	DDX_Control(pDX, IDC_EDIT1, m_resolution);
	DDX_Control(pDX, IDC_EDIT2, m_interval);
	DDX_Control(pDX, IDC_EDIT3, m_min_grid);
	DDX_Control(pDX, IDC_EDIT4, m_hsv_limit);
	DDX_Control(pDX, IDC_SLIDER_Test, m_sldTest);
	DDX_Control(pDX, IDC_EDIT_TEST, m_edTest);
}

BEGIN_MESSAGE_MAP(CSpinnaker_ImageGrab_MFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON1, &CSpinnaker_ImageGrab_MFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON1, &CSpinnaker_ImageGrab_MFCDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON2, &CSpinnaker_ImageGrab_MFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSpinnaker_ImageGrab_MFCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CSpinnaker_ImageGrab_MFCDlg::OnBnClickedButton4)	
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_TEST, &CSpinnaker_ImageGrab_MFCDlg::OnEnChangeEditTest)
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
	CString strText = _T("3");
	m_resolution.SetWindowTextW(strText);	
	strText = _T("30");
	m_interval.SetWindowTextW(strText);
	strText = _T("10");
	m_min_grid.SetWindowTextW(strText);
	strText = _T("50");
	m_hsv_limit.SetWindowTextW(strText);

	resolution_factor = 3;
	interval = 20;
	min_grid = 10;
	hsv_limit = 50;

	SetIcon(m_hIcon, FALSE);
	m_sldTest.SetRange(0, 100);
	m_sldTest.SetPos(50);
	
	int iPos = m_sldTest.GetPos();
	CString sPos;
	sPos.Format(_T("%d"), iPos);
	m_edTest.SetWindowTextW(sPos);



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

	//ImagePtr pResultImage = m_camera->GetNextImage(1000);
	//ImagePtr convertedImage = pResultImage->Convert(PixelFormat_BGR8, HQ_LINEAR);

	////cv로 변환
	//unsigned int XPadding = convertedImage->GetXPadding();
	//unsigned int YPadding = convertedImage->GetYPadding();
	//unsigned int rowsize = convertedImage->GetWidth();
	//unsigned int colsize = convertedImage->GetHeight();
	CDC *pDC = GetDlgItem(IDC_PC_VIEW)->GetDC(); //Get the picture control DC
	Mat img_blur;
	Mat gray;
	Mat inv_fg_mask;
	Mat inv_crop_fg_mask;
	vector<vector<Point> > contours;
	vector<vector<Point> > cropped_contours;
	vector<Vec4i> hierarchy;
	vector<Vec4i> cropped_hierarchy;
	RNG rng(12345);
	Scalar color = Scalar(255, 255, 255);
	
	
	/*CString strText = _T("1");
	m_interval.SetWindowTextW(strText);
	interval = _ttoi(strText);
	m_min_grid.SetWindowTextW(strText);
	min_grid = _ttoi(strText);*/
		

	//pResultImage->Release();
	
	clock_t begin = 0;
	CString strText = _T("1");
	while (m_ThreadContinue)
	{
		try
		{
			
			m_resolution.GetWindowTextW(strText);
			resolution_factor = _ttoi(strText);
			m_interval.GetWindowTextW(strText);
			interval = _ttoi(strText);
			m_min_grid.GetWindowTextW(strText);
			min_grid = _ttoi(strText);
			/*m_hsv_limit.GetWindowTextW(strText);
			hsv_limit = _ttoi(strText);*/
			m_edTest.GetWindowTextW(strText);
			hsv_limit = _ttoi(strText);
			hsv_limit = 100 - hsv_limit;

			ImagePtr pResultImage = m_camera->GetNextImage();			
			clock_t end = clock();
			
			//double st = getTickCount();
			cout << (double)(end - begin) / CLOCKS_PER_SEC << endl;			
			begin = end;
			

			//cout << fps << endl;
			ImagePtr convertedImage = pResultImage->Convert(PixelFormat_BGR8, HQ_LINEAR);
			unsigned int XPadding = convertedImage->GetXPadding();
			unsigned int YPadding = convertedImage->GetYPadding();
			unsigned int rowsize = convertedImage->GetWidth();
			unsigned int colsize = convertedImage->GetHeight();			

			if (pResultImage->IsIncomplete())
			{
				// Retrieve and print the image status description
				cout << "Image incomplete: " << Image::GetImageStatusDescription(pResultImage->GetImageStatus())
					<< "..." << endl
					<< endl;
			}
			else
			{
				//cv변환
				Mat image = cv::Mat(colsize + YPadding, rowsize + XPadding, CV_8UC3, convertedImage->GetData(), convertedImage->GetStride());

				//contour
				resize(image, image, cv::Size(image.cols / resolution_factor, image.rows / resolution_factor), 0, 0, INTER_LINEAR);
				GaussianBlur(image, img_blur, Size(7, 7), 0);

				cvtColor(img_blur, gray, COLOR_BGR2GRAY);
				threshold(gray, inv_fg_mask, 250, 255, THRESH_BINARY_INV);
				findContours(inv_fg_mask, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

				vector<vector<Point> > contours_poly(contours.size());
				vector<Rect> boundRect(contours.size());

				if (contours.size() > 0)
				{
					for (size_t i = 0; i < contours.size(); i++)
					{
						approxPolyDP(contours[i], contours_poly[i], 3, true);
						boundRect[i] = boundingRect(contours_poly[i]);

						//if ((boundRect[i].width > interval - 1) && (boundRect[i].height > interval - 1))
						if ((boundRect[i].width > min_grid) && (boundRect[i].height > min_grid))
						{
							vector<Point> rect_points; //초기화
							rect_points.push_back(boundRect[i].tl()); //시작점 넣기(x,y)
							rect_points.push_back(boundRect[i].br()); //끝점 넣기(x,y)
							Mat cropped_img = Mat::zeros(boundRect[i].height, boundRect[i].width, CV_8UC3);
							cropped_img = image(Range(rect_points[0].y, rect_points[1].y), Range(rect_points[0].x, rect_points[1].x));

							int rows = cropped_img.rows;
							int cols = cropped_img.cols;
							int total = cropped_img.cols* cropped_img.channels();

							for (int j = 0; j < cols; j++)
							{
								if (j % interval == 0)
								{
									for (int k = 0; k < rows; k++)
									{
										cropped_img.at<Vec3b>(k, j)[0] = 255;
										cropped_img.at<Vec3b>(k, j)[1] = 255;
										cropped_img.at<Vec3b>(k, j)[2] = 255;
									}
								}
							}

							for (int j = 0; j < rows; j++)
							{
								if (j % interval == 0)
								{
									for (int k = 0; k < cols; k++)
									{
										cropped_img.at<Vec3b>(j, k)[0] = 255;
										cropped_img.at<Vec3b>(j, k)[1] = 255;
										cropped_img.at<Vec3b>(j, k)[2] = 255;
									}
								}
							}

							Mat cropped_gray;
							cvtColor(cropped_img, cropped_gray, COLOR_BGR2GRAY);
							threshold(cropped_gray, inv_crop_fg_mask, 250, 255, THRESH_BINARY_INV);
							findContours(inv_crop_fg_mask, cropped_contours, cropped_hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
							vector<vector<Point> > contours_crop_poly(cropped_contours.size());
							vector<Rect> cropped_boundRect(contours_crop_poly.size());

							for (size_t j = 0; j < cropped_contours.size(); j++)
							{
								approxPolyDP(cropped_contours[j], contours_crop_poly[j], 3, true);
								cropped_boundRect[j] = boundingRect(contours_crop_poly[j]);

								vector<Point> path_rect_points; //초기화
								path_rect_points.push_back(cropped_boundRect[j].tl()); //시작점 넣기(x,y)
								path_rect_points.push_back(cropped_boundRect[j].br()); //끝점 넣기(x,y)							

																					   //if (cropped_boundRect[j].width > (interval - 1) && cropped_boundRect[j].height > (interval - 1))
								if (cropped_boundRect[j].width > 10 && cropped_boundRect[j].height > 10)   //위로 올려야될듯?
								{

									Mat path_img = Mat::zeros(cropped_boundRect[j].height, cropped_boundRect[j].width, CV_8UC3);
									path_img = cropped_img(Range(path_rect_points[0].y, path_rect_points[1].y), Range(path_rect_points[0].x, path_rect_points[1].x));

									Mat path_hsv = Mat::zeros(cropped_boundRect[j].height, cropped_boundRect[j].width, CV_8UC3);
									cvtColor(path_img, path_hsv, COLOR_BGR2HSV);	
									path_hsv = path_img;
									//imwrite("ccc.png", path_img);
									int width = path_hsv.cols;
									int height = path_hsv.rows;
									int dims = path_hsv.channels();
									int numCluster = 2;
									int numSample = width * height;

									Mat points(numSample, dims, CV_64FC1);//The data in EM is 64-bit
									Mat labels;

									// Convert image RGB pixel data to sample data 
									int index = 0;
									int white_check = 0;
									for (int row = 0; row < height; row++) // The steps here are the same as KMeans
									{
										for (int col = 0; col < width; col++)
										{
											index = row * width + col;
											Vec3b bgr = path_hsv.at<Vec3b>(row, col);

											points.at<double>(index, 0) = static_cast<int>(bgr[0]);
											points.at<double>(index, 1) = static_cast<int>(bgr[1]);
											points.at<double>(index, 2) = static_cast<int>(bgr[2]);

											if (points.at<double>(index, 2) > 240)
											{
												white_check = 1;
												break;
											}
										}
										if (white_check == 1)
										{
											break;
										}
									}
									if (white_check == 0)
									{
										Ptr<ml::EM> em_model = ml::EM::create(); // Generate EM expectation maximization, and its image segmentation method is based on machine learning
										em_model->setClustersNumber(numCluster); // Set the number of categories
										em_model->setCovarianceMatrixType(ml::EM::COV_MAT_SPHERICAL); // Covariance matrix type
										em_model->setTermCriteria(TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1)); // Iterative conditions, EM training is more time-consuming than KMeans and may not converge, so the number of iterations should be larger
										em_model->trainEM(points, noArray(), labels, noArray()); // EM training, to obtain the classification results, the parameters of labels and KMeans have the same meaning, and the speed is much slower than KMeans
										Mat em_mean = em_model->getMeans();

										double em_result[6] = { 0, }; //em_mean.rows * em_mean.cols										

										int em_index = 0;
										//cout << em_mean << endl;
										for (int row = 0; row < em_mean.rows; row++) // The steps here are the same as KMeans
										{

											for (int col = 0; col < em_mean.cols; col++)
											{
												em_index = row * em_mean.cols + col;
												double bgr = em_mean.at<double>(row, col);
												em_result[em_index] = bgr;
											}
										}

										int h_diff = abs(em_result[0] - em_result[3]);
										int s_diff = abs(em_result[1] - em_result[4]);
										int v_diff = abs(em_result[2] - em_result[5]);

										//if (h_diff > hsv_limit || s_diff > hsv_limit || v_diff > hsv_limit)
										if (v_diff > hsv_limit)
										{
											Scalar foreig_nobject = Scalar(0, 0, 255);
											rectangle(cropped_img, cropped_boundRect[j].tl(), cropped_boundRect[j].br(), foreig_nobject, 2);

											//usb_relay_device_open_one_relay_channel(m_hCurDevice, 1);
											//Sleep(1);
											//usb_relay_device_close_all_relay_channel(m_hCurDevice);
										}
									}
								}
							}
							//cvtColor(cropped_img, cropped_img, COLOR_BGR2HSV);
							//imwrite("bbb.png", cropped_img);
							//imshow("Result window", cropped_img);
							//waitKey(0);
							//m_bitmapInfo.bmiHeader.biWidth = cropped_img.cols;
							//m_bitmapInfo.bmiHeader.biHeight = -cropped_img.rows;
							//StretchDIBits(m_pDC->GetSafeHdc(), 10, 10, 320, 240, 0, 0, cropped_img.cols, cropped_img.rows, cropped_img.data, &m_bitmapInfo, DIB_RGB_COLORS, SRCCOPY);

							CRect rect;
							GetDlgItem(IDC_PC_VIEW)->GetClientRect(&rect); // Get the picture control rectangle
							resize(cropped_img, cropped_img, cv::Size(rect.Width(), rect.Height())); // Scale the Mat to fit the size of the image control

																									 // Convert format for easy access to BITMAPINFO
							switch (cropped_img.channels())
							{
							case 1:
								cvtColor(cropped_img, cropped_img, CV_GRAY2BGRA); // GRAY single channel
								break;
							case 3:
								cvtColor(cropped_img, cropped_img, CV_BGR2BGRA); // BGR three channels
								break;
							default:
								break;
							}

							int nPixelBytes = cropped_img.channels() * (cropped_img.depth() + 1); // Calculate how many bytes in a pixel

							BITMAPINFO bitInfo;
							bitInfo.bmiHeader.biBitCount = 8 * nPixelBytes;
							bitInfo.bmiHeader.biWidth = cropped_img.cols;
							bitInfo.bmiHeader.biHeight = -cropped_img.rows; //Note the "-" sign (draw when facing a positive number)
							bitInfo.bmiHeader.biPlanes = 1;
							bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
							bitInfo.bmiHeader.biCompression = BI_RGB;
							bitInfo.bmiHeader.biClrImportant = 0;
							bitInfo.bmiHeader.biClrUsed = 0;
							bitInfo.bmiHeader.biSizeImage = 0;
							bitInfo.bmiHeader.biXPelsPerMeter = 0;
							bitInfo.bmiHeader.biYPelsPerMeter = 0;
							//Drawing
							StretchDIBits(
								pDC->GetSafeHdc(),
								0, 0, rect.Width(), rect.Height(),
								0, 0, cropped_img.cols, cropped_img.rows,
								cropped_img.data,
								&bitInfo,
								DIB_RGB_COLORS,
								SRCCOPY
							);
						}
					}
				}
				else
				{
					CRect rect;
					GetDlgItem(IDC_PC_VIEW)->GetClientRect(&rect); // Get the picture control rectangle
					Mat cropped_img = image.clone();
					resize(cropped_img, cropped_img, cv::Size(rect.Width(), rect.Height())); // Scale the Mat to fit the size of the image control

																							 // Convert format for easy access to BITMAPINFO
					switch (cropped_img.channels())
					{
					case 1:
						cvtColor(cropped_img, cropped_img, CV_GRAY2BGRA); // GRAY single channel
						break;
					case 3:
						cvtColor(cropped_img, cropped_img, CV_BGR2BGRA); // BGR three channels
						break;
					default:
						break;
					}

					int nPixelBytes = cropped_img.channels() * (cropped_img.depth() + 1); // Calculate how many bytes in a pixel

					BITMAPINFO bitInfo;
					bitInfo.bmiHeader.biBitCount = 8 * nPixelBytes;
					bitInfo.bmiHeader.biWidth = cropped_img.cols;
					bitInfo.bmiHeader.biHeight = -cropped_img.rows; //Note the "-" sign (draw when facing a positive number)
					bitInfo.bmiHeader.biPlanes = 1;
					bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
					bitInfo.bmiHeader.biCompression = BI_RGB;
					bitInfo.bmiHeader.biClrImportant = 0;
					bitInfo.bmiHeader.biClrUsed = 0;
					bitInfo.bmiHeader.biSizeImage = 0;
					bitInfo.bmiHeader.biXPelsPerMeter = 0;
					bitInfo.bmiHeader.biYPelsPerMeter = 0;
					//Drawing
					StretchDIBits(
						pDC->GetSafeHdc(),
						0, 0, rect.Width(), rect.Height(),
						0, 0, cropped_img.cols, cropped_img.rows,
						cropped_img.data,
						&bitInfo,
						DIB_RGB_COLORS,
						SRCCOPY
					);
				}

				
				//double en = getTickCount();
				//double fps = 1000 / (en - st) / getTickFrequency();
				//cout << "fps : " << fps << endl;
				pResultImage->Release();
			}			
		}
		catch (Spinnaker::Exception &e)
		{
			cout << "Error: " << e.what() << endl;
		}
	}

	ReleaseDC(m_pDC);
	ReleaseDC(pDC);
	SetEvent(m_heventThreadDone);

	return 0;
}

void CSpinnaker_ImageGrab_MFCDlg::OnBnClickedButton1()
{	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	usb_relay_init();
	m_pDeviceList = usb_relay_device_enumerate();
	m_hCurDevice = usb_relay_device_open(m_pDeviceList);


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


void CSpinnaker_ImageGrab_MFCDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CString strText = _T("11");
	m_resolution.GetWindowTextW(strText);		
	resolution_factor = _ttoi(strText);	
}


void CSpinnaker_ImageGrab_MFCDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	CString strText = _T("11");
	m_interval.GetWindowTextW(strText);
	interval = _ttoi(strText);
}


void CSpinnaker_ImageGrab_MFCDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	CString strText = _T("11");
	m_resolution.GetWindowTextW(strText);
	min_grid = _ttoi(strText);
}


void CSpinnaker_ImageGrab_MFCDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CSpinnaker_ImageGrab_MFCDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	int iPos = m_sldTest.GetPos();
	
	CString sPos;
	sPos.Format(_T("%d"), iPos);
	m_edTest.SetWindowTextW(sPos);
	
	
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CSpinnaker_ImageGrab_MFCDlg::OnEnChangeEditTest()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString sPos;
	m_edTest.GetWindowTextW(sPos);
	int iPos = _ttoi(sPos);
	m_sldTest.SetPos(iPos);
}
