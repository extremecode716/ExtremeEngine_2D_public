#pragma once


// CHierarchyDlg 대화 상자입니다.
#include "TreeCtrlDlg.h"
#include "afxcmn.h"


class CGameObject;

class CHierarchyDlg : public CTreeCtrlDlg
{
	DECLARE_DYNAMIC(CHierarchyDlg)

public:
	CHierarchyDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CHierarchyDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HIERARCHYDLG };
#endif

private:
	bool				m_bDragMouseResDlg; // ResDlg로 드래그 상태
	CGameObject*		m_pDragGameObj;     // 드래그 중인 오브젝트

	HTREEITEM			m_hDragItem;		// 드래그 중인 아이템
	HTREEITEM			m_hTargetItem;		// 목적지 아이템
	HTREEITEM			m_hLBtnClickedItem;   // 좌측 클릭된 아이템
	HTREEITEM			m_hRBtnClickedItem;   // 우측 클릭된 아이템

private:
	void UpdateTreeControl();
	void AddGameObject(CGameObject* _pObj, HTREEITEM _hParent);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void PostNcDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnBegindragTree1(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuAddprefab();
	afx_msg void OnMenuDelete();
	afx_msg void OnTvnKeydownTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void OnOK();
	virtual void OnCancel();
};
