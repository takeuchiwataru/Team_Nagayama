//=============================================================================
//
// 3Dポリゴン処理 [scene3D.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "scene3D.h"
#include "main.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "player.h"
#include "game.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BG_SPEED		(0.0005f)	// テクスチャを流すスピード
#define SCENE3D_SIZE	(2.0f)		// サイズの調節

//=============================================================================
// 3Dポリゴンクラスのコンストラクタ
//=============================================================================
CScene3D::CScene3D(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// 値をクリア
	m_pTexture = NULL;						// テクスチャへのポインタ
	m_pVtxBuff = NULL;						// 頂点バッファへのポインタ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き

	for (int nCntNor = 0; nCntNor < NUM_VTX; nCntNor++)
	{
		m_aVec[nCntNor] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 法線
		m_aPos[nCntNor] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 法線
		m_aNor[nCntNor] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 法線
	}
	
	m_fDepth = 0.0f;		// 奥行
	m_fWifth = 0.0f;		// 幅
	m_fTextureU = 0.0f;					// テクスチャ分割数
	m_fTextureV = 0.0f;					// テクスチャ分割数
	m_nCounterAnim = 0;
	m_fBgSpeed = 0.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene3D::~CScene3D()
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CScene3D *CScene3D::Create(D3DXVECTOR3 pos, float fDepth, float fWifth, float fTextureU, float fTextureV)
{
	CScene3D *pScene3D = NULL;

	if (pScene3D == NULL)
	{
		// オブジェクトクラスの生成
		pScene3D = new CScene3D;

		if (pScene3D != NULL)
		{
			pScene3D->m_fDepth = fDepth;
			pScene3D->m_fWifth = fWifth;
			pScene3D->m_fTextureU = fTextureU;
			pScene3D->m_fTextureV = fTextureV;
			pScene3D->Init();
			pScene3D->m_pos = pos;
		}
	}

	return pScene3D;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene3D::Init(void)
{
	// ポリゴンの情報を設定
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounterAnim = 0;
	m_fBgSpeed = BG_SPEED;

	for (int nCntNor = 0; nCntNor < NUM_VTX; nCntNor++)
	{
		m_aVec[nCntNor] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 法線
		m_aPos[nCntNor] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 法線
		m_aNor[nCntNor] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 法線
	}

	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, WATER_NAME, &m_pTexture);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_fWifth, 0.0f, m_fDepth);
	pVtx[1].pos = D3DXVECTOR3(m_fWifth, 0.0f, m_fDepth);
	pVtx[2].pos = D3DXVECTOR3(-m_fWifth, 0.0f, -m_fDepth);
	pVtx[3].pos = D3DXVECTOR3(m_fWifth, 0.0f, -m_fDepth);

	// 法線の設定
	// ベクトルを求める
	m_aVec[0] = pVtx[2].pos - pVtx[3].pos;
	m_aVec[1] = pVtx[1].pos - pVtx[3].pos;
	m_aVec[2] = pVtx[1].pos - pVtx[0].pos;
	m_aVec[3] = pVtx[2].pos - pVtx[0].pos;

	// 外積を使って法線を求める
	D3DXVec3Cross(&m_aNor[0], &m_aVec[0], &m_aVec[1]);
	D3DXVec3Cross(&m_aNor[1], &m_aVec[2], &m_aVec[3]);

	// 正規化する
	D3DXVec3Normalize(&m_aNor[0], &m_aNor[0]);
	D3DXVec3Normalize(&m_aNor[1], &m_aNor[1]);

	// 法線の設定
	pVtx[0].nor = m_aNor[1];
	pVtx[1].nor = (m_aNor[0] + m_aNor[1]) / 2;
	pVtx[2].nor = (m_aNor[0] + m_aNor[1]) / 2;
	pVtx[3].nor = m_aNor[0];

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f * m_fTextureU, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f * m_fTextureV);
	pVtx[3].tex = D3DXVECTOR2(1.0f * m_fTextureU, 1.0f * m_fTextureV);

	for (int nCntPos = 0; nCntPos < NUM_VTX; nCntPos++)
	{
		m_aPos[nCntPos] = pVtx[nCntPos].pos;
		m_aNor[nCntPos] = pVtx[nCntPos].nor;
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScene3D::Uninit(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// 頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// オブジェクトの解放
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScene3D::Update(void)
{
	m_nCounterAnim++;// カウンター加算

	 // 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標を更新
	pVtx[0].tex = D3DXVECTOR2(0.0f - (m_nCounterAnim * (m_fBgSpeed)), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f - (m_nCounterAnim * (m_fBgSpeed)), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f - (m_nCounterAnim * (m_fBgSpeed)), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f - (m_nCounterAnim * (m_fBgSpeed)), 1.0f);

	if (pVtx[0].tex.x > 1.0f)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	}

	if (pVtx[2].tex.x > 1.0f)
	{
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void CScene3D::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// デバイスを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// 法線を取得
//=============================================================================
D3DXVECTOR3 CScene3D::GetNor(int nIdx)
{
	D3DXVECTOR3 vecA[2];
	return m_aNor[nIdx];
}

//=============================================================================
// 高さを取得
//============================================================================
float CScene3D::GetHeight(D3DXVECTOR3 pos)
{
	CScene *pScene = NULL;

	// 先頭のオブジェクトを取得(モデルの優先順位が1だから、1にあるオブジェクトをすべて見る)
	pScene = CScene::GetTop(PLAYER_PRIORITY);

	while (pScene != NULL)
	{// 優先順位が3のオブジェクトを1つ1つ確かめる
	 // 処理の最中に消える可能性があるから先に記録しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// 死亡フラグが立っていないもの
			if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
			{// オブジェクトの種類を確かめる
			 // 右側の三角にいるかどうかを取得
				bool bRTriangle;
				bRTriangle = ((CPlayer*)pScene)->GetRTriangle();

				if (bRTriangle == true)
				{
					pos.y = (((m_aNor[0].x * (pos.x - m_aPos[0].x) + m_aNor[0].z * (pos.z - m_aPos[0].z)) / -m_aNor[0].y) + m_aPos[0].y);
				}
				else
				{
					pos.y = (((m_aNor[3].x * (pos.x - m_aPos[3].x) + m_aNor[3].z * (pos.z - m_aPos[3].z)) / -m_aNor[3].y) + m_aPos[3].y);
				}
			}

			// 次のシーンに進める
			pScene = pSceneNext;
		}
	}
	
	return pos.y;
}

//=============================================================================
// 当たり判定
//=============================================================================
bool CScene3D::ColLand(D3DXVECTOR3 *pos, D3DXVECTOR3 radius)
{
	bool bLand = false;	// 乗っていない状態

	if (pos->x - radius.x < m_pos.x + m_fWifth - SCENE3D_SIZE && pos->x + radius.x > m_pos.x - m_fWifth + SCENE3D_SIZE
		&& pos->z - radius.z <= m_pos.z + m_fDepth - SCENE3D_SIZE && pos->z + radius.z >= m_pos.z - m_fDepth + SCENE3D_SIZE)
	{// 障害物の内側に乗った
		if (pos->y <= m_pos.y - PLAYER_HEIGHT)
		{// 上からブロックに当たったとき
			bLand = true;  // 乗った判定を返す
		}
	}

	return bLand;	// ブロックに乗っているかどうかを返す
}