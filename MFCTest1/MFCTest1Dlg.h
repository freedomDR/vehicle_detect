
// MFCTest1Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"


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
private:
	int picture_x;
	int picture_y;
public:
	afx_msg void OnEnChangeEdit1();
	CEdit show_text;
};
