//=============================================================================
//
// 全裸目黒処理 [fullMeguro.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "fullMeguro.h"
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
int CFullMeguro::m_nNumCoin = 0;			// コインの数

//=============================================================================
// コインクラスのコンストラクタ
//=============================================================================
CFullMeguro::CFullMeguro() : CSceneX(COIN_PRIORITY)
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
CFullMeguro::~CFullMeguro()
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CFullMeguro *CFullMeguro::Create(D3DXVECTOR3 pos)
{
	CFullMeguro *pCoin = NULL;

	if (pCoin == NULL)
	{
		// オブジェクトクラスの生成
		pCoin = new CFullMeguro;

		if (pCoin != NULL)
		{
			pCoin->SetPosition(pos);
			pCoin->BindModel(CResource::GetBuffMat(CResource::MODEL_MEGURO), CResource::GetNumMat(CResource::MODEL_MEGURO), CResource::GetMesh(CResource::MODEL_MEGURO));
			pCoin->Init();

			m_nNumCoin++;
		}
	}

	return pCoin;
}

//=============================================================================
// コイン初期化処理
//=============================================================================
HRESULT CFullMeguro::Init(void)
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
void CFullMeguro::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// コイン更新処理
//=============================================================================
void CFullMeguro::Update(void)
{
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//CPlayer *pPlayer = NULL;
	//pPlayer = CGame::GetPlayer();

	//// ゲームのモードを取得
	//CManager::MODE mode;
	//mode = CManager::GetMode();

	// 位置を取得
	m_pos = CSceneX::GetPosition();

	//m_rot.y += ROTATION_SPEED;

	//if (m_rot.y > D3DX_PI)
	//{
	//	m_rot.y -= D3DX_PI * 2.0f;
	//}
	//if (m_rot.y < -D3DX_PI)
	//{
	//	m_rot.y += D3DX_PI * 2.0f;
	//}

	//if (pPlayer->GetMove().y >= 0.0f)
	//{
	//	m_pos.y -= 0.0f;
	//}
	//else if (pPlayer->GetMove().y < -15.0f)
	//{
	//	m_pos.y += pPlayer->GetMove().y + 10.0f;
	//}

	//SetRot(m_rot);

	SetPosition(m_pos);

#ifdef _DEBUG
	CDebugProc::Print("cf", "目黒の位置 : ", m_pos.x);
#endif
}

//=============================================================================
// コイン描画処理
//=============================================================================
void CFullMeguro::Draw(void)
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
}

//=============================================================================
// 位置の取得
//=============================================================================
D3DXVECTOR3 CFullMeguro::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// 位置の設定
//=============================================================================
void CFullMeguro::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// コインの数の取得
//=============================================================================
int CFullMeguro::GetNumCoin(void)
{
	return m_nNumCoin;
}

//=============================================================================
// コインの数の設定
//=============================================================================
void CFullMeguro::SetNumCoin(int nNumCoin)
{
	m_nNumCoin = nNumCoin;
}