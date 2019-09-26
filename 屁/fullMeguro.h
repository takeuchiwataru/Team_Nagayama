//=============================================================================
//
// 全裸目黒処理 [fullMeguro.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _FULLMEGURO_H_
#define _FULLMEGURO_H_

#include "main.h"
#include "sceneX.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CShadow;

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//========================================
// クラスの定義
//========================================
//=====================
// ブロッククラス
//=====================
class CFullMeguro : public CSceneX
{
public:
	CFullMeguro();								// コンストラクタ
	~CFullMeguro();								// デストラクタ

	HRESULT Init(void);						// コイン初期化処理
	void Uninit(void);						// コイン終了処理
	void Update(void);						// コイン更新処理
	void Draw(void);						// コイン描画処理

	static CFullMeguro *Create(D3DXVECTOR3 pos);	// オブジェクトの生成

	D3DXVECTOR3 GetPos(void);						// 位置の取得
	void SetPos(D3DXVECTOR3 pos);					// 位置の設定
	static int GetNumCoin(void);						// コインの数の取得
	static void SetNumCoin(int nNumCoin);				// コインの数の設定

	bool CFullMeguro::Collision(D3DXVECTOR3 *pos, float fRadius);

private:
	static int				m_nNumCoin;			// コインの数
	D3DXVECTOR3				m_pos;				// 位置
	D3DXVECTOR3				m_move;				// 移動量
	D3DXVECTOR3				m_rot;				// 向き
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファへのポインタ
	D3DXVECTOR3				m_VtxMin, m_VtxMax;	// ブロックの最小値、最大値

	D3DXMATRIX				m_mtxWorld;		// ワールドマトリックス
};

#endif