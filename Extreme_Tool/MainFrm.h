
// MainFrm.h : CMainFrame 클래스의 인터페이스
//

#pragma once
#include "MySplitterWnd.h"

class CMapTool_2D;
class CSceneInfo;

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CMySplitterWnd m_MainSplitter;
	CMySplitterWnd m_SubSplitter;
	CMapTool_2D*   m_pMapTool2D;
	CSceneInfo*	   m_pSceneInfo;

public:
	HWND GetGameViewHwnd() { return m_SubSplitter.GetPane(1, 0)->m_hWnd; }
	CWnd* GetComponentView() { return m_MainSplitter.GetPane(0, 2); }
	CWnd* GetDebugView() { return m_SubSplitter.GetPane(2, 0); }
	CWnd* GetHierarchyView() { return m_MainSplitter.GetPane(0, 1); }
	CWnd* GetBtnView() { return m_SubSplitter.GetPane(0, 0); }
	void Init();
	void update();

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//afx_msg void OnApplicationLook(UINT id);
	//afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAddGameObject();
	afx_msg void OnSceneSave();
	afx_msg void OnSceneLoad();
	afx_msg void OnTileTool();
	afx_msg void OnToolTextureload();
	afx_msg void OnSceneSceneinfo();
};


