// CGameDlg.cpp : implementation file
//

#include "pch.h"
#include "LLK.h"
#include "CGameDlg.h"
#include "afxdialogex.h"
#include <algorithm>
#include <cstdlib>


// CGameDlg dialog

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_GameTop.x = 50;
	m_GameTop.y = 50;
	
	m_ElemSize.cx = 40;
	m_ElemSize.cy = 40;
	// ��ʼ����Ϸ�����С
	m_GameRec.left   = m_GameTop.x;
	m_GameRec.top    = m_GameTop.y;
	m_GameRec.right  = m_GameTop.x + m_ElemSize.cx * m_GameW;
	m_GameRec.bottom = m_GameTop.y + m_ElemSize.cy * m_GameH;

	m_bFirstPoint = true;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_BASIC_START, &CGameDlg::OnClickedBtnBasicStart)
	ON_BN_CLICKED(IDC_BTN_BASIC_TIP, &CGameDlg::OnBnClickedBtnBasicTip)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CGameDlg message handlers

void CGameDlg::InitBackground()
{
	// λͼ���
	HANDLE bmp = ::LoadImage(nullptr, _T("theme\\picture\\background.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// �ͻ��� device context
	CClientDC dc(this);
	// ����DC
	m_dcBG.CreateCompatibleDC(&dc);
	m_dcBG.SelectObject(bmp);

	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);

	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);
	UpdateWindow();
}

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitBackground();
	InitElement();
	// ������ͣ�����ģ���ʾ��ť������
	this->GetDlgItem(IDC_BTN_BASIC_PAUSE)->EnableWindow(false);
	this->GetDlgItem(IDC_BTN_BASIC_REARRANGE)->EnableWindow(false);
	this->GetDlgItem(IDC_BTN_BASIC_TIP)->EnableWindow(false);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CGameDlg::OnPaint()
{
	// DC := Device Context
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
	// Do not call CDialogEx::OnPaint() for painting messages
}

void CGameDlg::InitElement()
{
	// �ͻ��� device context
	CClientDC dc(this);
	// λͼ���
	HANDLE hBmp = ::LoadImage(nullptr, _T("theme\\picture\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// ����DC
	m_dcElement.CreateCompatibleDC(&dc);
	m_dcElement.SelectObject(hBmp);
	// ��������DC
	HANDLE hMask = ::LoadImage(nullptr, _T("theme\\picture\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(hMask);
}

void CGameDlg::UpdateWindow()
{
	// �������ڴ�С
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(&rtWin);
	this->GetClientRect(&rtClient);
	int nSpanWidth  = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	MoveWindow(rtWin.left, rtWin.top, 800 + nSpanWidth, 600 + nSpanHeight);
}

void CGameDlg::UpdateMap()
{
	int nLeft  = m_GameTop.x;
	int nTop   = m_GameTop.y;
	int nElemW = m_ElemSize.cx;
	int nElemH = m_ElemSize.cy;
	m_dcMem.BitBlt(m_GameRec.left, m_GameRec.top, m_GameRec.Width(), m_GameRec.Height(), &m_dcBG, m_GameRec.left, m_GameRec.top, SRCCOPY);
	for (int i = 0; i < m_GameH; i++) {
		for (int j = 0; j < m_GameW; j++) {
			int element = m_gameControl.GetElement(i, j);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, element * nElemH, SRCPAINT);
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, element * nElemH, SRCAND);
		}
	}
}

void CGameDlg::DrawTipFrame(int nRow, int nCol)
{
	CClientDC dc(this);
	CBrush brush(RGB(233,43,43));
	CRect frame;
	frame.top    = m_GameTop.y + nRow * m_ElemSize.cy;
	frame.bottom = frame.top + m_ElemSize.cy;
	frame.left   = m_GameTop.x + nCol * m_ElemSize.cx;
	frame.right  = frame.left + m_ElemSize.cx;
	dc.FrameRect(frame, &brush);
}


void CGameDlg::OnClickedBtnBasicStart()
{
	// ������ͣ�����ģ���ʾ��ť����
	this->GetDlgItem(IDC_BTN_BASIC_PAUSE)->EnableWindow(true);
	this->GetDlgItem(IDC_BTN_BASIC_REARRANGE)->EnableWindow(true);
	this->GetDlgItem(IDC_BTN_BASIC_TIP)->EnableWindow(true);
	// ��ʼ����Ϸ����
	m_gameControl.StartGame();
	UpdateMap();
	// �ػ����
	Invalidate();
	// ʹ��ʼ��Ϸ��ť��Ч
	this->GetDlgItem(IDC_BTN_BASIC_START)->EnableWindow(false);
}


void CGameDlg::OnBnClickedBtnBasicTip()
{
	// TODO: Add your control notification handler code here
}


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (point.x < m_GameTop.x || point.y < m_GameTop.y) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	// ��ȡ�����ͼƬ���ڵ����� 
	int nRow = (point.y - m_GameTop.y) / m_ElemSize.cy;
	int nCol = (point.x - m_GameTop.x) / m_ElemSize.cx;
	if (nRow >= m_GameH || nCol >= m_GameW) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if (m_bFirstPoint) {	// ��һ��ѡ��
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetFirstPoint(nRow, nCol);
	} 
	else {
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetSecondPoint(nRow, nCol);
		Vertex avPath[2];
		// �ж��Ƿ�Ϊͬһ��ͼƬ
		if (m_gameControl.Link(avPath)) {
			DrawTipLine(avPath);
		}
		UpdateMap();

		Sleep(200);
		InvalidateRect(m_GameRec, FALSE);
	}
	// ÿһ��ѡ�ж���m_bFirstPoint����ֵ
	m_bFirstPoint = !m_bFirstPoint;
}

void CGameDlg::DrawTipLine(Vertex avPath[2])
{
	// ��ȡDC
	CClientDC dc(this);
	// ���û���
	CPen penLine(PS_SOLID, 2, RGB(0,255,0));
	// ������ѡ��DC
	CPen* pOldPen = dc.SelectObject(&penLine);
	// ����������
	dc.MoveTo(m_GameTop.x + avPath[0].col * m_ElemSize.cx + m_ElemSize.cx / 2,
			  m_GameTop.y + avPath[0].row * m_ElemSize.cy + m_ElemSize.cy / 2);

	dc.LineTo(m_GameTop.x + avPath[1].col * m_ElemSize.cx + m_ElemSize.cx / 2,
			  m_GameTop.y + avPath[1].row * m_ElemSize.cy + m_ElemSize.cy / 2);

	dc.SelectObject(pOldPen);
}
