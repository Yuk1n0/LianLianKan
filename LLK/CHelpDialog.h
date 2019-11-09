#pragma once

// CHelpDialog 对话框
class CHelpDialog : public CDialogEx
{
    DECLARE_DYNAMIC(CHelpDialog)
    
public:
    CHelpDialog(CWnd* pParent = nullptr);   // 标准构造函数
    virtual ~CHelpDialog();
    // 对话框数据
    #ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DIALOG_HELP };
    #endif
    
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    HICON m_hicon;
    CDC m_dcMem;
    CDC m_dcHelp;
    CRect m_rtHelp;
    DECLARE_MESSAGE_MAP()
};
