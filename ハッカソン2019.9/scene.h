//=============================================================================
//
// シーン処理 [scene.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_OBJECT				(1024)	// テクスチャの数
#define NUM_PRIORITY			(8)		// 優先順位の数
#define SCENEOBJ_PRIORITY		(2)		// 設置するオブジェクトの優先順位
#define OBJ_PRIORITY			(4)		// オブジェクトの優先順位
#define OBSTACLE_PRIORITY		(3)		// 障害物の優先順位
#define GOAL_PRIORITY			(1)		// ゴールの優先順位
#define SCENEX_PRIORITY			(2)		// モデルの優先順位
#define MESHFIELD_PRIORITY		(3)		// メッシュフィールドの優先順位
#define POLYGON_PRIORITY		(3)		// 床の優先順位
#define SCENE3D_PRIORITY		(3)		// 川の優先順位
#define	PLAYER_PRIORITY			(5)		// プレイヤーの優先順位
#define	SHADOW_PRIORITY			(6)		// 影の優先順位
#define	PARTICLE_PRIORITY		(5)		// パーティクルの優先順位
#define COIN_PRIORITY			(4)		// コインの優先順位
#define LOGO_PRIORITY			(6)		// ロゴの優先順位
#define LOGOBACK_PRIORITY		(4)		// 背景ロゴの優先順位
#define HOLE_PRIORITY			(4)		// 地面全体の優先順位
#define TUTORIALLOGO_PRIORITY	(3)		// チュートリアルロゴの優先順位
#define GEM_PRIORITY			(4)
#define BLOCKPOS_PRIORITY		(6)
#define BULLET_PRIORITY			(5)
#define HEALTH_PRIORITY			(5)

//========================================
// クラスの定義
//========================================
//=====================
// オブジェクトクラス
//=====================
class CScene
{
public:
	typedef enum
	{// オブジェクトの種類
		OBJTYPE_NONE = 0,
		OBJTYPE_SCENE2D,	// 2Dポリゴン
		OBJTYPE_SCENE3D,	// 3Dポリゴン
		OBJTYPE_SCENEX,		// モデル
		OBJTYPE_POLYGON,	// ポリゴン
		OBJTYPE_FIELD,	// 地面
		OBJTYPE_BILLBOARD,	// ビルボード
		OBJTYPE_LOGO,		// ロゴ
		OBJTYPE_LOGOBACK,		// 背景ロゴ
		OBJTYPE_MESHFIELD,	// メッシュフィールド
		OBJTYPE_MESHCYLINDER,	// メッシュシリンダー
		OBJTYPE_PLAYER,		// プレイヤー
		OBJTYPE_BLOCK,		// ブロック
		OBJTYPE_WOODBLOCK,	// 木ブロック
		OBJTYPE_IRONBLOCK,		// 鉄ロック
		OBJTYPE_GOAL,		// ゴール
		OBJTYPE_COIN,		// コイン
		OBJTYPE_GEM,		// 宝石
		OBJTYPE_OBSTACLE,	// 障害物
		OBJTYPE_PAUSE,		// ポーズ
		OBJTYPE_SCORE,		// スコア
		OBJTYPE_NUMBLOCK,		// ブロックの数
		OBJTYPE_PARTICLE,	// パーティクル
		OBJTYPE_PEBBLE,		// 小石
		OBJTYPE_SETOBJECT,	// 設置するオブジェクト
		OBJTYPE_OBJECT,		// 切り替わるオブジェクト
		OBJTYPE_BLOCKPOS,		// ブロックの出現位置
		OBJTYPE_SHADOW,		// 影
		OBJTYPE_BULLET,		// 弾
		OBJTYPE_EFFECT,		// 弾
		OBJTYPE_MAX			// 総数
	} OBJTYPE;

	CScene(int nPriority = 3, OBJTYPE objType = OBJTYPE_NONE);	// コンストラクタ
	virtual ~CScene();											// デストラクタ

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void ReleseAll(void);								// 全てのオブジェクトの解放
	static void UpdeteAll(void);								// 全てのオブジェクトの更新
	static void DrawAll(void);									// 全てのオブジェクトの描画
	static CScene *GetTop(int nPriority);						// 先頭のオブジェクトを取得
	CScene *GetNext(void);										// 次のオブジェクトのポインタを取得
	bool GetDeath(void);										// 死亡フラグを取得
	void SetObjType(OBJTYPE objType);							// オブジェクトの種類の設定
	OBJTYPE GetObjType(void);									// オブジェクトの種類の取得
	int GetPriority(void);										// 優先順位の取得
	void SetPriority(int nPriority);							// 優先順位の設定

protected:
	void Release(void);											// 死亡フラグを立てる

private:
	void DeleteAll(void);										// 死亡フラグが立ったオブジェクトを消す

	static CScene *m_apTop[NUM_PRIORITY];						// 先頭オブジェクトへのポインタ
	static CScene *m_apCur[NUM_PRIORITY];						// 現在（最後尾）のオブジェクトへのポインタ
	CScene *m_pPrev;											// 前のオブジェクトへのポインタ
	CScene *m_pNext;											// 次のオブジェクトへのポインタ
	bool m_bDeath;												// 死亡フラグ
	static int m_nNumAll;										// 敵の総数 『静的メンバ変数』
	int m_nID;													// 自分自身のID
	int m_nPriority;											// 優先順位の番号
	static int m_nNumPriority[NUM_PRIORITY];					// その優先順位にあるオブジェクトの数
	OBJTYPE m_objType;											// オブジェクトの種類
};

#endif