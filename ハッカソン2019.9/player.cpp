//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "player.h"
#include "input.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "camera.h"
#include "scene3D.h"
#include "meshField.h"
#include "game.h"
#include "tutorial.h"
#include "goal.h"
#include "particle2D.h"
#include "particle3D.h"
#include "particleX.h"
#include "coin.h"
#include "score.h"
#include "field.h"
#include "sound.h"
#include "light.h"
#include "life.h"
#include "shadow.h"
#include "text.h"
#include "resource.h"
#include "health.h"
#include "onararemain.h"
#include "BAnimation.h"
#include "obstacle.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPD3DXMESH CPlayer::m_apMesh[MAX_PLAYER] = {};			// メッシュ情報（頂点情報）へのポインタ
LPD3DXBUFFER CPlayer::m_apBuffMat[MAX_PLAYER] = {};	// マテリアル情報へのポインタ
DWORD CPlayer::m_anNumMat[MAX_PLAYER] = {};				// マテリアル情報の数
CPlayer::STATE CPlayer::m_State = CPlayer::STATE_NORMAL;
bool CPlayer::m_bGoal = false;
bool CPlayer::m_bGameOver = false;
int CPlayer::m_nNumBlock = 0;
CShadow *CPlayer::m_pShadow = NULL;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MOVE_PLAYER				(6.0f)									//プレイヤー移動量
#define MOVE_INERTIA			(1.0f)									//プレイヤーの慣性
#define PLAYER_COLLISION		(D3DXVECTOR3(15.0f, 65.0f, 15.0f))		//プレイヤーの当たり判定
#define ITEM_COLLISION			(40.0f)									//アイテムの当たり判定
#define IRONBLOCK_COLLISION		(45.0f)									//鉄のブロックの当たり判定
#define WOODLOCK_COLLISION		(70.0f)									//木のブロックの当たり判定
#define POS_HAND				(D3DXVECTOR3(m_apModel[3]->GetMtxWorld()._41, m_apModel[3]->GetMtxWorld()._42, m_apModel[3]->GetMtxWorld()._43))	//手の位置
#define POS_BODY				(D3DXVECTOR3(m_apModel[0]->GetMtxWorld()._41, m_apModel[0]->GetMtxWorld()._42, m_apModel[0]->GetMtxWorld()._43))	//体の位置
#define ATTACK_KEY				(2)										//当たり判定を適応させるキー
#define BLOCK_SIZE				(50.0f)									// ブロックの大きさ
#define BLOCKPOS_SIZE			(25.0f)									// ブロックを置く場所の大きさ
#define BLOCK_RANGE				(65.0f)									// プレイヤーとブロックの距離
#define BLOCK_DECREASE			(30)
#define LIFE					(3)										// 体力
#define SCORE_COIN				(100)									// コイン獲得時のスコア
#define SCORE_GEM				(10000)									// 宝石獲得時のスコア
#define PLAYER_FALL				(150.0f)								// 落ちる判定
#define PLAYER_WALK				(0.25f)									// 歩いてる速さの最低値
#define JUMP					(9.0f)									// ジャンプ力
#define GRAVITY					(0.4f)									// 重力
#define RESPAWN_POS				(D3DXVECTOR3(80.0f, 40.0f, 250.0f))		// リスポーン位置
#define BLOCK_PARTICLE_POS		(D3DXVECTOR3(m_SetBlockPos.x, m_SetBlockPos.y - 20.0f, m_SetBlockPos.z))	// ブロック出現のパーティクルの位置
#define BLOCK_PARTICLE_SIZE		(5.0f)	// ブロック出現のパーティクルのサイズ
#define BLOCK_PARTICLE_LIFE		(20)								// ブロック出現のパーティクルの出現時間
#define WALK_PARTICLE_TIME		(20)								// 歩いた時の土煙がでるフレーム
#define WALK_PARTICLE_COLOR		(D3DXCOLOR(0.8f, 0.5f, 0.2f, 1.0f))	// 歩いた時の土煙がでる色
#define WALK_PARTICLE_SIZE		(10.0f)								// 歩いた時の土煙がでるサイズ
#define WALK_PARTICLE_LIFE		(10)								// 歩いた時の土煙がでる出現時間
#define BREAK_PARTICLE_NUM		(80)								// ブロックを破壊したときのパーティクル数
#define BREAK_PARTICLE_TIME		(20)								// ブロックを破壊したときのパーティクル出現時間
#define IRON_PARTICLE_NUM		(50)								// 鉄ブロックを破壊したときのパーティクル数
#define IRON_PARTICLE_SIZE		(3.0f)								// 鉄ブロックを破壊したときのパーティクルサイズ
#define IRON_PARTICLE_LIFE		(15)								// 鉄ブロックを破壊したときのパーティクル出現時間
#define WOOD_PARTICLE_NUM		(90)								// 木ブロックを破壊したときのパーティクル数
#define WOOD_PARTICLE_LIFE		(20)								// 木ブロックを破壊したときのパーティクル出現時間
#define COIN_PARTICLE_NUM		(50)								// コインを獲得したときのパーティクル数
#define COIN_PARTICLE_SIZE		(3.0f)								// コインを獲得したときのパーティクルサイズ
#define COIN_PARTICLE_LIFE		(15)								// コインを獲得したときのパーティクル出現時間
#define GEM_PARTICLE_NUM		(80)								// 宝石を獲得したときのパーティクル数
#define GEM_PARTICLE_SIZE		(5.0f)								// 宝石を獲得したときのパーティクルサイズ
#define GEM_PARTICLE_LIFE		(15)								// 宝石を獲得したときのパーティクル出現時間
#define WATER_PARTICLE_NUM		(6)									// 水に落ちたときのパーティクル数
#define WATER_PARTICLE_COLOR	(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f))	// 水に落ちたときのパーティクルの色
#define WATER_PARTICLE_SIZE		(5.0f)								// 水に落ちたときのパーティクルのサイズ
#define WATER_PARTICLE_LIFE		(10)								// 水に落ちたときのパーティクルの出現時間
#define CUT_LIFE				(1)									// 弾が当たったときに減らす体力
#define COLLISION_BULLET		(60)								// 弾が当たる判定
#define INVINCIBLE_TIME			(120)								// 無敵時間
#define ONARAREMAIN (3)
#define INVINCIBLE_TIME			(90)								// 無敵時間

//=============================================================================
// グローバル変数宣言
//=============================================================================
int g_nNumModel = 0;
char g_aFilenameModel[MAX_PLAYER][256];

