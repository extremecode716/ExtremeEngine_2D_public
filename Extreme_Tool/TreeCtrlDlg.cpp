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
	tItem.hInsertAfter = TVI_SORT;  // TVI_FISRT - ���� ���ʿ� �߰� //TVI_SORT - ����
	tItem.item.pszText = const_cast<wchar_t*>(_strName.c_str());
	tItem.item.iImage = 0;
	tItem.item.iSelectedImage = 0;
	tItem.item.mask = TVIF_TEXT;

	HTREEITEM hItem = m_ctrlTree.InsertItem(&tItem);
	m_ctrlTree.SetItemData(hItem, _dwData); // Tree Control�� 4����Ʈ �ּҰ��� ���� ������ �������ش�.

	return hItem;
}

void CTreeCtrlDlg::MoveTreeItem(HTREEITEM _hSrcItem, HTREEITEM _hDestItem)
{
	// �̵� ��ų �������� ������ �˾Ƴ���.

	wchar_t arrName[255] = {};
	TV_ITEMW item = {};
	item.hItem = _hSrcItem;
	item.pszText = arrName;
	item.cchTextMax = sizeof(arrName);
	item.mask = TVIF_TEXT | TVIF_HANDLE;

	m_ctrlTree.GetItem(&item);
	DWORD_PTR dwData = m_ctrlTree.GetItemData(_hSrcItem);

	HTREEITEM hCopyItem = AddItem(arrName, _hDestItem, dwData);

	// ���� �������� �ڽ��� �ִٸ�.
	vector<HTREEITEM> vecChildren;
	GetChildren(_hSrcItem, vecChildren);
	UINT vecSize = vecChildren.size();
	for (UINT i = 0; i < vecSize; ++i)
	{
		MoveTreeItem(vecChildren[i], hCopyItem);
	}

	// ������ ���� ���¸�, ���������۵� ����д�.
	if (item.state & TVIS_EXPANDED)
	{
		m_ctrlTree.Expand(hCopyItem, TVE_EXPAND);
	}

	// ���� �������� ������´�.
	if (NULL != _hDestItem)
	{
		m_ctrlTree.Expand(_hDestItem, TVE_EXPAND);
	}

	// ������ �����Ѵ�.
	m_ctrlTree.DeleteItem(_hSrcItem);

	// ī�� �������� �����Ѵ�.
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
		hChild = m_ctrlTree.GetNextSiblingItem(hChild); // ���� ���� ������ search

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

