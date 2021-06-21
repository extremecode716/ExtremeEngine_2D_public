#include "SceneMgr.h"

#include "Scene.h"
#include "Layer.h"
#include "GameObject.h"

#include "Transform.h"
#include "MeshRender.h"
#include "Camera.h"
#include "Collider_2D.h"

#include "Animation.h"
#include "Animator.h"

#include "Mesh.h"
#include "Shader.h"
#include "ShaderMgr.h"
#include "ResMgr.h"
#include "CollisionMgr.h"
#include "DestroyMgr.h"

#include "Material.h"

#include "Sound.h"
#include "FontEngine.h"

CSceneMgr::CSceneMgr()
	: m_pCurScene(NULL)
	, m_pPrevScene(NULL)
	, m_pNextScene(NULL)
	, m_bUpdateEvent(false)
	, m_eState(SCENE_STATE::NONE)
	, m_pToolCam(NULL)
{

}


CSceneMgr::~CSceneMgr()
{

	SAFE_DELETE(m_pCurScene);
	SAFE_DELETE(m_pPrevScene);
	SAFE_DELETE(m_pNextScene);
	CFontEngine::DeleteInst();
	CResMgr::GetInst()->ReleasePrefab();
	CResMgr::GetInst()->Release();

}

void CSceneMgr::init()
{
	// Sound Test

	// �ӽ� �׽�Ʈ �� �����ϱ�
	m_pCurScene = new CScene;
	m_pCurScene->AddLayer(L"Mouse");
	m_pCurScene->AddLayer(L"Tile");
	m_pCurScene->AddLayer(L"Portal");
	m_pCurScene->AddLayer(L"Player");
	m_pCurScene->AddLayer(L"Effect");
	m_pCurScene->AddLayer(L"Ui");

	m_pCurScene->AddLayer(L"Default");
	m_pCurScene->AddLayer(L"Transparent");
	m_pCurScene->AddLayer(L"Camera");


	CreateTestScene();

	m_pCurScene->awake();
	m_pCurScene->start();
}

int CSceneMgr::progress()
{
	if (SCENE_STATE::PLAY == m_eState)
	{
		m_pCurScene->update();
		m_pCurScene->lateupdate();
	}
	m_pCurScene->finalupdate();

	//�浹Mgr // ����Ƽ�� ������ �ٸ�.
	CCollisionMgr::GetInst()->update();
	

	return RET_SUCCESS;
}

void CSceneMgr::render()
{
	if (SCENE_STATE::PLAY == m_eState)
	{
		m_pCurScene->render();
	}
	else
	{
#ifdef _EXTREME_TOOL
		m_pCurScene->render(m_pToolCam);
#endif
	}

	////////////
	// Destory
	////////////
	CDestroyMgr::GetInst()->Destory();

	// ��ũ��Ʈ���� ����ȯ�� ��û ������
	if (NULL != m_pNextScene)
	{
		m_mapCurDontDetoryObj.insert(m_mapDontDestoryObj.begin(), m_mapDontDestoryObj.end());
		m_mapDontDestoryObj.clear();
		if (SCENE_STATE::PLAY == m_eState)
		{
			CScene* pTempScene;
			pTempScene = m_pCurScene;
			m_pCurScene = m_pNextScene;

			m_pNextScene->awake();
			m_pNextScene->start();

			m_pCurScene = pTempScene;
		}
		MoveObjectsNextScene(m_pNextScene);
		ChangeScene(m_pNextScene);
	}
}

void CSceneMgr::ChangeScene(CScene * _pNextScene, bool bScript)
{
	if (false == bScript)
	{
		if (NULL != m_pCurScene)
			delete m_pCurScene;

		m_pCurScene = _pNextScene;
		m_pNextScene = NULL;
	}
	else
	{
		m_pNextScene = _pNextScene;
	}
}

