//=============================================================================
//
// 障害物の処理 [obstacle.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "main.h"
#include "sceneX.h"
//=============================================================================
// 前方宣言
//=============================================================================

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_BULLET	(256)	// 弾の数
#define TEX_POS_X_INIT			(1.0f)									//テクスチャ座標Uの初期位置
#define TEX_POS_Y_INIT			(1.0f)									//テクスチャ座標Vの初期位置
#define TEX_LEFT				(0.0f)									//テクスチャ座標U左
#define TEX_RIGHT				(1.0f)									//テクスチャ座標U右
#define TEX_TOP					(0.0f)									//テクスチャ座標V上
#define TEX_BOT					(1.0f)									//テクスチャ座標V下

//========================================
// クラスの定義
//========================================
//=====================
// プレイヤークラス
//=====================
class CObstacle : public CSceneX
{
public:
	CObstacle();	// コンストラクタ
	~CObstacle();	// デストラクタ

	HRESULT Init(void);	// プレイヤー初期化処理
	void Uninit(void);	// プレイヤー終了処理
	void Update(void);	// プレイヤー更新処理
	void Draw(void);	// プレイヤー描画処理

	static CObstacle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col);	// オブジェクトの生成
	bool CollisionPlayer(D3DXVECTOR3 *pos, float fRadius);	// 当たり判定
	bool GetDestroy(void) { return m_bDestroy; }	// 消すフラグの取得

private:
	D3DXVECTOR3 m_pos;					// 位置
	D3DXVECTOR3 m_rot;					// 向き
	D3DXVECTOR3 m_move;					// 移動量
	D3DXCOLOR m_col;							// 色
	int m_nLife;
	bool m_bHit;	// 当たったかどうか
	bool m_bDestroy;	// 消すかどうか
	D3DXMATRIX				m_mtxWorld;		// ワールドマトリックス
	D3DXVECTOR3				m_VtxMin, m_VtxMax;	// ブロックの最小値、最大値
};

#endif