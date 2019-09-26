//=============================================================================
//
// ランキングの処理 [ranking.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "ranking.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "score.h"
#include "meshCylinder.h"
#include "sound.h"
#include "number.h"
#include "pressAnyButton.h"
#include "text.h"
#include "resource.h"
#include "rankinglogo.h"
#include "rankinglogo2.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CScore *CRanking::m_apScore[MAX_RANKING] = {};

//=============================================================================
// リザルトクラスのコンストラクタ
//=============================================================================
CRanking::CRanking()
{
	// 値をクリア
	m_nCntTimer = 0;

	m_nNumModel = 0;
	m_nNumRankModel = 0;
	m_nBlockTimer = 0;
	m_nCntBlock = 0;
	m_nBlockNumTimer = 0;
	m_nCntNumBlock = 0;
	m_bSetBlock = false;
	m_bSetNumBlock = false;
	for (int nCntBlock = 0; nCntBlock < 1000; nCntBlock++)
	{
		m_BlockPos[nCntBlock] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_BlockNumPos[nCntBlock] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
// リザルトの生成処理
//=============================================================================
CRanking *CRanking::Create()
{
	CRanking *pRanking = NULL;

	if (pRanking == NULL)
	{
		// オブジェクトクラスの生成
		pRanking = new CRanking;

		if (pRanking != NULL)
		{
			pRanking->Init();
		}
	}
	return pRanking;
}

//=============================================================================
// リザルトクラスのデストラクタ
//=============================================================================
CRanking::~CRanking()
{
}

//=============================================================================
// リザルトの初期化処理
//=============================================================================
HRESULT CRanking::Init()
{
	// 値の初期化
	m_nCntColor = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nCntTimer = 0;

	m_nNumModel = 0;
	m_nBlockTimer = 0;
	m_bSetBlock = true;
	m_bSetNumBlock = true;
	m_nCntBlock = 0;
	m_nNumRankModel = 0;
	m_nBlockNumTimer = 0;
	m_nCntNumBlock = 0;

	// メッシュシリンダーの生成
	CMeshCylinder::Create(D3DXVECTOR3(700.0f, 2000.0f, 0.0f), 4000.0, 100.0f);

	CPressAnyButton::Create(D3DXVECTOR3(SCREEN_WIDTH - 150.0f, SCREEN_HEIGHT - 40.0f, 0.0f), 150.0f, 70.0f, CResource::TEXTURE_ANYBUTTON);

	LoadCharFall();
	LoadCharNumFall();

	int aScore[MAX_RANKING] = {};

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		if (m_apScore[nCntRanking] == NULL)
		{
			aScore[nCntRanking] = CManager::GetRanking(nCntRanking);
			// スコアの生成
			m_apScore[nCntRanking] = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 300.0f, 250.0f + (nCntRanking * 95.0f) + 20, 0.0f), 37.0f, 60.0f);
			m_apScore[nCntRanking]->AddScore(aScore[nCntRanking]);
			m_apScore[nCntRanking]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
	
	// ランキングロゴ
	CRankingLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f, 0.0f), 300.0f, 200.0f, CResource::TEXTURE_RANKINGLOGO);


	// ランキングランクロゴ
	CRankingLogo2::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 500.0f, 0.0f), 100.0, 250.0f, CResource::TEXTURE_RANKINGRANK);

	return S_OK;
}

//=============================================================================
// リザルトの終了処理
//=============================================================================
void CRanking::Uninit(void)
{

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		m_apScore[nCntRanking] = NULL;
	}

	// 全てのオブジェクトを解放
	CScene::ReleseAll();
}

//=============================================================================
// リザルトの更新処理
//=============================================================================
void CRanking::Update(void)
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

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_START) == true || pInputJoypad->GetAnyButton(0) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			// 決定したときのSE
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER);
			pFade->SetFade(CManager::MODE_TITLE, CFade::FADE_OUT);
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

	m_nCntTimer++;

	if (m_nCntTimer >= 2000)
	{
		pFade->SetFade(CManager::MODE_TITLE, CFade::FADE_OUT);
		m_nCntTimer = 0;
	}

	CManager *pManager = NULL;
	int nUpdateScore = -1;
	nUpdateScore = pManager->GetUpdateScore();

	if (nUpdateScore >= 0 && nUpdateScore <= 4)
	{
		m_nCntColor++;

		if (m_nCntColor % 4 == 0)
		{
			if (m_col.g == 0.0f)
			{
				m_col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			}
			else
			{
				m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}
		}
		m_apScore[nUpdateScore]->SetColor(m_col);
	}
}

//=============================================================================
// リザルトの描画処理
//=============================================================================
void CRanking::Draw(void)
{
}

