//=============================================================================
//
// 3Dポリゴン処理 [scene3D.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define WATER_NAME		"data/TEXTURE/water.jpeg"			// チュートリアルロゴのテクスチャ名
#define GROUND_SIZE					(3000.0f)							// 地面の大きさ
#define NUM_VTX						(4)								// 頂点の数
//========================================
// クラスの定義
//========================================
//=====================
// オブジェクトクラス
//=====================
class CScene3D : public CScene
{
public:
	CScene3D(int nPriority = SCENE3D_PRIORITY, OBJTYPE objType = OBJTYPE_SCENE3D);											// コンストラクタ
	~CScene3D();										// デストラクタ

	HRESULT Init(void);							// 3Dオブジェクト初期化処理
	void Uninit(void);							// 3Dオブジェクト終了処理
	void Update(void);							// 3Dオブジェクト更新処理
	void Draw(void);							// 3Dオブジェクト描画処理

	D3DXVECTOR3 GetNor(int nIdx);				// 法線を取得

	bool ColLand(D3DXVECTOR3 *pos, D3DXVECTOR3 radius);

	float GetHeight(D3DXVECTOR3 pos);			// 高さの取得

	static CScene3D *Create(D3DXVECTOR3 pos, float fDepth, float fWifth, float fTextureU, float fTextureV);			// オブジェクトの生成

private:
	LPDIRECT3DTEXTURE9		m_pTexture;					// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// 頂点バッファへのポインタ
	D3DXMATRIX				m_mtxWorld;					// ワールドマトリックス
	D3DXVECTOR3				m_aNor[NUM_VTX];					// 法線
	D3DXVECTOR3				m_aVec[NUM_VTX];					// ベクトル
	D3DXVECTOR3				m_pos;						// ポリゴンの位置
	D3DXVECTOR3				m_aPos[NUM_VTX];					// 頂点の位置
	D3DXVECTOR3				m_rot;						// 上方向ベクトル
	float					m_fDepth;					// 大きさ
	float					m_fWifth;					// 大きさ
	float					m_fTextureU;					// テクスチャ分割数
	float					m_fTextureV;					// テクスチャ分割数
	float m_fBgSpeed;										// テクスチャの動く速さ
	int m_nCounterAnim;
};

#endif