//=============================================================================
//
// スコア処理 [score.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_SCORE	(6)	// テクスチャの数

//=============================================================================
// 前方宣言
//=============================================================================
class CNumber;

//========================================
// クラスの定義
//========================================
//=====================
// スコアクラス
//=====================
class CScore : public CScene
{
public:
	CScore(int nPriority = 5, OBJTYPE objType = OBJTYPE_SCORE);	// コンストラクタ
	~CScore();													// デストラクタ

	static CScore *Create(D3DXVECTOR3 pos, float fSize, float fWidth);

	HRESULT Init(void);							// スコアの初期化処理
	void Uninit(void);							// スコアの終了処理
	void Update(void);							// スコアの更新処理
	void Draw(void);							// スコアの描画処理

	void SetScore(int nScore);					// スコアの設定
	int GetScore(void);							// スコアの取得
	void AddScore(int nValue);					// スコア加算
	void SetColor(D3DXCOLOR color);				// 色の設定

private:
	CNumber *m_apNumber[MAX_SCORE];
	D3DXVECTOR3 m_pos;
	int m_nScore;
	float m_fSize;
	float m_fWidth;
};

#endif