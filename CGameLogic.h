#pragma once
#include "global.h"
class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();
	void InitMap(int** anMap);								// 初始化游戏地图
	void ReleaseMap(int** &anMap);							// 释放游戏地图
	bool IsLink(int** anMap, Vertex v1, Vertex v2);			// 判断两个点是否满足相连消除条件
	bool LinkInRow(int** anMap, Vertex v1, Vertex v2);		// 判断两个点是否在同一行上可以相连
	bool LinkInCol(int** anMap, Vertex v1, Vertex v2);		// 判断两个点是否在同一列上可以相连
	bool OneCornerLink(int** anMap, Vertex v1, Vertex v2);	// 判断两个点是否可以两条线相连
	bool TriLineLink(int** anMap, Vertex v1, Vertex v2);	// 判断两个点是否可以三条线相连
	bool LineX(int** anMap, int row, int col1, int col2);	// 判断X方向上是否连接
	bool LineY(int** anMap, int col, int row1, int row2);	// 判断Y方向上是否连接
	void Clear(int** anMap, Vertex v1, Vertex v2);			// 消除两个点
	int GetVexPath(Vertex avPath[4]);						// 得到路径，返回顶点数
	bool IsBlank(int** anMap);								// 判断图中顶点是否全为空

protected:
	Vertex m_avPath[4];				// 保存在进行连接判断时所经过的顶点
	int m_nVexNum=0;				// 顶点数
	void PushVertex(Vertex v);
	void PopVertex();
};

