#pragma once

#include "global.h"
#include "CGameControl.h"

// CGameDlg 对话框
class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr); // 标准构造函数
	virtual ~CGameDlg();

#ifdef AFX_DESIGN_TIME // 对话框数据
	enum
	{
		IDD = IDD_GAME_DIALOG
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 支持

	HICON m_hIcon;
	CDC m_dcMem;
	CDC m_dcElement;
	CDC m_dcMask;
	CDC m_dcBG;
	CDC m_dcCache;
	CDC m_dcPause;

	bool m_bPlaying;
	bool m_bPause;

	bool m_bFirstPoint;
	Vertex m_ptSelFirst;
	Vertex m_ptSelSec;

	CPoint m_ptGameTop; // 游戏起始点
	CSize m_sizeElem;
	CRect m_rtGameRect;

	CGameControl m_gameControl;

	void Initbackground();
	void InitElement();
	void DrawTipFrame(int nRow, int nCol);
	void DrawTipLine();
	void DrawTipLine(Vertex asvPath[2]);
	void DrawTipLine(Vertex asvPath[256], int nVexNum);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClickedBtnStart();

	void UpdateMap(void)
	{
		int nLeft = m_ptGameTop.y;
		int nTop = m_ptGameTop.x;
		int nElemW = m_sizeElem.cx;
		int nElemH = m_sizeElem.cy;

		m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);

		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				int nElemVal = m_gameControl.GetElement(i, j);
				if (nElemVal == BLANK)
					continue;
				// m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, m_anMap[i][j] * nElemH, SRCCOPY);
				// 将背景与掩码相或，边保留，图像区域为1
				m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nElemVal * nElemH, SRCPAINT);
				// 与元素图片相与，边保留，图像区域为元素图片
				m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, nElemVal * nElemH, SRCAND);
			}
		}
	}

	void UpdateWindow(void)
	{
		// 调整窗口大小
		CRect rtWin;
		CRect rtClient;
		this->GetWindowRect(rtWin);
		this->GetClientRect(rtClient);
		// 标题栏和外边框大小
		int nSpanWidth = rtWin.Width() - rtClient.Width();
		int nSpanHeight = rtWin.Height() - rtClient.Height();
		// 设置窗口大小
		MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
		CenterWindow();
	}
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickedButton3();
	afx_msg void OnClickedButton4();
	CProgressCtrl m_GameProgress;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void DrawGameTime(void);
	void JudgeWin(void);
	afx_msg void OnClickedBtnStop();
	afx_msg void OnClickedButton6();
};