//=============================================================================
// プレイヤークラスのコンストラクタ
//=============================================================================
CPlayer::CPlayer() : CScene(PLAYER_PRIORITY)
{
	// 値をクリア
	for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
	{
		m_apModel[nCntModel] = NULL;
		m_aPosOffset[nCntModel] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aVtxMin[nCntModel] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aVtxMax[nCntModel] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	for (int nCntMotionInfo = 0; nCntMotionInfo < STATE_MAX; nCntMotionInfo++)
	{
		m_aMotionInfo[nCntMotionInfo].nNumKey = 0;
		m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntMotionInfo].nFrame = 0;
		for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
		{
			m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntMotionInfo].aKey[nCntModel].fPosX = 0.0f;
			m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntMotionInfo].aKey[nCntModel].fPosY = 0.0f;
			m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntMotionInfo].aKey[nCntModel].fPosZ = 0.0f;
			m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntMotionInfo].aKey[nCntModel].fRotX = 0.0f;
			m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntMotionInfo].aKey[nCntModel].fRotY = 0.0f;
			m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntMotionInfo].aKey[nCntModel].fRotZ = 0.0f;
		}
	}
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き
	m_BlockPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ブロックの位置
	m_SetBlockPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 設置するブロックの位置
	m_pKeyInfo = NULL;
	m_nKey = 0;
	m_nCountMotion = 0;
	m_WalkTimer = 0;
	m_nLife = 0;
	m_nBulletTimer = 0;
	m_nDisTimer = 0;
	m_nOnaraRemain = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		// オブジェクトクラスの生成
		pPlayer = new CPlayer;

		if (pPlayer != NULL)
		{
			pPlayer->Init();
			pPlayer->m_pos = pos;
		}
	}

	return pPlayer;
}

//=============================================================================
// プレイヤー初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_PLAYER);

	// テキストからプレイヤーの情報を読み込む
	LoadMotion();

	// 頂点情報の最大値と最小値を設定
	SetVtx();

	// 値の初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	m_BlockPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDestAngle = 0;
	m_fDiffAngle = 0;
	m_bRTriangle = false;					// 右にいるかどうか
	m_nKey = 0;
	m_nCountMotion = 0;
	g_nNumModel = 0;
	m_bLand = false;
	m_bGoal = false;
	m_bGameOver = false;
	m_bPolygonLand = false;
	m_bIronSound = false;
	m_bWaterSound = true;
	m_bAttackSound = true;
	m_nNumBlock = 0;
	m_WalkTimer = 0;
	m_nLife = LIFE;
	m_bBulletHit = false;
	m_nBulletTimer = 0;
	m_nDisTimer = 0;
	m_nOnaraRemain = ONARAREMAIN;

	// ブロックの位置を保存
	m_BlockPos = D3DXVECTOR3((sinf(m_rot.y + D3DX_PI) * BLOCK_RANGE) + m_pos.x, m_pos.y, (cosf(m_rot.y + D3DX_PI) * BLOCK_RANGE) + m_pos.z);

	// マス目ごとに設置
	m_SetBlockPos.x = (float)(round(m_BlockPos.x / BLOCK_SIZE) * BLOCK_SIZE);
	m_SetBlockPos.y = (float)(round(m_BlockPos.y / BLOCK_SIZE) * BLOCK_SIZE);
	m_SetBlockPos.z = (float)(round(m_BlockPos.z / BLOCK_SIZE) * BLOCK_SIZE);

	//CBlock::Create(D3DXVECTOR3(m_SetBlockPos.x, m_SetBlockPos.y, m_SetBlockPos.z), CBlock::STATE_PLAYER);

	return S_OK;
}

//=============================================================================
// プレイヤー終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
	{
		if (m_apModel[nCntModel] != NULL)
		{
			m_apModel[nCntModel]->Uninit();

			// メモリを開放
			delete m_apModel[nCntModel];
			m_apModel[nCntModel] = NULL;
		}

		// メッシュの開放
		if (m_apMesh[nCntModel] != NULL)
		{
			m_apMesh[nCntModel] = NULL;
		}

		// マテリアルの開放
		if (m_apBuffMat[nCntModel] != NULL)
		{
			m_apBuffMat[nCntModel] = NULL;
		}
	}
	m_pShadow = NULL;
	// プレイヤー自体の解放
	Release();
}

//=============================================================================
// プレイヤー更新処理
//=============================================================================
void CPlayer::Update(void)
{
	// プレイヤーの動き
	Move();

	CollisonAll();

	Life();

	Health();

	OnaraRemain();

	// モーション
	UpdateMotion();

#ifdef _DEBUG
	CDebugProc::Print("cfccfccfc", "プレイヤーの位置 : x", m_pos.x, "f", "   y", m_pos.y, "f", "  z", m_pos.z, "f");
	CDebugProc::Print("cn", "設置したブロックの数 : ", m_nNumBlock);
	CDebugProc::Print("n", m_nKey);
	CDebugProc::Print("n", m_aMotionInfo[m_State].nNumKey);
	CDebugProc::Print("nc", m_nCountMotion, " / 60");
	CDebugProc::Print("cf", "move.y : ", m_move.y);

	if (m_bLand == true)
	{
		CDebugProc::Print("c", "乗っている");
	}
	else
	{
		CDebugProc::Print("c", "乗っていない");
	}

	if (m_bJump == true)
	{
		CDebugProc::Print("c", "飛んでる");
	}
	else
	{
		CDebugProc::Print("c", "飛んでない");
	}

	if (m_bPolygonLand == true)
	{
		CDebugProc::Print("c", "ポリゴン乗っている");
	}
	else
	{
		CDebugProc::Print("c", "ポリゴン乗っていない");
	}
	CDebugProc::Print("cn", "m_nOnara : ", m_nOnaraRemain);
	CDebugProc::Print("cfccfccfc", "vtxMax : x", m_aVtxMax[3].x, "f", "   y", m_aVtxMax[3].y, "f", "  z", m_aVtxMax[3].z, "f");
	CDebugProc::Print("cfccfccfc", "vtxMin : x", m_aVtxMin[3].x, "f", "   y", m_aVtxMin[3].y, "f", "  z", m_aVtxMin[3].z, "f");
	CDebugProc::Print("cfccfccfc", "offset : x", m_apModel[3]->GetMtxWorld()._41, "f", "   y", m_apModel[3]->GetMtxWorld()._42, "f", "  z", m_apModel[3]->GetMtxWorld()._43, "f");
#endif
}

//=============================================================================
// プレイヤー描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス

	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// 音楽情報を取得
	CSound *pSound;
	pSound = CManager::GetSound();

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

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	if (m_bBulletHit == false)
	{
		for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
		{
			if (m_apModel[nCntModel] != NULL)
			{
				// モデル描画処理
				m_apModel[nCntModel]->Draw();
			}
		}
	}
	else
	{
		m_nDisTimer++;

		if (m_nDisTimer % 5 == 0)
		{
			for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
			{
				if (m_apModel[nCntModel] != NULL)
				{
					// モデル描画処理
					m_apModel[nCntModel]->Draw();
				}
			}
		}
	}
}

