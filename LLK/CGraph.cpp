#include "stdafx.h"
#include "CGraph.h"

CGraph::CGraph()
{
    InitGraph();
}

CGraph::~CGraph()
{
}

void CGraph::InitGraph(void)
{
    //初始化计数器
    m_nVexnum = 0;
    m_nArcnum = 0;

    //初始化顶点
    for (int i = 0; i < MAX_VERTEX_NUM; i++)
    {
        m_Vertices[i] = -1;
    }

    //初始化边
    for (int i = 0; i < MAX_VERTEX_NUM; i++)
    {
        for (int j = 0; j < MAX_VERTEX_NUM; j++)
        {
            m_AdjMatrix[i][j] = false;
        }
    }
}

void CGraph::AddVertex(int nInfo)
{
    if (m_nVexnum >= MAX_VERTEX_NUM)
    {
        return;
    }
    m_Vertices[m_nVexnum] = nInfo;
    m_nVexnum++;
    //	return m_nVexnum;
}

int CGraph::GetVertex(int nIndex)
{
    return m_Vertices[nIndex];
}

void CGraph::AddArc(int nV1Index, int nV2Index)
{
    m_AdjMatrix[nV1Index][nV2Index] = true;
    m_AdjMatrix[nV2Index][nV1Index] = true;
}

bool CGraph::GetArc(int nV1Index, int nV2Index)
{
    return m_AdjMatrix[nV1Index][nV2Index];
}

int CGraph::GetVexnum(void)
{
    return m_nVexnum;
}

void CGraph::UpdateVertex(int nIndex, int nInfo)
{
    m_Vertices[nIndex] = nInfo;
}

void CGraph::ClearGraph()
{
    InitGraph();
}
