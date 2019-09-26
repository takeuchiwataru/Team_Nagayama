//=============================================================================
//
// ゲームオーバーの処理 [gameover.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "gameover.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "meshCylinder.h"
#include "sound.h"
#include "particleX.h"
#include "score.h"
#include "pressAnyButton.h"
#include "number.h"
#include "text.h"
#include "resource.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CBlock *CGameOver::m_pBlock[MAX_BLOCK] = {};
CScore *CGameOver::m_pScore = NULL;

//=============================================================================
// ゲームオーバークラスのコンストラクタ
//=============================================================================
CGameOver::CGameOver()
{
	// 値をクリア
	m_nNumModel = 0;
	m_nBlockTimer = 0;
	m_bSetBlock = true;
	m_nCntBlock = 0;
	m_nScore = 0;
	m_nCntScore = 0;
}

//=============================================================================
// ゲームオーバーの生成処理
//=============================================================================
CGameOver *CGameOver::Create()
{
	CGameOver *pGameOver = NULL;

	if (pGameOver == NULL)
	{
		// オブジェクトクラスの生成
		pGameOver = new CGameOver;

		if (pGameOver != NULL)
		{
			pGameOver->Init();
		}
	}
	return pGameOver;
}

//=============================================================================
// ゲームオーバークラスのデストラクタ
//=============================================================================
CGameOver::~CGameOver()
{
}

//=============================================================================
// ゲームオーバーの初期化処理
//=============================================================================
HRESULT CGameOver::Init(void)
{
	// 値の初期化
	m_nCntTimer = 0;

	m_nNumModel = 0;
	m_nBlockTimer = 0;
	m_bSetBlock = true;
	m_nCntBlock = 0;
	m_nScore = 0;
	m_nCntScore = 0;

	// パーティクルのモデルのロード
	CParticleX::LoadMat();

	//LoadCharFall();

	CPressAnyButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 650.0f, 0.0f), 200.0f, 170.0f, CResource::TEXTURE_ANYBUTTON);

	if (m_pScore == NULL)
	{
		int nScore = 0;

		nScore = CManager::SetScore();

		m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 280.0f, SCREEN_HEIGHT / 2 + 70.0f, 0.0f), 70.0f, 120.0f);
		m_pScore->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		m_pScore->AddScore(nScore);
	}

	int nCnt = 0;
	

	// メッシュシリンダーの生成
	CMeshCylinder::Create(D3DXVECTOR3(700.0f, 1700.0f, 0.0f), 2000.0, 30.0f);

	return S_OK;
}

//=============================================================================
// ゲームオーバーの終了処理
//=============================================================================
void CGameOver::Uninit(void)
{
	// パーティクル
	CParticleX::UnloadMat();

	m_pScore = NULL;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK + 1; nCntBlock++)
	{
		m_pBlock[nCntBlock] = NULL;
	}

	// 全てのオブジェクトを解放
	CScene::ReleseAll();
}

//=============================================================================
// ゲームオーバーの更新処理
//=============================================================================
void CGameOver::Update(void)
{
	CManager::MODE mode;
	mode = CManager::GetMode();

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

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_START) == true || pInputJoypad->GetAnyButton(0) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			// 決定したときのSE
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER);
			CManager::ReleaseScore();
			pFade->SetFade(CManager::MODE_RANKING, CFade::FADE_OUT);
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
}

//=============================================================================
// ゲームオーバーの描画処理
//=============================================================================
void CGameOver::Draw(void)
{
}

//=============================================================================
// モデルのロード
//=============================================================================
void CGameOver::LoadCharFall()
{
	//FILE *pFile = NULL;

	//CManager::MODE mode;
	//mode = CManager::GetMode();

	//CText *pText;
	//pText = CManager::GetText();

	//int nCharType = 0;

	//pFile = fopen(OBJECT_FILE_GAMEOVER, "r");

	//if (pFile != NULL)
	//{
	//	char *pStrCur;		// 文字列の先頭へのポインタ
	//	char aLine[256];	// 文字列読み込み用（1行分）
	//	char aStr[256];		// 文字列抜き出し用

	//	pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
	//	pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
	//	strcpy(&aStr[0], pStrCur);

	//	if (memcmp(&aStr[0], "SCRIPT", strlen("SCRIPT")) == 0)
	//	{
	//		while (1)
	//		{
	//			pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
	//			pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
	//			strcpy(&aStr[0], pStrCur);


	//			if (memcmp(&aStr[0], "NUM_MODEL =", strlen("NUM_MODEL =")) == 0)
	//			{
	//				pStrCur += strlen("NUM_MODEL =");	// 頭出し

	//				m_nNumModel = atoi(pStrCur);	// 文字列を値に変換


	//				for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	//				{
	//					pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
	//					pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
	//					strcpy(&aStr[0], pStrCur);

	//					D3DXVECTOR3 pos;
	//					D3DXVECTOR3 rot;

	//					if (memcmp(&aStr[0], "POS =", strlen("POS =")) == 0)
	//					{// 位置
	//						pStrCur += strlen("POS =");	// 頭出し
	//						int nWord;

	//						// floatに変換して代入
	//						pos.x = (float)atof(pStrCur);

	//						// aStr[0]に何文字入っているかを確かめる
	//						nWord = pText->PopString(pStrCur, &aStr[0]);

	//						// 次まで進める
	//						pStrCur += nWord;

	//						// floatに変換して代入
	//						pos.y = (float)atof(pStrCur);

	//						// aStr[0]に何文字入っているかを確かめる
	//						nWord = pText->PopString(pStrCur, &aStr[0]);

	//						// 次まで進める
	//						pStrCur += nWord;

	//						// floatに変換して代入
	//						pos.z = (float)atof(pStrCur);
	//					}

	//					pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
	//					pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
	//					strcpy(&aStr[0], pStrCur);

	//					if (memcmp(&aStr[0], "ROT =", strlen("ROT =")) == 0)
	//					{// 位置
	//						pStrCur += strlen("ROT =");	// 頭出し

	//						int nWord;

	//						// floatに変換して代入
	//						rot.x = (float)atof(pStrCur);

	//						// aStr[0]に何文字入っているかを確かめる
	//						nWord = pText->PopString(pStrCur, &aStr[0]);

	//						// 次まで進める
	//						pStrCur += nWord;

	//						// floatに変換して代入
	//						rot.y = (float)atof(pStrCur);

	//						// aStr[0]に何文字入っているかを確かめる
	//						nWord = pText->PopString(pStrCur, &aStr[0]);

	//						// 次まで進める
	//						pStrCur += nWord;

	//						// floatに変換して代入
	//						rot.z = (float)atof(pStrCur);
	//					}

	//					// 位置を取っておく
	//					m_BlockPpos[nCntModel] = pos;

	//					
	//				}
	//			}

	//			if (memcmp(&aStr[0], "ENDSCRIPT", strlen("ENDSCRIPT")) == 0)
	//			{
	//				break;
	//			}
	//		}
	//	}
	//	fclose(pFile);
	//}
}

//=============================================================================
// ブロック
//=============================================================================
void CGameOver::Block()
{
	
}