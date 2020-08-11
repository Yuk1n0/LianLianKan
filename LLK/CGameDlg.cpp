// CGameDlg.cpp : 实现文件

#include "afxdialogex.h"
#include "CGameControl.h"
#include "CGameDlg.h"
#include "CHelpDialog.h"
#include "LLK.h"
#include "stdafx.h"

// CGameDlg 对话框
IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIconW(IDR_MAINFRAME);

	m_ptGameTop.x = 50;
	m_ptGameTop.y = 50;

	// 单个元素图片大小的设置
	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;

	// 初始化游戏更新区域
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * 12;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * 12;

	// 初始点的标识
	m_bFirstPoint = true;
	m_bPlaying = false;
	m_bPause = false;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TIME, m_GameProgress);
}

void CGameDlg::Initbackground()
{
	// 获取当前对话框的视频内存
	CClientDC dc(this);
	// 加载bmp图片资源
	HANDLE bmp = ::LoadImageW(NULL, _T("theme\\picture\\fruit_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// 创建与视频内存兼容的内存DC
	m_dcBG.CreateCompatibleDC(&dc);
	// 将位图资源选入DC
	m_dcBG.SelectObject(bmp);

	// 初始化内存DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(bmpMem);

	// 绘制背景到内存DC中
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);

	UpdateWindow();
}

void CGameDlg::InitElement()
{
	CClientDC dc(this); // 获取当前对话框的视频内存

	HANDLE hbmp = ::LoadImageW(NULL, _T("theme\\picture\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); // 加载bmp图片资源

	m_dcElement.CreateCompatibleDC(&dc);
	m_dcElement.SelectObject(hbmp);

	HANDLE hmask = ::LoadImageW(NULL, _T("theme\\picture\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); // 加载bmp图片资源

	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(hmask);

	HANDLE hpause = ::LoadImageW(NULL, _T("theme\\picture\\fruit_pause.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); // 加载bmp图片资源
	m_dcPause.CreateCompatibleDC(&dc);
	m_dcPause.SelectObject(hpause);
}

void CGameDlg::DrawTipFrame(int nRow, int nCol) // 绘制边框
{
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}

void CGameDlg::DrawTipLine() // 连线
{
	CClientDC dc(this);
	CPen penLine(PS_SOLID, 3, RGB(0, 255, 0));
	CPen* pOldpen = dc.SelectObject(&penLine); // 将画笔选入DC
	dc.MoveTo(m_ptGameTop.x + m_ptSelFirst.col * m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + m_ptSelFirst.row * m_sizeElem.cy + m_sizeElem.cy / 2);
	dc.LineTo(m_ptGameTop.x + m_ptSelSec.col * m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + m_ptSelSec.row * m_sizeElem.cy + m_sizeElem.cy / 2);
	dc.SelectObject(pOldpen);
}

void CGameDlg::DrawTipLine(Vertex asvPath[2])
{
	CClientDC dc(this);
	CPen penLine(PS_SOLID, 3, RGB(0, 255, 0));
	CPen* pOldpen = dc.SelectObject(&penLine); // 将画笔选入DC
	dc.MoveTo(m_ptGameTop.x + asvPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + asvPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	dc.LineTo(m_ptGameTop.x + asvPath[1].col * m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + asvPath[1].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	dc.SelectObject(pOldpen);
}

void CGameDlg::DrawTipLine(Vertex asvPath[256], int nVexNum)
{
	// 获取DC
	CClientDC dc(this);

	// 设置画笔
	CPen penLine(PS_SOLID, 3, RGB(0, 255, 0));

	// 将画笔选进DC
	CPen* pOldPen = dc.SelectObject(&penLine);

	// 绘制连接线
	dc.MoveTo(m_ptGameTop.x + asvPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + asvPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	for (int i = 1; i < nVexNum; i++)
	{
		dc.LineTo(m_ptGameTop.x + asvPath[i].col * m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + asvPath[i].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}
	dc.SelectObject(pOldPen);
}

BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CGameDlg::OnClickedBtnStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON3, &CGameDlg::OnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CGameDlg::OnClickedButton4)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, &CGameDlg::OnClickedBtnStop)
	ON_BN_CLICKED(IDC_BUTTON6, &CGameDlg::OnClickedButton6)
END_MESSAGE_MAP()

// CGameDlg 消息处理程序

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: 在此添加额外的初始化

	Initbackground();
	InitElement();

	return TRUE; // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}

void CGameDlg::OnClickedBtnStart()
{
	// TODO: 在此添加控件通知处理程序代码
	m_gameControl.StartGame();
	m_bPlaying = true;
	this->GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);

	UpdateMap();
	Invalidate(FALSE);

	m_GameProgress.SetRange(0, 300);
	m_GameProgress.SetStep(-1);
	m_GameProgress.SetPos(300);
	this->SetTimer(PLAY_TIMER_ID, 1000, NULL);
}

void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.y < m_ptGameTop.y || point.x < m_ptGameTop.x)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
	if (nRow > 11 || nCol > 11)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	if (m_bFirstPoint)
	{
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetFirstPoint(nRow, nCol);
	}
	else
	{
		DrawTipFrame(nRow, nCol);
		// 判断是否是相同图片
		m_gameControl.SetSecPoint(nRow, nCol);
		Vertex avPath[256];
		int nVexNum = 0;
		if (m_gameControl.Link(avPath, nVexNum))
		{
			DrawTipLine(avPath, nVexNum);
			//			DrawTipLine();
			UpdateMap();
		}

		Sleep(200);
		InvalidateRect(m_rtGameRect, FALSE);

		JudgeWin();
	}
	m_bFirstPoint = !m_bFirstPoint;
}

void CGameDlg::OnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	Vertex avPath[256];
	int nVexnum = 0;
	if (m_gameControl.help(avPath, nVexnum))
	{
		DrawTipLine(avPath, nVexnum);
		UpdateMap();
	}
	Sleep(500);
	InvalidateRect(m_rtGameRect, FALSE);
}

void CGameDlg::OnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bPlaying == false)
	{
		return;
	}
	m_gameControl.StartGame();
	UpdateMap();
	Invalidate(FALSE);
}

void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == PLAY_TIMER_ID && m_bPlaying)
	{
		m_GameProgress.StepIt();
		JudgeWin();
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CGameDlg::DrawGameTime()
{
	// TODO: 在此处添加实现代码.
}

void CGameDlg::JudgeWin(void)
{
	// TODO: 在此处添加实现代码.
	bool bGameStatus = m_gameControl.isWin(m_GameProgress.GetPos());
	if (bGameStatus == GAME_PLAY)
	{
		return;
	}
	else
	{
		m_bPlaying = false;
		KillTimer(PLAY_TIMER_ID);
		CString strTitle;
		this->GetWindowTextW(strTitle);
		if (bGameStatus == GAME_SUCCESS)
		{
			MessageBox(_T("获胜！"), strTitle);
		}
		else if (bGameStatus == GAME_LOSE)
		{
			MessageBox(_T("很遗憾，时间到了"), strTitle);
		}
		this->GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	}
}

void CGameDlg::OnClickedBtnStop()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bPlaying == false)
	{
		return;
	}
	if (m_bPause == false)
	{
		m_bPause = !m_bPause;
	}
}

void CGameDlg::OnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CHelpDialog dlg;
	dlg.DoModal();
}
