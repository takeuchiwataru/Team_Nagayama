//=============================================================================
//
// 3Dモデル処理 [model.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "model.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "light.h"
#include "player.h"

//=============================================================================
// 3Dモデルクラスのコンストラクタ
//=============================================================================
CModel::CModel()
{
	// 値をクリア
	m_pParent = NULL;
	m_pVtxBuff = NULL;						// 頂点バッファへのポインタ
	m_pMesh = NULL;							// メッシュ情報（頂点情報）へのポインタ
	m_pBuffMat = NULL;						// マテリアル情報へのポインタ
	m_nNumMat = 0;							// マテリアル情報の数
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	D3DXMatrixIdentity(&m_mtxWorld);		// ワールドマトリックスの初期化
}

//=============================================================================
// デストラクタ
//=============================================================================
CModel::~CModel()
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CModel *CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CModel *pModel = NULL;

	if (pModel == NULL)
	{
		// オブジェクトクラスの生成
		pModel = new CModel;

		if (pModel != NULL)
		{
			pModel->Init();
			pModel->m_pos = pos;
			pModel->m_rot = rot;
		}
	}

	return pModel;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CModel::Init(void)
{
	m_pParent = NULL;

	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CModel::Uninit(void)
{
	// メッシュの開放
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	// マテリアルの開放
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CModel::Update(void)
{
#ifdef _DEBUG
	//CDebugProc::Print("cfccfccfc", "ModelPos : x", m_pos.x, "f", "   y", m_pos.y, "f", "  z", m_pos.z, "f");
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void CModel::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ
	D3DXMATRIX mtxParent;

	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// デバイスを取得
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

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// 親のマトリックスと掛け合わせる
	if (m_pParent != NULL)
	{
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//親の情報を入れる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, NULL);

		// モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// 親モデルの設定
//=============================================================================
void CModel::SetParent(CModel *pModel)
{
	m_pParent = pModel;
}

//=============================================================================
// 親モデルの取得
//=============================================================================
D3DXMATRIX CModel::GetMtxWorld(void)
{
	return m_mtxWorld;
}


//=============================================================================
// モデルを割り当てる
//=============================================================================
void CModel::BindModel(LPD3DXBUFFER pBuffMat, DWORD nNumMat, LPD3DXMESH pMesh)
{
	m_pBuffMat = pBuffMat;
	m_nNumMat = nNumMat;
	m_pMesh = pMesh;
}

//=============================================================================
// 向きの設定
//=============================================================================
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// 位置の設定
//=============================================================================
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// 向きの取得
//=============================================================================
D3DXVECTOR3 CModel::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// 位置の取得
//=============================================================================
D3DXVECTOR3 CModel::GetPos(void)
{
	return m_pos;
}