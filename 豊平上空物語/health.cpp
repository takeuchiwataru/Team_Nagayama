//=============================================================================
//
// 体力の処理 [health.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "health.h"
#include "renderer.h"
#include "resource.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_HEALTH	(3)

//=============================================================================
// 体力の生成処理
//=============================================================================
CHealth *CHealth::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CHealth *pHealth = NULL;

	if (pHealth == NULL)
	{
		// 体力クラスの生成
		pHealth = new CHealth;

		if (pHealth != NULL)
		{
			pHealth->SetPosition(pos);
			pHealth->SetWidth(fWidth);
			pHealth->SetHeight(fHeight);
			pHealth->Init();
			pHealth->BindTexture(CResource::GetTexture(CResource::TEXTURE_HEALTH));
		}
	}

	return pHealth;
}

//=============================================================================
// 体力クラスのコンストラクタ
//=============================================================================
CHealth::CHealth() : CScene2D(HEALTH_PRIORITY)
{
	// 値をクリア
	m_nHealth = 0;
}

//=============================================================================
// 体力クラスのデストラクタ
//=============================================================================
CHealth::~CHealth()
{
}

//=============================================================================
// 体力初期化処理
//=============================================================================
HRESULT CHealth::Init(void)
{
	// 2Dポリゴン初期化処理
	CScene2D::Init();

	m_nHealth = MAX_HEALTH;

	return S_OK;
}

//=============================================================================
// 体力終了処理
//=============================================================================
void CHealth::Uninit(void)
{
	// 2Dポリゴン終了処理
	CScene2D::Uninit();
}

//=============================================================================
// 体力更新処理
//=============================================================================
void CHealth::Update(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;
	pVtxBuff = CScene2D::GetVtxBuff();

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_nHealth == 3)
	{
		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		// 頂点情報を設定
		pVtx[0].pos = D3DXVECTOR3(CScene2D::GetPosition().x - 90.0f, CScene2D::GetPosition().y - 40.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(CScene2D::GetPosition().x + 90.0f, CScene2D::GetPosition().y - 40.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(CScene2D::GetPosition().x - 90.0f, CScene2D::GetPosition().y + 40.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(CScene2D::GetPosition().x + 90.0f, CScene2D::GetPosition().y + 40.0f, 0.0f);
	}
	else if (m_nHealth == 2)
	{
		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f * (2.0f / 3.0f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f * (2.0f / 3.0f), 1.0f);
		// 頂点情報を設定
		pVtx[0].pos = D3DXVECTOR3(CScene2D::GetPosition().x - (90.0f * (2.0f / 3.0f)) - 30.0f, CScene2D::GetPosition().y - 40.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(CScene2D::GetPosition().x + (90.0f * (2.0f / 3.0f)) - 30.0f, CScene2D::GetPosition().y - 40.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(CScene2D::GetPosition().x - (90.0f * (2.0f / 3.0f)) - 30.0f, CScene2D::GetPosition().y + 40.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(CScene2D::GetPosition().x + (90.0f * (2.0f / 3.0f)) - 30.0f, CScene2D::GetPosition().y + 40.0f, 0.0f);
	}
	else if (m_nHealth == 1)
	{
		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f * (1.0f / 3.0f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f* (1.0f / 3.0f), 1.0f);
		// 頂点情報を設定
		pVtx[0].pos = D3DXVECTOR3(CScene2D::GetPosition().x - (90.0f * (1.0f / 3.0f)) - 60.0f, CScene2D::GetPosition().y - 40.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(CScene2D::GetPosition().x + (90.0f * (1.0f / 3.0f)) - 60.0f, CScene2D::GetPosition().y - 40.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(CScene2D::GetPosition().x - (90.0f * (1.0f / 3.0f)) - 60.0f, CScene2D::GetPosition().y + 40.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(CScene2D::GetPosition().x + (90.0f * (1.0f / 3.0f)) - 60.0f, CScene2D::GetPosition().y + 40.0f, 0.0f);
	}
	else if (m_nHealth <= 0)
	{
		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	}

	// 頂点バッファをアンロック
	pVtxBuff->Unlock();

	CScene2D::SetVtxBuff(pVtxBuff);
}

//=============================================================================
// 体力描画処理
//=============================================================================
void CHealth::Draw(void)
{
	// 2Dポリゴン描画処理
	CScene2D::Draw();
}

//=============================================================================
// 体力減少処理
//=============================================================================
void CHealth::CutHealth(int nHealth)
{
	m_nHealth -= nHealth;
}