//=============================================================================
// プレイヤーが動く処理
//=============================================================================
void CPlayer::Move(void)
{
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// 入力情報を取得
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetInputJoypad();

	// カメラ取得
	CCamera *pCamera;
	pCamera = CManager::GetCamera();

	// カメラの向きを取得
	D3DXVECTOR3 cameraRot;
	cameraRot = pCamera->GetRot();

	// モードの取得
	CManager::MODE mode;
	mode = CManager::GetMode();

	// 音楽情報を取得
	CSound *pSound;
	pSound = CManager::GetSound();

	// 前のフレームの位置代入
	m_posOld = m_pos;

	//=====================================================
	// 移動
	//=====================================================
	float fMovePlayer = MOVE_PLAYER;	// プレイヤーの移動量を設定

	fMovePlayer = MOVE_PLAYER;

	// ジョイパット
	if (pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_LS_UP) == true ||
		pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_LS_DOWN) == true ||
		pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_LS_RIGHT) == true ||
		pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_LS_LEFT) == true)
	{// 左スティック
		m_move.x -= sinf(cameraRot.y - pInputJoypad->GetLeftAxiz()) * (fMovePlayer * 1.0f);
		m_move.z -= cosf(cameraRot.y - pInputJoypad->GetLeftAxiz()) * (fMovePlayer * 1.0f);

		m_fDestAngle = cameraRot.y - pInputJoypad->GetLeftAxiz();
	}

	if (pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_UP) == true ||
		pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_DOWN) == true ||
		pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_RIGHT) == true ||
		pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_LEFT) == true)
	{// 十字キー
		m_move.x += sinf(cameraRot.y + pInputJoypad->GetRadian()) * (fMovePlayer * 1.0f);
		m_move.z += cosf(cameraRot.y + pInputJoypad->GetRadian()) * (fMovePlayer * 1.0f);

		m_fDestAngle = cameraRot.y + pInputJoypad->GetRadian() - D3DX_PI;
	}

	//任意のキー←
	if (pInputKeyboard->GetPress(DIK_A) == true)
	{
		//モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
		m_move.x -= sinf(cameraRot.y + D3DX_PI * 0.5f) * fMovePlayer;
		m_move.z -= cosf(cameraRot.y + D3DX_PI * 0.5f) * fMovePlayer;
		m_fDestAngle = (cameraRot.y + D3DX_PI * 0.5f);

	}
	//任意のキー→
	else if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		//モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
			m_move.x -= sinf(cameraRot.y - D3DX_PI * 0.5f) * fMovePlayer;
			m_move.z -= cosf(cameraRot.y - D3DX_PI * 0.5f) * fMovePlayer;
			m_fDestAngle = (cameraRot.y - D3DX_PI * 0.5f);
	}
	/*if (pInputKeyboard->GetPress(DIK_W) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_A) == true)
	{
		m_pos.y += 20.0f;
	}
	if (pInputKeyboard->GetPress(DIK_S) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_A) == true)
	{
		m_pos.y -= 20.0f;
	}*/

	//向きの慣性
	m_fDiffAngle = m_fDestAngle - m_rot.y;

	//角度の設定
	if (m_fDiffAngle > D3DX_PI)
	{
		m_fDiffAngle -= D3DX_PI* 2.0f;
	}
	if (m_fDiffAngle < -D3DX_PI)
	{
		m_fDiffAngle += D3DX_PI* 2.0f;
	}

	m_rot.y += m_fDiffAngle * 0.1f;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI* 2.0f;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI* 2.0f;
	}

	if (pInputKeyboard->GetTrigger(DIK_W) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_A) == true)
	{
		m_move.y = 0.0f;

		pSound->PlaySound(CSound::SOUND_LABEL_SE_JUMP);

		// プレイヤーをジャンプ状態
		m_bJump = true;
		// ジャンプ力
		m_move.y -= (cosf(D3DX_PI * 1.0f) * JUMP);
		// キーとフレームを0にする
		m_nKey = 0;
		m_nCountMotion = 0;

		CBAnimation::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 80.0f, m_pos.z), D3DXCOLOR(1.0f, 0.8f, 0.0f, 1.0f), 50.0f, 50.0f, (1.0f / 6.0f), 1.0f, 1.0f, 6, 1, 0, 0, CResource::TEXTURE_HE);
	}

	if (m_move.x < PLAYER_WALK && m_move.x > -PLAYER_WALK && m_move.z < PLAYER_WALK && m_move.z > -PLAYER_WALK && m_bJump == false && m_State != STATE_BLOCK && m_State != STATE_BREAK && m_State != STATE_UPBREAK && m_State != STATE_LAND)
	{
		if (m_State == STATE_WALK)
		{
			// キーとフレームを0にする
			m_nKey = 0;
			m_nCountMotion = 0;
		}

		// 待機状態
		m_State = STATE_NORMAL;
	}
	else if (m_move.x >= PLAYER_WALK || m_move.x <= -PLAYER_WALK || m_move.z >= PLAYER_WALK || m_move.z <= -PLAYER_WALK && m_bJump == false)
	{
		if (m_bJump == false)
		{
			// 歩行状態
			m_State = STATE_WALK;
		}
	}

	if (m_State == STATE_LAND)
	{
		if (m_nKey == 1)
		{
			m_State = STATE_NORMAL;
		}
	}

	Action();

	// 位置更新
	m_pos.x += m_move.x;
	m_pos.z += m_move.z;
	m_pos.y += m_move.y;

	//減速
	m_move.x += (0.0f - m_move.x) * MOVE_INERTIA;
	m_move.z += (0.0f - m_move.z) * MOVE_INERTIA;

#if(1)
	// 重力加算
	if (m_move.y > -30.0f)
	{
		m_move.y -= cosf(D3DX_PI * 0.0f) * GRAVITY;
	}
#endif
}

//=============================================================================
// プレイヤーが動く処理
//=============================================================================
void CPlayer::Action(void)
{
	
}

//=============================================================================
// ブロックの位置
//=============================================================================
void CPlayer::SetBlock(void)
{
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// 入力情報を取得
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetInputJoypad();

	// ブロックの位置を保存 
	m_BlockPos = D3DXVECTOR3((sinf(m_rot.y + D3DX_PI) * BLOCK_RANGE) + m_pos.x, m_pos.y, (cosf(m_rot.y + D3DX_PI) * BLOCK_RANGE) + m_pos.z);

	// マス目ごとに設置
	m_SetBlockPos.x = (float)(round(m_BlockPos.x / BLOCK_SIZE) * BLOCK_SIZE);
	m_SetBlockPos.y = (float)(round(m_BlockPos.y / BLOCK_SIZE) * BLOCK_SIZE);
	m_SetBlockPos.z = (float)(round(m_BlockPos.z / BLOCK_SIZE) * BLOCK_SIZE);
}

//=============================================================================
// モデルとの当たり判定の処理
//=============================================================================
void CPlayer::CollisonModel(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius)
{

}

