#include "pch.h"
#include "CGameLogic.h"
#include "CGameControl.h"
#include <algorithm>

CGameLogic::CGameLogic()
{
}


CGameLogic::~CGameLogic()
{
}

void CGameLogic::InitMap(int** anMap)
{
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int nPicNum = CGameControl::s_nPicNum;
	int nPicMax = nRows * nCols / nPicNum;	// 每张图片的数目
	int** tmp = new int* [nRows];
	for (int i = 0; i < nRows; i++) {
		tmp[i] = new int[nCols];
	}
	int* cnt = new int[nPicNum];
	std::fill(cnt, cnt + nPicNum, 0);
	srand(time(0));		// 初始化随机数种子
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			int rand = std::rand() % nPicNum;
			if (cnt[rand] < nPicMax) {
				cnt[rand]++;
				tmp[i][j] = rand;
			}
			else {
				for (int k = 0; k < nPicNum; k++) {
					int index = (k + rand) % nPicNum;
					if (cnt[index] < nPicMax) {
						cnt[index]++;
						tmp[i][j] = index;
						break;
					}
				}
			}

		}
	}
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			int t = tmp[i][j];
			int ri = std::rand() % nRows;
			int rj = std::rand() % nCols;
			// 交换两个图片
			tmp[i][j] = tmp[ri][rj];
			tmp[ri][rj] = t;
		}
	}
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			anMap[i][j] = tmp[i][j];
		}
	}
}

void CGameLogic::ReleaseMap(int** &anMap)
{
	for (int i = 0; i < CGameControl::s_nRows; i++) {
		delete[] anMap[i];
	}
	delete[]anMap;
}

bool CGameLogic::IsLink(int** anMap, Vertex v1, Vertex v2)
{
	m_nVexNum = 0;
	// 路径中加入起始点
	PushVertex(v1);
	int nRow1 = v1.row;
	int nCol1 = v1.col;
	int nRow2 = v2.row;
	int nCol2 = v2.col;

	// 一条直线联通
	if (nRow1 == nRow2) {
		if (LinkInRow(anMap, v1, v2)) {
		// 路径中加入结束点，后面相同
			PushVertex(v2);
			return true;
		}
	}
	if (nCol1 == nCol2) {
		if (LinkInCol(anMap, v1, v2)) {
			PushVertex(v2);
			return true;
		}
	}
	// 两条直线联通
	if (OneCornerLink(anMap, v1, v2)) {
		PushVertex(v2);
		return true;
	}
	// 三条直线联通
	if (TriLineLink(anMap, v1, v2)) {
		PushVertex(v2);
		return true;
	}
	return false;
}

bool CGameLogic::LinkInRow(int** anMap, Vertex v1, Vertex v2)
{
	int row1 = v1.row;
	int row2 = v2.row;
	if (row1 != row2) return false;
	int col1 = v1.col;
	int col2 = v2.col;
	if (col1 > col2) {
		int tmp = col1;
		col1 = col2;
		col2 = tmp;
	}
	for (int i = col1+1; i <= col2; i++) {
		if (i == col2) return true;
		if (anMap[row1][i] != BLANK) break;
	}
	return false;
}

bool CGameLogic::LinkInCol(int** anMap, Vertex v1, Vertex v2)
{
	int col1 = v1.col;
	int col2 = v2.col;
	if (col1 != col2) return false;
	int row1 = v1.row;
	int row2 = v2.row;
	if (row1 > row2) {
		int tmp = row1;
		row1 = row2;
		row2 = tmp;
	}
	for (int i = row1 + 1; i <= row2; i++) {
		if (i == row2) return true;
		if (anMap[i][col1] != BLANK) break;
	}
	return false;
}

