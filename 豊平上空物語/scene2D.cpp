//=============================================================================
//
// シーン2D処理 [scene2D.h]
// Author : 長山拓実
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "input.h"

//=============================================================================
// シーンクラスのコンストラクタ
//=============================================================================
CScene2D::CScene2D(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// 値をクリア
	m_pTexture = NULL;
	
	m_pVtxBuff = NULL;

	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CScene2D *pScene2D = NULL;

	if (pScene2D == NULL)
	{
		// オブジェクトクラスの生成
		pScene2D = new CScene2D;

		if (pScene2D != NULL)
		{
			pScene2D->m_Pos = pos;
			pScene2D->m_fWidth = fWidth;
			pScene2D->m_fWidth = fHeight;
			pScene2D->Init();
		}
	}

	return pScene2D;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene2D::~CScene2D()
{
}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CScene2D::Init()
{
	// オブジェクトの種類の設定
	//SetObjType(CScene::OBJTYPE_SCENE2D);
	
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
		FVF_VERTEX_2D,									// 頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x - m_fWidth, m_Pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_fWidth, m_Pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x - m_fWidth, m_Pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_fWidth, m_Pos.y + m_fHeight, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CScene2D::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// オブジェクトの解放
	Release();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CScene2D::Update(void)
{
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CScene2D::Draw(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	if (m_pVtxBuff != NULL)
	{
		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, m_pTexture);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//=============================================================================
// 色の設定
//=============================================================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラー
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 位置の取得
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_Pos;
}

//=============================================================================
// 位置の設定
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//=============================================================================
// 幅の取得
//=============================================================================
float CScene2D::GetWidth(void)
{
	return m_fWidth;
}

//=============================================================================
// 幅の設定
//=============================================================================
void CScene2D::SetWidth(float fWidth)
{
	m_fWidth = fWidth;
}

//=============================================================================
// 高さの取得
//=============================================================================
float CScene2D::GetHeight(void)
{
	return m_fHeight;
}

//=============================================================================
// 高さの設定
//=============================================================================
void CScene2D::SetHeight(float fHeight)
{
	m_fHeight = fHeight;
}

//=============================================================================
// 頂点バッファの取得
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 CScene2D::GetVtxBuff(void)
{
	return m_pVtxBuff;
}

//=============================================================================
// 頂点バッファの設定
//=============================================================================
void CScene2D::SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 VtxBuff)
{
	m_pVtxBuff = VtxBuff;
}

//=============================================================================
// 共有テクスチャを割り当てる
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 Texture)
{
	m_pTexture = Texture;
}