//=============================================================================
// ゴールとの当たり判定の処理
//=============================================================================
void CPlayer::CollisionGoal(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius)
{
	CScene *pScene = NULL;

	// 先頭のオブジェクトを取得
	pScene = CScene::GetTop(GOAL_PRIORITY);

	while (pScene != NULL)
	{// 優先順位が3のオブジェクトを1つ1つ確かめる
	 // 処理の最中に消える可能性があるから先に記録しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// 死亡フラグが立っていないもの
			if (pScene->GetObjType() == CScene::OBJTYPE_GOAL)
			{// オブジェクトの種類を確かめる
				m_bGoal = ((CGoal*)pScene)->Collision(pos, posOld, move, radius);
			}
		}

		// 次のシーンに進める
		pScene = pSceneNext;
	}
}

//=============================================================================
// コインの当たり判定
//=============================================================================
void CPlayer::CollisonCoin(D3DXVECTOR3 *pos, float fRadius)
{
	// モードの取得
	CManager::MODE mode;
	mode = CManager::GetMode();

	// 音楽情報を取得
	CSound *pSound;
	pSound = CManager::GetSound();

	CScene *pScene = NULL;

	// 先頭のオブジェクトを取得(モデルの優先順位が3だから、3にあるオブジェクトをすべて見る)
	pScene = CScene::GetTop(COIN_PRIORITY);

	while (pScene != NULL)
	{// 優先順位が3のオブジェクトを1つ1つ確かめる
	 // 処理の最中に消える可能性があるから先に記録しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// 死亡フラグが立っていないもの
			if (pScene->GetObjType() == CScene::OBJTYPE_COIN)
			{// オブジェクトの種類を確かめる
				bool bHit = ((CCoin*)pScene)->Collision(pos, fRadius);

				if (((CCoin*)pScene)->Collision(pos, fRadius) == true)
				{
					pSound->PlaySound(CSound::SOUND_LABEL_SE_COIN);

					// コイン削除
					((CCoin*)pScene)->Uninit();

					// 取ったコインをカウントする
					int nNumCoin = ((CCoin*)pScene)->GetNumCoin();

					nNumCoin--;
					

					// ブロックの数取得
					CScore *pScore = NULL;

					// おなら残機の取得
					COnaraRemain *pOnaraRemain = NULL;

					if (mode == CManager::MODE_GAME)
					{
						pScore = CGame::GetScore();

						pOnaraRemain = CGame::GetOnaraRemain();
					}
					else if (mode == CManager::MODE_TUTORIAL)
					{
						pScore = CTutorial::GetScore();
					}

					pScore->AddScore(SCORE_COIN);

					if (m_nOnaraRemain < ONARAREMAIN)
					{
						m_nOnaraRemain++;

						pOnaraRemain->AddOnaraRemain(1);
					}

					for (int nCntParticle = 0; nCntParticle < COIN_PARTICLE_NUM; nCntParticle++)
					{
						CParticle3D::Create(D3DXVECTOR3(((CCoin*)pScene)->GetPos().x, ((CCoin*)pScene)->GetPos().y + 10.0f, ((CCoin*)pScene)->GetPos().z),
							D3DXVECTOR3(sinf(PARTICLE_ROT) * ((rand() % 5 + 1)), cosf(PARTICLE_ROT) * ((rand() % 5 + 1)), cosf(PARTICLE_ROT) * ((rand() % 5 + 1))),
							D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f),
							COIN_PARTICLE_SIZE,
							COIN_PARTICLE_SIZE,
							COIN_PARTICLE_LIFE,
							CParticle3D::TYPE_NORMAL,
							CResource::TEXTURE_PARTICLE2D);
					}

					((CCoin*)pScene)->SetNumCoin(nNumCoin);
				}
			}
		}

		// 次のシーンに進める
		pScene = pSceneNext;
	}
}

//=============================================================================
// 床との当たり判定の処理
//=============================================================================
void CPlayer::CollisionField(void)
{
	CScene *pScene = NULL;

	// 先頭のオブジェクトを取得(メッシュフィールドの優先順位が3だから、3にあるオブジェクトをすべて見る)
	pScene = CScene::GetTop(MESHFIELD_PRIORITY);

	while (pScene != NULL)
	{// 優先順位が3のオブジェクトを1つ1つ確かめる
	 // 処理の最中に消える可能性があるから先に記録しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// 死亡フラグが立っていないもの
			if (pScene->GetObjType() == CScene::OBJTYPE_MESHFIELD)
			{// オブジェクトの種類を確かめる
				float fHeight = ((CMeshField*)pScene)->GetHeight(m_pos);
				
				if (m_bJump == false)
				{
					// 床との当たり判定
					if (((CMeshField*)pScene)->GetLand() == false)
					{// プレイヤーのy座標が地面よりも高いとき
						m_move.y -= cosf(D3DX_PI * 0.0f) * GRAVITY;	// 重力加算
					}
					else if(((CMeshField*)pScene)->GetLand() == true && m_pos.y > fHeight - PLAYER_FALL)
					{// プレイヤーのy座標が地面よりも低いとき
						m_move.y = 0.0f;							// y軸の移動量を0にする
						m_pos.y = fHeight;							// y座標を地面の高さにする
						m_bJump = false;
					}
				}
				else
				{
					// ジャンプ状態に
					m_State = STATE_JUMP;
					if (m_pos.y <= fHeight)
					{// プレイヤーのy座標が地面よりも低いとき
						// ジャンプしていない状態にする
						m_bJump = false;
					}
				}

#ifdef _DEBUG
				if (((CMeshField*)pScene)->GetLand() == true)
				{
					CDebugProc::Print("c", "床乗っている");
				}
				else
				{
					CDebugProc::Print("c", "床乗っていない");
				}

				

#endif
			}
		}

		// 次のシーンに進める
		pScene = pSceneNext;
	}
}

