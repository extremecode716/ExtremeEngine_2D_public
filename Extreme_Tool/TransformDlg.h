#pragma once

#include "ComponentDlg.h"
#include "afxwin.h"
// CTransformDlg ��ȭ �����Դϴ�.

struct tLayerInfo;

class CTransformDlg : public CComponentDlg
{
	DECLARE_DYNAMIC(CTransformDlg)

public:
	CTransformDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTransformDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRANSFORMDLG };
#endif

public:
	virtual void UpdateComponent(CGameObject* _pObj);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	virtual void PostNcDestroy();
public:
	CEdit                   m_arrEdit[3][3];
	bool                    m_bFocus[3][3];
	CEdit                   m_editTag;
	bool	                m_bFocusTag;
	
	CComboBox               m_cbLayer;
	vector<tLayerInfo>		m_vecLayer;
	bool	                m_bFocusLayer;


	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnSetfocus(UINT _id);
	afx_msg void OnEnKillfocus(UINT _id);
	afx_msg void OnEnChange(UINT _id);


	afx_msg void OnEnSetfocusEditTag();
	afx_msg void OnEnKillfocusEditTag();
	afx_msg void OnEnChangeEditTag();
	afx_msg void OnCbnSelchangeLayer();
	afx_msg void OnCbnKillfocusLayer();
	afx_msg void OnCbnSetfocusLayer();
};
