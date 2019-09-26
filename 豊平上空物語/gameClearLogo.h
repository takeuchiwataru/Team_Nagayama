//=============================================================================
//
// タイトルロゴの処理 [titlelogo.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _GAMECLEARLOGO_H_
#define _GAMECLEARLOGO_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=========================
// タイトルロゴクラス
//=========================
class CGameClearLogo : public CLogo
{
public:

	CGameClearLogo();															// コンストラクタ
	~CGameClearLogo();															// デストラクタ

	static CGameClearLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);	// オブジェクトの生成

	HRESULT Init(void);															// タイトルロゴ初期化処理
	void Uninit(void);															// タイトルロゴ終了処理
	void Update(void);															// タイトルロゴ更新処理
	void Draw(void);															// タイトルロゴ描画処理

private:
};

#endif