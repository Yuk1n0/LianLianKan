// CGameControl.h : 游戏界面控制
#pragma once

#include "global.h"
#include "CGraph.h"

class CGameControl
{
public:
	CGameControl();
	~CGameControl();

private:
	CGraph m_graph;
	Vertex m_svSelFst;
	Vertex m_svSelSec;

public:
	void StartGame();
	int GetElement(int nRow, int nCol);
	void SetFirstPoint(int nRow, int nCol);
	void SetSecPoint(int nRow, int nCol);
	bool Link(Vertex avPath[256], int& nVexNum);
	bool isWin(int nTime);
	bool help(Vertex avPath[256], int& nVexnum);
};
