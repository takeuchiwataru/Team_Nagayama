//=============================================================================
//
// コイン処理 [coin.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "coin.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "camera.h"
#include "scene3D.h"
#include "meshField.h"
#include "player.h"
#include "game.h"
#include "resource.h"
#include "light.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ROTATION_SPEED	(0.05f)					// コインの回転スピード

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
int CCoin::m_nNumCoin = 0;			// コインの数

//=============================================================================
// コインクラスのコンストラクタ
//=============================================================================
CCoin::CCoin() : CSceneX(COIN_PRIORITY)
{
	// 値をクリア
	m_pVtxBuff = NULL;						// 頂点バッファへのポインタ
	D3DXMatrixIdentity(&m_mtxWorld);		// ワールドマトリックス
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CCoin::~CCoin()
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CCoin *CCoin::Create(D3DXVECTOR3 pos)
{
	CCoin *pCoin = NULL;

	if (pCoin == NULL)
	{
		// オブジェクトクラスの生成
		pCoin = new CCoin;

		if (pCoin != NULL)
		{
			pCoin->SetPosition(pos);
			pCoin->BindModel(CResource::GetBuffMat(CResource::MODEL_COIN), CResource::GetNumMat(CResource::MODEL_COIN), CResource::GetMesh(CResource::MODEL_COIN));
			pCoin->Init();

			m_nNumCoin++;
		}
	}

	return pCoin;
}

//=============================================================================
// コイン初期化処理
//=============================================================================
HRESULT CCoin::Init(void)
{
	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_COIN);

	// 初期化処理
	CSceneX::Init();

	return S_OK;
}

//=============================================================================
// コイン終了処理
//=============================================================================
void CCoin::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// コイン更新処理
//=============================================================================
void CCoin::Update(void)
{
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ゲームのモードを取得
	CManager::MODE mode;
	mode = CManager::GetMode();

	// 位置を取得
	m_pos = CSceneX::GetPosition();

	m_rot.y += ROTATION_SPEED;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	
	SetRot(m_rot);
	
	SetPosition(m_pos);

#ifdef _DEBUG
	//CDebugProc::Print("cn", "コインの数 : ", m_nNumCoin);
#endif
}

//=============================================================================
// コイン描画処理
//=============================================================================
void CCoin::Draw(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// 頂点法線の自動正規化	開始
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	CSceneX::Draw();

	// 頂点法線の自動正規化	終了
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

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
	vecLight = D3DXVECTOR4(-CLight::GetLight(0).Direction.x, -CLight::GetLight(0).Direction.y, -CLight::GetLight(0).Direction.z, 0.0f);

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
	pMat = (D3DXMATERIAL*)CResource::GetBuffMat(CResource::MODEL_COIN)->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)CResource::GetNumMat(CResource::MODEL_COIN); nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);

		// モデル(パーツ)の描画
		CResource::GetMesh(CResource::MODEL_COIN)->DrawSubset(nCntMat);
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
// コインとの当たり判定処理
//=============================================================================
bool CCoin::Collision(D3DXVECTOR3 *pos, float fRadius)
{
	bool bHit = false;	// 当たっていない状態

	// 中心と中心の差を求める
	D3DXVECTOR3 DiffLength = D3DXVECTOR3(pos->x - CSceneX::GetPosition().x, pos->y - CSceneX::GetPosition().y - 20.0f, pos->z - CSceneX::GetPosition().z);

	// 中心から中心のベクトルの長さを算出
	float fLength = sqrtf((DiffLength.x * DiffLength.x) + (DiffLength.y * DiffLength.y) + (DiffLength.z * DiffLength.z));

	if (fLength < fRadius + m_VtxMax.x && fLength < fRadius + m_VtxMax.y && fLength < fRadius + m_VtxMax.z)
	{// 長さが半径の和より小さければ当たっている
		bHit = true;
	}

	return bHit;	// コインに当たっているかどうかを返す
}

//=============================================================================
// 位置の取得
//=============================================================================
D3DXVECTOR3 CCoin::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// 位置の設定
//=============================================================================
void CCoin::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// コインの数の取得
//=============================================================================
int CCoin::GetNumCoin(void)
{
	return m_nNumCoin;
}

//=============================================================================
// コインの数の設定
//=============================================================================
void CCoin::SetNumCoin(int nNumCoin)
{
	m_nNumCoin = nNumCoin;
}