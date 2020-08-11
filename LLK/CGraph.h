#pragma once

class CGraph
{
public:
	CGraph();
	~CGraph();

#define MAX_VERTEX_NUM 256
	typedef int Vertices[MAX_VERTEX_NUM];                   // 顶点数据类型
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 边数据类型

	void InitGraph(void);
	void AddVertex(int nInfo);               // 将顶点info添加到顶点数组
	int GetVertex(int nIndex);               // 获取顶点数组中索引为nIndex的顶点
	void AddArc(int nV1Index, int nV2Index); // 添加关系矩阵中两个的关系
	bool GetArc(int nV1Index, int nV2Index);
	int GetVexnum(void);                      // 获取顶点数组中的顶点数
	void UpdateVertex(int nIndex, int nInfo); // 将索引号nIndex的顶点的值更新为nInfo
	void ClearGraph();
	int m_nVexnum; // 顶点数量

protected:
	Vertices m_Vertices;   // 顶点数组
	AdjMatrix m_AdjMatrix; // 关系矩阵
	int m_nArcnum;         // 边的数量
};
