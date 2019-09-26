//=============================================================================
//
// ランキングロゴの処理 [onaraUI.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _ONARAUI_H_
#define _ONARAUI_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=========================
// タイトルロゴクラス
//=========================
class COnaraUI : public CLogo
{
public:

	COnaraUI();															// コンストラクタ
	~COnaraUI();															// デストラクタ

	static COnaraUI *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);	// オブジェクトの生成

	HRESULT Init(void);															// タイトルロゴ初期化処理
	void Uninit(void);															// タイトルロゴ終了処理
	void Update(void);															// タイトルロゴ更新処理
	void Draw(void);															// タイトルロゴ描画処理

private:
};

#endif