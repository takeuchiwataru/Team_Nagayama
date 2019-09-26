//=============================================================================
//
// ポリゴン処理 [Bullet.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "obstacle.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "resource.h"
#include "particleX.h"
#include "player.h"
#include "game.h"
#include "tutorial.h"
#include "shadow.h"
#include "light.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PARTICLE_NUM		(80)	// ブロックを破壊したときのパーティクル数
#define PARTICLE_TIME		(20)	// ブロックを破壊したときのパーティクル出現時間
#define COLLISION_BLOCK		(40)	// ブロックとの当たり判定
#define BULLET_LIFE			(40)	// 弾の出現時間

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// プレイヤークラスのコンストラクタ
//=============================================================================
CObstacle::CObstacle() : CSceneX(BULLET_PRIORITY)
{
	// 値をクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動量
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nLife = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CObstacle::~CObstacle()
{
}

//=============================================================================
// 弾の生成処理
//=============================================================================
CObstacle *CObstacle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col)
{
	CObstacle *pBullet = NULL;

	if (pBullet == NULL)
	{
		// オブジェクトクラスの生成
		pBullet = new CObstacle;

		if (pBullet != NULL)
		{
			pBullet->m_pos = pos;
			pBullet->BindModel(CResource::GetBuffMat(CResource::MODEL_BULLET), CResource::GetNumMat(CResource::MODEL_BULLET), CResource::GetMesh(CResource::MODEL_BULLET));
			pBullet->Init();
			pBullet->m_move = move;
			pBullet->m_col = col;
		}
	}
	return pBullet;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CObstacle::Init(void)
{
	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_BULLET);

	CSceneX::Init();

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nLife = BULLET_LIFE;
	m_bHit = true;
	m_bDestroy = false;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CObstacle::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CObstacle::Update(void)
{
#ifdef _DEBUG
	//CDebugProc::Print("cfccfccfc", "BulletPos : x", pos.x, "f", "   y", pos.y, "f", "  z", pos.z, "f");
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void CObstacle::Draw(void)
{
	// 2Dオブジェクト描画処理
	CSceneX::Draw();

	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;					// マテリアルデータへのポインタ

										// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//================================================================
	// 影の設定
	//================================================================
	D3DXMATRIX mtxShadow;		// シャドウマトリックス
	D3DXPLANE planeField;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, normal;

	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ライトを無効にする
	pDevice->LightEnable(0, FALSE);
	pDevice->LightEnable(1, FALSE);
	pDevice->LightEnable(2, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// シャドウマトリックスの初期化
	D3DXMatrixIdentity(&mtxShadow);

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ライトの方向の設定
	vecLight = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.0f);

	// 位置を設定
	pos = D3DXVECTOR3(0.0f, 0.6f, 0.0f);

	// 地面の法線を設定
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 位置と法線を掛け合わせて面を作る
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);

	// ライトの方向と面でシャドウマトリックスを設定
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	// ワールドマトリックスと掛け合わせる
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	// シャドウマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)CResource::GetBuffMat(CResource::MODEL_BULLET)->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)CResource::GetNumMat(CResource::MODEL_BULLET); nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);

		// モデル(パーツ)の描画
		CResource::GetMesh(CResource::MODEL_BULLET)->DrawSubset(nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
	// ライトを有効にする
	pDevice->LightEnable(0, TRUE);
	pDevice->LightEnable(1, TRUE);
	pDevice->LightEnable(2, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//レンダーステイトを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// プレイヤーとの当たり判定処理
//=============================================================================
bool CObstacle::CollisionPlayer(D3DXVECTOR3 *pos, float fRadius)
{
	bool bHit = false;

	// 中心と中心の差を求める
	D3DXVECTOR3 DiffLength = D3DXVECTOR3(pos->x - m_pos.x, pos->y - m_pos.y + 50.0f, pos->z - m_pos.z);

	// 中心から中心のベクトルの長さを算出
	float fLength = sqrtf((DiffLength.x * DiffLength.x) + (DiffLength.y * DiffLength.y) + (DiffLength.z * DiffLength.z));

	if (fLength < fRadius && fLength < fRadius && fLength < fRadius)
	{// 長さが半径の和より小さければ当たっている
		bHit = true;
		m_bDestroy = true;
	}

	return bHit;	// ブロックに当たっているかどうかを返す
}