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
    bool SearchValidPath(CGraph &g);//��ʾ�㷨
protected:
    Vertex m_anPath[256];
    int m_avPath[256]; //������������ж�ʱ�������Ķ���
    int m_nCornor; //����·������m_anPath�еĹյ���
    int m_nVexNum; //������
    
    //	void AddVertex(Vertex v);
    //	void DeleteVertex();
    //	void PushVertex(Vertex v);
    void PushVertex(int nV);
    void PopVertex();
    void UpdateArc(CGraph &g, int nRow, int nCol);//�жϵ�ͼ��nRow�У�nCol�еĶ��������������ҵĶ����Ƿ��бߣ��У������ͼ�ṹ
    bool SearchPath(CGraph &g, int nV0, int nV1);//��������������ж�v0��v1�Ƿ�����
    bool IsExist(int nVi);//�ж�����ΪnVi�Ķ����Ƿ񱣴浽��ͨ����m_anPath��
    bool IsCornor(void);//�ж�·������m_anPath�У����������ܷ񹹳�һ������
    
    /*bool LinkInRow(int anMap[][12], Vertex v1, Vertex v2); //�жϺ����Ƿ���ͨ
     *	bool LinkInCol(int anMap[][12], Vertex v1, Vertex v2);//�ж������Ƿ���ͨ
     *	bool OneCornerLink(int anMap[][12], Vertex v1, Vertex v2);//һ���յ���ͨ�ж�
     *	bool TwoCornerLink(int anMap[][12], Vertex v1, Vertex v2);
     *	bool LineY(int anMap[][12], int nRow1, int nRow2, int nCol);//ֱ����ͨY��
     *	bool LineX(int anMap[][12], int nRow, int nCol1, int nCol2);//ֱ����ͨX��*/
};