//=============================================================================
// ポリゴンとの当たり判定の処理
//=============================================================================
void CPlayer::CollisonPolygon(D3DXVECTOR3 *pos, D3DXVECTOR3 fRadius)
{
	// 音楽情報を取得
	CSound *pSound;
	pSound = CManager::GetSound();

	CScene *pScene = NULL;

	// 先頭のオブジェクトを取得(メッシュフィールドの優先順位が3だから、3にあるオブジェクトをすべて見る)
	pScene = CScene::GetTop(POLYGON_PRIORITY);

	while (pScene != NULL)
	{// 優先順位が3のオブジェクトを1つ1つ確かめる
	 // 処理の最中に消える可能性があるから先に記録しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// 死亡フラグが立っていないもの
			if (pScene->GetObjType() == CScene::OBJTYPE_FIELD)
			{// オブジェクトの種類を確かめる
				float fHeight = ((CPolygon*)pScene)->GetHeight(m_pos);
				bool bLand = ((CPolygon*)pScene)->ColLand(pos, fRadius);


				if (m_bJump == false)
				{
					if (bLand == true && m_pos.y <= fHeight)
					{// プレイヤーのy座標が地面よりも低いとき
						m_move.y = 0.0f;							// y軸の移動量を0にする
						m_pos.y = fHeight;							// y座標を地面の高さにする
						m_bJump = false;
						m_bPolygonLand = true;

						if (m_State == STATE_WALK)
						{
							m_WalkTimer++;

							if (m_WalkTimer >= WALK_PARTICLE_TIME)
							{
								CParticle3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z),
									D3DXVECTOR3(sinf(PARTICLE_ROT), cosf(PARTICLE_ROT), cosf(-m_rot.y)),
									WALK_PARTICLE_COLOR,
									WALK_PARTICLE_SIZE,
									WALK_PARTICLE_SIZE,
									WALK_PARTICLE_LIFE,
									CParticle3D::TYPE_UP,
									CResource::TEXTURE_CLOUD);
								m_WalkTimer = 0;
							}
						}
					}
					else if (m_pos.y > fHeight)
					{
						m_bPolygonLand = false;
					}
				}
				else
				{
					// ジャンプ状態に
					m_State = STATE_JUMP;
					if (m_pos.y <= fHeight)
					{// プレイヤーのy座標が地面よりも低いとき
					 // ジャンプしていない状態にする
						m_bJump = false;

						// キーとフレームを0にする
						m_nKey = 0;
						m_nCountMotion = 0;
						m_State = STATE_LAND;
					}
				}
			}
		}

		// 次のシーンに進める
		pScene = pSceneNext;
	}

	// 水に落ちた時の判定
	pScene = NULL;

	// 先頭のオブジェクトを取得
	pScene = CScene::GetTop(SCENE3D_PRIORITY);

	while (pScene != NULL)
	{
	 // 処理の最中に消える可能性があるから先に記録しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// 死亡フラグが立っていないもの
			if (pScene->GetObjType() == CScene::OBJTYPE_SCENE3D)
			{// オブジェクトの種類を確かめる
				float fHeight = ((CScene3D*)pScene)->GetHeight(m_pos);
				bool bLand = ((CScene3D*)pScene)->ColLand(pos, fRadius);

				if (bLand == true && m_pos.y > -PLAYER_FALL)
				{
					if (m_bWaterSound == true)
					{
						pSound->PlaySound(CSound::SOUND_LABEL_SE_WATER);
						m_bWaterSound = false;
					}
					
					for (int nCntParticle = 0; nCntParticle < WATER_PARTICLE_NUM; nCntParticle++)
					{
						CParticle3D::Create(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z),
							D3DXVECTOR3(sinf(PARTICLE_ROT) * ((rand() % 5 + 1)), cosf(PARTICLE_ROT) * ((rand() % 5 + 1)), cosf(PARTICLE_ROT) * ((rand() % 5 + 1))),
							WATER_PARTICLE_COLOR,
							WATER_PARTICLE_SIZE,
							WATER_PARTICLE_SIZE,
							WATER_PARTICLE_LIFE,
							CParticle3D::TYPE_UP,
							CResource::TEXTURE_PARTICLE2D);
					}
				}
			}
		}

		// 次のシーンに進める
		pScene = pSceneNext;
	}
}

//=============================================================================
// 頂点座標の設定処理
//=============================================================================
void CPlayer::SetVtx(void)
{
	DWORD sizeFvF;	//頂点フォーマットのサイズ
	D3DXVECTOR3 vtx;
	int nNumVtx;	//頂点数
	BYTE *pVtxBuff;	//頂点バッファへのポインタ

	for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
	{// パーツ分繰り返す
		// 頂点数を取得
		nNumVtx = m_apMesh[nCntModel]->GetNumVertices();
		// 頂点フォーマットのサイズを取得
		sizeFvF = D3DXGetFVFVertexSize(m_apMesh[nCntModel]->GetFVF());

		// 頂点の最小値と最大値を代入
		m_aVtxMin[nCntModel] = D3DXVECTOR3(10000, 10000, 10000);
		m_aVtxMax[nCntModel] = D3DXVECTOR3(-10000, -10000, -10000);

		//頂点バッファをロック
		m_apMesh[nCntModel]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{//頂点座標の代入
			vtx = *(D3DXVECTOR3*)pVtxBuff;

			if (m_aVtxMin[nCntModel].x > vtx.x)
			{
				m_aVtxMin[nCntModel].x = vtx.x;
			}
			if (m_aVtxMin[nCntModel].y > vtx.y)
			{
				m_aVtxMin[nCntModel].y = vtx.y;
			}
			if (m_aVtxMin[nCntModel].z > vtx.z)
			{
				m_aVtxMin[nCntModel].z = vtx.z;
			}

			if (m_aVtxMax[nCntModel].x < vtx.x)
			{
				m_aVtxMax[nCntModel].x = vtx.x;
			}
			if (m_aVtxMax[nCntModel].y < vtx.y)
			{
				m_aVtxMax[nCntModel].y = vtx.y;
			}
			if (m_aVtxMax[nCntModel].z < vtx.z)
			{
				m_aVtxMax[nCntModel].z = vtx.z;
			}

			//サイズ分ポインタを進める
			pVtxBuff += sizeFvF;
		}
		//頂点バッファをアンロック
		m_apMesh[nCntModel]->UnlockVertexBuffer();
	}
}

//=============================================================================
// モーション処理
//=============================================================================
void CPlayer::UpdateMotion(void)
{
	KEY *pKey, *pKeyNext;
	float fRateMotion;
	float fDiffMotion;
	D3DXVECTOR3 modelRot;
	D3DXVECTOR3 modelPos;

	for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
	{
		if (m_apModel[nCntModel] != NULL)
		{
			// 現在のキーを取得
			pKey = &m_aMotionInfo[m_State].aKeyInfo[m_nKey].aKey[nCntModel];

			// 次のキーを取得
			pKeyNext = &m_aMotionInfo[m_State].aKeyInfo[(m_nKey + 1) % m_aMotionInfo[m_State].nNumKey].aKey[nCntModel];

			// 現在のキーと次のキーへの再生フレーム数におけるモーションカウンターの相対値を算出
			fRateMotion = (float)m_nCountMotion / (float)m_aMotionInfo[m_State].aKeyInfo[m_nKey].nFrame;

			//========================================
			// xの向き
			//========================================
			// 現在のキーと次のキーの各要素の差分を算出
			fDiffMotion = pKeyNext->fRotX - pKey->fRotX;

			// 相対値と差分を使って各要素の値を算出する
			modelRot.x = pKey->fRotX + (fDiffMotion * fRateMotion);

			//========================================
			// yの向き
			//========================================
			// 現在のキーと次のキーの各要素の差分を算出
			fDiffMotion = pKeyNext->fRotY - pKey->fRotY;

			// 相対値と差分を使って各要素の値を算出する
			modelRot.y = pKey->fRotY + (fDiffMotion * fRateMotion);

			//========================================
			// zの向き
			//========================================
			// 現在のキーと次のキーの各要素の差分を算出
			fDiffMotion = pKeyNext->fRotZ - pKey->fRotZ;

			// 相対値と差分を使って各要素の値を算出する
			modelRot.z = pKey->fRotZ + (fDiffMotion * fRateMotion);

			//========================================
			// xの位置
			//========================================
			// 現在のキーと次のキーの各要素の差分を算出
			fDiffMotion = pKeyNext->fPosX - pKey->fPosX;

			// 相対値と差分を使って各要素の値を算出する
			modelPos.x = pKey->fPosX + (fDiffMotion * fRateMotion);

			//========================================
			// yの位置
			//========================================
			// 現在のキーと次のキーの各要素の差分を算出
			fDiffMotion = pKeyNext->fPosY - pKey->fPosY;

			// 相対値と差分を使って各要素の値を算出する
			modelPos.y = pKey->fPosY + (fDiffMotion * fRateMotion);

			//========================================
			// zの位置
			//========================================
			// 現在のキーと次のキーの各要素の差分を算出
			fDiffMotion = pKeyNext->fPosZ - pKey->fPosZ;

			// 相対値と差分を使って各要素の値を算出する
			modelPos.z = pKey->fPosZ + (fDiffMotion * fRateMotion);

			// 位置を設定
			m_apModel[nCntModel]->SetPos(m_aPosOffset[nCntModel] + modelPos);
			// 向きを設定
			m_apModel[nCntModel]->SetRot(modelRot);
		}
	}

	
	if (m_aMotionInfo[m_State].bLoop == true)
	{// ループするモーション
		m_nCountMotion++;
		if (m_nCountMotion >= m_aMotionInfo[m_State].aKeyInfo[m_nKey].nFrame)
		{
			if (m_nKey >= m_aMotionInfo[m_State].nNumKey - 1)
			{
				m_nKey = 0;
			}
			else
			{
				m_nKey++;
			}

			m_nCountMotion = 0;
		}
	}
	else
	{// ループしないモーション
		if (m_nKey < m_aMotionInfo[m_State].nNumKey - 1)
		{
		
			m_nCountMotion++;

			if (m_nCountMotion >= m_aMotionInfo[m_State].aKeyInfo[m_nKey].nFrame)
			{
				m_nCountMotion = 0;

				if (m_nKey <= m_aMotionInfo[m_State].nNumKey - 1)
				{
					m_nKey++;	// キーを一つ進める
				}
			}
			
		}
	}
}

