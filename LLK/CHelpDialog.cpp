// CHelpDialog.cpp: 实现文件

#include "stdafx.h"
#include "LLK.h"
#include "CHelpDialog.h"
#include "afxdialogex.h"

// CHelpDialog 对话框

IMPLEMENT_DYNAMIC(CHelpDialog, CDialogEx)

CHelpDialog::CHelpDialog(CWnd *pParent /*=nullptr*/)
    : CDialogEx(IDD_DIALOG_HELP, pParent)
{
}

CHelpDialog::~CHelpDialog()
{
}

void CHelpDialog::DoDataExchange(CDataExchange *pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHelpDialog, CDialogEx)
END_MESSAGE_MAP()

// CHelpDialog 消息处理程序
