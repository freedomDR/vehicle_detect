// BasicInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCTest1.h"
#include "MFCTest1Dlg.h"
#include "BasicInfoDlg.h"
#include "afxdialogex.h"


// BasicInfoDlg 对话框

IMPLEMENT_DYNAMIC(BasicInfoDlg, CDialogEx)

BasicInfoDlg::BasicInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BASICINFODLG, pParent)
{

}

BasicInfoDlg::~BasicInfoDlg()
{
}

void BasicInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(BasicInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &BasicInfoDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &BasicInfoDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// BasicInfoDlg 消息处理程序


void BasicInfoDlg::OnBnClickedOk()
{
	this->ShowWindow(SW_HIDE);
	CMFCTest1Dlg dlg;
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
	::SendMessage(this->GetSafeHwnd(), WM_CLOSE, NULL, NULL);
}


void BasicInfoDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