void CSceneMgr::MoveObjectsNextScene(CScene * _pNextScene)
{
	const map<wstring, CGameObject*>& mapDontDestroyObj = m_mapCurDontDetoryObj;

	UINT iMapSize = mapDontDestroyObj.size();
	if (iMapSize == 0) return;

	CScene* pCurScene = m_pCurScene;

	map<wstring, CGameObject*>::const_iterator iter = mapDontDestroyObj.begin();
	for (; iter != mapDontDestroyObj.end(); ++iter)
	{
		CLayer* pCurLayer = pCurScene->FindLayer(iter->second->GetLayerName());
		
		CLayer* pNextLayer = _pNextScene->FindLayer(iter->second->GetLayerName());
		if (NULL != pCurLayer)
		{
			// ���� ������ erase �Ѵ�.(���� ���� �ʰ� �ϱ� ����)
			pCurLayer->SubGameObjectByChild(iter->second);
		}
		if (NULL != pNextLayer)
		{
			// ���� ������ ������Ʈ�� �Ѱ��ش�.
			pNextLayer->AddGameObject(iter->second, true, true);
		}
	}
}

void CSceneMgr::ChagneState(SCENE_STATE _eState)
{
	SCENE_STATE ePreState = m_eState;
	m_eState = _eState;
	switch (_eState)
	{
	case SCENE_STATE::NONE:
		break;
	case SCENE_STATE::PLAY:
		if (SCENE_STATE::STOP == ePreState || SCENE_STATE::NONE == ePreState)
		{
			m_pCurScene->awake();
			m_pCurScene->start();
		}
		break;
	case SCENE_STATE::PAUSE:
		break;
	case SCENE_STATE::STOP:
		break;
	case SCENE_STATE::END:
		break;
	default:
		break;
	}
}

/*
�Լ���  : DontDestroyOnLoad(CGameObject * _pObj)
�뵵    : �� ��ȯ�� mapDontDesytoyObj�� ���� �� ��ε��ϴ� �뵵�� ���.
*/
void CSceneMgr::DontDestroyOnLoad(CGameObject * _pObj)
{

	CGameObject* pObj = _pObj;
	CGameObject* pParentObj = _pObj->GetParentObj();
	while (pParentObj != NULL)
	{
		pObj = pParentObj;
		pParentObj = pObj->GetParentObj();
	}

	CLayer* pLayer = GetCurScene()->FindLayer(pObj->GetLayerName());

	if (pLayer == NULL) return;

	m_mapDontDestoryObj.insert(make_pair(pObj->GetTag(), pObj));
}

const map<wstring, CGameObject*>& CSceneMgr::GetDontDestroyObjs()
{
	return m_mapDontDestoryObj;
}