//=============================================================================
// 落ちるブロックの位置情報のロード
//=============================================================================
void CRanking::LoadCharFall(void)
{
	FILE *pFile = NULL;

	CManager::MODE mode;
	mode = CManager::GetMode();

	CText *pText;
	pText = CManager::GetText();

	int nCharType = 0;

	pFile = fopen(CHAR_RANKING_FILE, "r");

	if (pFile != NULL)
	{
		char *pStrCur;		// 文字列の先頭へのポインタ
		char aLine[256];	// 文字列読み込み用（1行分）
		char aStr[256];		// 文字列抜き出し用

		pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
		pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
		strcpy(&aStr[0], pStrCur);

		if (memcmp(&aStr[0], "SCRIPT", strlen("SCRIPT")) == 0)
		{
			while (1)
			{
				pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
				pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
				strcpy(&aStr[0], pStrCur);


				if (memcmp(&aStr[0], "NUM_MODEL =", strlen("NUM_MODEL =")) == 0)
				{
					pStrCur += strlen("NUM_MODEL =");	// 頭出し

					m_nNumModel = atoi(pStrCur);	// 文字列を値に変換


					for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
					{
						pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
						pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
						strcpy(&aStr[0], pStrCur);

						D3DXVECTOR3 pos;
						D3DXVECTOR3 rot;

						if (memcmp(&aStr[0], "POS =", strlen("POS =")) == 0)
						{// 位置
							pStrCur += strlen("POS =");	// 頭出し
							int nWord;

							// floatに変換して代入
							pos.x = (float)atof(pStrCur);

							// aStr[0]に何文字入っているかを確かめる
							nWord = pText->PopString(pStrCur, &aStr[0]);

							// 次まで進める
							pStrCur += nWord;

							// floatに変換して代入
							pos.y = (float)atof(pStrCur);

							// aStr[0]に何文字入っているかを確かめる
							nWord = pText->PopString(pStrCur, &aStr[0]);

							// 次まで進める
							pStrCur += nWord;

							// floatに変換して代入
							pos.z = (float)atof(pStrCur);
						}

						pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
						pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
						strcpy(&aStr[0], pStrCur);

						if (memcmp(&aStr[0], "ROT =", strlen("ROT =")) == 0)
						{// 位置
							pStrCur += strlen("ROT =");	// 頭出し

							int nWord;

							// floatに変換して代入
							rot.x = (float)atof(pStrCur);

							// aStr[0]に何文字入っているかを確かめる
							nWord = pText->PopString(pStrCur, &aStr[0]);

							// 次まで進める
							pStrCur += nWord;

							// floatに変換して代入
							rot.y = (float)atof(pStrCur);

							// aStr[0]に何文字入っているかを確かめる
							nWord = pText->PopString(pStrCur, &aStr[0]);

							// 次まで進める
							pStrCur += nWord;

							// floatに変換して代入
							rot.z = (float)atof(pStrCur);
						}

						// 位置を取っておく
						m_BlockPos[nCntModel] = pos;
					}
				}

				if (memcmp(&aStr[0], "ENDSCRIPT", strlen("ENDSCRIPT")) == 0)
				{
					break;
				}
			}
		}
		fclose(pFile);
	}
}

//=============================================================================
// 落ちるブロックの位置情報のロード
//=============================================================================
void CRanking::LoadCharNumFall(void)
{
	FILE *pFile = NULL;

	CManager::MODE mode;
	mode = CManager::GetMode();

	CText *pText;
	pText = CManager::GetText();

	int nCharType = 0;

	pFile = fopen(CHAR_RANKINGNUM_FILE, "r");

	if (pFile != NULL)
	{
		char *pStrCur;		// 文字列の先頭へのポインタ
		char aLine[256];	// 文字列読み込み用（1行分）
		char aStr[256];		// 文字列抜き出し用

		pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
		pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
		strcpy(&aStr[0], pStrCur);

		if (memcmp(&aStr[0], "SCRIPT", strlen("SCRIPT")) == 0)
		{
			while (1)
			{
				pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
				pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
				strcpy(&aStr[0], pStrCur);


				if (memcmp(&aStr[0], "NUM_MODEL =", strlen("NUM_MODEL =")) == 0)
				{
					pStrCur += strlen("NUM_MODEL =");	// 頭出し

					m_nNumRankModel = atoi(pStrCur);	// 文字列を値に変換


					for (int nCntModel = 0; nCntModel < m_nNumRankModel; nCntModel++)
					{
						pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
						pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
						strcpy(&aStr[0], pStrCur);

						D3DXVECTOR3 pos;
						D3DXVECTOR3 rot;

						if (memcmp(&aStr[0], "POS =", strlen("POS =")) == 0)
						{// 位置
							pStrCur += strlen("POS =");	// 頭出し
							int nWord;

							// floatに変換して代入
							pos.x = (float)atof(pStrCur);

							// aStr[0]に何文字入っているかを確かめる
							nWord = pText->PopString(pStrCur, &aStr[0]);

							// 次まで進める
							pStrCur += nWord;

							// floatに変換して代入
							pos.y = (float)atof(pStrCur);

							// aStr[0]に何文字入っているかを確かめる
							nWord = pText->PopString(pStrCur, &aStr[0]);

							// 次まで進める
							pStrCur += nWord;

							// floatに変換して代入
							pos.z = (float)atof(pStrCur);
						}

						pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
						pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
						strcpy(&aStr[0], pStrCur);

						if (memcmp(&aStr[0], "ROT =", strlen("ROT =")) == 0)
						{// 位置
							pStrCur += strlen("ROT =");	// 頭出し

							int nWord;

							// floatに変換して代入
							rot.x = (float)atof(pStrCur);

							// aStr[0]に何文字入っているかを確かめる
							nWord = pText->PopString(pStrCur, &aStr[0]);

							// 次まで進める
							pStrCur += nWord;

							// floatに変換して代入
							rot.y = (float)atof(pStrCur);

							// aStr[0]に何文字入っているかを確かめる
							nWord = pText->PopString(pStrCur, &aStr[0]);

							// 次まで進める
							pStrCur += nWord;

							// floatに変換して代入
							rot.z = (float)atof(pStrCur);
						}

						// 位置を取っておく
						m_BlockNumPos[nCntModel] = pos;
					}
				}

				if (memcmp(&aStr[0], "ENDSCRIPT", strlen("ENDSCRIPT")) == 0)
				{
					break;
				}
			}
		}
		fclose(pFile);
	}
}