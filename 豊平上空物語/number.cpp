//=============================================================================
//
// ナンバー処理 [number.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "number.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "resource.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// ナンバーの生成処理
//=============================================================================
CNumber *CNumber::Create(D3DXVECTOR3 pos, float fSize)
{
	CNumber *pNumber = NULL;

	if (pNumber == NULL)
	{
		// オブジェクトクラスの生成
		pNumber = new CNumber;

		if (pNumber != NULL)
		{
			pNumber->Init(pos, fSize);
		}
	}

	return pNumber;
}

//=============================================================================
// ナンバークラスのコンストラクタ
//=============================================================================
CNumber::CNumber()
{
	// 値をクリア
	m_pVtxBuff = NULL;
}

//=============================================================================
// ナンバークラスのデストラクタ
//=============================================================================
CNumber::~CNumber()
{
}

//=============================================================================
// ナンバー初期化処理
//=============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, float fSize)
{
	// ポリゴンの位置を設定
	// 位置を取得
	D3DXVECTOR3 posNumber;
	posNumber = pos;

	// サイズを取得
	float fNumSize;
	fNumSize = fSize;

	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// 頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(posNumber.x - fNumSize, posNumber.y - fNumSize, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(posNumber.x + fNumSize, posNumber.y - fNumSize, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(posNumber.x - fNumSize, posNumber.y + fNumSize, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(posNumber.x + fNumSize, posNumber.y + fNumSize, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// ナンバー終了処理
//=============================================================================
void CNumber::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// ナンバー更新処理
//=============================================================================
void CNumber::Update(void)
{

}

//=============================================================================
// ナンバー描画処理
//=============================================================================
void CNumber::Draw(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, CResource::GetTexture(CResource::TEXTURE_NUMBER));

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// ナンバー設定処理
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + (nNumber * 0.1f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + (nNumber * 0.1f), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (nNumber * 0.1f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (nNumber * 0.1f), 1.0f);

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 色の設定処理
//=============================================================================
void CNumber::SetColor(D3DXCOLOR color)
{
	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}