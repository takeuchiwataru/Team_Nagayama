//=============================================================================
//
// タイトルロゴの処理 [titlelogo.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "titlelogo.h"
#include "renderer.h"
#include "fade.h"
#include "input.h"
#include "resource.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BUTTON_COLOR		(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))
#define BLINK_COUNT			(60)
#define BLINK_COUNT_FAST	(2)

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// タイトルロゴの生成処理
//=============================================================================
CTitleLogo *CTitleLogo::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType)
{
	CTitleLogo *pGameOverLogo = NULL;

	if (pGameOverLogo == NULL)
	{
		// タイトルロゴクラスの生成
		pGameOverLogo = new CTitleLogo;

		if (pGameOverLogo != NULL)
		{
			pGameOverLogo->SetPosition(pos);
			pGameOverLogo->SetWidth(fWidth);
			pGameOverLogo->SetHeight(fHeight);
			pGameOverLogo->Init();
			pGameOverLogo->BindTexture(CResource::GetTexture(nType));
		}
	}

	return pGameOverLogo;
}

//=============================================================================
// タイトルロゴクラスのコンストラクタ
//=============================================================================
CTitleLogo::CTitleLogo()
{
}

//=============================================================================
// タイトルロゴクラスのデストラクタ
//=============================================================================
CTitleLogo::~CTitleLogo()
{
}

//=============================================================================
// タイトルロゴ初期化処理
//=============================================================================
HRESULT CTitleLogo::Init(void)
{
	// 2Dオブジェクト初期化処理
	CLogo::Init();


	CLogo::SetCol(BUTTON_COLOR);

	return S_OK;
}

//=============================================================================
// タイトルロゴ終了処理
//=============================================================================
void CTitleLogo::Uninit(void)
{
	// 2Dオブジェクト終了処理
	CLogo::Uninit();
}

//=============================================================================
// タイトルロゴ更新処理
//=============================================================================
void CTitleLogo::Update(void)
{
	//// 入力情報を取得
	//CInputKeyboard *pInputKeyboard;
	//pInputKeyboard = CManager::GetInputKeyboard();

	//// 入力情報を取得
	//CInputJoypad *pInputJoypad;
	//pInputJoypad = CManager::GetInputJoypad();

	//// フェードの状態を取得
	//CFade::FADE fade;
	//fade = CFade::GetFade();
}

//=============================================================================
// タイトルロゴ描画処理
//=============================================================================
void CTitleLogo::Draw(void)
{
	// 2Dオブジェクト描画処理
	CLogo::Draw();
}