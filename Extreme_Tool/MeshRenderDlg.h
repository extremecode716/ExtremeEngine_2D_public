#pragma once


// CMeshRenderDlg ��ȭ �����Դϴ�.

#include "ComponentDlg.h"
#include "afxwin.h"
#include "MaterialDlg.h"

class CMeshRenderDlg : public CComponentDlg
{
	DECLARE_DYNAMIC(CMeshRenderDlg)

public:
	CMeshRenderDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMeshRenderDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MESHRENDERDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	vector<CMaterialDlg*> m_vecMtrlDlg;

	CEdit m_editMesh;
	CEdit m_editMtrl;
	CComboBox m_cbRS;

	bool m_bFocus_mesh;
	bool m_bFocus_mtrl;
	bool m_bFocus_rs;


	LONG m_lHeightDlg;
	bool m_bMtrlShaderBn;
	CButton m_bnMtrlSP;

public:
	virtual void UpdateComponent(CGameObject* _pObj);
	virtual void PostNcDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnEnSetfocus(UINT _id);
	afx_msg void OnEnKillfocus(UINT _id);

	afx_msg void OnCbnSetfocusRs();
	afx_msg void OnCbnKillfocusRs();
	afx_msg void OnCbnEditchangeRs();
	afx_msg void OnCbnSelchangeRs();
	afx_msg void OnMeshBnClicked();
	afx_msg void OnMatrlBnClicked();
	afx_msg void OnSubComponentBnClicked();
	afx_msg void OnMtrlShaderBnClicked();
};
