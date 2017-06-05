#pragma once


// BasicInfoDlg 对话框

class BasicInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BasicInfoDlg)

public:
	BasicInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~BasicInfoDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BASICINFODLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();
};
