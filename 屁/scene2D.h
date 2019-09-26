//=============================================================================
//
// シーン処理 [scene2D.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_NAME		"data/TEXTURE/player000.png"	// プレイヤーのテクスチャ名
#define BULLET_NAME		"data/TEXTURE/bullet000.png"	// 弾のテクスチャ名
#define MAX_TEX_TYPE	(2)								// テクスチャの種類

//========================================
// クラスの定義
//========================================
//=====================
// オブジェクトクラス
//=====================
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority = 3, OBJTYPE objType = OBJTYPE_SCENE2D);			// コンストラクタ
	~CScene2D();															// デストラクタ

	virtual HRESULT Init(void);												// 2Dオブジェクト初期化処理
	virtual void Uninit(void);												// 2Dオブジェクト終了処理
	virtual void Update(void);												// 2Dオブジェクト更新処理
	virtual void Draw(void);												// 2Dオブジェクト描画処理

	D3DXVECTOR3 GetPosition(void);											// 位置を取得
	void SetPosition(D3DXVECTOR3 pos);										// 位置を設定
	float GetWidth(void);													// 幅を取得
	void SetWidth(float fWidth);											// 幅を設定
	float GetHeight(void);													// 高さを取得
	void SetHeight(float fHeight);											// 高さを設定
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void);								// 頂点バッファを取得
	void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 VtxBuff);						// 頂点バッファの設定
	
	static CScene2D *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// オブジェクトの生成
	void BindTexture(LPDIRECT3DTEXTURE9	Texture);							// 共有テクスチャを割り当てる
	void SetCol(D3DXCOLOR col);												// 色の設定

private:
	LPDIRECT3DTEXTURE9		m_pTexture;										// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;										// 頂点バッファへのポインタ

	D3DXVECTOR3				m_Pos;											// ポリゴンの位置

	float					m_fWidth;										// 幅
	float					m_fHeight;										// 高さ
};

#endif