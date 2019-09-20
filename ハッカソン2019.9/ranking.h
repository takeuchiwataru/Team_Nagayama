//=============================================================================
//
// ランキングの処理 [ranking.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_RANKING	(5)	// ランキングで表示するスコアの数
#define CHAR_RANKING_FILE	"data\\TEXT\\modelRanking.txt"	// 設置したモデルを書き出すテキスト
#define CHAR_RANKINGNUM_FILE	"data\\TEXT\\ranking.txt"	// 設置したモデルを書き出すテキスト

//=============================================================================
// 前方宣言
//=============================================================================
class CScene2D;
class CScore;
//class CRenderer;

//=============================================================================
// クラスの定義
//=============================================================================
//==================================================================
// ランキングクラス
//==================================================================
class CRanking
{
public:
	CRanking();						// コンストラクタ
	~CRanking();						// デストラクタ

	static CRanking *Create();		// ランキングを生成

	HRESULT Init(void);				// ランキング初期化処理
	void Uninit(void);				// ランキング終了処理
	void Update(void);				// ランキング更新処理
	void Draw(void);				// ランキング描画処理

	void LoadCharFall(void);							// 文字に使われているモデルの位置情報を読み込み
	void LoadCharNumFall(void);							// 文字に使われているモデルの位置情報を読み込み

private:
	static CScore *m_apScore[MAX_RANKING];
	int m_nCntColor;
	int m_nCntTimer;
	D3DXCOLOR m_col;

	int m_nNumModel;		// 一文字に使われているモデルの数
	int m_nNumRankModel;		// 一文字に使われているモデルの数
	int m_nBlockTimer;							// ブロックの設置の時間を遅らせるタイマー
	int m_nBlockNumTimer;							// ブロックの設置の時間を遅らせるタイマー
	int m_nCntBlock;							// 落とすブロックのカウント
	int m_nCntNumBlock;							// 落とすブロックのカウント
	bool m_bSetBlock;
	bool m_bSetNumBlock;
	D3DXVECTOR3 m_BlockPos[1000];
	D3DXVECTOR3 m_BlockNumPos[1000];
	/*static CRenderer *m_pRenderer;*/
};

#endif