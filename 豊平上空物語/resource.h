//=============================================================================
//
// 素材管理処理処理 [resource.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//========================================
// クラスの定義
//========================================
//=====================
// 素材クラス
//=====================
class CResource
{
public:
	typedef enum // cppのやつと数と並びを揃える
	{
		MODEL_BLOCK = 0,	// ブロック
		MODEL_WOODBLOCK,	// 木ブロック
		MODEL_IRONBLOCK,	// 鉄ブロック
		MODEL_DEBRIS,		// 木の破片パーティクル
		MODEL_COIN,			// コイン
		MODEL_GEM,			// 宝石
		MODEL_PEBBLE,		// 小石
		MODEL_GOAL,			// ゴール
		MODEL_OBSTACLE,		// 障害物
		MODEL_BULLET,		// 弾
		MODEL_MEGURO,		// 目黒
	} MODEL;

	typedef enum // cppのやつと数と並びを揃える
	{
		TEXTURE_ANYBUTTON = 0,	// プレスエニーボタン
		TEXTURE_ENTER,			// エンターボタン
		TEXTURE_FIELD,			// 地面
		TEXTURE_PARTICLE2D,		// 2Dパーティクル
		TEXTURE_CLOUD,			// 煙パーティクル
		TEXTURE_LOGOBACK,		// 背景ロゴ
		TEXTURE_SCORE,			// スコアロゴ
		TEXTURE_BLOCK,			// ブロックロゴ
		TEXTURE_LIFE,			// 残機ロゴ
		TEXTURE_BLOCKCROSS,		// ブロックの個数ロゴ
		TEXTURE_PLAYERCROSS,	// プレイヤーの個数ロゴ
		TEXTURE_MOVE,			// 移動方法
		TEXTURE_JUMP,			// ジャンプ方法
		TEXTURE_SET,			// 設置方法
		TEXTURE_DESTROY,		// 破壊方法
		TEXTURE_END,			// 終了
		TEXTURE_NUMBER,			// 数字
		TEXTURE_BULLET,			// 弾
		TEXTURE_HEALTH,			// 体力
		TEXTURE_TITLELOGO,		// タイトルロゴ 竹内追加
		TEXTURE_TUTORIALLOGO,	// チュートリアルロゴ 竹内追加
		TEXTURE_ONARAREMAIN,	// おなら残機 竹内追加
		TEXTURE_HE,				// 屁
		TEXTURE_RANKINGLOGO,	// ランキングロゴ竹内追加
		TEXTURE_RANKINGRANK,	// ランキングランク
	} TEXTURE;

	CResource();		// コンストラクタ
	~CResource();	// デストラクタ

	static HRESULT LoadModel(void);
	static void UnloadModel(void);
	static HRESULT LoadTex(void);
	static void UnloadTex(void);

	static LPD3DXMESH GetMesh(int nIdx);
	static LPD3DXBUFFER GetBuffMat(int nIdx);
	static DWORD GetNumMat(int nIdx);
	static LPDIRECT3DTEXTURE9 GetTexture(int nIdx);

private:
	static LPDIRECT3DTEXTURE9	*m_pTexture;					// テクスチャへのポインタ
	static LPD3DXMESH		*m_pMesh;		// メッシュ情報（頂点情報）へのポインタ
	static LPD3DXBUFFER		*m_pBuffMat;		// マテリアル情報へのポインタ
	static DWORD			*m_nNumMat;		// マテリアル情報の数
	static const char *m_apModelFilename[];
	static const char *m_apTexFilename[];
};

#endif