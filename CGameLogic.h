#pragma once
#include "global.h"
class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();
	void InitMap(int** anMap);
	bool IsLink(int** anMap, Vertex v1, Vertex v2);
	void Clear(int** anMap, Vertex v1, Vertex v2);
};