bool CGameLogic::OneCornerLink(int** anMap, Vertex v1, Vertex v2)
{
	int row1 = v1.row;
	int col1 = v1.col;
	int row2 = v2.row;
	int col2 = v2.col;
	if (row1 > row2) {
		int tmp = row1;
		row1 = row2;
		row2 = tmp;
		tmp  = col1;
		col1 = col2;
		col2 = tmp;
	}
	// 左下、右下
	if (anMap[row1][col2] == BLANK) {
		if (LineY(anMap, col2, row1, row2) && LineX(anMap, row1, col1, col2)) {
			// 添加节点
			Vertex v = {row1, col2, BLANK};
			PushVertex(v);
			return true;
		}
	}
	// 下左、下右
	if (anMap[row2][col1] == BLANK) {
		if (LineY(anMap, col1, row1, row2) && LineX(anMap, row2, col1, col2)) {
			// 添加节点
			Vertex v = {row2, col1, BLANK};
			PushVertex(v);
			return true;
		}
	}
	return false;
}

bool CGameLogic::TriLineLink(int** anMap, Vertex v1, Vertex v2)
{
	int row1 = v1.row;
	int col1 = v1.col;
	int row2 = v2.row;
	int col2 = v2.col;
	if (row1 > row2) {
		int tmp = row1;
		row1 = row2;
		row2 = tmp;
		tmp = col1;
		col1 = col2;
		col2 = tmp;
	}
	for (int col = 0; col < CGameControl::s_nCols; col++) {
		if (anMap[row1][col] == BLANK && anMap[row2][col] == BLANK) {
			if (LineY(anMap, col, row1, row2)) {
				if (LineX(anMap, row1, col1, col) && LineX(anMap, row2, col2, col)) {
					// 保存节点
					Vertex v1 = { row1, col, BLANK };
					Vertex v2 = { row2, col, BLANK };
					PushVertex(v1);
					PushVertex(v2);
					return true;
				}
			}
		}
	}
	for (int row = 0; row < CGameControl::s_nRows; row++) {
		if (anMap[row][col1] == BLANK && anMap[row][col2] == BLANK) {
			if (LineX(anMap, row, col1, col2)) {
				if (LineY(anMap, col1, row, row1) && LineY(anMap, col2, row, row2)) {
					// 保存节点
					Vertex v1 = { row, col1, BLANK };
					Vertex v2 = { row, col2, BLANK };
					PushVertex(v1);
					PushVertex(v2);
					return true;
				}
			}
		}
	}
	return false;
}

bool CGameLogic::LineX(int** anMap, int row, int col1, int col2)
{
	if (col1 > col2) {
		int tmp = col1;
		col1 = col2;
		col2 = tmp;
	}
	for (int i = col1 + 1; i <= col2; i++) {
		if (i == col2) return true;
		if (anMap[row][i] != BLANK) break;
	}
	return false;
}

bool CGameLogic::LineY(int** anMap, int col, int row1, int row2)
{
	if (row1 > row2) {
		int tmp = row1;
		row1 = row2;
		row2 = tmp;
	}
	for (int i = row1 + 1; i <= row2; i++) {
		if (i == row2) return true;
		if (anMap[i][col] != BLANK) break;
	}
	return false;
}

void CGameLogic::Clear(int** anMap, Vertex v1, Vertex v2)
{
	anMap[v1.row][v1.col] = BLANK;
	anMap[v2.row][v2.col] = BLANK;
}

int CGameLogic::GetVexPath(Vertex avPath[4])
{
	for (int i = 0; i < m_nVexNum; i++) {
		avPath[i] = m_avPath[i];
	}
	return m_nVexNum;
}

bool CGameLogic::IsBlank(int** anMap)
{
	for (int i = 0; i <= CGameControl::s_nRows; i++) {
		if (i == CGameControl::s_nRows) return true;
		for (int j = 0; j < CGameControl::s_nCols; j++) {
			if (anMap[i][j] != BLANK) return false;
		}
	}
	return false;
}

void CGameLogic::PushVertex(Vertex v)
{
	m_avPath[m_nVexNum++] = v;
}

void CGameLogic::PopVertex()
{
}

