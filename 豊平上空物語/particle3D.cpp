//=============================================================================
//
// パーティクルの処理 [particle3D.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "particle3D.h"
#include "manager.h"
#include "renderer.h"
#include "resource.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PARTICLE3D_GRAVITY	(0.5f)	// 重力

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// パーティクルの生成処理
//=============================================================================
CParticle3D *CParticle3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fWidth, float fHeight, int nLife, PARTICLE_TYPE type, int nTexture)
{
	CParticle3D *pParticle = NULL;

	if (pParticle == NULL)
	{
		// パーティクルクラスの生成
		pParticle = new CParticle3D;

		if (pParticle != NULL)
		{
			pParticle->SetPosition(pos);					// 位置の設定
			pParticle->m_move = move;						// 移動量の設定
			pParticle->SetWidth(fWidth);					// 幅の設定
			pParticle->SetHeight(fHeight);					// 高さの設定
			pParticle->m_nLife = nLife;						// ライフの設定
			pParticle->Init();								// 初期化処理
			pParticle->BindTexture(CResource::GetTexture(nTexture));
			pParticle->m_ParticleType = type;				// 種類の設定
			pParticle->SetCol(col);							// 色の設定
		}
	}
	return pParticle;
}

//=============================================================================
// パーティクルクラスのコンストラクタ
//=============================================================================
CParticle3D::CParticle3D() : CBillboard(PARTICLE_PRIORITY)
{
	// 値をクリア
	m_nLife = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ParticleType = TYPE_NORMAL;
}

//=============================================================================
// パーティクルクラスのデストラクタ
//=============================================================================
CParticle3D::~CParticle3D()
{
}

//=============================================================================
// パーティクルの初期化処理
//=============================================================================
HRESULT CParticle3D::Init(void)
{
	// 2Dオブジェクト初期化処理
	CBillboard::Init();

	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_PARTICLE);

	// タイプの初期設定
	m_ParticleType = TYPE_NORMAL;

	return S_OK;
}

//=============================================================================
// パーティクルの終了処理
//=============================================================================
void CParticle3D::Uninit(void)
{
	// 2Dオブジェクト終了処理
	CBillboard::Uninit();
}

//=============================================================================
// パーティクルの更新処理
//=============================================================================
void CParticle3D::Update(void)
{
	// サイズを取得
	float fWidth = CBillboard::GetWidth();

	// サイズを取得
	float fHeight = CBillboard::GetHeight();

	// 位置を取得
	D3DXVECTOR3 pos;
	pos = CBillboard::GetPosition();

	// 頂点バッファを取得
	LPDIRECT3DVERTEXBUFFER9 VtxBuff;
	VtxBuff = CBillboard::GetVtxBuff();

	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 一定時間経過
	m_nLife--;

	fWidth -= 0.1f;
	fHeight -= 0.1f;

	if (fWidth <= 0 && fHeight <= 0)
	{
		fWidth = 0.0f;
		fHeight = 0.0f;
	}

	// 頂点座標の更新
	pVtx[0].pos = D3DXVECTOR3(-fWidth, fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(fWidth, fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-fWidth, -fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(fWidth, -fHeight, 0.0f);

	pos -= m_move;

	switch (m_ParticleType)
	{
		// 通常状態
	case TYPE_NORMAL:
		break;
		// 上昇状態
	case TYPE_UP:
		// 重力減算
		m_move.y -= cosf(D3DX_PI * 0.0f) * PARTICLE3D_GRAVITY;
		break;
		// 下降状態
	case TYPE_DOWN:
		// 重力加算
		m_move.y += cosf(D3DX_PI * 0.0f) * PARTICLE3D_GRAVITY;
		break;
	}

	// 頂点バッファをアンロック
	VtxBuff->Unlock();

	// 位置の設定
	CBillboard::SetPosition(pos);

	// 回転の設定
	CBillboard::SetRot(m_rot);

	// 幅の設定
	CBillboard::SetWidth(fWidth);

	// 高さの設定
	CBillboard::SetHeight(fHeight);

	if (m_nLife <= 0)
	{
		// 消す
		Uninit();
	}
}

//=============================================================================
// パーティクルの描画処理
//=============================================================================
void CParticle3D::Draw(void)
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

	// 深度バッファを有効にする
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// 2Dオブジェクト描画処理
	CBillboard::Draw();

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// 深度バッファを無効にする
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}