#pragma once
#include "afxwin.h"
// CMapTool_2D ��ȭ �����Դϴ�.

class CTileMgrScript;

class CMapTool_2D : public CDialogEx
{
	DECLARE_DYNAMIC(CMapTool_2D)

public:
	CMapTool_2D(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMapTool_2D();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOL_2D };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

private:
	CTileMgrScript* m_pTileMgrScript;

	DECLARE_MESSAGE_MAP()
public:

	bool  m_bFocuse;
	CEdit m_EditStartPosX;
	CEdit m_EditStartPosY;
	CEdit m_EditTileSizeX;
	CEdit m_EditTileSizeY;
	CEdit m_EditTileCountX;
	CEdit m_EditTileCountY;
	afx_msg void OnMapInfoChangeClickedButton();
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
