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
	void DrawTipLine(Vertex avPath[4], int nVexNum);				// ������ʾ��
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
	bool m_bPlaying;				// ��Ϸ״̬��ʶ����ʶ��Ϸ�Ƿ����ڽ���
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClickedBtnBasicStart();
	afx_msg void OnBnClickedBtnBasicTip();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
private:
	static const int m_GameW  = MAX_COL;		// ��Ϸ���
	static const int m_GameH  = MAX_ROW;		// ��Ϸ�߶�
	static const int m_PicCnt = MAX_PICNUM;		// ͼƬ��Ŀ
};
