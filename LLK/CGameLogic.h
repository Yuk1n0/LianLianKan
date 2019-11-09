#pragma once
#include "global.h"
#include "CGraph.h"
class CGameLogic
{
public:
    CGameLogic();
    ~CGameLogic();
    void InitMap(CGraph &g);
    bool isLink(CGraph &g,Vertex v1,Vertex v2);
    void Clear(CGraph &g, Vertex v1, Vertex v2);
    int GetVexPath(Vertex avPath[256]);
    bool isBlank(CGraph &g);
    bool SearchValidPath(CGraph &g);//提示算法
protected:
    Vertex m_anPath[256];
    int m_avPath[256]; //保存进行连接判断时所经过的顶点
    int m_nCornor; //连接路径数组m_anPath中的拐点数
    int m_nVexNum; //顶点数
    
    //	void AddVertex(Vertex v);
    //	void DeleteVertex();
    //	void PushVertex(Vertex v);
    void PushVertex(int nV);
    void PopVertex();
    void UpdateArc(CGraph &g, int nRow, int nCol);//判断地图中nRow行，nCol列的顶点与它上下左右的顶点是否有边，有，则更新图结构
    bool SearchPath(CGraph &g, int nV0, int nV1);//深度优先搜索，判断v0与v1是否相连
    bool IsExist(int nVi);//判断索引为nVi的顶点是否保存到连通数组m_anPath中
    bool IsCornor(void);//判断路径数组m_anPath中，三个顶点能否构成一个顶点
    
    /*bool LinkInRow(int anMap[][12], Vertex v1, Vertex v2); //判断横向是否联通
     *	bool LinkInCol(int anMap[][12], Vertex v1, Vertex v2);//判断纵向是否联通
     *	bool OneCornerLink(int anMap[][12], Vertex v1, Vertex v2);//一个拐点联通判断
     *	bool TwoCornerLink(int anMap[][12], Vertex v1, Vertex v2);
     *	bool LineY(int anMap[][12], int nRow1, int nRow2, int nCol);//直线联通Y轴
     *	bool LineX(int anMap[][12], int nRow, int nCol1, int nCol2);//直线联通X轴*/
};

