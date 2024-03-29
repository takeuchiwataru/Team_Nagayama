//=============================================================================
//
// ポーズの処理 [pause.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"
#include "scene.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CScene2D;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PAUSE_NAME				"data/TEXTURE/PAUSE/pause100.png"		// ポーズのテクスチャ名
#define PAUSET_TEXTURE_NAME0	"data/TEXTURE/PAUSE/pause200.png"	// ポーズセレクト0のテクスチャ名
#define PAUSET_TEXTURE_NAME1	"data/TEXTURE/PAUSE/pause201.png"	// ポーズセレクト1のテクスチャ名
#define PAUSET_TEXTURE_NAME2	"data/TEXTURE/PAUSE/pause202.png"	// ポーズセレクト2のテクスチャ名
#define MAX_PAUSE_TEXTURE		(4)								// ポーズセレクトのテクスチャ数
#define MAX_PAUSE				(3)								// ポーズセレクトの数

//=========================
// ポーズクラス
//=========================
class CPause : public CScene
{
public:
	typedef enum
	{
		MODE_NONE = 0,	// 通常状態
		MODE_CONTINUE,	// コンティニュー
		MODE_RETRY,		// リトライ
		MODE_QUIT,		// クイット
		MODE_MAX
	} MODE;

	typedef enum
	{
		SELECT_NONE = 0,	// 選ばれていない状態
		SELECT_SELECT,		// 選ばれている状態
		SELECT_MAX
	} SELECT;

	CPause(int nPriority = 7, OBJTYPE objType = OBJTYPE_PAUSE);									// コンストラクタ
	~CPause();													// デストラクタ

	static HRESULT Load(void);									// テクスチャ読み込み
	static void Unload(void);									// テクスチャ解放
	
	static CPause *Create(void);								// ポーズを生成

	HRESULT Init(void);	// ポーズ初期化処理
	void Uninit(void);											// ポーズ終了処理
	void Update(void);											// ポーズ更新処理
	void Draw(void);											// ポーズ描画処理
	static	MODE GetMode(void);									// ポーズを取得
	int GetSelect(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_PAUSE_TEXTURE];
	CScene2D *m_apScene2D[MAX_PAUSE_TEXTURE];
	SELECT m_aSelect[MAX_PAUSE];
	D3DXCOLOR m_aCol[MAX_PAUSE];
	static MODE m_Mode;
	int	m_nSelect;
};
#endif