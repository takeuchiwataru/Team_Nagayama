//=============================================================================
//
// 壁の処理 [billboard.h]
// Author :  長山拓実
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BILLBOARD_TEXTURENAME	 "data\\TEXTURE\\tree000.png"	//テクスチャのファイル名
#define TEX_POS_X_INIT			(1.0f)							//テクスチャ座標Uの初期位置
#define TEX_POS_Y_INIT			(1.0f)							//テクスチャ座標Vの初期位置
#define TEX_LEFT				(0.0f)							//テクスチャ座標U左
#define TEX_RIGHT				(1.0f)							//テクスチャ座標U右
#define TEX_TOP					(0.0f)							//テクスチャ座標V上
#define TEX_BOT					(1.0f)							//テクスチャ座標V下

//========================================
// クラスの定義
//========================================
//=====================
// オブジェクトクラス
//=====================
class CBillboard : public CScene
{
public:
	CBillboard(int nPriority = 3, OBJTYPE objType = OBJTYPE_BILLBOARD);	// コンストラクタ
	~CBillboard();														// デストラクタ

	HRESULT Init(void);													// 3Dオブジェクト初期化処理
	void Uninit(void);													// 3Dオブジェクト終了処理
	void Update(void);													// 3Dオブジェクト更新処理
	void Draw(void);													// 3Dオブジェクト描画処理

	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void);							// 頂点バッファの取得
	void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 VtxBuff);	// 頂点バッファの設定

	D3DXVECTOR3 GetPosition(void);						// 位置を取得
	void SetPosition(D3DXVECTOR3 pos);					// 位置を設定
	D3DXVECTOR3 GetRot(void);						// 向きを取得
	void SetRot(D3DXVECTOR3 rot);					// 向きを設定
	float GetWidth(void);													// 幅を取得
	void SetWidth(float fWidth);											// 幅を設定
	float GetHeight(void);													// 高さを取得
	void SetHeight(float fHeight);											// 高さを設定

	void SetCol(D3DXCOLOR col);												// 色の設定

	void BindTexture(LPDIRECT3DTEXTURE9	Texture);	// 共有テクスチャを割り当てる

	static CBillboard *Create(D3DXVECTOR3 pos);							// オブジェクトの生成
	void SetAnimation(int m_PatternAnim, float fUV_U, float fUV_V);

private:
	D3DXVECTOR3 m_pos;					// 位置
	D3DXVECTOR3 m_rot;					// 回転
	D3DXMATRIX	m_mtxWorld;				// ワールドマトリックス
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9	m_pTexture;		//テクスチャへのポインタ
	float m_fWidth;
	float m_fHeight;
};

#endif