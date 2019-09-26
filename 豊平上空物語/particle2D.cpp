//=============================================================================
//
// パーティクルの処理 [particle2D.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "particle2D.h"
#include "manager.h"
#include "renderer.h"
#include "resource.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// エフェクトの生成処理
//=============================================================================
CParticle2D *CParticle2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fWidth, float fHeight)
 {
	CParticle2D *pParticle = NULL;

	if (pParticle == NULL)
	{
		// オブジェクトクラスの生成
		pParticle = new CParticle2D;

		if (pParticle != NULL)
		{
			pParticle->Init();
			pParticle->SetCol(col);
			pParticle->SetPosition(pos);
			pParticle->m_move = move;
			pParticle->SetWidth(fWidth);
			pParticle->SetHeight(fHeight);
			pParticle->BindTexture(CResource::GetTexture(CResource::TEXTURE_PARTICLE2D));
		}
	}
	return pParticle;
}

//=============================================================================
// エフェクトクラスのコンストラクタ
//=============================================================================
CParticle2D::CParticle2D(int nPriority, OBJTYPE objType)
{
	// 値をクリア
	m_nLife = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// エフェクトクラスのデストラクタ
//=============================================================================
CParticle2D::~CParticle2D()
{
}

//=============================================================================
// エフェクトの初期化処理
//=============================================================================
HRESULT CParticle2D::Init(void)
{
	// 2Dオブジェクト初期化処理
	CScene2D::Init();

	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_PARTICLE);

	// 値を初期化
	m_nLife = 10;

	return S_OK;
}

//=============================================================================
// エフェクトの終了処理
//=============================================================================
void CParticle2D::Uninit(void)
{
	// 2Dオブジェクト終了処理
	CScene2D::Uninit();
}

//=============================================================================
// エフェクトの更新処理
//=============================================================================
void CParticle2D::Update(void)
{
	// サイズを取得
	float fWidth = CScene2D::GetWidth();

	// サイズを取得
	float fHeight = CScene2D::GetHeight();

	// 位置を取得
	D3DXVECTOR3 pos;
	pos = CScene2D::GetPosition();

	// 頂点バッファを取得
	LPDIRECT3DVERTEXBUFFER9 VtxBuff;
	VtxBuff = CScene2D::GetVtxBuff();

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 一定時間経過
	m_nLife--;

	if (m_nLife <= 0)
	{
		// 消す
		Uninit();
	}

	fWidth -= 1.0f;
	fHeight -= 1.0f;

	if (fWidth <= 0 && fHeight <= 0)
	{
		fWidth = 0.0f;
		fHeight = 0.0f;
	}

	pos -= m_move;

	// 頂点座標の更新
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y - fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y - fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y + fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y + fHeight, 0.0f);

	// 頂点バッファをアンロック
	VtxBuff->Unlock();

	// 位置の設定
	CScene2D::SetPosition(pos);

	// 幅の設定
	CScene2D::SetWidth(fWidth);

	// 高さの設定
	CScene2D::SetHeight(fHeight);

	// 頂点バッファの設定
	CScene2D::SetVtxBuff(VtxBuff);
}

//=============================================================================
// エフェクトの描画処理
//=============================================================================
void CParticle2D::Draw(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 2Dオブジェクト描画処理
	CScene2D::Draw();

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}