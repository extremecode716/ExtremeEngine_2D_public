#include "stdafx.h"
#include "TreeCtrlDlg.h"


CTreeCtrlDlg::CTreeCtrlDlg()
{
}

CTreeCtrlDlg::CTreeCtrlDlg(UINT nIDTemplate, CWnd * pParent)
	: CDialogEx(nIDTemplate, pParent)
{
}


CTreeCtrlDlg::~CTreeCtrlDlg()
{
}


HTREEITEM CTreeCtrlDlg::AddItem(const wstring & _strName, HTREEITEM _hParent, DWORD_PTR _dwData)
{
	//Tree Control Node Insert
	TVINSERTSTRUCT tItem = {};

	tItem.hParent = _hParent;
	tItem.hInsertAfter = TVI_SORT;  // TVI_FISRT - 제일 뒤쪽에 추가 //TVI_SORT - 정렬
	tItem.item.pszText = const_cast<wchar_t*>(_strName.c_str());
	tItem.item.iImage = 0;
	tItem.item.iSelectedImage = 0;
	tItem.item.mask = TVIF_TEXT;

	HTREEITEM hItem = m_ctrlTree.InsertItem(&tItem);
	m_ctrlTree.SetItemData(hItem, _dwData); // Tree Control은 4바이트 주소값을 넣을 공간을 제공해준다.

	return hItem;
}

void CTreeCtrlDlg::MoveTreeItem(HTREEITEM _hSrcItem, HTREEITEM _hDestItem)
{
	// 이동 시킬 아이템의 정보를 알아낸다.

	wchar_t arrName[255] = {};
	TV_ITEMW item = {};
	item.hItem = _hSrcItem;
	item.pszText = arrName;
	item.cchTextMax = sizeof(arrName);
	item.mask = TVIF_TEXT | TVIF_HANDLE;

	m_ctrlTree.GetItem(&item);
	DWORD_PTR dwData = m_ctrlTree.GetItemData(_hSrcItem);

	HTREEITEM hCopyItem = AddItem(arrName, _hDestItem, dwData);

	// 원본 아이템이 자식이 있다면.
	vector<HTREEITEM> vecChildren;
	GetChildren(_hSrcItem, vecChildren);
	UINT vecSize = vecChildren.size();
	for (UINT i = 0; i < vecSize; ++i)
	{
		MoveTreeItem(vecChildren[i], hCopyItem);
	}

	// 원본이 열린 상태면, 복제아이템도 열어둔다.
	if (item.state & TVIS_EXPANDED)
	{
		m_ctrlTree.Expand(hCopyItem, TVE_EXPAND);
	}

	// 들어가는 목저지를 열어놓는다.
	if (NULL != _hDestItem)
	{
		m_ctrlTree.Expand(_hDestItem, TVE_EXPAND);
	}

	// 원본을 삭제한다.
	m_ctrlTree.DeleteItem(_hSrcItem);

	// 카피 아이템을 선택한다.
	m_ctrlTree.SelectItem(hCopyItem);
}

void CTreeCtrlDlg::GetChildren(HTREEITEM _hParent, vector<HTREEITEM>& _vecOut)
{
	if (!m_ctrlTree.ItemHasChildren(_hParent))
		return;

	HTREEITEM hChild = m_ctrlTree.GetChildItem(_hParent);

	while (true)
	{
		_vecOut.push_back(hChild);
		hChild = m_ctrlTree.GetNextSiblingItem(hChild); // 다음 형제 아이템 search

		if (NULL == hChild)
			break;
	}
}

void CTreeCtrlDlg::DeleteChildren(HTREEITEM _hParent)
{
	if (!m_ctrlTree.ItemHasChildren(_hParent))
		return;

	HTREEITEM hChild = m_ctrlTree.GetChildItem(_hParent);
	HTREEITEM hNextChild = NULL;

	while (true)
	{
		hNextChild = m_ctrlTree.GetNextSiblingItem(hChild);
		m_ctrlTree.DeleteItem(hChild);
		hChild = hNextChild;

		if (NULL == hChild)
			break;
	}
}

void CTreeCtrlDlg::Init()
{
	m_ctrlTree.DeleteAllItems();
	//Invalidate();
}

