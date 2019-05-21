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
	void DrawTipLine(Vertex avPath[2]);				// 绘制提示线
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CDC  m_dcMem;					// 内存DC
	CDC m_dcBG;						// 背景DC
	CDC m_dcElement;				// 元素DC
	CDC m_dcMask;					// 掩码DC
	CRect m_GameRec;				// 游戏区域
	CPoint m_GameTop;				// 游戏地图起始点
	CSize m_ElemSize;				// 图片尺寸
	CGameControl m_gameControl;		// 游戏控制类
	bool m_bFirstPoint;				// 是否是第一个选中的图片
	DECLARE_MESSAGE_MAP()
public:
	static const int m_GameW  = 16;	// 游戏宽度
	static const int m_GameH  = 10;	// 游戏高度
	static const int m_PicCnt = 20;	// 图片数目
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClickedBtnBasicStart();
	afx_msg void OnBnClickedBtnBasicTip();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
