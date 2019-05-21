#include "pch.h"
#include "CGameLogic.h"
#include <algorithm>

CGameLogic::CGameLogic()
{
}


CGameLogic::~CGameLogic()
{
}

void CGameLogic::InitMap(int** anMap)
{
	int** tmp = new int* [10];
	for (int i = 0; i < 10; i++) {
		tmp[i] = new int[16];
	}
	int* cnt = new int[20];
	std::fill(cnt, cnt + 20, 0);
	srand(time(0));		// 初始化随机数种子
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 16; j++) {
			int rand = std::rand() % 20;
			if (cnt[rand] < 8) {
				cnt[rand]++;
				tmp[i][j] = rand;
			}
			else {
				for (int k = 0; k < 20; k++) {
					int index = (k + rand) % 20;
					if (cnt[index] < 8) {
						cnt[index]++;
						tmp[i][j] = index;
						break;
					}
				}
			}

		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 16; j++) {
			int t = tmp[i][j];
			int ri = std::rand() % 10;
			int rj = std::rand() % 16;
			// 交换两个图片
			tmp[i][j] = tmp[ri][rj];
			tmp[ri][rj] = t;
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 16; j++) {
			anMap[i][j] = tmp[i][j];
		}
	}
}

bool CGameLogic::IsLink(int** anMap, Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nCol1 = v1.col;
	int nRow2 = v2.row;
	int nCol2 = v2.col;
	if (nRow1 == nRow2 && nCol1 == nCol2) return false;
	if (anMap[nRow1][nCol1] == anMap[nRow2][nCol2]) return true;
	return false;
}

void CGameLogic::Clear(int** anMap, Vertex v1, Vertex v2)
{
	anMap[v1.row][v1.col] = BLANK;
	anMap[v2.row][v2.col] = BLANK;
}

