//=============================================================================
//
// 円柱のポリゴン処理 [meshCylinder.h]
// Author :  長山拓実
//
//=============================================================================
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MESHCYLINDER_TEXTURENAME		 "data\\TEXTURE\\sky.jpg"	//テクスチャのファイル名
#define TEX_POS_X_INIT			(1.0f)								//テクスチャ座標Uの初期位置
#define TEX_POS_Y_INIT			(1.0f)								//テクスチャ座標Vの初期位置
#define TEX_LEFT				(0.0f)								//テクスチャ座標U左
#define TEX_RIGHT				(1.0f)								//テクスチャ座標U右
#define TEX_TOP					(0.0f)								//テクスチャ座標V上
#define TEX_BOT					(1.0f)								//テクスチャ座標V下
#define FIELD_SIZE				(400.0f)							//地面の大きさ
#define X_CYLINDERPOSSIZE		(100)								//Xの大きさ
#define Y_CYLINDERPOSSIZE		(100)								//Zの大きさ
#define CYLINDER_X				(60)								// ポリゴンの数（X）
#define CYLINDER_Y				(200)									// ポリゴンの数（Z）
#define NUM_CYLINDER_POLYGON				(10000)							// メッシュフィールドの大きさ

//========================================
// クラスの定義
//========================================
//=========================
// メッシュシリンダークラス
//=========================
class CMeshCylinder : public CScene
{
public:
	CMeshCylinder(int nPriority = 3, OBJTYPE objType = OBJTYPE_MESHCYLINDER);	// コンストラクタ
	~CMeshCylinder();														// デストラクタ

	static CMeshCylinder *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);							// オブジェクトの生成

	HRESULT Init(void);													// メッシュシリンダー初期化処理
	void Uninit(void);													// メッシュシリンダー終了処理
	void Update(void);													// メッシュシリンダー更新処理
	void Draw(void);													// メッシュシリンダー描画処理

	void SetNor(void);													// 法線の設定

private:
	LPDIRECT3DTEXTURE9		m_pTexture;									// テクスチャへのポインタ
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;									// インデックスバッファへのポインタ
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;									// 頂点バッファへのポインタ
	D3DXMATRIX				m_mtxWorld;									// ワールドマトリックス
	D3DXVECTOR3				m_pos;										// ポリゴンの位置
	D3DXVECTOR3				m_rot;										// ポリゴンの向き
	D3DXVECTOR3				m_aNor[NUM_CYLINDER_POLYGON];
	float m_fSizeX;
	float m_fSizeY;
	int						m_nNumVerTex;								// 頂点数
	int						m_nNumIndex;								// インデックス数
	int						m_nNumPolygon;								// ポリゴン数
	bool					m_bLand;									// ポリゴンに乗っている
};

#endif
