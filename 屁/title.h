//=============================================================================
//
// タイトルの処理 [title.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CScene2D;
class CBlock;
//class CRenderer;

//=============================================================================
// クラスの定義
//=============================================================================
//==================================================================
// タイトルクラス
//==================================================================
class CTitle
{
public:
	CTitle();						// コンストラクタ
	~CTitle();						// デストラクタ

	static CTitle *Create();		// タイトルを生成

	HRESULT Init(void);				// タイトル初期化処理
	void Uninit(void);				// タイトル終了処理
	void Update(void);				// タイトル更新処理
	void Draw(void);				// タイトル描画処理

	void LoadMap(void);				// 背景オブジェクトの読み込み

	D3DXVECTOR3 GetBlockPos(int nCntBlock);

private:
	static CBlock *m_pBlock[225];
	D3DXVECTOR3 m_BlockPpos[220];
	int m_nBlockTimer;							// ブロックの設置の時間を遅らせるタイマー
	int m_nCntBlock;							// 落とすブロックのカウント
	int m_nBlock;							// 消すブロックのカウント
	int m_nCntFrame;							// フレームのカウント
	int m_nCntTimer;							// 遷移に使うタイマー
												/*static CRenderer *m_pRenderer;*/
	bool m_bSetBlock;							// ブロックを設置するかどうか
};

#endif