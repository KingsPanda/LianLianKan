#include "pch.h"
#include "CGameControl.h"
#include "CGameLogic.h"

CGameControl::CGameControl()
{
}


CGameControl::~CGameControl()
{
}

void CGameControl::StartGame() 
{
	// Initialize Game Map
	m_anMap = new int* [10];
	for (int i = 0; i < 10; i++) m_anMap[i] = new int[16];
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

bool CGameControl::Link(Vertex avPath[2])
{
	if (m_ptFirstPoint.row == m_ptSecondPoint.row && m_ptFirstPoint.col == m_ptSecondPoint.col) return false;
	if (m_anMap[m_ptFirstPoint.row][m_ptFirstPoint.col] != m_anMap[m_ptSecondPoint.row][m_ptSecondPoint.col]) return false;
	CGameLogic gameLogic;
	if (gameLogic.IsLink(m_anMap, m_ptFirstPoint, m_ptSecondPoint)) {
		m_gameLogic.Clear(m_anMap, m_ptFirstPoint, m_ptSecondPoint);
		avPath[0].row = m_ptFirstPoint.row;
		avPath[0].col = m_ptFirstPoint.col;
		avPath[1].row = m_ptSecondPoint.row;
		avPath[1].col = m_ptSecondPoint.col;
		return true;
	}
	return false;
}