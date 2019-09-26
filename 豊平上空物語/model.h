//=============================================================================
//
// モデル処理 [model.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//========================================
// クラスの定義
//========================================
//=====================
// オブジェクトクラス
//=====================
class CModel
{
public:
	CModel();																// コンストラクタ
	~CModel();																// デストラクタ

	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// オブジェクトの生成

	HRESULT Init(void);														// モデル初期化処理
	void Uninit(void);														// モデル終了処理
	void Update(void);														// モデル更新処理
	void Draw(void);														// モデル描画処理

	void SetParent(CModel *pModel);
	D3DXMATRIX GetMtxWorld(void);

	void SetRot(D3DXVECTOR3 rot);
	void SetPos(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetRot(void);
	D3DXVECTOR3 GetPos(void);

	void BindModel(LPD3DXBUFFER pBuffMat, DWORD nNumMat, LPD3DXMESH pMesh);	// モデルを割り当てる

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;										// 頂点バッファへのポインタ
	LPD3DXMESH				m_pMesh;										// メッシュ情報（頂点情報）へのポインタ
	LPD3DXBUFFER			m_pBuffMat;										// マテリアル情報へのポインタ
	D3DXMATRIX				m_mtxWorld;										// ワールドマトリックス
	DWORD					m_nNumMat;										// マテリアル情報の数

	D3DXVECTOR3				m_pos;											// モデルの位置
	D3DXVECTOR3				m_rot;											// 上方向ベクトル

	CModel *m_pParent;														// 親モデルへのポインタ
};

#endif