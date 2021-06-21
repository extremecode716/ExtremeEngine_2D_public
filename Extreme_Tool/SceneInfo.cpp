// SceneInfo.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Extreme_Tool.h"
#include "SceneInfo.h"
#include "afxdialogex.h"

#include "SceneMgr.h"
#include "Scene.h"
#include "Layer.h"
#include "CollisionMgr.h"


// CSceneInfo ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSceneInfo, CDialogEx)

CSceneInfo::CSceneInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SCENEINFO, pParent)
{

}

CSceneInfo::~CSceneInfo()
{
}

void CSceneInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editLayerName);
	DDX_Control(pDX, IDC_EDIT2, m_editCheckCollision1);
	DDX_Control(pDX, IDC_EDIT3, m_editCheckCollision2);
	DDX_Control(pDX, IDC_LIST1, m_listBoxLayer);
	DDX_Control(pDX, IDC_LIST2, m_listBoxCollision);
}


BEGIN_MESSAGE_MAP(CSceneInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSceneInfo::OnBnClicked_AddLayer)
	ON_BN_CLICKED(IDC_BUTTON5, &CSceneInfo::OnBnClicked_AddCheckCollision)
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_LAYERMENU_DELETE, &CSceneInfo::OnLayerDelete)
	ON_COMMAND(ID_COLLISIONMENU_DELETE, &CSceneInfo::OnCollisionDelete)
	ON_LBN_SELCHANGE(IDC_LIST1, &CSceneInfo::OnSelchangeLayerList)
	ON_LBN_SELCHANGE(IDC_LIST2, &CSceneInfo::OnSelchangeCollisionList)
END_MESSAGE_MAP()


// CSceneInfo �޽��� ó�����Դϴ�.


void CSceneInfo::UpdateLayer()
{
	vector<tLayerInfo>		vecLayer;
	vecLayer.clear();
	m_listBoxLayer.ResetContent();
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	pCurScene->GetLayers(vecLayer);

	UINT iVecSize = vecLayer.size();
	for (UINT i = 0; i < iVecSize; ++i)
	{
		m_listBoxLayer.InsertString(i, vecLayer[i].strName.c_str());
	}
}

void CSceneInfo::UpdateCheckCollision()
{

	vector<tLayerInfo>	vecLayer;
	vecLayer.clear();
	m_listBoxCollision.ResetContent();
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	pCurScene->GetLayers(vecLayer);
	const UINT* pArrColMat = CCollisionMgr::GetInst()->GetArrColMat();
	UINT listNum = 0;
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		for (UINT j = i; j < MAX_LAYER; ++j)
		{
			if ((pArrColMat[i] >> j) & 1)    // ���̾� �浹 ����
			{
		/*		wstring strCheckCol = 
				m_listBoxCollision.InsertString(listNum, )*/
			}
		}
	}
}

void CSceneInfo::PostNcDestroy()
{
	delete this;
	CDialogEx::PostNcDestroy();
}


BOOL CSceneInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_menuLayer.LoadMenuW(IDR_MENU1);
	m_menuCollision.LoadMenuW(IDR_MENU1);
	return TRUE;  // return TRUE unless you set the focus to a control
}


void CSceneInfo::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		UpdateLayer();
	}
}


/*
�Լ���  : OnBnClicked_AddLayer()
�뵵    : ��ư�� ������ ��� editLayer Text�� �о� ���̾� �߰�
*/
void CSceneInfo::OnBnClicked_AddLayer()
{
	CString str;
	m_editLayerName.GetWindowTextW(str);
	if (true == str.IsEmpty())
	{
		MessageBox(L"�Էµ��� �ʾҽ��ϴ�", L"���â", MB_OK);
		return;
	}

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddLayer(str.GetBuffer());

	UpdateLayer();
}
/*
�Լ���  : OnSelchangeLayerList()
�뵵    : ���̾� ����Ʈ �ڽ� ������ ����Ǿ��� ��� ���̾�� �޴��� ���
*/
void CSceneInfo::OnSelchangeLayerList()
{
	
		int iIdx = m_listBoxLayer.GetCurSel();
		if (-1 == iIdx) return;
		m_listBoxLayer.GetText(iIdx, m_strSelect);
	
		CMenu *p_Menu = m_menuLayer.GetSubMenu(4);
		if (NULL == p_Menu) return;

		CPoint	point;
		GetCursorPos(&point);
		p_Menu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

/*
�Լ���  : OnLayerDelete()
�뵵    : ���̾�� �޴� �� Delete ��ư�� ������ ��� ���̾��Ʈ�ڽ� �� �� ���̾�� �����ϴ� �뵵.
*/
void CSceneInfo::OnLayerDelete()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->DeleteLayer(m_strSelect.GetBuffer());
	UpdateLayer();
}


/*
�Լ���  : OnBnClicked_AddCheckCollision()
�뵵    : ��ư�� ������ ��� editCollision1/2 Text�� �о� üũ �� �浹üũ
*/
void CSceneInfo::OnBnClicked_AddCheckCollision()
{
	CString str1 , str2;
	m_editCheckCollision1.GetWindowTextW(str1);
	m_editCheckCollision2.GetWindowTextW(str2);

	if (true == str1.IsEmpty() || true == str2.IsEmpty())
	{
		MessageBox(L"�Էµ��� �ʾҽ��ϴ�", L"���â", MB_OK);
		return;
	}

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLeftLayer = pCurScene->FindLayer(str1.GetBuffer());
	CLayer* pRightLayer = pCurScene->FindLayer(str2.GetBuffer());

	if (pLeftLayer == NULL || pRightLayer == NULL)
	{
		MessageBox(L"���̾ �����ϴ�", L"���â", MB_OK);
		return;
	}


	//UpdateCheckCollision();
}


void CSceneInfo::OnSelchangeCollisionList()
{

}


void CSceneInfo::OnCollisionDelete()
{
}
