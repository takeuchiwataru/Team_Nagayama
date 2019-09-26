//=============================================================================
//
// マネージャ処理 [manager.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "manager.h"
#include "main.h"
#include "scene2D.h"
#include "scene3D.h"
#include "sceneX.h"
#include "billboard.h"
#include "renderer.h"
#include "input.h"
#include "debugProc.h"
#include "game.h"
#include "title.h"
#include "tutorial.h"
#include "gameclear.h"
#include "gameover.h"
#include "ranking.h"
#include "fade.h"
#include "light.h"
#include "camera.h"
#include "number.h"
#include "sound.h"
#include "shadow.h"
#include "mask.h"
#include "text.h"
#include "resource.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CManager::MODE CManager::m_mode = CManager::MODE_NONE;
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputJoypad *CManager::m_pInputJoypad = NULL;
CDebugProc *CManager::m_pDebugProc = NULL;
CGame *CManager::m_pGame = NULL;
CTitle *CManager::m_pTitle = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CGameClear *CManager::m_pGameClear = NULL;
CGameOver *CManager::m_pGameOver = NULL;
CRanking *CManager::m_pRanking = NULL;
CFade *CManager::m_pFade = NULL;
CLight *CManager::m_pLight = NULL;
CCamera *CManager::m_pCamera = NULL;
int CManager::m_aScore[MAX_RANKING] = {};
int CManager::m_nScore = 0;
int CManager::m_nUpdateScore = 0;
CSound *CManager::m_pSound = NULL;
CMask *CManager::m_pMask = NULL;
CText *CManager::m_pText = NULL;

//=============================================================================
// マネージャクラスのコンストラクタ
//=============================================================================
CManager::CManager()
{
	m_fData = 0.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// マネージャ初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// 最初の画面
	//m_mode = MODE_GAMEOVER;
	//m_mode = MODE_GAME;
	//m_mode = MODE_GAME;
	//m_mode = MODE_TITLE;
	m_mode = MODE_RANKING;;

	m_fData = 0.0f;

	int nScore = 10000;

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		m_aScore[nCnt] = nScore;
		nScore -= 1000;
	}

	m_nUpdateScore = 0;

	if (m_pRenderer == NULL)
	{
		// レンダリングクラスの生成
		m_pRenderer = new CRenderer;

		if (m_pRenderer != NULL)
		{
			// 初期化処理
			if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
			{
				return -1;
			}
		}
	}

	if (m_pInputKeyboard == NULL)
	{
		// 入力クラスの生成
		m_pInputKeyboard = new CInputKeyboard;

		if (m_pInputKeyboard != NULL)
		{
			m_pInputKeyboard->Init(hInstance, hWnd);
		}
	}

	if (m_pInputJoypad == NULL)
	{
		// 入力クラスの生成
		m_pInputJoypad = new CInputJoypad;

		if (m_pInputJoypad != NULL)
		{
			m_pInputJoypad->Init(hInstance, hWnd);
		}
	}

	if (m_pCamera == NULL)
	{
		// カメラクラスの生成
		m_pCamera = new CCamera;

		if (m_pCamera != NULL)
		{
			m_pCamera->Init();
		}
	}

	if (m_pFade == NULL)
	{
		m_pFade = CFade::Create();
	}

	if (m_pMask == NULL)
	{
		m_pMask = CMask::Create();
	}

	if (m_pLight == NULL)
	{
		// ライトクラスの生成
		m_pLight = new CLight;

		if (m_pLight != NULL)
		{
			m_pLight->Init();
		}
	}

	if (m_pText == NULL)
	{
		// ライトクラスの生成
		m_pText = new CText;
	}

#ifdef _DEBUG
	if (m_pDebugProc == NULL)
	{
		// デバック表示クラスの生成
		m_pDebugProc = new CDebugProc;

		if (m_pDebugProc != NULL)
		{
			m_pDebugProc->Init();
		}
	}
#endif

	if (m_pSound == NULL)
	{
		// サウンドクラスの生成
		m_pSound = new CSound;

		if (m_pSound != NULL)
		{
			m_pSound->InitSound(hWnd);
		}
	}

	CShadow::Load();

	CResource::LoadModel();
	CResource::LoadTex();

	// モード切替
	SetMode(m_mode);

	return S_OK;
}

