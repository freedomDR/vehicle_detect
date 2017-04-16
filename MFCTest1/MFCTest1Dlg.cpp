
// MFCTest1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCTest1.h"
#include "MFCTest1Dlg.h"
#include "afxdialogex.h"
#include "MyTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCTest1Dlg 对话框



CMFCTest1Dlg::CMFCTest1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCTEST1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTest1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHARE, picture_share);
	DDX_Control(pDX, PAUSE, stopbtn);
	DDX_Control(pDX, IDC_EDIT1, show_text);
}

BEGIN_MESSAGE_MAP(CMFCTest1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(PAUSE, &CMFCTest1Dlg::OnBnClickedPause)
	ON_BN_CLICKED(IDC_BTN_END, &CMFCTest1Dlg::OnBnClickedBtnEnd)
	ON_BN_CLICKED(BTNSTART, &CMFCTest1Dlg::OnBnClickedBtnstart)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCTest1Dlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CMFCTest1Dlg 消息处理程序

BOOL CMFCTest1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	namedWindow("view", WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle("view");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_SHARE)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	CRect rc;
	CWnd *pWnd = GetDlgItem(IDC_SHARE);//IDC_PIC_2D为控件ID
	pWnd->GetClientRect(&rc);//rc为控件的大小。
	picture_x = rc.Height();
	picture_y = rc.Width();


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCTest1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCTest1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCTest1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

UINT CMFCTest1Dlg::PlayVideo(LPVOID pParam)
{
	VideoCapture capture("D:\\video_test_1.mp4");
	//VideoCapture capture(0);
	Mat pictureBackground;
	int frame_order = 0;
	//VideoCapture capture(0);
	CMFCTest1Dlg* this_back = (CMFCTest1Dlg*)pParam;

	
	while (1)
	{
		MSG my_msg;
		if(PeekMessage(&my_msg, 0, 0, 0, PM_REMOVE)) 
		{
			if (my_msg.message == WM_QUIT)
			{
				capture.release();
				return 0;
			}
		}
		else 
		{
			Mat frame;
			if (CMFCTest1Dlg::playFlag == 1)
			{
				capture.set(CV_CAP_PROP_POS_FRAMES, 0);
				CMFCTest1Dlg::playFlag = 0;
				frame_order = 0;
			}
			if (CMFCTest1Dlg::playFlag == 0)
			{
				//第一种处理方法
				
				CMFCTest1Dlg::FirstDeal(pParam, capture,pictureBackground);
				frame_order++;
			}
			if (CMFCTest1Dlg::playFlag == 3)
			{
				break;
			}
			waitKey(30);
		}
	}
	capture.release();
	return 0;
}



bool CMFCTest1Dlg::FirstDeal(LPVOID param, VideoCapture& capture,Mat& pictureBackground)
{
	int frame_order = capture.get(CV_CAP_PROP_POS_FRAMES);
	Mat frame;
	CMFCTest1Dlg* this_back = (CMFCTest1Dlg*)param;
	if (frame_order % 10 == 0)
	{
		pictureBackground = MyTools::getPictureBackground(capture, frame_order);
		medianBlur(pictureBackground, pictureBackground, 3);
		//
		Mat mid_three;
		resize(pictureBackground, mid_three, Size(this_back->picture_y, this_back->picture_x));
		imshow("背景图", mid_three);
		imwrite("lala.jpg", pictureBackground);

	}
	//cvtColor(pictureBackground, mid, COLOR_BGR2GRAY);
	//Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//Mat dstImage;
	//erode(frame, dstImage, element);
	//blur(mid, mid, Size(7, 7));
	//Canny(mid, mid, 0, 30, 3);

	if (!capture.read(frame)) return false;
	Mat mid;
	cvtColor(frame, frame, COLOR_BGR2GRAY);
	medianBlur(frame, frame, 3);

	Mat mid_one, mid_two;
	resize(frame, mid_one, Size(this_back->picture_y, this_back->picture_x));
	imshow("frame_median.jpg", mid_one);
	subtract(frame, pictureBackground, frame);
	resize(frame, mid_two, Size(this_back->picture_y, this_back->picture_x));
	imshow("差分图.jpg", mid_two);

	//重置大小，满足需求
	Mat des = Mat::zeros(this_back->picture_x, this_back->picture_y, CV_8UC3);
	resize(frame, des, des.size());


	Mat dst;
	double thres_value;
	thres_value = threshold(des, dst, 0, 255, CV_THRESH_OTSU);

	//Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	//erode(dst, dst, element);

	CString mid_value;
	mid_value.Format(L"%lf", thres_value);
	//this_back->show_text.SetWindowTextW(mid_value);
	this_back->SetDlgItemText(IDC_EDIT1, mid_value);


	imshow("view", dst);
	return false;
}

void CMFCTest1Dlg::OnBnClickedPause()
{
	CString buttonText;
	stopbtn.GetWindowText(buttonText);

	if (CMFCTest1Dlg::playFlag != 0)
	{
		CMFCTest1Dlg::playFlag = 0;
		stopbtn.SetWindowTextW(_T("继续"));

	}
	else
	{
		CMFCTest1Dlg::playFlag = 2;
		stopbtn.SetWindowText(_T("暂停"));
	}
}


void CMFCTest1Dlg::OnBnClickedBtnEnd()
{
	CMFCTest1Dlg::playFlag = 3;
	::PostThreadMessage(playThread->m_nThreadID, WM_QUIT, 0, 0);
}


void CMFCTest1Dlg::OnBnClickedBtnstart()
{
	//LPVOID param;
	int mid = CMFCTest1Dlg::playFlag;
	CMFCTest1Dlg::playFlag = 1;
	if (mid != 2 || playThread == NULL)
	{
		//LPVOID param;
		playThread = AfxBeginThread(PlayVideo,this, 0, 0, 0, 0);
	}
}

int CMFCTest1Dlg::playFlag = 2;

void CMFCTest1Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


