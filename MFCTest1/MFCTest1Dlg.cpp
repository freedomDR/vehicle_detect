
// MFCTest1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCTest1.h"
#include "MFCTest1Dlg.h"
#include "afxdialogex.h"
#include "MyTools.h"
#include "VehicleDetector.h"
#include "PeopleDetector.h"
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
	DDX_Control(pDX, IDC_SPLIT1, choose);
	DDX_Control(pDX, IDC_EDIT2,show_text2);
}

BEGIN_MESSAGE_MAP(CMFCTest1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(PAUSE, &CMFCTest1Dlg::OnBnClickedPause)
	ON_BN_CLICKED(IDC_BTN_END, &CMFCTest1Dlg::OnBnClickedBtnEnd)
	ON_BN_CLICKED(BTNSTART, &CMFCTest1Dlg::OnBnClickedBtnstart)
	ON_UPDATE_COMMAND_UI(ID_CAPTION1, &CMFCTest1Dlg::OnUpdateCaption1)
	ON_UPDATE_COMMAND_UI(ID_CAPTION2, &CMFCTest1Dlg::OnUpdateCaption2)
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

	namedWindow("vehicle", WINDOW_AUTOSIZE);
	//namedWindow("people",WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle("vehicle");
	//HWND hwndd = (HWND)cvGetWindowHandle("people");
	HWND hParent = ::GetParent(hWnd);
	//HWND hParentt = ::GetParent(hwndd);
	::SetParent(hWnd, GetDlgItem(IDC_SHARE)->m_hWnd);
	//::SetParent(hwndd,GetDlgItem(IDC_SHARE)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);
	//::ShowWindow(hParentt, SW_HIDE);
	setMouseCallback("vehicle", VehicleDetector::onMouseAction,(void*)&vehicleDetector);
	//setMouseCallback("vehicle", VehicleDetector::onMouseAction);

	CRect rc;
	CWnd *pWnd = GetDlgItem(IDC_SHARE);//IDC_PIC_2D为控件ID
	pWnd->GetClientRect(&rc);//rc为控件的大小。
	picture_x = rc.Height();
	picture_y = rc.Width();

	choose.SetDropDownMenu(IDR_MENU1,0);

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
	CMFCTest1Dlg* this_back = (CMFCTest1Dlg*)pParam;
	VideoCapture capture;
	
	if (this_back->current_func== VERICHL_COUNT)
	{
		capture.open("D:\\test.avi");
	}
	if (this_back->current_func == PEOPLE_DETECT) 
	{
		capture.open("D:\\格式工厂新行人检测视频1.mp4");
	}
	if (this_back->current_func == NO_FUNCTION)
	{
		return false;
	}
	int frame_order = 0;
	
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
				if (this_back->current_func == VERICHL_COUNT)
				{
					this_back->vehicleDetector.process(capture, pParam);
				}
				if (this_back->current_func == PEOPLE_DETECT)
				{
					this_back->peopleDetector.process2(capture, pParam);
					
				}
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
	count = 0;
	count2 = 0;
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

//选择车辆检测
void CMFCTest1Dlg::OnUpdateCaption1(CCmdUI *pCmdUI)
{
	choose.SetWindowTextW(L"车流量检测");
	current_func = VERICHL_COUNT;
}


void CMFCTest1Dlg::OnUpdateCaption2(CCmdUI *pCmdUI)
{
	choose.SetWindowTextW(L"行人检测");
	current_func = PEOPLE_DETECT;
}
