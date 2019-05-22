#include "pch.h"
#include "CGameControl.h"

int CGameControl::s_nRows = MAX_ROW;
int CGameControl::s_nCols = MAX_COL;
int CGameControl::s_nPicNum = MAX_PICNUM;

CGameControl::CGameControl()
{
}


CGameControl::~CGameControl()
{
}

void CGameControl::StartGame() 
{
	// Initialize Game Map
	m_anMap = new int* [s_nRows];
	for (int i = 0; i < 10; i++) m_anMap[i] = new int[s_nCols];
	CGameLogic gameLogic;
	gameLogic.InitMap(m_anMap);
}

int CGameControl::GetElement(int row, int col)
{
	return m_anMap[row][col];
}

void CGameControl::SetFirstPoint(int row, int col)
{
	m_ptFirstPoint.row = row;
	m_ptFirstPoint.col = col;
}

void CGameControl::SetSecondPoint(int row, int col)
{
	m_ptSecondPoint.row = row;
	m_ptSecondPoint.col = col;
}

bool CGameControl::Link(Vertex avPath[4], int &nVexNum)
{
	// 两次点击图片不同的话返回false
	if (m_anMap[m_ptFirstPoint.row][m_ptFirstPoint.col] != m_anMap[m_ptSecondPoint.row][m_ptSecondPoint.col]) return false;
	// 两次点击同一个点的话返回false
	if (m_ptFirstPoint.row == m_ptSecondPoint.row && m_ptFirstPoint.col == m_ptSecondPoint.col) return false;
	// 判断两次点击的点                                                                                                       
	if (m_gameLogic.IsLink(m_anMap, m_ptFirstPoint, m_ptSecondPoint)) {
		// 消除两个点
		m_gameLogic.Clear(m_anMap, m_ptFirstPoint, m_ptSecondPoint);
		nVexNum = m_gameLogic.GetVexPath(avPath);
		return true;
	}
	return false;
}

bool CGameControl::IsWin()
{
	return m_gameLogic.IsBlank(m_anMap);
}