//=============================================================================
// マネージャ終了処理
//=============================================================================
void CManager::Uninit(void)
{
	CShadow::UnLoad();

	if (m_pFade != NULL)
	{// フェードの終了
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}

	if (m_pRenderer != NULL)
	{// レンダリングクラスの破棄
		// 終了処理
		m_pRenderer->Uninit();

		// メモリを開放
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	if (m_pCamera != NULL)
	{// カメラクラスの破棄
	 // 終了処理
		m_pCamera->Uninit();

		// メモリを開放
		delete m_pCamera;
		m_pCamera = NULL;
	}

	if (m_pLight != NULL)
	{// ライトクラスの破棄
	 // 終了処理
		m_pLight->Uninit();

		// メモリを開放
		delete m_pLight;
		m_pLight = NULL;
	}

	if (m_pInputKeyboard != NULL)
	{// レンダリングクラスの破棄
		 // 終了処理
		m_pInputKeyboard->Uninit();

		// メモリを開放
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	if (m_pInputJoypad != NULL)
	{// 入力クラスの破棄
	 // 終了処理
		m_pInputJoypad->Uninit();

		// メモリを開放
		delete m_pInputJoypad;
		m_pInputJoypad = NULL;
	}

	if (m_pSound != NULL)
	{// 入力クラスの破棄
	 // 終了処理
		m_pSound->UninitSound();

		// メモリを開放
		delete m_pSound;
		m_pSound = NULL;
	}

	if (m_pMask != NULL)
	{// 影の終了
		m_pMask->Uninit();
		delete m_pMask;
		m_pMask = NULL;
	}

	if (m_pText != NULL)
	{// 影の終了
		delete m_pText;
		m_pText = NULL;
	}

	switch (m_mode)
	{
		// タイトル画面終了処理
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();

			// メモリを開放
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;
		// チュートリアル画面終了処理
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();

			// メモリを開放
			delete m_pTutorial;
			m_pTutorial = NULL;
		}
		break;
		// ゲーム画面終了処理
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();

			// メモリを開放
			delete m_pGame;
			m_pGame = NULL;
		}
		break;
		// ゲームクリア画面終了処理
	case MODE_GAMECLEAR:
		if (m_pGameClear != NULL)
		{
			m_pGameClear->Uninit();

			// メモリを開放
			delete m_pGameClear;
			m_pGameClear = NULL;
		}
		break;
		// ゲームオーバー画面終了処理
	case MODE_GAMEOVER:
		if (m_pGameOver != NULL)
		{
			m_pGameOver->Uninit();

			// メモリを開放
			delete m_pGameOver;
			m_pGameOver = NULL;
		}
		break;
		// ランキング画面終了処理
	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_nUpdateScore = 0;
			m_pRanking->Uninit();

			// メモリを開放
			delete m_pRanking;
			m_pRanking = NULL;
		}
		break;
	}

#ifdef _DEBUG
	if (m_pDebugProc != NULL)
	{// デバック表示クラスの破棄
		// 終了処理
		m_pDebugProc->Uninit();

		// メモリを開放
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}
#endif

	CResource::UnloadModel();
	CResource::UnloadTex();

	// 全てのオブジェクトを解放
	CScene::ReleseAll();
}

