//=============================================================================
//
// 残機処理 [life.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_NUMLIFE	(1)	// テクスチャの数

//=============================================================================
// 前方宣言
//=============================================================================
class CNumber;

//========================================
// クラスの定義
//========================================
//=====================
// 残機の数クラス
//=====================
class CLife : public CScene
{
public:
	CLife(int nPriority = 5, OBJTYPE objType = OBJTYPE_SCORE);	// コンストラクタ
	~CLife();													// デストラクタ

	static CLife *Create(D3DXVECTOR3 pos, float fSize);

	HRESULT Init(void);							// 残機の数の初期化処理
	void Uninit(void);							// 残機の数の終了処理
	void Update(void);							// 残機の数の更新処理
	void Draw(void);							// 残機の数の描画処理

	void SetLife(int nScore);					// 残機の数の設定
	int GetLife(void);							// 残機の数の取得
	void AddLife(int nValue);					// 残機の数加算
	void SetColor(D3DXCOLOR color);				// 色の設定

private:
	CNumber *m_apLife[MAX_NUMLIFE];
	D3DXVECTOR3 m_pos;
	int m_nNumLife;
	float m_fSize;
};

#endif