#include "stdafx.h"
#include "CGameLogic.h"
#include "global.h"
#include <stdlib.h>

CGameLogic::CGameLogic()
{
    m_nVexNum = 0;
    m_nCornor = 0;
}

CGameLogic::~CGameLogic()
{
}

void CGameLogic::InitMap(CGraph &g)
{
    //	int anTemp[12][12] = { 2,0,1,3,2,2,1,3,2,1,0,0,1,3,0,3 };
    int anTemp[12][12];
    g.m_nVexnum = 0;
    srand((int)time(NULL));
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            anTemp[i][j] = rand() % 20;
        }
    }
    
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            //赋值
            g.AddVertex(anTemp[i][j]);
        }
    }
    
    //更新弧信息
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            UpdateArc(g, i, j);
        }
    }
}

bool CGameLogic::isLink(CGraph &g, Vertex v1, Vertex v2)
{
    /*
     *	int nRow1 = v1.row;
     *	int nCol1 = v1.col;
     *	if (anMap[nRow1][nCol1] == anMap[v2.row][v2.col])
     *	{
     *		return true;
}
return false;
*/
    
    /*//一条直线联通
    int nRow1 = v1.row;
    int nCol1 = v1.col;
    int nRow2 = v2.row;
    int nCol2 = v2.col;
    AddVertex(v1);
    if (nRow1 == nRow2)
    {
    if (LinkInRow(anMap, v1, v2) == true)
    {
    AddVertex(v2);
    return true;
}
}
if (nCol1 == nCol2)
{
if (LinkInCol(anMap, v1, v2) == true)
{
AddVertex(v2);
return true;
}
}

//两条直线连通
if (OneCornerLink(anMap, v1, v2) == true)
{
AddVertex(v2);
return true;
}

//三条直线联通
if (TwoCornerLink(anMap, v1, v2) == true)
{
AddVertex(v2);
return true;
}
DeleteVertex();*/
    
    //获取顶点索引号
    int nV1Index = v1.row * 12 + v1.col;
    int nV2Index = v2.row * 12 + v2.col;
    
    //压入第一个点
    PushVertex(nV1Index);
    
    //判断两顶点是否联通
    /*if (g.GetArc(nV1Index, nV2Index) == true)
     *	{
     *		PushVertex(v2);
     *		return true;
}

PopVertex();
*/
    
    if (SearchPath(g, nV1Index, nV2Index)==true)
    {
        return true;
    }
    PopVertex();
    return false;
}

void CGameLogic::Clear(CGraph &g, Vertex v1, Vertex v2)
{
    int nV1Index = v1.row * 12 + v1.col;
    int nV2Index = v2.row * 12 + v2.col;
    
    //更新顶点信息
    g.UpdateVertex(nV1Index, BLANK);
    g.UpdateVertex(nV2Index, BLANK);
    
    //更新边信息
    //	UpdateArc(g, nV1Index, nV2Index);
    UpdateArc(g, v1.row, v1.col);
    UpdateArc(g, v2.row, v2.col);
}

int CGameLogic::GetVexPath(Vertex avPath[256])
{
    for (int i = 0; i < m_nVexNum; i++)
    {
        avPath[i].col = m_avPath[i] % 12;
        avPath[i].row = m_avPath[i] / 12;
    }
    return m_nVexNum;
}

bool CGameLogic::isBlank(CGraph & g)
{
    int nVertex = g.GetVexnum();
    for (int i = 0; i < nVertex; i++)
    {
        if (g.GetVertex(i) != BLANK)
        {
            return false;
        }
    }
    return true;
}

bool CGameLogic::SearchValidPath(CGraph & g)
{
    int nVexnum = g.GetVexnum();
    for (int i = 0; i < nVexnum; i++)
    {
        //1.得到第一个非空顶点
        if (g.GetVertex(i) == BLANK)
        {
            continue;
        }
        
        //遍历得到第二个同色景点
        for (int j = 0; j < nVexnum; j++)
        {
            if (i != j)
            {
                PushVertex(i);
                if (g.GetVertex(i) != g.GetVertex(j))
                {
                    PopVertex();
                    continue;
                }
                
                if (SearchPath(g, i, j) == true)
                {
                    return true;
                }
                
                PopVertex();
            }
            
        }
    }
    return false;
}

/*void CGameLogic::AddVertex(Vertex v)
 * {
 *	m_avPath[m_nVexNum] = v;
 *	m_nVexNum++;
 * }*/

/*void CGameLogic::DeleteVertex()
 * {
 *	m_nVexNum--;
 * }*/

/*void CGameLogic::PushVertex(Vertex v)
 * {
 *	m_avPath[m_nVexNum] = v;
 *	m_nVexNum++;
 * }*/

