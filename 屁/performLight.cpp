//=============================================================================
//
// スポットライト/ポイントライト処理 [performLight.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "performLight.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

//=============================================================================
// ライトクラスのコンストラクタ
//=============================================================================
CPerformLight::CPerformLight()
{
	// 値のクリア
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));	// ライトをクリアする
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置をクリア
}

//=============================================================================
// デストラクタ
//=============================================================================
CPerformLight::~CPerformLight()
{
}

//=============================================================================
// ライトの生成処理
//=============================================================================
CPerformLight *CPerformLight::Create(D3DXVECTOR3 pos, TYPE type)
{
	CPerformLight *pPerformLight = NULL;

	if (pPerformLight == NULL)
	{
		// オブジェクトクラスの生成
		pPerformLight = new CPerformLight;

		if (pPerformLight != NULL)
		{
			pPerformLight->m_pos = pos;
			pPerformLight->m_type = type;

			pPerformLight->Init();
		}
	}

	return pPerformLight;
}

//=============================================================================
// ライトの初期化処理
//=============================================================================
void CPerformLight::Init(void)
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

	// ライトをクリアする
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));

	// ライトの種類を設定
	switch (m_type)
	{
		// ポイントライト
	case TYPE_POINT:
		m_light.Type = D3DLIGHT_POINT;
		break;

		// スポットライト
	case TYPE_SPOT:
		m_light.Type = D3DLIGHT_SPOT;
		break;
	}

	// ライトが放射するディフューズ色を設定
	m_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// スペキュラー色(輝く効果を出す反射)??
	m_light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//環境光(光が当たらない部分へ間接的に当たる光の強さ)??
	m_light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 光源の位置を設定
	m_light.Position = m_pos;

	// ライトの方向の設定
	vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	D3DXVec3Normalize(&vecDir, &vecDir);		//正規化にする
	m_light.Direction = vecDir;

	// 光源の有効距離を設定
	m_light.Range = 500.0f;

	// よくわからんけど開発者の多くは1.0fを設定してるらしい
	m_light.Falloff = 1.0f;

	//ライトの強度(1と2を0.0fにすることで減衰しない光になる)
	m_light.Attenuation0 = 1.0f;
	m_light.Attenuation1 = 0.0f;
	m_light.Attenuation2 = 0.0f;

	//内部コーン（よく光が当たる場所）
	m_light.Theta = D3DXToRadian(30.0f);

	//外部コーン（若干光が当たる場所）
	m_light.Phi = D3DXToRadian(50.0f);

	// ライトを設定する
	pDevice->SetLight(0, &m_light);

	// ライトを有効にする
	pDevice->LightEnable(0, true);
}

//=============================================================================
// ライトの終了処理
//=============================================================================
void CPerformLight::Uninit(void)
{
}

//=============================================================================
// ライトの更新処理
//=============================================================================
void CPerformLight::Update(void)
{
}