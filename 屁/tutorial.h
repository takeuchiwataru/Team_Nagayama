//=============================================================================
//
// チュートリアルの処理 [tutorial.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define IRON_FILE_GAME	"data\\TEXT\\modelIron.txt"	// 設置したモデルを書き出すテキスト
#define WOOD_FILE_GAME	"data\\TEXT\\modelWood.txt"	// 設置したモデルを書き出すテキスト

//=============================================================================
// 前方宣言
//=============================================================================
//class CRenderer;
class CInputKeyboard;
class CScore;
class CNumBlock;
class CLife;
class CHealth;

//=============================================================================
// クラスの定義
//=============================================================================
//=====================
// マネージャクラス
//=====================
class CTutorial
{
public:
	CTutorial();	// コンストラクタ
	~CTutorial();	// デストラクタ

	static CTutorial *Create();		// チュートリアルを生成
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScore *GetScore(void);
	static CNumBlock *GetNumBlock(void);
	static CLife *GetLife(void);
	static CHealth *GetHealth(void) { return m_pHealth; }

	void CreateSceneObj(void);								// その他オブジェクトの生成
	
private:
	static CScore *m_pScore;
	static CNumBlock *m_pNumBlock;
	static CLife *m_pLife;
	static CHealth *m_pHealth;
};

#endif