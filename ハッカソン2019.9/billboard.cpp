//=============================================================================
//
// ビルボード処理 [Billboard.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "billboard.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"

//=============================================================================
// ビルボードクラスのコンストラクタ
//=============================================================================
CBillboard::CBillboard(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// 値をクリア
	m_pTexture = NULL;						// テクスチャへのポインタ
	m_pVtxBuff = NULL;						// 頂点バッファへのポインタ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転
	D3DXMatrixIdentity(&m_mtxWorld);		// ワールドマトリックスの初期化
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBillboard::~CBillboard()
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CBillboard *CBillboard::Create(D3DXVECTOR3 pos)
{
	CBillboard *pSceneBillboard = NULL;

	if (pSceneBillboard == NULL)
	{
		// オブジェクトクラスの生成
		pSceneBillboard = new CBillboard;

		if (pSceneBillboard != NULL)
		{
			pSceneBillboard->m_pos = pos;
			pSceneBillboard->Init();
		}
	}

	return pSceneBillboard;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBillboard::Init(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;
	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, m_fHeight * 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, m_fHeight * 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, 0.0f, 0.0f);

	//法線の設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBillboard::Uninit(void)
{	
	// 頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;

		// メモリの開放(解体)
		delete m_pVtxBuff;
	}

	// オブジェクトの解放
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBillboard::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CBillboard::Draw(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	D3DXMATRIX  mtxView, mtxTrans;				//計算用マトリックス
	D3DXMATRIX mtxRot;

	//アルファテスト(透明色を描画しないように)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//逆行列を設定
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	VERTEX_3D *pVtx;
	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//法線の設定
	pVtx[0].nor = D3DXVECTOR3(m_mtxWorld._31, m_mtxWorld._32, m_mtxWorld._33);
	pVtx[1].nor = D3DXVECTOR3(m_mtxWorld._31, m_mtxWorld._32, m_mtxWorld._33);
	pVtx[2].nor = D3DXVECTOR3(m_mtxWorld._31, m_mtxWorld._32, m_mtxWorld._33);
	pVtx[3].nor = D3DXVECTOR3(m_mtxWorld._31, m_mtxWorld._32, m_mtxWorld._33);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットを設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ビルボードの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,	//開始する頂点のインデックス
		2); //描画するプリミティブ数

	//レンダーステートの設定を元に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// 頂点バッファの取得
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 CBillboard::GetVtxBuff(void)
{
	return m_pVtxBuff;
}

//=============================================================================
// 頂点バッファの設定
//=============================================================================
void CBillboard::SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 VtxBuff)
{
	m_pVtxBuff = VtxBuff;
}

//=============================================================================
// 位置の取得
//=============================================================================
D3DXVECTOR3 CBillboard::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
// 位置の設定
//=============================================================================
void CBillboard::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// 回転の取得
//=============================================================================
D3DXVECTOR3 CBillboard::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// 回転の設定
//=============================================================================
void CBillboard::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// 共有テクスチャを割り当てる
//=============================================================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 Texture)
{
	m_pTexture = Texture;
}

//=============================================================================
// 幅の取得
//=============================================================================
float CBillboard::GetWidth(void)
{
	return m_fWidth;
}

//=============================================================================
// 幅の設定
//=============================================================================
void CBillboard::SetWidth(float fWidth)
{
	m_fWidth = fWidth;
}

//=============================================================================
// 高さの取得
//=============================================================================
float CBillboard::GetHeight(void)
{
	return m_fHeight;
}

//=============================================================================
// 高さの設定
//=============================================================================
void CBillboard::SetHeight(float fHeight)
{
	m_fHeight = fHeight;
}

//=============================================================================
// 色の設定
//=============================================================================
void CBillboard::SetCol(D3DXCOLOR col)
{
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

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