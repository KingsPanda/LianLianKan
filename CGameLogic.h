#pragma once
#include "global.h"
class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();
	void InitMap(int** anMap);								// ��ʼ����Ϸ��ͼ
	void ReleaseMap(int** &anMap);							// �ͷ���Ϸ��ͼ
	bool IsLink(int** anMap, Vertex v1, Vertex v2);			// �ж��������Ƿ�����������������
	bool LinkInRow(int** anMap, Vertex v1, Vertex v2);		// �ж��������Ƿ���ͬһ���Ͽ�������
	bool LinkInCol(int** anMap, Vertex v1, Vertex v2);		// �ж��������Ƿ���ͬһ���Ͽ�������
	bool OneCornerLink(int** anMap, Vertex v1, Vertex v2);	// �ж��������Ƿ��������������
	bool TriLineLink(int** anMap, Vertex v1, Vertex v2);	// �ж��������Ƿ��������������
	bool LineX(int** anMap, int row, int col1, int col2);	// �ж�X�������Ƿ�����
	bool LineY(int** anMap, int col, int row1, int row2);	// �ж�Y�������Ƿ�����
	void Clear(int** anMap, Vertex v1, Vertex v2);			// ����������
	int GetVexPath(Vertex avPath[4]);						// �õ�·�������ض�����
	bool IsBlank(int** anMap);								// �ж�ͼ�ж����Ƿ�ȫΪ��

protected:
	Vertex m_avPath[4];				// �����ڽ��������ж�ʱ�������Ķ���
	int m_nVexNum=0;				// ������
	void PushVertex(Vertex v);
	void PopVertex();
};

