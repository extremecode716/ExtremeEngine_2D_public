#pragma once


// CResDlg 대화 상자입니다.
enum class RES_TYPE
{
	MESH,
	TEXTURE,
	MATERIAL,
	PREFAB,
	SOUND,
	CLONE,
	END
};


#include "TreeCtrlDlg.h"

class CResDlg : public CTreeCtrlDlg
{
	DECLARE_DYNAMIC(CResDlg)

public:
	CResDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CResDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESDLG };
#endif

private:
	HTREEITEM m_arrResRoot[(UINT)RES_TYPE::END];
	
	HTREEITEM m_hLBtnClickedItem;	 // 좌측 클릭된 아이템
	HTREEITEM m_hRBtnClickedItem;     // 우측 클릭된 아이템

public:
	void UpdateTreeControl();
	virtual void Init();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	afx_msg void OnNMClickTree2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnKeydownTree2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTree2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnResmenuDelete();
	virtual void OnOK();
	virtual void OnCancel();
};