//=============================================================================
// モーションのロード処理
//=============================================================================
void CPlayer::LoadMotion(void)
{
	D3DXVECTOR3 pos[MAX_PLAYER];
	D3DXVECTOR3 rot[MAX_PLAYER];
	int nWord;
	int nIdx;
	int nParent[MAX_PLAYER];
	int nLoop;
	int nCntMotionInfo = 0;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	CText *pText;
	pText = CManager::GetText();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	FILE *pFile;

	pFile = fopen(MOTION_FILENAME, "r");

	if (pFile != NULL)
	{
		char *pStrCur;		// 文字列の先頭へのポインタ
		char aLine[256];	// 文字列読み込み用（1行分）
		char aStr[256];		// 文字列抜き出し用
		int nCntModel = 0;

		while (1)
		{
			pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
			pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
			strcpy(&aStr[0], pStrCur);

			if (memcmp(&aStr[0], "SCRIPT", strlen("SCRIPT")) == 0)
			{
				// 1行読み込み
				pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
				pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定

				strcpy(&aStr[0], pStrCur);
			}
			if (memcmp(&aStr[0], NUMMODEL, strlen(NUMMODEL)) == 0)
			{
				pStrCur += strlen(NUMMODEL);	// 頭出し

				g_nNumModel = atoi(pStrCur);	// 文字列を値に変換

				for (int nCntModel = 0; nCntModel < g_nNumModel; nCntModel++)
				{// モデルの読み込み
					pStrCur = pText->ReadLine(pFile, &aLine[0]);
					pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
					strcpy(&aStr[0], pStrCur);

					if (memcmp(&aStr[0], MODEL_FILE, strlen(MODEL_FILE)) == 0)
					{
						pStrCur += strlen(MODEL_FILE);

						strcpy(&aStr[0], pStrCur);

						// コメントを消す
						int nNullNum = pText->PopString(pStrCur, &aStr[0]);
						strcpy(&aStr[0], pStrCur);
						aStr[nNullNum - 1] = '\0';

						strcpy(&g_aFilenameModel[nCntModel][0], aStr);	//

						D3DXLoadMeshFromX(&g_aFilenameModel[nCntModel][0],
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&m_apBuffMat[nCntModel],
							NULL,
							&m_anNumMat[nCntModel],
							&m_apMesh[nCntModel]);
					}
				}
			}
			else if (memcmp(&aStr[0], CHARACTER_SET, strlen(CHARACTER_SET)) == 0)
			{// キャラクターモデルの設定

					// 1行読み込み
				pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
				pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定

				strcpy(&aStr[0], pStrCur);

				if (memcmp(&aStr[0], NUM_PARTS, strlen(NUM_PARTS)) == 0)
				{
					pStrCur += strlen(NUM_PARTS);	// 頭出し

					m_nNumParts = atoi(pStrCur);

					pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
					pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定

					strcpy(&aStr[0], pStrCur);
				}

				for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
				{

					if (memcmp(&aStr[0], PARTSSET, strlen(PARTSSET)) == 0)
					{

						pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
						pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定

						strcpy(&aStr[0], pStrCur);

						if (memcmp(&aStr[0], INDEX, strlen(INDEX)) == 0)
						{// インデックス
							pStrCur += strlen(INDEX);
							nIdx = atoi(pStrCur);

							pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
							pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定

							strcpy(&aStr[0], pStrCur);
						}
						if (memcmp(&aStr[0], PARENT, strlen(PARENT)) == 0)
						{// 親
							pStrCur += strlen(PARENT);	// 頭出し

							nParent[nIdx] = atoi(pStrCur);	// aStr[0]に何文字入っているかを確かめる

							pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
							pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定

							strcpy(&aStr[0], pStrCur);
						}
						if (memcmp(&aStr[0], POS, strlen(POS)) == 0)
						{// 位置
							pStrCur += strlen(POS);	// 頭出し

							// floatに変換して代入
							pos[nIdx].x = (float)atof(pStrCur);

							// aStr[0]に何文字入っているかを確かめる
							nWord = pText->PopString(pStrCur, &aStr[0]);

							// 次まで進める
							pStrCur += nWord;

							// floatに変換して代入
							pos[nIdx].y = (float)atof(pStrCur);

							// aStr[0]に何文字入っているかを確かめる
							nWord = pText->PopString(pStrCur, &aStr[0]);

							// 次まで進める
							pStrCur += nWord;

							// floatに変換して代入
							pos[nIdx].z = (float)atof(pStrCur);

							pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
							pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定

							strcpy(&aStr[0], pStrCur);
						}
						if (memcmp(&aStr[0], ROT, strlen(ROT)) == 0)
						{// 向き
							pStrCur += strlen(ROT);	// 頭出し

							// floatに変換して代入
							rot[nIdx].x = (float)atof(pStrCur);

							// aStr[0]に何文字入っているかを確かめる
							nWord = pText->PopString(pStrCur, &aStr[0]);

							// 次まで進める
							pStrCur += nWord;

							// floatに変換して代入
							rot[nIdx].y = (float)atof(pStrCur);

							// aStr[0]に何文字入っているかを確かめる
							nWord = pText->PopString(pStrCur, &aStr[0]);

							// 次まで進める
							pStrCur += nWord;

							// floatに変換して代入
							rot[nIdx].z = (float)atof(pStrCur);

							pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
							pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定

							strcpy(&aStr[0], pStrCur);
						}
						if (memcmp(&aStr[0], END_PARTSSET, strlen(END_PARTSSET)) == 0)
						{
							pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
							pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定

							strcpy(&aStr[0], pStrCur);
						}

						if (nParent[nIdx] == -1)
						{
							m_apModel[0] = CModel::Create(D3DXVECTOR3(m_pos.x + pos[nIdx].x, m_pos.y + pos[nIdx].y, m_pos.z + pos[nIdx].z), m_rot);
							m_apModel[0]->BindModel(m_apBuffMat[nIdx], m_anNumMat[nIdx], m_apMesh[nIdx]);
							m_apModel[0]->SetParent(NULL);
							// オフセットに代入
							m_aPosOffset[0] = m_apModel[0]->GetPos();
						}
						else if (nParent[nIdx] > -1)
						{
							// モデルを作成
							m_apModel[nIdx] =
								CModel::Create(D3DXVECTOR3(m_pos.x + pos[nIdx].x, m_pos.y + pos[nIdx].y, m_pos.z + pos[nIdx].z), rot[nIdx]);
							m_apModel[nIdx]->BindModel(m_apBuffMat[nIdx], m_anNumMat[nIdx], m_apMesh[nIdx]);
							m_apModel[nIdx]->SetParent(m_apModel[nParent[nIdx]]);

							// オフセットに代入
							m_aPosOffset[nIdx] = m_apModel[nIdx]->GetPos();
						}
					}
				}
			}
			else if (memcmp(&aStr[0], END_CHARACTER_SET, strlen(END_CHARACTER_SET)) == 0)
			{
				pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
				pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定

				strcpy(&aStr[0], pStrCur);
			}
			else if (memcmp(&aStr[0], MOTIONSET, strlen(MOTIONSET)) == 0)
			{// キャラクターモーションの設定
				while (1)
				{
					pStrCur = pText->ReadLine(pFile, &aLine[0]);
					pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
					strcpy(&aStr[0], pStrCur);

					if (memcmp(&aStr[0], LOOP, strlen(LOOP)) == 0)
					{
						pStrCur += strlen(LOOP);	// 頭出し

						nLoop = atoi(pStrCur);

						if (nLoop == 0)
						{
							m_aMotionInfo[nCntMotionInfo].bLoop = false;
						}
						else if (nLoop == 1)
						{
							m_aMotionInfo[nCntMotionInfo].bLoop = true;
						}
					}
					else if (memcmp(&aStr[0], NUM_KEY, strlen(NUM_KEY)) == 0)
					{
						pStrCur += strlen(NUM_KEY);	// 頭出し

						m_aMotionInfo[nCntMotionInfo].nNumKey = atoi(pStrCur);

						pStrCur = pText->ReadLine(pFile, &aLine[0]);
						pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
						strcpy(&aStr[0], pStrCur);

						for (int nCntKeySet = 0; nCntKeySet < m_aMotionInfo[nCntMotionInfo].nNumKey; nCntKeySet++)
						{
							if (memcmp(&aStr[0], KEYSET, strlen(KEYSET)) == 0)
							{// キー設定の始まり
								pStrCur = pText->ReadLine(pFile, &aLine[0]);
								pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
								strcpy(&aStr[0], pStrCur);
								if (memcmp(&aStr[0], FRAME, strlen(FRAME)) == 0)
								{// フレームを読み込み
									pStrCur += strlen(FRAME);	// 頭出し

									m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntKeySet].nFrame = atoi(pStrCur);
								}

								pStrCur = pText->ReadLine(pFile, &aLine[0]);
								pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
								strcpy(&aStr[0], pStrCur);

								for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
								{
									if (memcmp(&aStr[0], "KEY", strlen("KEY")) == 0)
									{// キーを読み込み
										pStrCur = pText->ReadLine(pFile, &aLine[0]);
										pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
										strcpy(&aStr[0], pStrCur);

										if (memcmp(&aStr[0], POS, strlen(POS)) == 0)
										{// 位置
											pStrCur += strlen(POS);	// 頭出し

											// floatに変換して代入
											m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntKeySet].aKey[nCntParts].fPosX = (float)atof(pStrCur);

											// aStr[0]に何文字入っているかを確かめる
											nWord = pText->PopString(pStrCur, &aStr[0]);

											// 次まで進める
											pStrCur += nWord;

											// floatに変換して代入
											m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntKeySet].aKey[nCntParts].fPosY = (float)atof(pStrCur);

											// aStr[0]に何文字入っているかを確かめる
											nWord = pText->PopString(pStrCur, &aStr[0]);

											// 次まで進める
											pStrCur += nWord;

											// floatに変換して代入
											m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntKeySet].aKey[nCntParts].fPosZ = (float)atof(pStrCur);

											pStrCur = pText->ReadLine(pFile, &aLine[0]);
											pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
											strcpy(&aStr[0], pStrCur);
										}
										if (memcmp(&aStr[0], ROT, strlen(ROT)) == 0)
										{// 向き
											pStrCur += strlen(ROT);	// 頭出し

											// floatに変換して代入
											m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntKeySet].aKey[nCntParts].fRotX = (float)atof(pStrCur);

											// aStr[0]に何文字入っているかを確かめる
											nWord = pText->PopString(pStrCur, &aStr[0]);

											// 次まで進める
											pStrCur += nWord;

											// floatに変換して代入
											m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntKeySet].aKey[nCntParts].fRotY = (float)atof(pStrCur);

											// aStr[0]に何文字入っているかを確かめる
											nWord = pText->PopString(pStrCur, &aStr[0]);

											// 次まで進める
											pStrCur += nWord;

											// floatに変換して代入
											m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntKeySet].aKey[nCntParts].fRotZ = (float)atof(pStrCur);

											pStrCur = pText->ReadLine(pFile, &aLine[0]);
											pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
											strcpy(&aStr[0], pStrCur);

										}
										if (memcmp(&aStr[0], "END_KEY", strlen("END_KEY")) == 0)
										{
											pStrCur = pText->ReadLine(pFile, &aLine[0]);
											pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
											strcpy(&aStr[0], pStrCur);
										}

									}

								}
							}
							if (memcmp(&aStr[0], END_KEYSET, strlen(END_KEYSET)) == 0)
							{// キー設定の終わり
								pStrCur = pText->ReadLine(pFile, &aLine[0]);
								pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
								strcpy(&aStr[0], pStrCur);
							}
						}
					}
					if (memcmp(&aStr[0], END_MOTIONSET, strlen(END_MOTIONSET)) == 0)
					{
						m_pKeyInfo = &m_aMotionInfo[nCntMotionInfo].aKeyInfo[0];
						nCntMotionInfo++;
						break;
					}
				}
			}
			else if(memcmp(&aStr[0], "END_SCRIPT", strlen("END_SCRIPT")) == 0)
			{
				break;
			}
		}

		fclose(pFile);
	}
}