void CSceneMgr::CreateTestScene()
{
	CLayer* pLayer = m_pCurScene->FindLayer(L"Default");
	//pLayer->SetZOrder(true);

	// Scene �� Layer �߰��ϱ�
	//m_pCurScene->AddLayer(L"Player");
	//m_pCurScene->AddLayer(L"Monster");
	//m_pCurScene->AddLayer(L"Bullet");
	//m_pCurScene->AddLayer(L"Item");


	CGameObject* pCamObj = new CGameObject;
	pCamObj->SetTag(L"MainCamera");
	pCamObj->AddComponent<CTransform>(new CTransform);
	pCamObj->AddComponent<CCamera>(new CCamera);
	pCamObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, -1.f));
	pCamObj->Camera()->SetAllLayerRenderCheck();
	//pCamObj->Camera()->LayerRenderCheck(L"Default");
	//pCamObj->Camera()->LayerRenderCheck(L"Portal");
	//pCamObj->Camera()->LayerRenderCheck(L"Player");
	//pCamObj->Camera()->LayerRenderCheck(L"Tile");
	//pCamObj->Camera()->LayerRenderCheck(L"Mouse");
	//pCamObj->Camera()->LayerRenderCheck(L"Portal");
	//pCamObj->Camera()->LayerRenderCheck(L"Player");
	//pCamObj->Camera()->LayerRenderCheck(L"Monster");
	//pCamObj->Camera()->LayerRenderCheck(L"Bullet");
	//pCamObj->Camera()->LayerRenderCheck(L"Item");
	m_pCurScene->FindLayer(L"Camera")->AddGameObject(pCamObj);


	// Texture �ϳ� �ε��ϱ�
	CResPtr<CTexture> pTex =(CTexture*)CResMgr::GetInst()->Load<CTexture>(L"PlayerTex", L"Texture\\PlayerTex1.jpg");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"BasicBulletTex", L"Texture\\BasicBulletTex.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"MissileBulletTex", L"Texture\\MissileBulletTex.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"ParabolaBulletTex", L"Texture\\ParabolaBulletTex.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"RevolveBulletTex", L"Texture\\RevolveBulletTex.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"DvaTex", L"Texture\\DvaTex.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"ShieldItemTex", L"Texture\\ShieldItemTex.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"ControlTex", L"Texture\\ControlTex.png");

	// Effect
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"CriticalTex", L"Texture\\CriticalTex.png");

	// UI
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"Press_EnterKey", L"Texture\\UI\\PressEnter.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"UI_BaseTex", L"Texture\\UI\\UIbasewinTex.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"UI_ShortcutTex", L"Texture\\UI\\UIshortcutTex.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"UI_HpbarTex", L"Texture\\UI\\img_hpbar_mini.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"NumberTex", L"Texture\\UI\\NumberTex.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"YellowNumberTex", L"Texture\\UI\\YellowNumberTex.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"RedNumberTex", L"Texture\\UI\\RedNumberTex.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"EquipWinTex", L"Texture\\UI\\equipwin_bg2.bmp");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"FocuseTileTex", L"Texture\\UI\\FocuseTile.png");


	// inventory Tex
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"itemwin_leftTex", L"Texture\\UI\\itemwin_left.bmp");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"itemwin_midTex", L"Texture\\UI\\itemwin_mid.bmp");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"titlebar_fixTex", L"Texture\\UI\\titlebar_fix.bmp");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"sys_close_offTex", L"Texture\\UI\\sys_close_off.bmp");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"tab_itm_01Tex", L"Texture\\UI\\tab_itm_01.bmp");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"tab_itm_02Tex", L"Texture\\UI\\tab_itm_02.bmp");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"tab_itm_03Tex", L"Texture\\UI\\tab_itm_03.bmp");

	// ItemTex
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��伮�ܰ�Tex", L"Texture\\Item\\��伮�ܰ�.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"�Ӹ���Tex", L"Texture\\Item\\�Ӹ���.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"���ô޸��ư���Tex", L"Texture\\Item\\���ô޸��ư���.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"����Tex", L"Texture\\Item\\����.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��������Tex", L"Texture\\Item\\��������.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��öTex", L"Texture\\Item\\��ö.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��öȭ��Tex", L"Texture\\Item\\��öȭ��.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��ȭŬ��Tex", L"Texture\\Item\\��ȭŬ��.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"�ű�Tex", L"Texture\\Item\\�ű�.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"���Tex", L"Texture\\Item\\���.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��������������Tex", L"Texture\\Item\\��������������.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��е�ī����Tex", L"Texture\\Item\\��е�ī����.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"���߹ٴ�Tex", L"Texture\\Item\\���߹ٴ�.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��ȭTex", L"Texture\\Item\\��ȭ.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"�ɹ���Tex", L"Texture\\Item\\�ɹ���.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"���������Ѿ�üTex", L"Texture\\Item\\���������Ѿ�ü.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"�����ǳ���Tex", L"Texture\\Item\\�����ǳ���.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"�������Tex", L"Texture\\Item\\�������.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"�������ǻ�Tex", L"Texture\\Item\\�������ǻ�.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��ƺ��罺����Tex", L"Texture\\Item\\��ƺ��罺����.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��ƺ��罺�Ƹ�Tex", L"Texture\\Item\\��ƺ��罺�Ƹ�.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"����Tex", L"Texture\\Item\\����.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"���÷�Tex", L"Texture\\Item\\���÷�.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"�̽�ƽ������Tex", L"Texture\\Item\\�̽�ƽ������.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��������Tex", L"Texture\\Item\\��������.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"�̸�����ī��Tex", L"Texture\\Item\\�̸�����ī��.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"�̼���������Tex", L"Texture\\Item\\�̼���������.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"������ŰTex", L"Texture\\Item\\������Ű.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"�Ͼ�����Tex", L"Texture\\Item\\�Ͼ�����.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"��ȸŻTex", L"Texture\\Item\\��ȸŻ.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"�ĵ�Tex", L"Texture\\Item\\�ĵ�.png");

	// Map
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"ground1", L"Texture\\Map\\ground1.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"RagnarokMain", L"Texture\\Map\\RagnarokMain.png");
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"Water1", L"Texture\\Map\\WaterTex.png");
	//pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"Water2", L"Texture\\Map\\Water2.png");
	//pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"Water3", L"Texture\\Map\\Water3.png");

	CreateMaterial();

	CreateGameObject();
}