//=============================================================================
// マネージャ更新処理
//=============================================================================
void CManager::Update(void)
{
#ifdef _DEBUG
	// デバック表示を消す
	CDebugProc::ReleseStr();
#endif

	if (m_pRenderer != NULL)
	{// レンダラー更新処理
		m_pRenderer->Update();
	}

	if (m_pCamera != NULL)
	{// カメラ更新処理
		m_pCamera->Update();
	}

	if (m_pLight != NULL)
	{// ライト更新処理
		m_pLight->Update();
	}

	if (m_pInputKeyboard != NULL)
	{// キーボード入力更新処理
		m_pInputKeyboard->Update();
	}

	if (m_pInputJoypad != NULL)
	{// キーボード入力更新処理
		m_pInputJoypad->Update();
	}

	if (m_pFade != NULL)
	{// キーボード入力更新処理
		m_pFade->Update();
	}

	switch (m_mode)
	{
		// タイトル画面更新処理
	case MODE_TITLE:
#ifdef _DEBUG
		CDebugProc::Print("c", "タイトル");
#endif
		m_pTitle->Update();
		break;
		// チュートリアル画面更新処理
	case MODE_TUTORIAL:
#ifdef _DEBUG
		CDebugProc::Print("c", "チュートリアル");
#endif
		m_pTutorial->Update();
		break;
		// ゲーム画面更新処理
	case MODE_GAME:
#ifdef _DEBUG
		CDebugProc::Print("c", "ゲーム");
#endif
		m_pGame->Update();
		break;
		// ゲームクリア画面更新処理
	case MODE_GAMECLEAR:
#ifdef _DEBUG
		CDebugProc::Print("c", "ゲームクリア");
#endif
		m_pGameClear->Update();
		break;
		// ゲームオーバー画面更新処理
	case MODE_GAMEOVER:
#ifdef _DEBUG
		CDebugProc::Print("c", "ゲームオーバー");
#endif
		m_pGameOver->Update();
		break;
		// ランキング画面終了処理
	case MODE_RANKING:
#ifdef _DEBUG
		CDebugProc::Print("c", "ランキング");
#endif
		m_pRanking->Update();
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	if (m_pCamera != NULL)
	{// カメラを設定
		m_pCamera->SetCamera();
	}

	if (m_pRenderer != NULL)
	{// レンダラー描画処理
		m_pRenderer->Draw();
	}

	switch (m_mode)
	{
		// タイトル画面描画処理
	case MODE_TITLE:
		m_pTitle->Draw();
		break;
		// タイトル画面描画処理
	case MODE_TUTORIAL:
		m_pTutorial->Draw();
		break;
		// ゲーム画面描画処理
	case MODE_GAME:
		m_pGame->Draw();
		break;
		// ゲームクリア画面描画処理
	case MODE_GAMECLEAR:
		m_pGameClear->Draw();
		break;
		// ゲームオーバー画面描画処理
	case MODE_GAMEOVER:
		m_pGameOver->Draw();
		break;
		// ランキング画面描画処理
	case MODE_RANKING:
		m_pRanking->Draw();
		break;
	}
}

//=============================================================================
// デバイスの設定
//=============================================================================
void CManager::SetMode(MODE mode)
{
	switch (m_mode)
	{
		// タイトル画面終了処理
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pSound->StopSound(CSound::SOUND_LABEL_BGM_TITLE);

			m_pTitle->Uninit();

			// メモリを開放
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;
		// チュートリアル画面終了処理
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pSound->StopSound(CSound::SOUND_LABEL_BGM_TUTORIAL0);
			m_pTutorial->Uninit();

			// メモリを開放
			delete m_pTutorial;
			m_pTutorial = NULL;
		}
		break;
		// ゲーム画面終了処理
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pSound->StopSound(CSound::SOUND_LABEL_BGM_TUTORIAL);
			m_pGame->Uninit();

			// メモリを開放
			delete m_pGame;
			m_pGame = NULL;
		}
		break;
		// ゲームクリア画面終了処理
	case MODE_GAMECLEAR:
		if (m_pGameClear != NULL)
		{
			m_pSound->StopSound(CSound::SOUND_LABEL_BGM_RESULTCLEAR);
			m_pGameClear->Uninit();

			// メモリを開放
			delete m_pGameClear;
			m_pGameClear = NULL;
		}
		break;
		// ゲームオーバー画面終了処理
	case MODE_GAMEOVER:
		if (m_pGameOver != NULL)
		{
			m_pSound->StopSound(CSound::SOUND_LABEL_BGM_RESULTOVER);
			m_pGameOver->Uninit();

			// メモリを開放
			delete m_pGameOver;
			m_pGameOver = NULL;
		}
		break;
		// ランキング画面終了処理
	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pSound->StopSound(CSound::SOUND_LABEL_BGM_RANKING);
			m_nUpdateScore = 0;
			m_pRanking->Uninit();

			// メモリを開放
			delete m_pRanking;
			m_pRanking = NULL;
		}
		break;
	}

	switch (mode)
	{
		// タイトル画面初期化処理
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{
			if (m_pCamera != NULL)
			{
				m_pCamera->Init();
			}
			// ゲームを生成
			m_pTitle = CTitle::Create();
			m_nUpdateScore = MAX_RANKING + 1;
			m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);
		}
		break;
		// タイトル画面初期化処理
	case MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			if (m_pCamera != NULL)
			{
				m_pCamera->Init();
			}
			// ゲームを生成
			m_pTutorial = CTutorial::Create();
			m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_TUTORIAL);
		}
		break;
		// ゲーム画面初期化処理
	case MODE_GAME:
		if (m_pGame == NULL)
		{
			if (m_pCamera != NULL)
			{
				m_pCamera->Init();
			}
			// ゲームを生成
			m_pGame = CGame::Create();
			m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_TUTORIAL);
		}
		break;
		// ゲームクリア画面初期化処理
	case MODE_GAMECLEAR:
		if (m_pGameClear == NULL)
		{
			if (m_pCamera != NULL)
			{
				m_pCamera->Init();
			}
			// ゲームを生成
			m_pGameClear = CGameClear::Create();
			m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_RESULTCLEAR);
		}
		break;

		// ゲームクリア画面初期化処理
	case MODE_GAMEOVER:
		if (m_pGameOver == NULL)
		{
			if (m_pCamera != NULL)
			{
				m_pCamera->Init();
			}
			// ゲームを生成
			m_pGameOver = CGameOver::Create();
			m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_RESULTOVER);
		}
		break;
		// ランキング画面初期化処理
	case MODE_RANKING:
		if (m_pRanking == NULL)
		{
			if (m_pCamera != NULL)
			{
				m_pCamera->Init();
			}
			// ゲームを生成
			m_pRanking = CRanking::Create();
			m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_RANKING);
		}
		break;
	}
	m_mode = mode;
}

