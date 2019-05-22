#pragma once
#include "global.h"
#include "CGameLogic.h"
class CGameControl
{
public:
	CGameControl();
	~CGameControl();
	void StartGame();							// ��ʼ��Ϸ
	int GetElement(int row, int col);			// ��ȡ����Ԫ��
	void SetFirstPoint(int row, int col);		// ���õ�һ������Ľ��
	void SetSecondPoint(int row, int col);		// ���õڶ�������Ľ��
	bool Link(Vertex avPath[4], int &nVexNum);	// �ж��Ƿ���������ȡ·�������Ϣ
	bool IsWin();								// �ж��Ƿ��ʤ
private:
	int**  m_anMap;					// ��Ϸ��ͼ
	Vertex m_ptFirstPoint;			// ��һ��ѡ�еĵ�
	Vertex m_ptSecondPoint;			// �ڶ���ѡ�еĵ�
public:
	CGameLogic m_gameLogic;			// ��Ϸ�߼�
	static int s_nRows;				// ��Ϸ����
	static int s_nCols;				// ��Ϸ����
	static int s_nPicNum;			// Ԫ��ͼƬ��
};

