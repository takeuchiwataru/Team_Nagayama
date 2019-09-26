//=============================================================================
//
// ゲームオーバーの処理 [gameover.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "gameclear.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define NUM_X (53)
#define NUM_Y (7)

//=============================================================================
// 前方宣言
//=============================================================================
class CScene2D;
class CScore;
class CBlock;

//=============================================================================
// クラスの定義
//=============================================================================
//==================================================================
// ゲームオーバークラス
//==================================================================
class CGameOver
{
public:
	CGameOver();						// コンストラクタ
	~CGameOver();						// デストラクタ

	static CGameOver *Create();		// タイトルを生成

	HRESULT Init(void);				// タイトル初期化処理
	void Uninit(void);				// タイトル終了処理
	void Update(void);				// タイトル更新処理
	void Draw(void);				// タイトル描画処理

	void LoadCharFall(void);				// 背景オブジェクトの読み込み
	void Block(void);				// ブロック

private:
	static CBlock *m_pBlock[MAX_BLOCK];
	static CScore *m_pScore;
	int m_nCntTimer;
	int m_nNumModel;		// 一文字に使われているモデルの数
	int m_nBlockTimer;							// ブロックの設置の時間を遅らせるタイマー
	int m_nCntBlock;							// 落とすブロックのカウント
	int m_nScore;
	int m_nCntScore;
	bool m_bSetBlock;
	D3DXVECTOR3 m_BlockPpos[1000];
};

#endif