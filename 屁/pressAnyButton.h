//=============================================================================
//
// プレスエニーボタンの処理 [pressAnyButton.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _PRESSANYBUTTON_H_
#define _PRESSANYBUTTON_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=========================
// プレスエニーボタンロゴクラス
//=========================
class CPressAnyButton : public CLogo
{
public:

	CPressAnyButton();															// コンストラクタ
	~CPressAnyButton();															// デストラクタ

	static CPressAnyButton *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);	// オブジェクトの生成

	HRESULT Init(void);															// プレスエニーボタンロゴ初期化処理
	void Uninit(void);															// プレスエニーボタンロゴ終了処理
	void Update(void);															// プレスエニーボタンロゴ更新処理
	void Draw(void);															// プレスエニーボタンロゴ描x画処理

private:
	int	m_nCntEnter;
	float m_fEnterTimer;
	bool m_bPress;
};

#endif