//=============================================================================
// 全ての当たり判定
//=============================================================================
void CPlayer::CollisonAll(void)
{
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// 入力情報を取得
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetInputJoypad();

	// モデルとの当たり判定
	CollisonModel(&m_pos, &D3DXVECTOR3(m_posOld.x, m_posOld.y + 1.0f, m_posOld.z), &m_move, PLAYER_COLLISION);

	// ゴールとの当たり判定
	CollisionGoal(&m_pos, &m_posOld, &m_move, PLAYER_COLLISION);

	// コインとの当たり判定
	CollisonCoin(&POS_BODY, ITEM_COLLISION);

	// ポリゴンとの当たり判定
	CollisonPolygon(&m_pos, PLAYER_COLLISION);

	if (pInputKeyboard->GetPress(DIK_9) && pInputKeyboard->GetPress(DIK_0) == true)
	{
		// コインとの当たり判定
		CollisonCoin(&POS_BODY, ITEM_COLLISION * 100.0f);
	}

	// 弾との当たり判定
	if (m_bBulletHit == false)
	{
		CollisonObstacle(&m_pos, COLLISION_BULLET);
	}
	else
	{
		m_nBulletTimer++;

		if (m_nBulletTimer > INVINCIBLE_TIME)
		{
			m_bBulletHit = false;
			// カウンターをリセット
			m_nBulletTimer = 0;
			m_nDisTimer = 0;
		}
	}
}

