//=============================================================================
//
// ゲームクリアの処理 [gameClear.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _GAMECLEAR_H_
#define _GAMECLEAR_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_BLOCK (450)
#define NUM_BLOCK_X (59)
#define NUM_BLOCK_Y (7)

//=============================================================================
// 前方宣言
//=============================================================================
class CScene2D;
class CBlock;
class CScore;

//=============================================================================
// クラスの定義
//=============================================================================
//==================================================================
// タイトルクラス
//==================================================================
class CGameClear
{
public:
	CGameClear();						// コンストラクタ
	~CGameClear();						// デストラクタ

	static CGameClear *Create();		// タイトルを生成

	HRESULT Init(void);				// タイトル初期化処理
	void Uninit(void);				// タイトル終了処理
	void Update(void);				// タイトル更新処理
	void Draw(void);				// タイトル描画処理
	void Block(void);				// ブロック設置

	void LoadCharFall(void);				// 背景オブジェクトの読み込み

private:
	static CScore *m_pScore;
	int m_nCntTimer;
	int m_nNumModel;		// 一文字に使われているモデルの数
	int m_nBlockTimer;							// ブロックの設置の時間を遅らせるタイマー
	int m_nCntBlock;							// 落とすブロックのカウント
	bool m_bSetBlock;
	static CBlock *m_pBlock[MAX_BLOCK];
	D3DXVECTOR3 m_BlockPpos[1000];
};

#endif