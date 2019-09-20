//=============================================================================
//
// ロゴの処理 [logo.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _LOGO_H_
#define _LOGO_H_

#include "main.h"
#include "scene.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RESULT_LOGO_NAME		"data/TEXTURE/resultLogo.png"		// リザルトロゴのテクスチャ名
#define PRESSENTER_LOGO_NAME	"data/TEXTURE/press_enter.png"		// プレスエンターロゴのテクスチャ名
#define RANKING_NUMBER_NAME		"data/TEXTURE/RANKING/ranking.png"			// プレスエンターロゴのテクスチャ名
#define A_LOGO_NAME				"data/TEXTURE/ALogo.png"			// プレスAロゴのテクスチャ名
#define PICKUP_LOGO_NAME		"data/TEXTURE/pickup.png"			// ピックアップロゴのテクスチャ名
#define SCOREUP_LOGO_NAME		"data/TEXTURE/ScoreUp.png"			// スコアアップロゴのテクスチャ名
#define GAMESTART_LOGO_NAME		"data/TEXTURE/GameStart.png"		// ゲームスタートロゴのテクスチャ名
#define STARTSKIP_LOGO_NAME		"data/TEXTURE/startskip.png"		// スタートスキップロゴのテクスチャ名

//========================================
// クラスの定義
//========================================
//=====================
// ロゴクラス
//=====================
class CLogo : public CScene
{
public:
	CLogo(int nPriority = LOGO_PRIORITY, OBJTYPE objType = OBJTYPE_LOGO);			// コンストラクタ
	~CLogo();															// デストラクタ

	void BindTexture(LPDIRECT3DTEXTURE9	Texture);						// 共有テクスチャを割り当てる

	virtual HRESULT Init(void);											// ロゴ初期化処理
	virtual void Uninit(void);											// ロゴ終了処理
	virtual void Update(void);											// ロゴ更新処理
	virtual void Draw(void);											// ロゴ描画処理
	void SetCol(D3DXCOLOR col);											// ロゴの色の設定

	D3DXVECTOR3 GetPosition(void);										// 位置の取得
	void SetPosition(D3DXVECTOR3 pos);									// 位置の設定
	float GetWidth(void);												// 幅の取得
	void SetWidth(float fWidth);										// 幅の設定
	float GetHeight(void);												// 高さの取得
	void SetHeight(float fHeight);										// 高さの設定

private:
	LPDIRECT3DTEXTURE9		m_pTexture;									// テクスチャへのポインタ
	D3DXVECTOR3				m_Pos;										// ポリゴンの位置
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;									// 頂点バッファへのポインタ
	float					m_fWidth;									// オブジェクトの幅
	float					m_fHeight;									// オブジェクトの高さ
};

#endif