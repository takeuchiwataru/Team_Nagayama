//=============================================================================
//
// チュートリアルロゴの処理 [tutoriallogo.h]
// Author : 竹内亘
//
//=============================================================================
#ifndef _TUTORIALLOGO_H_
#define _TUTORIALLOGO_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=========================
// チュートリアルロゴクラス
//=========================
class CTutorialLogo : public CLogo
{
public:

	CTutorialLogo();															// コンストラクタ
	~CTutorialLogo();															// デストラクタ

	static CTutorialLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);	// オブジェクトの生成

	HRESULT Init(void);															// チュートリアルロゴ初期化処理
	void Uninit(void);															// チュートリアルロゴ終了処理
	void Update(void);															// チュートリアルロゴ更新処理
	void Draw(void);															// チュートリアルロゴ描画処理

private:
};

#endif