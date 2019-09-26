//=============================================================================
//
// ランキングロゴ2の処理 [rankinglogo2.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _RAKINGLOG02_H_
#define _RAKINGLOGO2_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=========================
// タイトルロゴクラス
//=========================
class CRankingLogo2: public CLogo
{
public:

	CRankingLogo2();															// コンストラクタ
	~CRankingLogo2();															// デストラクタ

	static CRankingLogo2 *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);	// オブジェクトの生成

	HRESULT Init(void);															// タイトルロゴ初期化処理
	void Uninit(void);															// タイトルロゴ終了処理
	void Update(void);															// タイトルロゴ更新処理
	void Draw(void);															// タイトルロゴ描画処理

private:
};

#endif