//=============================================================================
// 残機処理
//=============================================================================
void CPlayer::Life(void)
{
	// モードを取得
	CManager::MODE mode;
	mode = CManager::GetMode();

	// 残機取得
	CLife *pLife = NULL;

	if (mode == CManager::MODE_TUTORIAL)
	{
		pLife = CTutorial::GetLife();
	}
	else if (mode == CManager::MODE_GAME)
	{
		pLife = CGame::GetLife();
	}

}

//=============================================================================
// 体力処理
//=============================================================================
void CPlayer::Health(void)
{
	// モードを取得
	CManager::MODE mode;
	mode = CManager::GetMode();

	// 体力取得
	CHealth *pHealth = NULL;

	// 残機取得
	CLife *pLife = NULL;


	if (mode == CManager::MODE_TUTORIAL)
	{
		pLife = CTutorial::GetLife();
		pHealth = CTutorial::GetHealth();
	}
	else if (mode == CManager::MODE_GAME)
	{
		pLife = CGame::GetLife();
		pHealth = CGame::GetHealth();
	}

	if (pHealth->GetHealth() <= 0)
	{
		m_bGameOver = true;	// ゲームオーバーにする
	}
}
//=============================================================================
// おなら残機処理
//=============================================================================
void CPlayer::OnaraRemain(void)
{
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// モードを取得
	CManager::MODE mode;
	mode = CManager::GetMode();

	// おなら残機取得
	COnaraRemain *pOnaraRemain = NULL;

	if (mode == CManager::MODE_GAME)
	{
		pOnaraRemain = CGame::GetOnaraRemain();

	}

	if (mode == CManager::MODE_GAME)
	{
		if (pInputKeyboard->GetTrigger(DIK_W) == true)
		{// Wを押したらおなら残機を減らす

			if (m_nOnaraRemain > 0)
			{
				m_nOnaraRemain--;

				pOnaraRemain->AddOnaraRemain(-1);
			}
		}


	
	}
}

	//if (mode == CManager::MODE_TUTORIAL)
	//{
	//	if (m_pos.y <= -PLAYER_FALL)
	//	{// 床から落ちた時
	//		m_bGameOver = true;	// ゲームオーバーにする
	//	}
	//}

//=============================================================================
// 右側にいるかどうかを取得
//=============================================================================
bool CPlayer::GetRTriangle(void)
{
	return m_bRTriangle;
}

//=============================================================================
// プレイヤーの位置を取得する処理
//=============================================================================
D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// 1フレーム前のプレイヤーの位置を取得する処理
//=============================================================================
D3DXVECTOR3 *CPlayer::GetPosOld(void)
{
	return &m_posOld;
}

//=============================================================================
// プレイヤーの移動量を取得する処理
//=============================================================================
D3DXVECTOR3 CPlayer::GetMove(void)
{
	return m_move;
}

//=============================================================================
// プレイヤーがジャンプしているかどうかを設定する処理
//=============================================================================
void CPlayer::SetJump(bool bJump)
{
	m_bJump = bJump;
}

//=============================================================================
// プレイヤーがジャンプしているかどうかを取得する処理
//=============================================================================
bool CPlayer::GetJump(void)
{
	return m_bJump;
}

//=============================================================================
// プレイヤーの状態を設定
//=============================================================================
void CPlayer::SetState(STATE state)
{
	m_State = state;
}

//=============================================================================
// プレイヤーの向きを取得する処理
//=============================================================================
D3DXVECTOR3 CPlayer::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// プレイヤーがゴールしているかを取得する処理
//=============================================================================
bool CPlayer::GetGoal(void)
{
	return m_bGoal;
}

//=============================================================================
// プレイヤーがゲームオーバーかを取得する処理
//=============================================================================
bool CPlayer::GetGameOver(void)
{
	return m_bGameOver;
}

//=============================================================================
// ブロックの位置を取得する処理
//=============================================================================
D3DXVECTOR3 CPlayer::GetBlockPos(void)
{
	return m_SetBlockPos;
}

//=============================================================================
// 弾との当たり判定の処理
//=============================================================================
void CPlayer::CollisonObstacle(D3DXVECTOR3 *pos, float fRadius)
{
	// モードの取得
	CManager::MODE mode;
	mode = CManager::GetMode();

	// 体力を取得
	CHealth *pHealth = NULL;

	pHealth = CGame::GetHealth();
	

	// 音楽情報を取得
	CSound *pSound;
	pSound = CManager::GetSound();

	CScene *pScene = NULL;

	// 先頭のオブジェクトを取得(メッシュフィールドの優先順位が3だから、3にあるオブジェクトをすべて見る)
	pScene = CScene::GetTop(BULLET_PRIORITY);

	while (pScene != NULL)
	{// 優先順位が3のオブジェクトを1つ1つ確かめる
	 // 処理の最中に消える可能性があるから先に記録しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// 死亡フラグが立っていないもの
			if (pScene->GetObjType() == CScene::OBJTYPE_BULLET)
			{// オブジェクトの種類を確かめる
				if (m_bBulletHit == false)
				{
					if (((CObstacle*)pScene)->CollisionPlayer(pos, fRadius) == true)
					{
						pHealth->CutHealth(CUT_LIFE);
						m_bBulletHit = true;
					}
				}
			}
		}

		// 次のシーンに進める
		pScene = pSceneNext;
	}
}