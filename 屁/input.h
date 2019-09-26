//=============================================================================
//
// ���͏��� [input.h]
// Author :�@���R���
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_KEY_MAX			(256)	// �L�[�̍ő吔
#define	NUM_JOYPAD_MAX		(32)	// �L�[�̍ő吔
#define DI_JOY_I_INPUT		(1000)

//========================================
// �N���X�̒�`
//========================================
//=====================
// ���̓N���X
//=====================
class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
	virtual void Uninit(void);								// �I������
	virtual void Update(void) = 0;							// �X�V����

protected:
	static LPDIRECTINPUT8	m_pInput;
	LPDIRECTINPUTDEVICE8	m_pDevice;
};

//=====================
// �L�[�{�[�h�N���X
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
	BYTE m_aKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̓��͏��i�v���X���j
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̓��͏��i�g���K�[���j
};

//=====================
// �W���C�p�b�g�N���X
//=====================
class CInputJoypad : public CInput
{
public:
	typedef enum
	{// �{�^���̔z��
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
		DIJS_BUTTON_RIGHT,		// �\���E
		DIJS_BUTTON_LEFT,		// �\����
		DIJS_BUTTON_UP,			// �\����
		DIJS_BUTTON_DOWN,		// �\����
		DIJS_BUTTON_RS_RIGHT,	// �E�X�e�B�b�N�E
		DIJS_BUTTON_RS_LEFT,	// �E�X�e�B�b�N��
		DIJS_BUTTON_RS_UP,		// �E�X�e�B�b�N��
		DIJS_BUTTON_RS_DOWN,	// �E�X�e�B�b�N��
		DIJS_BUTTON_LS_RIGHT,	// ���X�e�B�b�N�E
		DIJS_BUTTON_LS_LEFT,	// ���X�e�B�b�N��
		DIJS_BUTTON_LS_UP,		// ���X�e�B�b�N��
		DIJS_BUTTON_LS_DOWN,	// ���X�e�B�b�N��
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
	BYTE m_aKeyState[NUM_JOYPAD_MAX];			// �W���C�p�b�g�̓��͏��i�v���X���j
	BYTE m_aKeyStateTrigger[NUM_JOYPAD_MAX];	// �W���C�p�b�g�̓��͏��i�g���K�[���j
	float m_LeftAxizX;
	float m_LeftAxizY;
	float m_RightAxizX;
	float m_RightAxizY;
	float m_Radian;
};

#endif