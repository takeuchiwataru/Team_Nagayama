//=============================================================================
//
// パーティクルの処理 [particle3D.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _PARTICLE3D_H_
#define _PARTICLE3D_H_

#include "main.h"
#include "billboard.h"
#include "particle2D.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_PARTICLE3D		(256)							// パーティクルの数
#define MAX_TEXTURE			(2)								// パーティクルの数
#define EFFECT_CLOUD_NAME	"data/TEXTURE/cloud.png"		// 煙エフェクトのテクスチャ名

//========================================
// クラスの定義
//========================================
//=====================
// パーティクルクラス
//=====================
class CParticle3D : public CBillboard
{
public:
	typedef enum
	{// キー要素
		TYPE_NORMAL = 0,	// 通常状態
		TYPE_UP,			// 上昇状態
		TYPE_DOWN,			// 下降状態
		PARTICLESTATE_MAX			// プレイヤーの種類の総数
	} PARTICLE_TYPE;

	CParticle3D();	// コンストラクタ
	~CParticle3D();	// デストラクタ

	HRESULT Init(void);	// 3Dパーティクル初期化処理
	void Uninit(void);	// 3Dパーティクル終了処理
	void Update(void);	// 3Dパーティクル更新処理
	void Draw(void);	// 3Dパーティクル描画処理

	static CParticle3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fWidth, float fHeight, int nLife, PARTICLE_TYPE type, int nTexture);	// オブジェクトの生成

private:
	int m_nLife;
	D3DXCOLOR m_col;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	PARTICLE_TYPE m_ParticleType;
};

#endif