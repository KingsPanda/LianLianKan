#pragma once
#include "global.h"
#include "CGameLogic.h"
class CGameControl
{
public:
	CGameControl();
	~CGameControl();
	void StartGame();
	int GetElement(int row, int col);
	void SetFirstPoint(int row, int col);
	void SetSecondPoint(int row, int col);
	bool Link(Vertex avPath[2]);
private:
	int**  m_anMap;					// ��Ϸ��ͼ
	Vertex m_ptFirstPoint;			// ��һ��ѡ�еĵ�
	Vertex m_ptSecondPoint;			// �ڶ���ѡ�еĵ�
public:
	CGameLogic m_gameLogic;			// ��Ϸ�߼�
};

