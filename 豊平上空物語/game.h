//=============================================================================
//
// ゲーム処理 [game.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_
#include "main.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CInputKeyboard;
class CDebugProc;
class CScene3D;
class CPlayer;
class CScore;
class CNumBlock;
class CHealth;
class COnaraRemain;

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_COIN (30)

//=============================================================================
// クラスの定義
//=============================================================================
//=====================
// ゲームクラス
//=====================
class CGame
{
public:
	CGame();	// コンストラクタ
	~CGame();	// デストラクタ

	static CGame *Create();		// ゲームを生成
	HRESULT Init(void);			// ゲームの初期化
	void Uninit(void);			// ゲームの終了処理
	void Update(void);			// ゲームの更新処理
	void Draw(void);			// ゲームの描画
	static CScore *GetScore(void);
	static CNumBlock *GetNumBlock(void);
	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CHealth *GetHealth(void) { return m_pHealth; }
	static COnaraRemain *GetOnaraRemain(void);

	void LoadCoin(void);				// コインの読み込み
	void LoadMat(void);					// マテリアルの読み込み
	void UnLoadMat(void);				// マテリアルの開放
	void BlockCreate(void);				// ブロックの生成
	void FieldCreate(void);				// フィールドの生成

private:
	static CScore *m_pScore;
	static CNumBlock *m_pNumBlock;
	static CHealth *m_pHealth;
	static COnaraRemain *m_pOnaraRemain;
	static CPlayer *m_pPlayer;
};

#endif