//=============================================================================
// レンダラーの取得
//=============================================================================
CFade *CManager::GetFade(void)
{
	return m_pFade;
}

//=============================================================================
// デバイスの取得
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
// レンダラーの取得
//=============================================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// 入力情報の取得
//=============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
// 入力情報の取得
//=============================================================================
CInputJoypad *CManager::GetInputJoypad(void)
{
	return m_pInputJoypad;
}

//=============================================================================
// カメラの取得
//=============================================================================
CCamera *CManager::GetCamera(void)
{
	return m_pCamera;
}

//=============================================================================
// ランキングの取得
//=============================================================================
int CManager::GetRanking(int nIdx)
{
	return m_aScore[nIdx];
}

//=============================================================================
// ランキングスコアの取得
//=============================================================================
void CManager::GetRankingScore(int nScore)
{
	int nData = 0;
	int nUpdateScore = 0;

	if (m_aScore[MAX_RANKING - 1] <= nScore)
	{
		m_aScore[MAX_RANKING - 1] = nScore;
		nUpdateScore = nScore;
	}
	else
	{
		m_nUpdateScore = MAX_RANKING + 1;
	}

	for (int nCntData = 0; nCntData < MAX_RANKING; nCntData++)
	{// 大きい順並び替え
		for (int nCntNumber = 0; nCntNumber < MAX_RANKING - 1; nCntNumber++)
		{
			if (m_aScore[nCntNumber] < m_aScore[nCntNumber + 1])
			{
				nData = m_aScore[nCntNumber];
				m_aScore[nCntNumber] = m_aScore[nCntNumber + 1];
				m_aScore[nCntNumber + 1] = nData;
			}
		}

		if (m_aScore[nCntData] == nUpdateScore)
		{
			m_nUpdateScore = nCntData;
		}
	}
}

//=============================================================================
// スコアの取得
//=============================================================================
void CManager::GetScore(int nScore)
{
	m_nScore = nScore;
}

//=============================================================================
// スコアの設定
//=============================================================================
int CManager::SetScore(void)
{
	return m_nScore;
}

//=============================================================================
// スコアのリセット
//=============================================================================
void CManager::ReleaseScore(void)
{
	m_nScore = 0;
}

//=============================================================================
// アップデートスコアの取得
//=============================================================================
int CManager::GetUpdateScore(void)
{
	return m_nUpdateScore;
}

//=============================================================================
// 音楽情報の取得
//=============================================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}

//=============================================================================
// マスクの取得
//=============================================================================
CMask *CManager::GetMask(void)
{
	return m_pMask;
}

//=============================================================================
// テキスト読み込みクラスの取得
//=============================================================================
CText *CManager::GetText(void)
{
	return m_pText;
}