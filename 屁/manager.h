//=============================================================================
//
// マネージャ処理 [manager.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "ranking.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CRenderer;
class CInputKeyboard;
class CInputJoypad;
class CDebugProc;
class CScene3D;
class CGame;
class CTitle;
class CTutorial;
class CGameClear;
class CGameOver;
class CRanking;
class CFade;
class CLight;
class CCamera;
class CSound;
class CMask;
class CText;

//=============================================================================
// クラスの定義
//=============================================================================
//=====================
// マネージャクラス
//=====================
class CManager
{
public:
	typedef enum
	{// ゲームのモード
		MODE_NONE = 0,
		MODE_TITLE,		// タイトル
		MODE_TUTORIAL,	// チュートリアル
		MODE_GAME,		// ゲーム
		MODE_GAMECLEAR,	// ゲームクリア
		MODE_GAMEOVER,	// ゲームオーバー
		MODE_RANKING,	// ランキング
		MODE_MAX
	} MODE;

	CManager();		// コンストラクタ
	~CManager();	// デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CFade *GetFade(void);
	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static void SetMode(MODE mode);
	static MODE GetMode(void);
	static CCamera *GetCamera(void);
	static int GetRanking(int nIdx);
	static void GetRankingScore(int nScore);
	static void GetScore(int nScore);
	static int SetScore(void);
	static void ReleaseScore(void);
	static int GetUpdateScore(void);
	static CSound *GetSound(void);
	static CInputJoypad *GetInputJoypad(void);
	static CMask *GetMask(void);
	static CText *GetText(void);

private:
	static MODE m_mode;
	static CRenderer *m_pRenderer;
	static CInputKeyboard *m_pInputKeyboard;
	static CDebugProc *m_pDebugProc;
	static CGame *m_pGame;
	static CTitle *m_pTitle;
	static CTutorial *m_pTutorial;
	static CGameClear *m_pGameClear;
	static CGameOver *m_pGameOver;
	static CRanking *m_pRanking;
	static CFade *m_pFade;
	static CLight *m_pLight;
	static CCamera *m_pCamera;
	static CSound *m_pSound;
	static CMask *m_pMask;
	static CInputJoypad *m_pInputJoypad;
	static CText *m_pText;
	static int m_aScore[MAX_RANKING];
	static int m_nScore;
	static int m_nUpdateScore;
	float m_fData;
};

#endif