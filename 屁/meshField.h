//=============================================================================
//
// メッシュフィールドの処理 [meshFiled.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MESHFIELD_TEXTURE_NAME	"data\\TEXTURE\\soil.jpg"	// 地面のテクスチャ名
#define	SOIL_FILENAME			"data\\TEXT\\soil.bin"					// ツールのテキスト
#define POLYGON_X				(50)								// ポリゴンの数（X）
#define POLYGON_Z				(50)							// ポリゴンの数（Z）
#define MESHFIELD_SIZE			(35.0f)						// ポリゴンの大きさ
#define MESHFIELD_WIDTH			(MESHFIELD_SIZE * POLYGON_X)	// メッシュフィールドの大きさ(幅)
#define MESHFIELD_DEPTH			(MESHFIELD_SIZE * POLYGON_Z)	// メッシュフィールドの大きさ(奥行)
#define NUM_POLYGON				(10000)							// メッシュフィールドの大きさ

//========================================
// クラスの定義
//========================================
//=========================
// メッシュフィールドクラス
//=========================
class CMeshField : public CScene
{
public:
	CMeshField(int nPriority = MESHFIELD_PRIORITY, OBJTYPE objType = OBJTYPE_MESHFIELD);	// コンストラクタ
	~CMeshField();														// デストラクタ

	static CMeshField *Create(D3DXVECTOR3 pos);							// オブジェクトの生成

	HRESULT Init(void);													// メッシュフィールド初期化処理
	void Uninit(void);													// メッシュフィールド終了処理
	void Update(void);													// メッシュフィールド更新処理
	void Draw(void);													// メッシュフィールド描画処理

	void SetNor(void);													// 法線の設定
	float GetHeight(D3DXVECTOR3 pos);									// 高さの取得
	bool GetLand(void);													// 乗っているかどうかの取得
	void LoadHeight(void);												// 高さのロード

private:
	LPDIRECT3DTEXTURE9		m_pTexture;									// テクスチャへのポインタ
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;									// インデックスバッファへのポインタ
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;									// 頂点バッファへのポインタ
	D3DXMATRIX				m_mtxWorld;									// ワールドマトリックス
	D3DXVECTOR3				m_pos;										// ポリゴンの位置
	D3DXVECTOR3				m_rot;										// ポリゴンの向き
	D3DXVECTOR3				m_aNor[NUM_POLYGON];
	float					m_aHeight[POLYGON_Z + 1][POLYGON_X + 1];
	int						m_nNumVerTex;								// 頂点数
	int						m_nNumIndex;								// インデックス数
	int						m_nNumPolygon;								// ポリゴン数
	bool					m_bLand;									// ポリゴンに乗っている
};

#endif