void CSceneMgr::CreateMaterial()
{
	// �ӽ� mtrl
	// player Mtrl
	CMaterial* pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"TexShader"));
	float fData = 0.f;
	CTexture* pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"PlayerTex");
	pMtrl->SetData(SHADER_PARAM::SP_FLOAT_0, &fData);
	pMtrl->SetData(SHADER_PARAM::SP_TEX_0, &pTex);

	CResMgr::GetInst()->AddMtrl(L"PlayerMtrl", pMtrl);

	// Dva Mtrl
	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"TexShader"));
	fData = 0.f;
	pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"DvaTex");
	pMtrl->SetData(SHADER_PARAM::SP_FLOAT_0, &fData);
	pMtrl->SetData(SHADER_PARAM::SP_TEX_0, &pTex);

	CResMgr::GetInst()->AddMtrl(L"DvaMtrl", pMtrl);

	// Basic Bullet Mtrl
	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"TexShader"));
	fData = 0.f;
	pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"BasicBulletTex");
	pMtrl->SetData(SHADER_PARAM::SP_FLOAT_0, &fData);
	pMtrl->SetData(SHADER_PARAM::SP_TEX_0, &pTex);

	CResMgr::GetInst()->AddMtrl(L"BasicBulletMtrl", pMtrl);

	// Missile Bullet Mtrl;
	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"TexShader"));
	fData = 0.f;
	pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"MissileBulletTex");
	pMtrl->SetData(SHADER_PARAM::SP_FLOAT_0, &fData);
	pMtrl->SetData(SHADER_PARAM::SP_TEX_0, &pTex);

	CResMgr::GetInst()->AddMtrl(L"MissileBulletMtrl", pMtrl);

	// Parabola Bullet Mtrl;
	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"TexShader"));
	fData = 0.f;
	pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"ParabolaBulletTex");
	pMtrl->SetData(SHADER_PARAM::SP_FLOAT_0, &fData);
	pMtrl->SetData(SHADER_PARAM::SP_TEX_0, &pTex);

	CResMgr::GetInst()->AddMtrl(L"ParabolaBulletMtrl", pMtrl);

	// Revolve Bullet Mtrl;
	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"TexShader"));
	fData = 0.f;
	pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"RevolveBulletTex");
	pMtrl->SetData(SHADER_PARAM::SP_FLOAT_0, &fData);
	pMtrl->SetData(SHADER_PARAM::SP_TEX_0, &pTex);

	CResMgr::GetInst()->AddMtrl(L"RevolveBulletMtrl", pMtrl);

	// Revolve Item Mtrl;
	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"TexShader"));
	fData = 0.f;
	pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"ShieldItemTex");
	pMtrl->SetData(SHADER_PARAM::SP_FLOAT_0, &fData);
	pMtrl->SetData(SHADER_PARAM::SP_TEX_0, &pTex);

	CResMgr::GetInst()->AddMtrl(L"ShieldItemMtrl", pMtrl);

	//Control Mtrl
	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"TexShader"));
	fData = 0.f;
	pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"ControlTex");
	pMtrl->SetData(SHADER_PARAM::SP_FLOAT_0, &fData);
	pMtrl->SetData(SHADER_PARAM::SP_TEX_0, &pTex);

	CResMgr::GetInst()->AddMtrl(L"ControlMtrl", pMtrl);

	// Effect Mtrl
	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"TexShader"));
	CResMgr::GetInst()->AddMtrl(L"EffectMtrl", pMtrl);
	pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"CriticalTex");
	pMtrl->SetData(SHADER_PARAM::SP_TEX_0, &pTex);

	// UI Mtrl
	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"TexShader"));
	fData = 0.f;
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"UI_BaseTex");
	pMtrl->SetData(SHADER_PARAM::SP_FLOAT_0, &fData);
	pMtrl->SetData(SHADER_PARAM::SP_TEX_0, &pTex);
	CResMgr::GetInst()->AddMtrl(L"UIMtrl", pMtrl);

	// UIsMtrl
	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"TexShader"));
	fData = 0.f;
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"UI_ShortcutTex");
	pMtrl->SetData(SHADER_PARAM::SP_FLOAT_0, &fData);
	pMtrl->SetData(SHADER_PARAM::SP_TEX_0, &pTex);
	CResMgr::GetInst()->AddMtrl(L"UIsMtrl", pMtrl);

	// Splite Mtrl
	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"Split2DShader"));	
	int iData = 0;
	pMtrl->SetData(SHADER_PARAM::SP_INT_0, &iData);
	Vec4 vSplit = { 0.f, 0.f, 1.f, 1.f };
	pMtrl->SetData(SHADER_PARAM::SP_VEC4_0, &vSplit);
	CResMgr::GetInst()->AddMtrl(L"SpliteMtrl", pMtrl);

	// Slot Mtrl
	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"TexShader"));
	fData = 0.f;
	pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"itemwin_midTex");
	pMtrl->SetData(SHADER_PARAM::SP_FLOAT_0, &fData);
	pMtrl->SetData(SHADER_PARAM::SP_TEX_0, &pTex);
	CResMgr::GetInst()->AddMtrl(L"SlotMtrl", pMtrl);

	// Damage Mtrl
	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"Damage2DShader"));
	CResMgr::GetInst()->AddMtrl(L"DamageMtrl", pMtrl);

	// Item Mtrl
	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"TexShader"));
	fData = 0.f;
	pMtrl->SetData(SHADER_PARAM::SP_FLOAT_0, &fData);
	CResMgr::GetInst()->AddMtrl(L"ItemMtrl", pMtrl);

	// Black Effect Mtrl
	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"Std2DShader"));
	CResMgr::GetInst()->AddMtrl(L"EffectStd2DShader", pMtrl);

	// MapMtrl Mtrl
	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"Std2DShader"));
	CResMgr::GetInst()->AddMtrl(L"MapMtrl", pMtrl);

	// Flow Mtrl
	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"FlowStd2DShader"));
	CResMgr::GetInst()->AddMtrl(L"FlowStd2DMtrl", pMtrl);

	// MapMtrl Mtrl
	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"Std2DShader"));
	CResMgr::GetInst()->AddMtrl(L"MainMapMtrl", pMtrl);

	// Std2DMtrl Mtrl
	pMtrl = new CMaterial;
	pMtrl->SetShader(CShaderMgr::GetInst()->FindShader(L"Std2DShader"));

	CResMgr::GetInst()->AddMtrl(L"Std2DMtrl", pMtrl);

}



