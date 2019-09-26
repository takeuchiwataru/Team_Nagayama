//=============================================================================
//
// ポーズの処理 [pause.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "pause.h"
#include "renderer.h"
#include "input.h"
#include "scene2D.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PAUSE_POS_X		((SCREEN_WIDTH / 2))		// ポーズの左上X座標
#define PAUSE_POS_Y		((SCREEN_HEIGHT / 2))		// ポーズの左上Y座標
#define PAUSE_WIDTH		((SCREEN_WIDTH / 2))		// ポーズの幅
#define PAUSE_HEIGHT	((SCREEN_HEIGHT / 2))		// ポーズの高さ
#define PAUSE_SIZE		(200)						// ポーズのサイズ

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CPause::m_apTexture[MAX_PAUSE_TEXTURE] = {};
CPause::MODE CPause::m_Mode = CPause::MODE_NONE;

//=============================================================================
// ポーズの生成処理
//=============================================================================
CPause *CPause::Create(void)
{
	CPause *pPause = NULL;

	if (pPause == NULL)
	{
		// 背景クラスの生成
		pPause = new CPause;

		if (pPause != NULL)
		{
			pPause->Load();
			pPause->Init();
		}
	}
	return pPause;
}

//=============================================================================
// ポーズクラスのコンストラクタ
//=============================================================================
CPause::CPause(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// 値をクリア
	for (int nCntPause = 0; nCntPause < MAX_PAUSE_TEXTURE; nCntPause++)
	{
		m_apScene2D[nCntPause] = NULL;
	}

	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		m_aCol[nCntPause] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}

	m_nSelect = 0;
}

//=============================================================================
// ポーズクラスのデストラクタ
//=============================================================================
CPause::~CPause()
{
}

//=============================================================================
// ポーズ初期化処理
//=============================================================================
HRESULT CPause::Init(void)
{
	m_nSelect = 0;
	m_Mode = MODE_NONE;

	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		m_aSelect[nCntPause] = SELECT_NONE;
		m_aCol[nCntPause] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);	// 真ん中の座標を設定

	// 2Dオブジェクト初期化処理
	m_apScene2D[0] = new CScene2D(7);
	m_apScene2D[0]->SetPosition(pos);
	m_apScene2D[0]->SetWidth(200.0f);
	m_apScene2D[0]->SetHeight(200.0f);
	m_apScene2D[0]->Init();
	m_apScene2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
	m_apScene2D[0]->BindTexture(m_apTexture[0]);

	// コンティニューを選択状態にする
	m_aSelect[0] = SELECT_SELECT;

	for (int nCntPause = 0; nCntPause < MAX_PAUSE_TEXTURE - 1; nCntPause++)
	{
		m_apScene2D[nCntPause + 1] = new CScene2D(7);
		m_apScene2D[nCntPause + 1]->SetPosition(D3DXVECTOR3(pos.x, pos.y - 120 + (nCntPause * 120), 0.0f));
		m_apScene2D[nCntPause + 1]->SetWidth(120.0f);
		m_apScene2D[nCntPause + 1]->SetHeight(50.0f);
		m_apScene2D[nCntPause + 1]->Init();
		m_apScene2D[nCntPause + 1]->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		m_apScene2D[nCntPause + 1]->BindTexture(m_apTexture[nCntPause + 1]);
	}

	return S_OK;
}

//=============================================================================
// ポーズ終了処理
//=============================================================================
void CPause::Uninit(void)
{
	Unload();
	// 2Dオブジェクト終了処理
	for (int nCntPause = 0; nCntPause < MAX_PAUSE_TEXTURE; nCntPause++)
	{
		if (m_apScene2D[nCntPause] != NULL)
		{
			m_apScene2D[nCntPause]->Uninit();
			m_apScene2D[nCntPause] = NULL;
		}
	}

	// オブジェクトの解放
	Release();
}

//=============================================================================
// ポーズ更新処理
//=============================================================================
void CPause::Update(void)
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

	if (pInputKeyboard->GetTrigger(DIK_DOWN) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_DOWN) == true
		|| pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_LS_DOWN) == true)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		m_aSelect[m_nSelect] = SELECT_NONE;
		m_nSelect = (m_nSelect + 1) % 3;
		m_aSelect[m_nSelect] = SELECT_SELECT;
	}
	if (pInputKeyboard->GetTrigger(DIK_UP) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_UP) == true
		|| pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_LS_UP) == true)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		m_aSelect[m_nSelect] = SELECT_NONE;
		m_nSelect = (m_nSelect + 2) % 3;
		m_aSelect[m_nSelect] = SELECT_SELECT;
	}

	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		if (m_aSelect[nCntPause] == SELECT_SELECT)
		{// 選択
			m_aCol[m_nSelect] = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
		}
		else
		{// 選択していない
			m_aCol[m_nSelect] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		if (m_apScene2D[nCntPause + 1] != NULL)
		{// 情報が入っていたら色を設定する
			m_apScene2D[nCntPause + 1]->SetCol(m_aCol[m_nSelect]);
		}
	}
}

//=============================================================================
// ポーズ描画処理
//=============================================================================
void CPause::Draw(void)
{
}

//=============================================================================
// ポーズのテクスチャ読み込み処理
//=============================================================================
HRESULT CPause::Load(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, PAUSE_NAME, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, PAUSET_TEXTURE_NAME0, &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, PAUSET_TEXTURE_NAME1, &m_apTexture[2]);
	D3DXCreateTextureFromFile(pDevice, PAUSET_TEXTURE_NAME2, &m_apTexture[3]);

	return S_OK;
}

//=============================================================================
// ポーズのテクスチャ解放処理
//=============================================================================
void CPause::Unload(void)
{
	for (int nCntPause = 0; nCntPause < MAX_PAUSE_TEXTURE; nCntPause++)
	{
		if (m_apTexture[nCntPause] != NULL)
		{// テクスチャの破棄
			m_apTexture[nCntPause]->Release();
			m_apTexture[nCntPause] = NULL;
		}
	}
}

//=============================================================================
// ポーズセレクトの取得
//=============================================================================
CPause::MODE CPause::GetMode(void)
{
	return m_Mode;
}

//=============================================================================
// セレクトの取得
//=============================================================================
int CPause::GetSelect(void)
{
	return m_nSelect;
}