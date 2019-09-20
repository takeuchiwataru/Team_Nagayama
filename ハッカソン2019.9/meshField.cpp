//=============================================================================
//
// メッシュフィールドの処理 [meshField.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "meshField.h"
#include "main.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"

//=============================================================================
// メッシュフィールドのコンストラクタ
//=============================================================================
CMeshField::CMeshField(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// 値をクリア
	m_pTexture = NULL;	// テクスチャへのポインタ
	m_pVtxBuff = NULL;	// 頂点バッファへのポインタ
	m_pIdxBuff = NULL;
	m_nNumVerTex = 0;
	m_nNumIndex = 0;
	m_nNumPolygon = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCntNor = 0; nCntNor < NUM_POLYGON; nCntNor++)
	{
		m_aNor[nCntNor] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	for (int nCntZ = 0; nCntZ < POLYGON_Z + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < POLYGON_X + 1; nCntX++)
		{
			m_aHeight[nCntZ][nCntX] = 0.0f;
		}
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CMeshField::~CMeshField()
{
}

//=============================================================================
// メッシュフィールドの生成処理
//=============================================================================
CMeshField *CMeshField::Create(D3DXVECTOR3 pos)
{
	CMeshField *pMeshField = NULL;

	if (pMeshField == NULL)
	{
		// オブジェクトクラスの生成
		pMeshField = new CMeshField;

		if (pMeshField != NULL)
		{
			pMeshField->m_pos = pos;	// 位置の設定
			pMeshField->Init();			// 初期化処理
		}
	}

	return pMeshField;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshField::Init(void)
{
	// 値の初期化
	m_pTexture = NULL;	// テクスチャへのポインタ
	m_pVtxBuff = NULL;	// 頂点バッファへのポインタ
	m_pIdxBuff = NULL;
	m_nNumVerTex = 0;
	m_nNumIndex = 0;
	m_nNumPolygon = 0;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bLand = false;
	for (int nCntZ = 0; nCntZ < POLYGON_Z + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < POLYGON_X + 1; nCntX++)
		{
			m_aHeight[nCntZ][nCntX] = 0.0f;
		}
	}

	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{// デバイスの取得
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURE_NAME, &m_pTexture);

	// 頂点情報の作成
	int nVtxCounter = 0;
	int nIdxCounter = 0;

	int nCntVtxZ;
	int nCntVtxX;
	int nCntIdxZ;
	int nCntIdxX;

	// 頂点数
	m_nNumVerTex = (POLYGON_X + 1) * (POLYGON_Z + 1);

	// インデックス数
	m_nNumIndex = (POLYGON_X + 1) * (POLYGON_Z + 1)
		+ (2 * (POLYGON_Z - 1))
		+ (POLYGON_X + 1) * (POLYGON_Z - 1);

	// ポリゴン数
	m_nNumPolygon = m_nNumIndex - 2;

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

	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntVtxZ = 0; nCntVtxZ < POLYGON_Z + 1; nCntVtxZ++)
	{
		for (nCntVtxX = 0; nCntVtxX < POLYGON_X + 1; nCntVtxX++)
		{
			// 頂点座標の設定
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].pos = D3DXVECTOR3((nCntVtxX * MESHFIELD_SIZE), 0.0f, (-nCntVtxZ * MESHFIELD_SIZE));
			// 法線の設定
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			// 頂点カラーの設定
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			// テクスチャ座標の設定
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].tex = 
				D3DXVECTOR2(0.0f + (nCntVtxX), 0.0f + (nCntVtxZ));
		}
		nVtxCounter += POLYGON_X;
	}
	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	SetNor();	// 法線の設定

	WORD *pIdx;	// インデックスデータへのポインタ

	// インデックスバッファをロックし、インデックスデータへのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntIdxZ = 0; nCntIdxZ < POLYGON_Z; nCntIdxZ++)
	{
		for (nCntIdxX = 0; nCntIdxX < POLYGON_X + 1; nCntIdxX++, nIdxCounter++)
		{
			pIdx[0] = nIdxCounter + POLYGON_X + 1;
			pIdx[1] = nIdxCounter;
			pIdx += 2;

			if (nCntIdxZ < POLYGON_Z - 1 && nCntIdxX == POLYGON_X)
			{
				pIdx[0] = nIdxCounter;
				pIdx[1] = nIdxCounter + (POLYGON_X + 1) + 1;
				pIdx += 2;
			}
		}
	}

	// インデックスバッファをアンロック
	m_pIdxBuff->Unlock();

	LoadHeight();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMeshField::Uninit(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;

		// メモリの開放(解体)
		delete m_pTexture;
	}

	// 頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;

		// メモリの開放(解体)
		delete m_pVtxBuff;
	}

	// インデックスバッファの開放
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;

		// メモリの開放(解体)
		delete m_pIdxBuff;
	}

	// オブジェクトの解放
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshField::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshField::Draw(void)
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
void CMeshField::SetNor(void)
{
	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntPolygon = 0;
	int nCntNorPolygon = 0;

	for (int nCntZ = 0; nCntZ < POLYGON_Z; nCntZ++)
	{
		for (int nCntX = 0; nCntX < POLYGON_X; nCntX++)
		{
			D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;
			D3DXVECTOR3 vec0, vec1, vec2;
			D3DXVECTOR3 nor;

			// 一方のポリゴンの２つのベクトルから法線を算出
			pPos0 = &pVtx[nCntX + nCntZ + nCntPolygon].pos;
			pPos1 = &pVtx[(nCntX + nCntZ + nCntPolygon) + (POLYGON_X + 1)].pos;
			pPos2 = &pVtx[(nCntX + nCntZ + nCntPolygon) + (POLYGON_X + 1) + 1].pos;
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

		nCntPolygon += POLYGON_X;
		nCntNorPolygon += (POLYGON_X * 2) - 2;
	}

	for (int nCntPolygonZ = 0; nCntPolygonZ < POLYGON_Z + 1; nCntPolygonZ++)
	{
		for (int nCntPolygonX = 0; nCntPolygonX < POLYGON_X + 1; nCntPolygonX++)
		{
			if (nCntPolygonZ == 0)
			{// 上端
				if (nCntPolygonX == 0)
				{// 左端
					pVtx[0].nor = (m_aNor[0] + m_aNor[1]) / 2;
				}
				else if (nCntPolygonX == POLYGON_X)
				{// 右端
					pVtx[POLYGON_X].nor = m_aNor[POLYGON_X + (POLYGON_X - 1)];
				}
				else
				{// 上端の真ん中
					pVtx[nCntPolygonX].nor =
						(m_aNor[(nCntPolygonX * 2) - 1] + m_aNor[((nCntPolygonX * 2) - 1) + 1] + m_aNor[((nCntPolygonX * 2) - 1) + 2]) / 3;
				}
			}
			else if (nCntPolygonZ == POLYGON_Z)
			{// 下端
				if (nCntPolygonX == 0)
				{// 左端
					pVtx[POLYGON_Z * (POLYGON_X + 1)].nor = m_aNor[2 * (POLYGON_X * (POLYGON_Z - 1))];
				}
				else if (nCntPolygonX == POLYGON_X)
				{// 右端
					pVtx[(POLYGON_X * POLYGON_Z) + (POLYGON_X + POLYGON_Z)].nor =
						(m_aNor[(2 * (POLYGON_X * (POLYGON_Z - 1))) + (2 * (POLYGON_X - 1))] +
							m_aNor[((2 * (POLYGON_X * (POLYGON_Z - 1))) + (2 * (POLYGON_X - 1))) + 1]) / 2;
				}
				else
				{// 下端の真ん中
					pVtx[(POLYGON_Z * (POLYGON_X + 1)) + nCntPolygonX].nor =
						(m_aNor[(POLYGON_Z - 1) * (POLYGON_X * 2) + (nCntPolygonX * 2) - 2] +
							m_aNor[((POLYGON_Z - 1) * (POLYGON_X * 2) + (nCntPolygonX * 2) - 2) + 1] +
							m_aNor[((POLYGON_Z - 1) * (POLYGON_X * 2) + (nCntPolygonX * 2) - 2) + 2]) / 3;
				}
			}
			else
			{// 真ん中
				if (nCntPolygonX == 0)
				{// 左端
					pVtx[(POLYGON_X + 1) * nCntPolygonZ].nor =
						(m_aNor[(nCntPolygonZ * (2 * POLYGON_X)) - (2 * POLYGON_X)] +
							m_aNor[(nCntPolygonZ * (2 * POLYGON_X))] +
							m_aNor[(nCntPolygonZ * (2 * POLYGON_X) + 1)]) / 3;
				}
				else if (nCntPolygonX == POLYGON_X)
				{// 右端
					pVtx[((nCntPolygonZ + 1) * POLYGON_X) + nCntPolygonZ].nor =
						(m_aNor[((POLYGON_X - 1) * 2 + ((POLYGON_X * 2)* (nCntPolygonZ - 1)))]
							+ m_aNor[((POLYGON_X - 1) * 2 + ((POLYGON_X * 2)* (nCntPolygonZ - 1))) + 1]
							+ m_aNor[((POLYGON_X - 1) * 2 + ((POLYGON_X * 2)* (nCntPolygonZ - 1))) + ((POLYGON_X * 2) + 1)]) / 3;
				}
				else
				{
					pVtx[(POLYGON_X + 2) + (nCntPolygonX - 1) + ((nCntPolygonZ * (POLYGON_X + 1)) - (POLYGON_X + 1))].nor =
						(m_aNor[((nCntPolygonX - 1) * 2) + ((nCntPolygonZ * (2 * POLYGON_X)) - (2 * POLYGON_X))] +
							m_aNor[((((nCntPolygonX - 1) * 2) + 1) + ((nCntPolygonZ * (2 * POLYGON_X)) - (2 * POLYGON_X)))] +
							m_aNor[((((nCntPolygonX - 1) * 2) + 2) + ((nCntPolygonZ * (2 * POLYGON_X)) - (2 * POLYGON_X)))] +
							m_aNor[((2 * POLYGON_X) + ((nCntPolygonZ * (2 * POLYGON_X)) - (2 * POLYGON_X))) + ((nCntPolygonX * 2) - 1)] +
							m_aNor[((2 * POLYGON_X) + ((nCntPolygonZ * (2 * POLYGON_X)) - (2 * POLYGON_X)) + 1) + ((nCntPolygonX * 2) - 1)] +
							m_aNor[((2 * POLYGON_X) + ((nCntPolygonZ * (2 * POLYGON_X)) - (2 * POLYGON_X)) + 2) + ((nCntPolygonX * 2) - 1)]) / 6;
				}
			}
		}
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 高さを取得
//=============================================================================
float CMeshField::GetHeight(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 vec0, vec1;	// ポリゴンのベクトル
	D3DXVECTOR3 nor;		// 法線
	D3DXVECTOR3 aVtxpos[3];	// ポリゴンの頂点情報

	// メッシュフィールドとの位置の差分
	D3DXVECTOR3 posMtx = pos - m_pos;

	int nNumber;	// どっちの三角形にいるかで使う
	float fHeight;	// プレイヤーの高さを保管

	// 今どのブロックにいるのか
	int nMeshX = (int)((posMtx.x) / (MESHFIELD_WIDTH / POLYGON_X));
	int nMeshZ = (int)((posMtx.z) / (MESHFIELD_DEPTH / POLYGON_Z) * -1);

	float fMeshX = posMtx.x / (MESHFIELD_WIDTH / POLYGON_X + 1);
	float fMeshZ = posMtx.z / (MESHFIELD_DEPTH / POLYGON_Z + 1) * -1;

	// 今乗っている頂点を出す
	int nMeshLU = nMeshX + nMeshZ * (POLYGON_X + 1);				// 左上
	int nMeshRU = (nMeshX + 1) + nMeshZ * (POLYGON_X + 1);			// 右上
	int nMeshLD = nMeshX + (nMeshZ + 1) * (POLYGON_X + 1);			// 左下
	int nMeshRD = (nMeshX + 1) + (nMeshZ + 1) * (POLYGON_X + 1);	// 右下

	// 頂点情報を設定
	VERTEX_3D * pVtx;					// 頂点情報へのポインタ

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 三角形のベクトルを出す
	vec0 = pVtx[nMeshLU].pos - pVtx[nMeshRD].pos;	// 右の辺のベクトル
	vec1 = posMtx - pVtx[nMeshRD].pos;				// 自分の位置と右下の頂点のベクト

	// 頂点を入れなおす
	if ((vec0.x * vec1.z) - (vec0.z * vec1.x) <= 0)
	{// 右のポリゴンにいる場合
#ifdef _DEBUG
		CDebugProc::Print("c", "migi");
#endif
		vec0 = posMtx - pVtx[nMeshLU].pos;

		aVtxpos[0] = pVtx[nMeshRU].pos;
		aVtxpos[1] = pVtx[nMeshRD].pos;
		aVtxpos[2] = pVtx[nMeshLU].pos;

		nNumber = 3;
	}
	else if ((vec0.x * vec1.z) - (vec0.z * vec1.x) >= 0)
	{// 左のポリゴンにいる場合
#ifdef _DEBUG
		CDebugProc::Print("c", "hidari");
#endif
		vec0 = posMtx - pVtx[nMeshRD].pos;

		aVtxpos[0] = pVtx[nMeshLD].pos;
		aVtxpos[1] = pVtx[nMeshLU].pos;
		aVtxpos[2] = pVtx[nMeshRD].pos;

		nNumber = 0;
	}

	fHeight = aVtxpos[0].y;

	aVtxpos[2].y -= aVtxpos[0].y;
	aVtxpos[1].y -= aVtxpos[0].y;
	aVtxpos[0].y -= aVtxpos[0].y;

	// 入れなおした頂点でベクトルを出す
	vec0 = aVtxpos[1] - aVtxpos[0];
	vec1 = aVtxpos[2] - aVtxpos[0];

	// 外積を使って法線を求める
	D3DXVec3Cross(&nor, &vec0, &vec1);

	// 法線を正規化
	D3DXVec3Normalize(&nor, &nor);

	// プレイヤーとのベクトル
	vec0 = posMtx - aVtxpos[0];

	// 内積の式
	vec0.y = (-(vec0.x * nor.x) - (vec0.z * nor.z)) / nor.y;

	// プレイヤーの位置を元に戻す
	posMtx.y = vec0.y + fHeight + m_pos.y;

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	if (fMeshX >= 0 && fMeshX < POLYGON_X && nMeshZ >= 0 && nMeshZ < POLYGON_Z)
	{
		m_bLand = true;

		if (pos.y > posMtx.y)
		{
			m_bLand = false;
		}
	}
	else
	{
		m_bLand = false;
	}


	return posMtx.y;
}

//=============================================================================
// 乗っているかを取得
//=============================================================================
bool CMeshField::GetLand()
{
	return m_bLand;
}

//=============================================================================
// 高さをロード
//=============================================================================
void CMeshField::LoadHeight(void)
{
	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

						// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	FILE *pFile = NULL;

	pFile = fopen(SOIL_FILENAME, "rb");

	if (pFile != NULL)
	{
		fread(&m_aHeight[0][0], sizeof(float), POLYGON_Z * POLYGON_X, pFile);	// データのアドレス,データのサイズ,データの個数,ファイルポインタ

		fclose(pFile);
	}
	else
	{
		printf("number.txtを開けませんでした。\n");
	}

	for (int nCntZ = 0; nCntZ < POLYGON_Z + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < POLYGON_X + 1; nCntX++)
		{// posを代入
			pVtx->pos.y = m_aHeight[nCntZ][nCntX];

			pVtx++;
		}
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}