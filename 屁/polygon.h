//=============================================================================
//
// ポリゴン処理 [polygon.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _POLYGONHOLE_H_
#define _POLYGONHOLE_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_VTX						(4)								// 頂点の数
//========================================
// クラスの定義
//========================================
//=====================
// オブジェクトクラス
//=====================
class CPolygon : public CScene
{
public:
	CPolygon(int nPriority = 2, OBJTYPE objType = OBJTYPE_POLYGON);											// コンストラクタ
	~CPolygon();										// デストラクタ

	HRESULT Init(void);							// 3Dオブジェクト初期化処理
	void Uninit(void);							// 3Dオブジェクト終了処理
	void Update(void);							// 3Dオブジェクト更新処理
	void Draw(void);							// 3Dオブジェクト描画処理

	D3DXVECTOR3 GetNor(int nIdx);				// 法線を取得

	static CPolygon *Create(D3DXVECTOR3 pos, float fDepth, float fWifth, float fTextureU, float fTextureV);			// オブジェクトの生成

	void BindTexture(LPDIRECT3DTEXTURE9	Texture);	// 共有テクスチャを割り当てる
	void SetCol(D3DXCOLOR col);												// 色の設定
	void SetPos(D3DXVECTOR3 pos);												// 位置の設定
	D3DXVECTOR3 GetPos(void);												// 位置の取得
	void SetRot(D3DXVECTOR3 rot);												// 位置の設定
	void SetDepth(float	fDepth);												// 大きさの設定
	void SetWidth(float	fWifth);												// 大きさの設定
	void SetTextureU(float	fTextureU);												// テクスチャ分割数
	void SetTextureV(float	fTextureV);												// テクスチャ分割数

	bool ColLand(D3DXVECTOR3 *pos, D3DXVECTOR3 radius);

	float GetHeight(D3DXVECTOR3 pos);			// 高さの取得

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

};
#endif