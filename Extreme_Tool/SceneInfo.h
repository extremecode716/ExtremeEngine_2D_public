#pragma once
#include "afxwin.h"


// CSceneInfo ��ȭ �����Դϴ�.
struct tLayerInfo;

class CSceneInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CSceneInfo)

public:
	CSceneInfo(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSceneInfo();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCENEINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CEdit                   m_editLayerName;
	CEdit                   m_editCheckCollision1;
	CEdit					m_editCheckCollision2;
	CListBox                m_listBoxLayer;
	CListBox                m_listBoxCollision;

	CMenu					m_menuLayer;
	CMenu					m_menuCollision;
	CString					m_strSelect;

public:
	void UpdateLayer();
	void UpdateCheckCollision();

	afx_msg void OnBnClicked_AddLayer();
	afx_msg void OnBnClicked_AddCheckCollision();
	virtual void PostNcDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLayerDelete();
	afx_msg void OnCollisionDelete();
	afx_msg void OnSelchangeLayerList();
	afx_msg void OnSelchangeCollisionList();

};
