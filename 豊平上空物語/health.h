//=============================================================================
//
// 体力 [health.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _HEALTH_H_
#define _HEALTH_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=========================
// スコアロゴクラス
//=========================
class CHealth : public CScene2D
{
public:
	CHealth();															// コンストラクタ
	~CHealth();															// デストラクタ

	static CHealth *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// オブジェクトの生成

	HRESULT Init(void);				// 体力初期化処理
	void Uninit(void);				// 体力終了処理
	void Update(void);				// 体力更新処理
	void Draw(void);				// 体力描画処理
	void CutHealth(int nHealth);	// 体力減少処理
	int GetHealth(void) { return m_nHealth; }	// 体力取得

private:
	int m_nHealth;
};

#endif