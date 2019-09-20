//=============================================================================
//
// 入力処理 [input.h]
// Author :　長山拓実
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_KEY_MAX			(256)	// キーの最大数
#define	NUM_JOYPAD_MAX		(32)	// キーの最大数
#define DI_JOY_I_INPUT		(1000)

//========================================
// クラスの定義
//========================================
//=====================
// 入力クラス
//=====================
class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化処理
	virtual void Uninit(void);								// 終了処理
	virtual void Update(void) = 0;							// 更新処理

protected:
	static LPDIRECTINPUT8	m_pInput;
	LPDIRECTINPUTDEVICE8	m_pDevice;
};

//=====================
// キーボードクラス
//=====================
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];			// キーボードの入力情報（プレス情報）
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];	// キーボードの入力情報（トリガー情報）
};

//=====================
// ジョイパットクラス
//=====================
class CInputJoypad : public CInput
{
public:
	typedef enum
	{// ボタンの配列
		DIJS_BUTTON_X = 0,
		DIJS_BUTTON_A,
		DIJS_BUTTON_B,
		DIJS_BUTTON_Y,
		DIJS_BUTTON_LB,
		DIJS_BUTTON_RB,
		DIJS_BUTTON_LT,
		DIJS_BUTTON_RT,
		DIJS_BUTTON_BACK,
		DIJS_BUTTON_START,
		DIJS_BUTTON_LSTICK_PUSH,
		DIJS_BUTTON_RSTICK_PUSH,
		DIJS_BUTTON_12,
		DIJS_BUTTON_13,
		DIJS_BUTTON_14,
		DIJS_BUTTON_15,
		DIJS_BUTTON_16,
		DIJS_BUTTON_17,
		DIJS_BUTTON_18,
		DIJS_BUTTON_19,
		DIJS_BUTTON_RIGHT,		// 十字右
		DIJS_BUTTON_LEFT,		// 十字左
		DIJS_BUTTON_UP,			// 十字上
		DIJS_BUTTON_DOWN,		// 十字下
		DIJS_BUTTON_RS_RIGHT,	// 右スティック右
		DIJS_BUTTON_RS_LEFT,	// 右スティック左
		DIJS_BUTTON_RS_UP,		// 右スティック上
		DIJS_BUTTON_RS_DOWN,	// 右スティック下
		DIJS_BUTTON_LS_RIGHT,	// 左スティック右
		DIJS_BUTTON_LS_LEFT,	// 左スティック左
		DIJS_BUTTON_LS_UP,		// 左スティック上
		DIJS_BUTTON_LS_DOWN,	// 左スティック下
		DIJS_BUTTON_MAX
	} DIJS_BUTTON;

	CInputJoypad();
	~CInputJoypad();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(DIJS_BUTTON button);
	bool GetAnyButton(int nNumber);

	float GetLeftAxiz(void);

	float GetRightAxiz(void);

	float GetRadian(void);
private:
	BYTE m_aKeyState[NUM_JOYPAD_MAX];			// ジョイパットの入力情報（プレス情報）
	BYTE m_aKeyStateTrigger[NUM_JOYPAD_MAX];	// ジョイパットの入力情報（トリガー情報）
	float m_LeftAxizX;
	float m_LeftAxizY;
	float m_RightAxizX;
	float m_RightAxizY;
	float m_Radian;
};

#endif