//=============================================================================
//
// スポットライト/ポイントライト処理 [performLight.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _PERFORMLIGHT_H_
#define _PERFORMLIGHT_H_

#include "main.h"

//========================================
// クラスの定義
//========================================
//=====================
// ライトクラス
//=====================
class CPerformLight
{
public:
	typedef enum
	{// 種類
		TYPE_POINT = 0,											// スポットライト
		TYPE_SPOT,												// ポイントライト
		TYPE_MAX
	} TYPE;

	CPerformLight();											// コンストラクタ
	~CPerformLight();											// デストラクタ

	static CPerformLight *Create(D3DXVECTOR3 pos, TYPE type);	// ライトの生成

	void Init(void);											// 初期化
	void Uninit(void);											// 終了
	void Update(void);											// 更新

private:
	D3DLIGHT9 m_light;											// ライトの情報
	D3DXVECTOR3 m_pos;											// ライトの位置
	TYPE m_type;												// ライトの種類
};

#endif