void CSceneMgr::CreateGameObject()
{
	/*
	// ī�޶� GameObject �߰��ϱ�
	CGameObject* pCamObj = new CGameObject;
	pCamObj->SetTag(L"MainCamera");
	pCamObj->AddComponent<CTransform>(new CTransform);
	pCamObj->AddComponent<CCamera>(new CCamera);
	pCamObj->AddComponent<CScript>(new CCameraScript);

	// ī�޶� Render check
	pCamObj->Camera()->LayerRenderCheck(L"Default");
	pCamObj->Camera()->LayerRenderCheck(L"Player");
	pCamObj->Camera()->LayerRenderCheck(L"Monster");
	pCamObj->Camera()->LayerRenderCheck(L"Bullet");
	pCamObj->Camera()->LayerRenderCheck(L"Item");

	m_pCurScene->FindLayer(L"Camera")->AddGameObject(pCamObj);


	/////////////////
	// Create Prefab 
	/////////////////

	// Basic Bullet Prefab
	CGameObject* pBasicBulletPrefab = new CGameObject;
	pBasicBulletPrefab->SetTag(L"BasicBullet");
	pBasicBulletPrefab->AddComponent<CTransform>(new CTransform);
	pBasicBulletPrefab->AddComponent<CMeshRender>(new CMeshRender);
	pBasicBulletPrefab->AddComponent<CScript>(new CBasicBulletScript);

	pBasicBulletPrefab->MeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pBasicBulletPrefab->MeshRender()->SetMaterial(CResMgr::GetInst()->FindMaterial(L"BasicBulletMtrl"));

	CResMgr::GetInst()->AddPrefab(L"BasicBullet", pBasicBulletPrefab);

	// Parabola Bullet Prefab
	CGameObject* pParabolaBulletPrefab = new CGameObject;
	pParabolaBulletPrefab->SetTag(L"ParabolaBullet");
	pParabolaBulletPrefab->AddComponent<CTransform>(new CTransform);
	pParabolaBulletPrefab->AddComponent<CMeshRender>(new CMeshRender);
	pParabolaBulletPrefab->AddComponent<CScript>(new CParabolaBulletScript);

	pParabolaBulletPrefab->MeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pParabolaBulletPrefab->MeshRender()->SetMaterial(CResMgr::GetInst()->FindMaterial(L"ParabolaBulletMtrl"));

	CResMgr::GetInst()->AddPrefab(L"ParabolaBullet", pParabolaBulletPrefab);

	// Missile Bullet Prefab
	CGameObject* pMissileBulletPrefab = new CGameObject;
	pMissileBulletPrefab->SetTag(L"MissileBullet");
	pMissileBulletPrefab->AddComponent<CTransform>(new CTransform);
	pMissileBulletPrefab->AddComponent<CMeshRender>(new CMeshRender);
	pMissileBulletPrefab->AddComponent<CScript>(new CMissileBulletScript);

	pMissileBulletPrefab->MeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pMissileBulletPrefab->MeshRender()->SetMaterial(CResMgr::GetInst()->FindMaterial(L"MissileBulletMtrl"));

	CResMgr::GetInst()->AddPrefab(L"MissileBullet", pMissileBulletPrefab);


	// Revolve Bullet Prefab
	CGameObject* pRevolveBulletPrefab = new CGameObject;
	pRevolveBulletPrefab->SetTag(L"RevolveBullet");
	pRevolveBulletPrefab->AddComponent<CTransform>(new CTransform);
	pRevolveBulletPrefab->AddComponent<CMeshRender>(new CMeshRender);
	pRevolveBulletPrefab->AddComponent<CScript>(new CRevolveBulletScript);

	pRevolveBulletPrefab->MeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pRevolveBulletPrefab->MeshRender()->SetMaterial(CResMgr::GetInst()->FindMaterial(L"RevolveBulletMtrl"));

	CResMgr::GetInst()->AddPrefab(L"RevolveBullet", pRevolveBulletPrefab);

	// Revolve Item Prefab
	CGameObject* pRevolveItemPrefab = new CGameObject;
	pRevolveItemPrefab->SetTag(L"RevolveItem");
	pRevolveItemPrefab->AddComponent<CTransform>(new CTransform);
	pRevolveItemPrefab->AddComponent<CMeshRender>(new CMeshRender);
	pRevolveItemPrefab->AddComponent<CScript>(new CRevolveItemScript);

	pRevolveItemPrefab->MeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pRevolveItemPrefab->MeshRender()->SetMaterial(CResMgr::GetInst()->FindMaterial(L"ShieldItemMtrl"));

	CResMgr::GetInst()->AddPrefab(L"RevolveItem", pRevolveItemPrefab);

	//////////////////////
	// Create GameObject
	//////////////////////


	// Monster GameObject
	CGameObject* pMonster = new CGameObject;
	pMonster->SetTag(L"Monster");
	pMonster->AddComponent<CTransform>(new CTransform);
	pMonster->AddComponent<CMeshRender>(new CMeshRender);
	pMonster->AddComponent<CScript>(new CMonsterScript);
	pMonster->AddComponent<CCollider>(new CCollider_2D);

	pMonster->Transform()->SetLocalScale(Vec3(100.f, 100.f, 98.f));
	pMonster->Transform()->SetLocalPos(Vec3(0.f, 0.f, 100.f));
	pMonster->MeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pMonster->MeshRender()->SetMaterial(CResMgr::GetInst()->FindMaterial(L"DvaMtrl"));
	pMonster->Collider()->SetOffsetScale(Vec3(1.0f, 1.0f, 1.f));

	m_pCurScene->FindLayer(L"Monster")->AddGameObject(pMonster);

	// �÷��̾� GameObject �����
	CGameObject* pPlayer = new CGameObject;
	pPlayer->SetTag(L"Player");
	pPlayer->AddComponent<CTransform>(new CTransform);
	pPlayer->AddComponent<CMeshRender>(new CMeshRender);
	pPlayer->AddComponent<CScript>(new CPlayerScript);
	pPlayer->AddComponent<CCollider>(new CCollider_2D);
	pPlayer->AddComponent<CAnimator>(new CAnimator);

	pPlayer->MeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pPlayer->MeshRender()->SetMaterial(CResMgr::GetInst()->FindMaterial(L"Std2DMtrl"));
	pPlayer->Collider()->SetOffsetScale(Vec3(1.0f, 1.0f, 1.f));

	CTexture* pTex = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"PlayerTex");
	pPlayer->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::SP_TEX_0, &pTex);

	pPlayer->Animator()->LoadAnimation_2D(L"Texture\\Animation\\Explosion");
	pPlayer->Animator()->LoadAnimation_2D(L"Texture\\Animation\\Explosion_01");
	pPlayer->Animator()->LoadAnimation_2D(L"Texture\\Animation\\Player");
	pPlayer->Animator()->PlayAnimation(L"EXPLOSION_01");

	m_pCurScene->FindLayer(L"Player")->AddGameObject(pPlayer);


	// Respawn GameObject
	CGameObject* pObj = new CGameObject;
	pObj->SetTag(L"ItemRespawn");
	pObj->AddComponent<CTransform>(new CTransform);
	pObj->AddComponent<CMeshRender>(new CMeshRender);
	pObj->AddComponent<CScript>(new CRespawnScript);

	m_pCurScene->FindLayer(L"Default")->AddGameObject(pObj);


	// ControlUI GameObject
	pObj = new CGameObject;
	pObj->SetTag(L"ControlUI");
	pObj->AddComponent<CTransform>(new CTransform);
	pObj->AddComponent<CMeshRender>(new CMeshRender);

	pObj->Transform()->SetLocalPos(Vec3(-700.f, -300.f, 100.f));
	pObj->Transform()->SetLocalScale(Vec3(300.f, 300.f, 1.f));
	pObj->MeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindMaterial(L"ControlMtrl"));

	m_pCurScene->FindLayer(L"Default")->AddGameObject(pObj);

	//*/
}
