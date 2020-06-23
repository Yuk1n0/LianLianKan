#pragma once
class CGraph
{
public:
	CGraph();
	~CGraph();

#define MAX_VERTEX_NUM 256
	typedef int Vertices[MAX_VERTEX_NUM];//������������
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//����������

	void InitGraph(void);
	void AddVertex(int nInfo);//������info��ӵ���������
	int GetVertex(int nIndex);//��ȡ��������������ΪnIndex�Ķ���
	void AddArc(int nV1Index, int nV2Index);//��ӹ�ϵ�����������Ĺ�ϵ
	bool GetArc(int nV1Index, int nV2Index);
	int GetVexnum(void);//��ȡ���������еĶ�����
	void UpdateVertex(int nIndex, int nInfo);//��������nIndex�Ķ����ֵ����ΪnInfo
	void ClearGraph();
    int m_nVexnum;//��������

protected:
	Vertices m_Vertices;//��������
	AdjMatrix m_AdjMatrix;//��ϵ����
	int m_nArcnum;//�ߵ�����

};

