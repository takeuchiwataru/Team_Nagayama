//=============================================================================
//
// タイトルの処理 [title.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "scene2D.h"
#include "player.h"
#include "particleX.h"
#include "meshCylinder.h"
#include "sound.h"
#include "field.h"
#include "pressAnyButton.h"
#include "text.h"
#include "resource.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CBlock *CTitle::m_pBlock[225] = {};

//=============================================================================
// タイトルクラスのコンストラクタ
//=============================================================================
CTitle::CTitle()
{
	// 値をクリア
	//m_nCntTimer = 0;

	for (int nCntPos = 0; nCntPos < 220; nCntPos++)
	{
		m_BlockPpos[nCntPos] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	m_nBlockTimer = 0;
	m_nCntBlock = 0;
	m_nBlock = 0;
	m_nCntFrame = 0;
	m_nCntTimer = 0;
	m_bSetBlock = true;
}

//=============================================================================
// タイトルの生成処理
//=============================================================================
CTitle *CTitle::Create()
{
	CTitle *pTitle = NULL;

	if (pTitle == NULL)
	{
		// オブジェクトクラスの生成
		pTitle = new CTitle;

		if (pTitle != NULL)
		{
			pTitle->Init();
		}
	}
	return pTitle;
}

//=============================================================================
// タイトルクラスのデストラクタ
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// タイトルの初期化処理
//=============================================================================
HRESULT CTitle::Init()
{
	// 値を初期化
	//m_nCntTimer = 0;

	m_nBlockTimer = 0;
	m_nCntBlock = 0;
	m_nBlock = 50;
	m_nCntFrame = 0;
	m_nCntTimer = 0;
	m_bSetBlock = true;

	// パーティクルのマテリアルのロード
	CParticleX::LoadMat();

	CPressAnyButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 650.0f, 0.0f), 200.0f, 170.0f, CResource::TEXTURE_ANYBUTTON);

	// メッシュシリンダーの生成
	CMeshCylinder::Create(D3DXVECTOR3(700.0f, 1700.0f, 0.0f), 1500.0, 30.0f);


	LoadMap();

	return S_OK;
}

//=============================================================================
// タイトルの終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	// モデルとマテリアルの情報を解放
	// パーティクル
	CParticleX::UnloadMat();

	for (int nCntBlock = 0; nCntBlock < 225; nCntBlock++)
	{
		m_pBlock[nCntBlock] = NULL;
	}

	// 全てのオブジェクトを解放
	CScene::ReleseAll();
}

//=============================================================================
// タイトルの更新処理
//=============================================================================
void CTitle::Update(void)
{
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// フェード取得
	CFade *pFade = CManager::GetFade();

	// 入力情報を取得
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetInputJoypad();

	// 音楽情報を取得
	CSound *pSound;
	pSound = CManager::GetSound();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_START) == true  || pInputJoypad->GetAnyButton(0) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			// 決定したときのSE
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER);
			pFade->SetFade(CManager::MODE_TUTORIAL, CFade::FADE_OUT);
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

	if (m_nCntTimer >= 1000)
	{
		pFade->SetFade(CManager::MODE_RANKING, CFade::FADE_OUT);
		m_nCntTimer = 0;
	}
	//pFade->SetFade(CManager::MODE_TUTORIAL, CFade::FADE_OUT);
}

//=============================================================================
// タイトルの描画処理
//=============================================================================
void CTitle::Draw(void)
{
}

//=============================================================================
// モデルのロード
//=============================================================================
void CTitle::LoadMap()
{
	//FILE *pFile = NULL;

	//CManager::MODE mode;
	//mode = CManager::GetMode();

	//CText *pText;
	//pText = CManager::GetText();

	//int nNumModel = 0;
	//
	//pFile = fopen(OBJECT_FILE_TITLE, "r");

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

	//				nNumModel = atoi(pStrCur);	// 文字列を値に変換
	//			}

	//			if (memcmp(&aStr[0], "MODEL INFO", strlen("MODEL INFO")) == 0)
	//			{
	//				for (int nCntModel = 0; nCntModel < nNumModel; nCntModel++)
	//				{
	//					pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
	//					pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
	//					strcpy(&aStr[0], pStrCur);

	//					int nCntTimer = 0;

	//					if (memcmp(&aStr[0], "ModelType", strlen("ModelType")) == 0)
	//					{
	//						pStrCur += strlen("ModelType");	// 頭出し

	//						int nType = atoi(pStrCur);	// 文字列を値に変換

	//						pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
	//						pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
	//						strcpy(&aStr[0], pStrCur);

	//						D3DXVECTOR3 pos;
	//						D3DXVECTOR3 rot;

	//						if (memcmp(&aStr[0], "POS =", strlen("POS =")) == 0)
	//						{// 位置
	//							pStrCur += strlen("POS =");	// 頭出し
	//							int nWord;

	//							// floatに変換して代入
	//							pos.x = (float)atof(pStrCur);

	//							// aStr[0]に何文字入っているかを確かめる
	//							nWord = pText->PopString(pStrCur, &aStr[0]);

	//							// 次まで進める
	//							pStrCur += nWord;

	//							// floatに変換して代入
	//							pos.y = (float)atof(pStrCur);

	//							// aStr[0]に何文字入っているかを確かめる
	//							nWord = pText->PopString(pStrCur, &aStr[0]);

	//							// 次まで進める
	//							pStrCur += nWord;

	//							// floatに変換して代入
	//							pos.z = (float)atof(pStrCur);
	//						}

	//						pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
	//						pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
	//						strcpy(&aStr[0], pStrCur);

	//						if (memcmp(&aStr[0], "ROT =", strlen("ROT =")) == 0)
	//						{// 向き
	//							pStrCur += strlen("ROT =");	// 頭出し

	//							int nWord;

	//							// floatに変換して代入
	//							rot.x = (float)atof(pStrCur);

	//							// aStr[0]に何文字入っているかを確かめる
	//							nWord = pText->PopString(pStrCur, &aStr[0]);

	//							// 次まで進める
	//							pStrCur += nWord;

	//							// floatに変換して代入
	//							rot.y = (float)atof(pStrCur);

	//							// aStr[0]に何文字入っているかを確かめる
	//							nWord = pText->PopString(pStrCur, &aStr[0]);

	//							// 次まで進める
	//							pStrCur += nWord;

	//							// floatに変換して代入
	//							rot.z = (float)atof(pStrCur);
	//						}

	//						// 位置を取っておく
	//						m_BlockPpos[nCntModel].x = pos.x;
	//						m_BlockPpos[nCntModel].y = pos.y;
	//						m_BlockPpos[nCntModel].z = pos.z;
	//					}
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
// ブロックの位置を取得する処理
//=============================================================================
D3DXVECTOR3 CTitle::GetBlockPos(int nCntBlock)
{
	return m_BlockPpos[nCntBlock];
}