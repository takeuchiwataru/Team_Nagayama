//=============================================================================
//
// チュートリアル処理 [tutorial.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "tutorial.h"
#include "main.h"
#include "player.h"
#include "scene2D.h"
#include "input.h"
#include "fade.h"
#include "meshCylinder.h"
#include "manager.h"
#include "field.h"
#include "score.h"
#include "particle2D.h"
#include "particle3D.h"
#include "particleX.h"
#include "goal.h"
#include "pressAnyButton.h"
#include "sound.h"
#include "number.h"
#include "text.h"
#include "resource.h"
#include "health.h"
#include "tutoriallogo.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CScore *CTutorial::m_pScore = NULL;
CNumBlock *CTutorial::m_pNumBlock = NULL;
CLife *CTutorial::m_pLife = NULL;
CHealth *CTutorial::m_pHealth = NULL;

//=============================================================================
// チュートリアルの生成処理
//=============================================================================
CTutorial *CTutorial::Create()
{
	CTutorial *pTutorial = NULL;

	if (pTutorial == NULL)
	{
		// オブジェクトクラスの生成
		pTutorial = new CTutorial;

		if (pTutorial != NULL)
		{
			pTutorial->Init();
		}
	}

	return pTutorial;
}

//=============================================================================
// チュートリアルのコンストラクタ
//=============================================================================
CTutorial::CTutorial()
{
}

//=============================================================================
// チュートリアルのデストラクタ
//=============================================================================
CTutorial::~CTutorial()
{
}

//=============================================================================
// ゲーム初期化処理
//=============================================================================
HRESULT CTutorial::Init(void)
{
	//// テクスチャを読み込む

	//// モデルを読み込む
	//// パーティクルのモデルのロード
	//CParticleX::LoadMat();

	//// プレイヤーの生成
	//CPlayer::Create(D3DXVECTOR3(0.0f, 50.0f, 220.0f));

	//if (m_pScore == NULL)
	//{
	//	// スコアの生成
	//	m_pScore = CScore::Create(D3DXVECTOR3(800.0f, 70.0f, 0.0f), 37.0f, 60.0f);
	//}

	//if (m_pLife == NULL)
	//{
	//	// ブロックの数の生成
	//	m_pLife = CLife::Create(D3DXVECTOR3(260.0f, 75.0f, 0.0f), 40.0f);
	//}

	//CreateSceneObj();
	CTutorialLogo::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, CResource::TEXTURE_TUTORIALLOGO);

	CPressAnyButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 500.0f, 650.0f, 0.0f), 150.0f, 100.0f, CResource::TEXTURE_ENTER);

	return S_OK;
}

//=============================================================================
// チュートリアル終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
	// パーティクル
	CParticleX::UnloadMat();

	// 情報を空にする
	m_pScore = NULL;
	m_pNumBlock = NULL;
	m_pLife = NULL;
	m_pHealth = NULL;

	// 全てのオブジェクトを解放
	CScene::ReleseAll();
}

//=============================================================================
// チュートリアル更新処理
//=============================================================================
void CTutorial::Update(void)
{
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// 入力情報を取得
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetInputJoypad();

	// 音楽情報を取得
	CSound *pSound;
	pSound = CManager::GetSound();

	// フェード取得
	CFade *pFade = CManager::GetFade();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_GAME, CFade::FADE_OUT);
		}
	}

	// デバック用
	if (pInputKeyboard->GetTrigger(DIK_1) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_TITLE, CFade::FADE_OUT);
		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_2) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_TUTORIAL, CFade::FADE_OUT);
		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_3) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_GAME, CFade::FADE_OUT);
		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_4) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_GAMECLEAR, CFade::FADE_OUT);
		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_5) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_GAMEOVER, CFade::FADE_OUT);
		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_6) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_RANKING, CFade::FADE_OUT);
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_START) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			// 決定したときのSE
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER);
			// フェード情報を取得
			pFade->SetFade(CManager::MODE_GAME, CFade::FADE_OUT);
		}
	}
}

//=============================================================================
// チュートリアル描画処理
//=============================================================================
void CTutorial::Draw(void)
{
}

//=============================================================================
//  その他オブジェクトの生成
//=============================================================================
void CTutorial::CreateSceneObj(void)
{
	CPressAnyButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 500.0f, 650.0f, 0.0f), 150.0f, 100.0f, CResource::TEXTURE_ENTER);

	// メッシュシリンダーの生成
	CMeshCylinder::Create(D3DXVECTOR3(0.0f, 1500.0f, 0.0f), 3000.0f, 30.0f);

	// 床ポリゴンの生成
	CFeild::Create(D3DXVECTOR3(0.0f, 0.5f, 1600.0f), 1000.0f, 4000.0f, 40.0f, 10.0f);
	CFeild::Create(D3DXVECTOR3(0.0f, 0.5f, 220.0f), 300.0f, 4000.0f, 20.0f, 1.0f);

	// ゴールの生成
	CGoal::Create(D3DXVECTOR3(0.0f, 0.0f, 1800.0f));

	// 背景ロゴの生成
	m_pHealth = CHealth::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 450.0f, 150.0f, 0.0f), 90.0f, 40.0f);
}

//=============================================================================
// スコアの取得
//=============================================================================
CScore *CTutorial::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
// ブロックの数の取得
//=============================================================================
CNumBlock *CTutorial::GetNumBlock(void)
{
	return m_pNumBlock;
}

//=============================================================================
// 残機の取得
//=============================================================================
CLife *CTutorial::GetLife(void)
{
	return m_pLife;
}