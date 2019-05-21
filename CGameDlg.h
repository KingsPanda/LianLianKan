#pragma once
#include "global.h"
#include "CGameControl.h"
// CGameDlg dialog

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CGameDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	void InitBackground();
	void InitElement();
	void UpdateWindow();
	void UpdateMap();
	void DrawTipFrame(int nRow, int nCol);
	void DrawTipLine(Vertex avPath[2]);				// ������ʾ��
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CDC  m_dcMem;					// �ڴ�DC
	CDC m_dcBG;						// ����DC
	CDC m_dcElement;				// Ԫ��DC
	CDC m_dcMask;					// ����DC
	CRect m_GameRec;				// ��Ϸ����
	CPoint m_GameTop;				// ��Ϸ��ͼ��ʼ��
	CSize m_ElemSize;				// ͼƬ�ߴ�
	CGameControl m_gameControl;		// ��Ϸ������
	bool m_bFirstPoint;				// �Ƿ��ǵ�һ��ѡ�е�ͼƬ
	DECLARE_MESSAGE_MAP()
public:
	static const int m_GameW  = 16;	// ��Ϸ���
	static const int m_GameH  = 10;	// ��Ϸ�߶�
	static const int m_PicCnt = 20;	// ͼƬ��Ŀ
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClickedBtnBasicStart();
	afx_msg void OnBnClickedBtnBasicTip();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