void CGameLogic::PushVertex(int nV)
{
    m_avPath[m_nVexNum] = nV;
    m_nVexNum++;
    
    if (IsCornor())
    {
        m_nCornor++;
    }
}

void CGameLogic::PopVertex()
{
    if (IsCornor())
    {
        m_nCornor--;
    }
    m_nVexNum--;
}

void CGameLogic::UpdateArc(CGraph & g, int nRow, int nCol)
{
    int nV1Index = nRow * 12 + nCol;
    if (nCol > 0)
    {
        int nV2Index = nV1Index - 1;
        //判断与左边相邻的是否有关系
        int nV1Info = g.GetVertex(nV1Index);
        int nV2Info = g.GetVertex(nV2Index);
        if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
        {
            g.AddArc(nV1Index, nV2Index);
        }
    }
    if (nCol < 11)
    {
        int nV2Index = nV1Index + 1;
        //判断与右边是否有关系
        int nV1Info = g.GetVertex(nV1Index);
        int nV2Info = g.GetVertex(nV2Index);
        if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
        {
            g.AddArc(nV1Index, nV2Index);
        }
    }
    if (nRow > 0)
    {
        int nV2Index = nV1Index - 12;
        //判断与上方是否有关系
        int nV1Info = g.GetVertex(nV1Index);
        int nV2Info = g.GetVertex(nV2Index);
        if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
        {
            g.AddArc(nV1Index, nV2Index);
        }
    }
    if (nRow < 11)
    {
        int nV2Index = nV1Index + 12;
        //判断与下方是否有关系
        int nV1Info = g.GetVertex(nV1Index);
        int nV2Info = g.GetVertex(nV2Index);
        if (nV1Info == nV2Info || nV1Info == BLANK || nV2Info == BLANK)
        {
            g.AddArc(nV1Index, nV2Index);
        }
    }
}

bool CGameLogic::SearchPath(CGraph & g, int nV0, int nV1)
{
    //得到顶点数
    int nVexnum = g.GetVexnum();
    
    //遍历图中nV0行，从0列到nVexnum列，值为true的点
    for (int nVi = 0; nVi < nVexnum; nVi++)
    {
        if (g.GetArc(nV0, nVi) && !IsExist(nVi))
        {
            //压入当前顶点，假设路径为一个有效顶点
            PushVertex(nVi);
            if (m_nCornor > 2)
            {
                PopVertex();
                continue;
            }
            
            //当中间顶点不是nV1时，继续搜寻下一个相邻且连通的顶点
            if (nVi != nV1)
            {
                //当中间顶点不为空时，表示该条路径不空
                if (g.GetVertex(nVi) != BLANK)
                {
                    PopVertex(); //去除压入的顶点，与pushvertex（nvi）对应
                    continue;
                }
                
                if (SearchPath(g, nVi, nV1))
                {
                    //表示找到了一条路径
                    return true;
                }
            }
            else //相等，则表示已经找到一条路径
            {
                return true;
            }
            
            PopVertex();//取出压入的顶点
        }
    }
    return false;
}

bool CGameLogic::IsExist(int nVi)
{
    for (int i = 0; i < m_nVexNum; i++)
    {
        if (m_avPath[i] == nVi)
        {
            return true;
        }
    }
    return false;
}

bool CGameLogic::IsCornor(void)
{
    if (m_nVexNum >= 3)
    {
        if ((m_avPath[m_nVexNum - 1] + m_avPath[m_nVexNum - 3]) / 2 == m_avPath[m_nVexNum - 2])
        {
            return true;
        }
    }
    return false;
}

