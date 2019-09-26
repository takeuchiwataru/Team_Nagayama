//=============================================================================
//
// 円柱のポリゴン処理 [meshCylinder.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "meshCylinder.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CYLINDER_ROT_SPEED	(0.0005f)	// 回転スピード

//=============================================================================
// メッシュシリンダーのコンストラクタ
//=============================================================================
CMeshCylinder::CMeshCylinder(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// 値をクリア
	m_pTexture = NULL;	// テクスチャへのポインタ
	m_pVtxBuff = NULL;	// 頂点バッファへのポインタ
	m_pIdxBuff = NULL;
	m_nNumVerTex = 0;
	m_nNumIndex = 0;
	m_nNumPolygon = 0;
	m_fSizeX = 0.0f;
	m_fSizeY = 0.0f;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bLand = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMeshCylinder::~CMeshCylinder()
{
}

//=============================================================================
// メッシュシリンダーの生成処理
//=============================================================================
CMeshCylinder *CMeshCylinder::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	CMeshCylinder *pMeshCylinder = NULL;

	if (pMeshCylinder == NULL)
	{
		// オブジェクトクラスの生成
		pMeshCylinder = new CMeshCylinder;

		if (pMeshCylinder != NULL)
		{
			pMeshCylinder->m_fSizeX = fSizeX;
			pMeshCylinder->m_fSizeY = fSizeY;
			pMeshCylinder->m_pos = pos;	// 位置の設定
			pMeshCylinder->Init();			// 初期化処理
		}
	}

	return pMeshCylinder;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshCylinder::Init(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{// デバイスの取得
		pDevice = pRenderer->GetDevice();
	}

	int nCntVtxX = 0;
	int nCntVtxY = 0;
	int nCntIdxY;
	int nCntIdxX;
	int nIdxCounter = 0;
	int nCntVtx = 0;
	float fPos_X = 0;
	float fPos_Y = 0;
	float fXpos = -m_fSizeX;
	float fYpos = m_fSizeY;
	int nCntIdx = 0;
	float fCylinder = 0.0f;
	int  nCylinder = 0;

	// 頂点数
	m_nNumVerTex = (CYLINDER_X + 1) * (CYLINDER_Y + 1);

	// インデックス数
	m_nNumIndex = (CYLINDER_X + 1) * (CYLINDER_Y + 1)
		+ (2 * (CYLINDER_Y - 1))
		+ (CYLINDER_X + 1) * (CYLINDER_Y - 1);

	// ポリゴン数
	m_nNumPolygon = m_nNumIndex - 2;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MESHCYLINDER_TEXTURENAME, &m_pTexture);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVerTex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIndex,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,										// 16ビットのデータを確保
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);


	VERTEX_3D *pVtx;
	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	//座標を中心にする
	fPos_X = (fXpos * CYLINDER_X) / 2;
	fPos_Y = (fYpos * CYLINDER_Y) / 2;

	for (nCntVtxY = 0; nCntVtxY < CYLINDER_Y + 1; nCntVtxY++)
	{
		for (nCntVtxX = 0; nCntVtxX < CYLINDER_X + 1; nCntVtxX++)
		{

			//頂点情報の設定
			pVtx[(nCntVtxY + nCntVtxX) + nCntVtx].pos = D3DXVECTOR3(sinf(fCylinder * D3DX_PI) * fXpos, 20.0f - nCylinder, cosf(fCylinder * D3DX_PI) * fXpos);

			// 法線の設定
			pVtx[(nCntVtxY + nCntVtxX) + nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点カラー
			pVtx[(nCntVtxY + nCntVtxX) + nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ座標
			pVtx[(nCntVtxY + nCntVtxX) + nCntVtx].tex = D3DXVECTOR2(0.0f + (nCntVtxX * (1.0f / CYLINDER_X)), 0.0f + (nCntVtxY * (1.0f / CYLINDER_Y)));

			//角度1を上回る
			if (fCylinder >= 1.0f)
			{
				fCylinder = -1.0f;
			}

			//Xの分割数/2で1を割る
			fCylinder += 1.0f / (CYLINDER_X / 2);

		}
		//頂点情報の値を保持
		nCntVtx += CYLINDER_X;
		nCylinder += (int)m_fSizeY;
		fCylinder = 0.0f;
	}

	//SetNor();

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
	
	//インデックスデータへのポインタ
	WORD *pIdx;
	// インデックスバッファをロックし、インデックスデータへのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntIdxY = 0; nCntIdxY < CYLINDER_Y; nCntIdxY++)
	{
		for (nCntIdxX = 0; nCntIdxX < CYLINDER_X + 1; nCntIdxX++, nIdxCounter++)
		{
			pIdx[0] = nIdxCounter + CYLINDER_X + 1;
			pIdx[1] = nIdxCounter;
			pIdx += 2;

			if (nCntIdxY < CYLINDER_Y - 1 && nCntIdxX == CYLINDER_X)
			{
				pIdx[0] = nIdxCounter;
				pIdx[1] = nIdxCounter + (CYLINDER_X + 1) + 1;
				pIdx += 2;
			}
		}
	}

	// インデックスバッファをアンロック
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMeshCylinder::Uninit(void)
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

	// インデックスバッファの開放
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	// オブジェクトの解放
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshCylinder::Update(void)
{
	// 回転
	m_rot.y += CYLINDER_ROT_SPEED;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshCylinder::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{// デバイスの取得
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

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVerTex, 0, m_nNumPolygon);
}

//=============================================================================
// 法線の設定
//=============================================================================
void CMeshCylinder::SetNor(void)
{
	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntPolygon = 0;
	int nCntNorPolygon = 0;

	for (int nCntZ = 0; nCntZ < CYLINDER_Y; nCntZ++)
	{
		for (int nCntX = 0; nCntX < CYLINDER_X; nCntX++)
		{
			D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;
			D3DXVECTOR3 vec0, vec1, vec2;
			D3DXVECTOR3 nor;

			// 一方のポリゴンの２つのベクトルから法線を算出
			pPos0 = &pVtx[nCntX + nCntZ + nCntPolygon].pos;
			pPos1 = &pVtx[(nCntX + nCntZ + nCntPolygon) + (CYLINDER_X + 1)].pos;
			pPos2 = &pVtx[(nCntX + nCntZ + nCntPolygon) + (CYLINDER_X + 1) + 1].pos;
			pPos3 = &pVtx[(nCntX + nCntZ + nCntPolygon) + 1].pos;

			vec0 = *pPos1 - *pPos0;
			vec1 = *pPos2 - *pPos0;
			vec2 = *pPos3 - *pPos0;

			// 外積を使って各ポリゴンの法線を求める
			D3DXVec3Cross(&nor, &vec1, &vec0);
			// 正規化する
			D3DXVec3Normalize(&nor, &nor);
			// 法線を保存
			m_aNor[(nCntZ * 2) + (nCntX * 2) + nCntNorPolygon] = nor;

			// 外積を使って各ポリゴンの法線を求める
			D3DXVec3Cross(&nor, &vec2, &vec1);
			// 正規化する
			D3DXVec3Normalize(&nor, &nor);
			// 法線を保存
			m_aNor[(nCntZ * 2) + (nCntX * 2) + nCntNorPolygon + 1] = nor;
		}

		nCntPolygon += CYLINDER_X;
		nCntNorPolygon += (CYLINDER_X * 2) - 2;
	}

	int nData0 = 0;
	int nData1 = 0;

	for (int nCntPolygonZ = 0; nCntPolygonZ < CYLINDER_Y + 1; nCntPolygonZ++)
	{
		for (int nCntPolygonX = 0; nCntPolygonX < CYLINDER_X + 1; nCntPolygonX++)
		{
			if (nCntPolygonZ == 0)
			{// 上端
				if (nCntPolygonX == 0)
				{// 左端
					pVtx[0].nor = (m_aNor[0] + m_aNor[1]) / 2;
				}
				else if (nCntPolygonX == CYLINDER_X)
				{// 右端
					pVtx[CYLINDER_X].nor = m_aNor[CYLINDER_X + (CYLINDER_X - 1)];
				}
				else
				{// 上端の真ん中
					pVtx[nCntPolygonX].nor =
						(m_aNor[(nCntPolygonX * 2) - 1] + m_aNor[((nCntPolygonX * 2) - 1) + 1] + m_aNor[((nCntPolygonX * 2) - 1) + 2]) / 3;
				}
			}
			else if (nCntPolygonZ == CYLINDER_Y)
			{// 下端
				if (nCntPolygonX == 0)
				{// 左端
					pVtx[CYLINDER_Y * (CYLINDER_X + 1)].nor = m_aNor[2 * (CYLINDER_X * (CYLINDER_Y - 1))];
				}
				else if (nCntPolygonX == CYLINDER_X)
				{// 右端
					pVtx[(CYLINDER_X * CYLINDER_Y) + (CYLINDER_X + CYLINDER_Y)].nor =
						(m_aNor[(2 * (CYLINDER_X * (CYLINDER_Y - 1))) + (2 * (CYLINDER_X - 1))] +
							m_aNor[((2 * (CYLINDER_X * (CYLINDER_Y - 1))) + (2 * (CYLINDER_X - 1))) + 1]) / 2;
				}
				else
				{// 下端の真ん中
					pVtx[(CYLINDER_Y * (CYLINDER_X + 1)) + nCntPolygonX].nor =
						(m_aNor[(CYLINDER_Y - 1) * (CYLINDER_X * 2) + (nCntPolygonX * 2) - 2] +
							m_aNor[((CYLINDER_Y - 1) * (CYLINDER_X * 2) + (nCntPolygonX * 2) - 2) + 1] +
							m_aNor[((CYLINDER_Y - 1) * (CYLINDER_X * 2) + (nCntPolygonX * 2) - 2) + 2]) / 3;
				}
			}
			else
			{// 真ん中
				if (nCntPolygonX == 0)
				{// 左端
					pVtx[(CYLINDER_X + 1) * nCntPolygonZ].nor =
						(m_aNor[(nCntPolygonZ * (2 * CYLINDER_X)) - (2 * CYLINDER_X)] +
							m_aNor[(nCntPolygonZ * (2 * CYLINDER_X))] +
							m_aNor[(nCntPolygonZ * (2 * CYLINDER_X) + 1)]) / 3;
				}
				else if (nCntPolygonX == CYLINDER_X)
				{// 右端
					pVtx[((nCntPolygonZ + 1) * CYLINDER_X) + nCntPolygonZ].nor =
						(m_aNor[((CYLINDER_X - 1) * 2 + ((CYLINDER_X * 2)* (nCntPolygonZ - 1)))]
							+ m_aNor[((CYLINDER_X - 1) * 2 + ((CYLINDER_X * 2)* (nCntPolygonZ - 1))) + 1]
							+ m_aNor[((CYLINDER_X - 1) * 2 + ((CYLINDER_X * 2)* (nCntPolygonZ - 1))) + ((CYLINDER_X * 2) + 1)]) / 3;
				}
				else
				{
					pVtx[(CYLINDER_X + 2) + (nCntPolygonX - 1) + ((nCntPolygonZ * (CYLINDER_X + 1)) - (CYLINDER_X + 1))].nor =
						(m_aNor[((nCntPolygonX - 1) * 2) + ((nCntPolygonZ * (2 * CYLINDER_X)) - (2 * CYLINDER_X))] +
							m_aNor[((((nCntPolygonX - 1) * 2) + 1) + ((nCntPolygonZ * (2 * CYLINDER_X)) - (2 * CYLINDER_X)))] +
							m_aNor[((((nCntPolygonX - 1) * 2) + 2) + ((nCntPolygonZ * (2 * CYLINDER_X)) - (2 * CYLINDER_X)))] +
							m_aNor[((2 * CYLINDER_X) + ((nCntPolygonZ * (2 * CYLINDER_X)) - (2 * CYLINDER_X))) + ((nCntPolygonX * 2) - 1)] +
							m_aNor[((2 * CYLINDER_X) + ((nCntPolygonZ * (2 * CYLINDER_X)) - (2 * CYLINDER_X)) + 1) + ((nCntPolygonX * 2) - 1)] +
							m_aNor[((2 * CYLINDER_X) + ((nCntPolygonZ * (2 * CYLINDER_X)) - (2 * CYLINDER_X)) + 2) + ((nCntPolygonX * 2) - 1)]) / 6;
				}
			}
		}
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}