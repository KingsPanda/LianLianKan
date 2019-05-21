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
	int**  m_anMap;					// 游戏地图
	Vertex m_ptFirstPoint;			// 第一个选中的点
	Vertex m_ptSecondPoint;			// 第二个选中的点
public:
	CGameLogic m_gameLogic;			// 游戏逻辑
};

