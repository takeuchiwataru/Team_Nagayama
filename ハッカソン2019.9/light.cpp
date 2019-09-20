//=============================================================================
//
// ライト処理 [light.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "light.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
D3DLIGHT9 CLight::m_light[MAX_LIGHT] = {};

//=============================================================================
// ライトクラスのコンストラクタ
//=============================================================================
CLight::CLight()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CLight::~CLight()
{
}

//=============================================================================
// ライトの初期化処理
//=============================================================================
void CLight::Init(void)
{
	D3DXVECTOR3 vecDir;

	// デバイスの取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		// ライトをクリアする
		ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));
	}

	// ライトの種類を設定
	m_light[0].Type = D3DLIGHT_DIRECTIONAL;
	m_light[1].Type = D3DLIGHT_DIRECTIONAL;
	m_light[2].Type = D3DLIGHT_DIRECTIONAL;

	// ライトの拡散光を設定
	m_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_light[1].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
	m_light[2].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);

	// ライトの方向の設定
	vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// 正規化する
	m_light[0].Direction = vecDir;

	vecDir = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// 正規化する
	m_light[1].Direction = vecDir;

	vecDir = D3DXVECTOR3(0.9f, -0.1f, 0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// 正規化する
	m_light[2].Direction = vecDir;

	// ライトを設定する
	pDevice->SetLight(0, &m_light[0]);
	pDevice->SetLight(1, &m_light[1]);
	pDevice->SetLight(2, &m_light[2]);

	// ライトを有効にする
	pDevice->LightEnable(0, TRUE);
	pDevice->LightEnable(1, TRUE);
	pDevice->LightEnable(2, TRUE);
}

//=============================================================================
// ライトの終了処理
//=============================================================================
void CLight::Uninit(void)
{
}

//=============================================================================
// ライトの更新処理
//=============================================================================
void CLight::Update(void)
{
}

//=============================================================================
// ライトの取得処理
//=============================================================================
D3DLIGHT9 CLight::GetLight(int nIndex)
{
	return m_light[nIndex];
}