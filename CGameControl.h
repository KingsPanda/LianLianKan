#pragma once
#include "global.h"
#include "CGameLogic.h"
class CGameControl
{
public:
	CGameControl();
	~CGameControl();
	void StartGame();							// 开始游戏
	int GetElement(int row, int col);			// 获取顶点元素
	void SetFirstPoint(int row, int col);		// 设置第一个点击的结点
	void SetSecondPoint(int row, int col);		// 设置第二个点击的结点
	bool Link(Vertex avPath[4], int &nVexNum);	// 判断是否相连并获取路径结点信息
	bool IsWin();								// 判断是否获胜
private:
	int**  m_anMap;					// 游戏地图
	Vertex m_ptFirstPoint;			// 第一个选中的点
	Vertex m_ptSecondPoint;			// 第二个选中的点
public:
	CGameLogic m_gameLogic;			// 游戏逻辑
	static int s_nRows;				// 游戏行数
	static int s_nCols;				// 游戏列数
	static int s_nPicNum;			// 元素图片数
};