/*
 * bool CGameLogic::LinkInRow(int anMap[][12], Vertex v1, Vertex v2)
 * {
 *	int nCol1 = v1.col;
 *	int nCol2 = v2.col;
 *	int nRow = v1.row;
 * 
 *	if (nCol1 > nCol2)
 *	{
 *		int temp = nCol1;
 *		nCol1 = nCol2;
 *		nCol2 = temp;
 *	}
 * 
 *	for (int i = nCol1 + 1; i <= nCol2; i++)
 *	{
 *		if (i == nCol2)	return true;
 *		if (anMap[nRow][i] != BLANK) break;
 *	}
 *	return false;
 * }
 * 
 * bool CGameLogic::LinkInCol(int anMap[][12], Vertex v1, Vertex v2)
 * {
 *	int nRow1 = v1.row;
 *	int nRow2 = v2.row;
 *	int nCol = v1.col;
 * 
 *	if (nRow1 > nRow2)
 *	{
 *		int temp = nRow1;
 *		nRow1 = nRow2;
 *		nRow2 = temp;
 *	}
 * 
 *	for (int i = nRow1 + 1; i <= nRow2; i++)
 *	{
 *		if (i == nRow2)	return true;
 *		if (anMap[i][nCol] != BLANK) break;
 *	}
 *	return false;
 * }
 * 
 * bool CGameLogic::OneCornerLink(int anMap[][12], Vertex v1, Vertex v2)
 * {
 *	int nRow1 = v1.row;
 *	int nRow2 = v2.row;
 *	int nCol1 = v1.col;
 *	int nCol2 = v2.col;
 * 
 *	if (nRow1 > nRow2)
 *	{
 *		//
 *		int nTemp = nRow1;
 *		nRow1 = nRow2;
 *		nRow2 = nTemp;
 *		nTemp = nCol1;
 *		nCol1 = nCol2;
 *		nCol2 = nTemp;
 *	}
 *	if (nCol1 > nCol2)
 *	{
 *		if (LineY(anMap, nRow1 + 1, nRow2, nCol1) && LineX(anMap, nRow2, nCol1, nCol2 + 1))
 *		{
 *			Vertex v;
 *			v.row = nRow2;
 *			v.col = nCol1;
 *			AddVertex(v);
 *			return true;
 *		}
 *		if (LineY(anMap, nRow2 - 1, nRow1, nCol2) && LineX(anMap, nRow1, nCol2, nCol1 - 1))
 *		{
 *			Vertex v;
 *			v.row = nRow1;
 *			v.col = nCol2;
 *			AddVertex(v);
 *			return true;
 *		}
 * 
 *	}
 *	else
 *	{
 *		if (LineY(anMap, nRow1 + 1, nRow2, nCol1) && LineX(anMap, nRow2, nCol1, nCol2 - 1))
 *		{
 *			Vertex v;
 *			v.row = nRow2;
 *			v.col = nCol1;
 *			AddVertex(v);
 *			return true;
 *		}
 *		if (LineY(anMap, nRow2 - 1, nRow1, nCol2) && LineX(anMap, nRow1, nCol2, nCol1 + 1))
 *		{
 *			Vertex v;
 *			v.row = nRow1;
 *			v.col = nCol2;
 *			AddVertex(v);
 *			return true;
 *		}
 *	}
 *	return false;
 * }
 * 
 * bool CGameLogic::TwoCornerLink(int anMap[][12], Vertex v1, Vertex v2)
 * {
 *	int nRow1 = v1.row;
 *	int nRow2 = v2.row;
 *	int nCol1 = v1.col;
 *	int nCol2 = v2.col;
 * 
 *	for (int nCol = 0; nCol < 12; nCol++)
 *	{
 *		if (anMap[nRow1][nCol] == BLANK && anMap[nRow2][nCol] == BLANK)
 *		{
 * 
 *			if (LineY(anMap, nRow1, nRow2, nCol))
 *			{
 *				Vertex V1;
 *				V1.row = nRow2;
 *				V1.col = nCol;
 *				if (OneCornerLink(anMap, v1, V1) == true)
 *				{
 *					AddVertex(V1);
 *					return true;
 *				}
 *			}
 *		}
 *	}
 *	for (int nRow = 0; nRow < 12; nRow++)
 *	{
 *		if (anMap[nRow][nCol1] == BLANK && anMap[nRow][nCol2] == BLANK)
 *		{
 *			if (LineX(anMap, nRow, nCol1, nCol2))
 *			{
 *				Vertex V1;
 *				V1.row = nRow;
 *				V1.col = nCol2;
 *				if (OneCornerLink(anMap, v1, V1) == true)
 *				{
 *					AddVertex(V1);
 *					return true;
 *				}
 *			}
 *		}
 *	}
 *	return false;
 * }
 * 
 * bool CGameLogic::LineY(int anMap[][12], int nRow1, int nRow2, int nCol)
 * {
 *	if (nRow1 > nRow2)
 *	{
 *		int nTemp = nRow1;
 *		nRow1 = nRow2;
 *		nRow2 = nTemp;
 *	}
 *	for (int nRow = nRow1; nRow <= nRow2; nRow++)
 *	{
 *		if (anMap[nRow][nCol] != BLANK)
 *			break;
 *		if (nRow == nRow2)
 *			return true;
 *	}
 *	return false;
 * }
 * 
 * bool CGameLogic::LineX(int anMap[][12], int nRow, int nCol1, int nCol2)
 * {
 *	if (nCol1 > nCol2)
 *	{
 *		int nTemp = nCol1;
 *		nCol1 = nCol2;
 *		nCol2 = nTemp;
 *	}
 *	for (int nCol = nCol1; nCol <= nCol2; nCol++)
 *	{
 *		if (anMap[nRow][nCol] != BLANK)
 *			break;
 *		if (nCol == nCol2)
 *			return true;
 *	}
 *	return false;
 * }
 */
