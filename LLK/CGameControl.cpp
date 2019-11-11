#include "stdafx.h"
#include "CGameControl.h"
#include "global.h"
#include "CGameLogic.h"

CGameControl::CGameControl()
{
}

CGameControl::~CGameControl()
{
}

void CGameControl::StartGame()
{
    CGameLogic gameLogic;
    gameLogic.InitMap(m_graph);
}

int CGameControl::GetElement(int nRow, int nCol)
{
    //	return m_anMap[nRow][nCol];
    return m_graph.GetVertex(nRow * 12 + nCol);
}

void CGameControl::SetFirstPoint(int nRow, int nCol)
{
    m_svSelFst.row = nRow;
    m_svSelFst.col = nCol;
}

void CGameControl::SetSecPoint(int nRow, int nCol)
{
    m_svSelSec.row = nRow;
    m_svSelSec.col = nCol;
}

bool CGameControl::Link(Vertex avPath[256], int &nVexNum)
{
    //判断是否是同一张图片
    if (m_svSelFst.row == m_svSelSec.row && m_svSelFst.col == m_svSelSec.col)
    {
        return false;
    }
    //判断图片是否相同

    int nInfo1 = m_graph.GetVertex(m_svSelFst.row * 12 + m_svSelFst.col);
    int nInfo2 = m_graph.GetVertex(m_svSelSec.row * 12 + m_svSelSec.col);
    if (nInfo1 != nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
    {
        return false;
    }

    //判断是否连通
    CGameLogic gameLogic;
    if (gameLogic.isLink(m_graph, m_svSelFst, m_svSelSec))
    {
        nVexNum = gameLogic.GetVexPath(avPath);           //消子
        gameLogic.Clear(m_graph, m_svSelFst, m_svSelSec); //返回路径顶点
        return true;                                      //表示连通
    }
    return false;
}

bool CGameControl::isWin(int nTime)
{
    CGameLogic logic;
    if (nTime <= 0)
    {
        m_graph.ClearGraph();
        return GAME_LOSE;
    }

    if (logic.isBlank(m_graph))
    {
        m_graph.ClearGraph();
        return GAME_SUCCESS;
    }
    return GAME_PLAY;
}

bool CGameControl::help(Vertex avPath[256], int &nVexnum)
{
    CGameLogic logic;
    if (logic.SearchValidPath(m_graph))
    {
        nVexnum = logic.GetVexPath(avPath);
        return true;
    }
    return false;
}
