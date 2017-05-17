
// MFCTest1Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "Blob.h"
#include "afxmenubutton.h"
#include "VehicleDetector.h"
#include "PeopleDetector.h"


// CMFCTest1Dlg 对话框
class CMFCTest1Dlg : public CDialogEx
{
// 构造
public:
	CMFCTest1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTEST1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic picture_share;
	
public:
	static UINT PlayVideo(LPVOID pParam);
	CWinThread* playThread;
	CButton stopbtn;
	static int playFlag;
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedBtnEnd();
	afx_msg void OnBnClickedBtnstart();
public:
	int picture_x;
	int picture_y;
public:
	CEdit show_text;
	CEdit show_text2;
	vector<Blob> blobs; // 所有团块
	vector<Blob> pre_blobs; // 前一帧的团块
	vector<Blob> cur_blobs; // 当前帧的团块
	int count=0; // 车辆总数
	int count2=0;
	CSplitButton choose;
	afx_msg void OnUpdateCaption1(CCmdUI *pCmdUI);

	int frame_order;

	static const int VERICHL_COUNT = 1;//功能1 车辆检测
	static const int PEOPLE_DETECT = 2;//功能2 行人违规检测
	static const int NO_FUNCTION = -1;//未选择功能

	int current_func = NO_FUNCTION;//代表当前功能选择
	afx_msg void OnUpdateCaption2(CCmdUI *pCmdUI);
	VehicleDetector vehicleDetector;

	PeopleDetector peopleDetector;
};
