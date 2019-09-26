//=============================================================================
//
// 入力処理 [input.cpp]
// Author :　長山拓実
//
//=============================================================================
#include "input.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CInput::~CInput()
{
}

//=============================================================================
// 入力初期化処理
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		// DirectInputオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//=============================================================================
// 入力終了処理
//=============================================================================
void CInput::Uninit(void)
{
	// DirectInputオブジェクトの開放
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}

	// 入力デバイス(キーボード)の開放
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();	// キーボードへのアクセス権を放棄
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//=============================================================================
// キーボード入力のコンストラクタ
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		m_aKeyState[nCntKey] = 0;
		m_aKeyStateTrigger[nCntKey] = 0;
	}
}

//=============================================================================
// キーボード入力のデストラクタ
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{
}

//=============================================================================
// キーボード入力初期化処理
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// 入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// キーボード入力終了処理
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	// 入力終了処理
	CInput::Uninit();
}

//=============================================================================
// キーボード入力更新処理
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	// キーボードの入力情報
	int nCntKey;

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];	// キーボード入力情報保存
		}
	}
	else
	{
		m_pDevice->Acquire();	// キーボードへのアクセス権を獲得
	}
}

//=============================================================================
// キーボードの入力情報(プレス情報)を取得
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// キーボードの入力情報(トリガー情報)を取得
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// ジョイパット入力のコンストラクタ
//=============================================================================
CInputJoypad::CInputJoypad()
{
	for (int nCntButton = 0; nCntButton < NUM_JOYPAD_MAX; nCntButton++)
	{
		m_aKeyState[nCntButton] = 0;
		m_aKeyStateTrigger[nCntButton] = 0;
	}
}

//=============================================================================
// ジョイパット入力のデストラクタ
//=============================================================================
CInputJoypad::~CInputJoypad()
{
}

//=============================================================================
// ジョイパット入力初期化処理
//=============================================================================
HRESULT CInputJoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// 入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_Joystick, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIJoystick)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	if (m_pDevice != NULL)
	{// 生成できた
		DIPROPRANGE diprg;

		// 軸の値の範囲を設定
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = -DI_JOY_I_INPUT;
		diprg.lMax = DI_JOY_I_INPUT;

		// 軸の設定
		// 左アナログスティック
		diprg.diph.dwObj = DIJOFS_X;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Y;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Z;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// 右アナログスティック
		diprg.diph.dwObj = DIJOFS_RX;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RY;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RZ;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// ?
		//diprg.diph.dwObj = DIJOFS_SLIDER(0);
		//g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// 十字キー(上を0度とし時計回りに角度 * 100)
		diprg.diph.dwObj = DIJOFS_POV(0);
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// ジョイスティックへのアクセス権を獲得(入力制御開始)
		m_pDevice->Acquire();
	}


	return S_OK;
}

//=============================================================================
// ジョイパット入力終了処理
//=============================================================================
void CInputJoypad::Uninit(void)
{
	// 入力終了処理
	CInput::Uninit();
}

//=============================================================================
// ジョイパット入力更新処理
//=============================================================================
void CInputJoypad::Update(void)
{
	DIJOYSTATE JoypadState;	// ジョイパットの入力情報
	int nCntKey;

	if (m_pDevice != NULL)
	{
		m_pDevice->Poll();

		// 入力デバイスからデータを取得
		if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIJOYSTATE), &JoypadState)))
		{
			m_LeftAxizX = (float)JoypadState.lX;
			m_LeftAxizY = (float)JoypadState.lY;
			m_RightAxizX = (float)JoypadState.lZ;
			m_RightAxizY = (float)JoypadState.lRz;

			if (m_LeftAxizY <= -100)
			{// 左スティックの上
				JoypadState.rgbButtons[DIJS_BUTTON_LS_UP] = 0x80;
			}
			if (m_LeftAxizY >= 100)
			{// 左スティックの下
				JoypadState.rgbButtons[DIJS_BUTTON_LS_DOWN] = 0x80;
			}
			if (m_LeftAxizX <= -100)
			{// 左スティックの右
				JoypadState.rgbButtons[DIJS_BUTTON_LS_RIGHT] = 0x80;
			}
			if (m_LeftAxizX >= 100)
			{// 左スティックの左
				JoypadState.rgbButtons[DIJS_BUTTON_LS_LEFT] = 0x80;
			}

			if (m_RightAxizY <= -100)
			{// 右スティックの上
				JoypadState.rgbButtons[DIJS_BUTTON_RS_UP] = 0x80;
			}
			if (m_RightAxizY >= 100)
			{// 右スティックの下
				JoypadState.rgbButtons[DIJS_BUTTON_RS_DOWN] = 0x80;
			}
			if (m_RightAxizX <= -100)
			{// 右スティックの右
				JoypadState.rgbButtons[DIJS_BUTTON_RS_RIGHT] = 0x80;
			}
			if (m_RightAxizX >= 100)
			{// 右スティックの左
				JoypadState.rgbButtons[DIJS_BUTTON_RS_LEFT] = 0x80;
			}

			if (JoypadState.rgdwPOV[0] == 0)
			{// 十字キー上
				JoypadState.rgbButtons[DIJS_BUTTON_UP] = 0x80;

				m_Radian = D3DXToRadian(JoypadState.rgdwPOV[0]);
			}
			if (JoypadState.rgdwPOV[0] == 18000)
			{// 十字キー下
				JoypadState.rgbButtons[DIJS_BUTTON_DOWN] = 0x80;

				m_Radian = D3DXToRadian(JoypadState.rgdwPOV[0]);
			}
			if (JoypadState.rgdwPOV[0] == 9000)
			{// 十字キー右
				JoypadState.rgbButtons[DIJS_BUTTON_RIGHT] = 0x80;

				m_Radian = D3DXToRadian(JoypadState.rgdwPOV[0]);
			}
			if (JoypadState.rgdwPOV[0] == 27000)
			{// 十字キー左
				JoypadState.rgbButtons[DIJS_BUTTON_LEFT] = 0x80;

				m_Radian = D3DXToRadian(JoypadState.rgdwPOV[0]);
			}
			if (JoypadState.rgdwPOV[0] == 4500)
			{// 十字キー右上
				JoypadState.rgbButtons[DIJS_BUTTON_UP] = 0x80;
				JoypadState.rgbButtons[DIJS_BUTTON_RIGHT] = 0x80;

				m_Radian = D3DXToRadian(JoypadState.rgdwPOV[0]);
			}
			if (JoypadState.rgdwPOV[0] == 13500)
			{// 十字キー右下
				JoypadState.rgbButtons[DIJS_BUTTON_DOWN] = 0x80;
				JoypadState.rgbButtons[DIJS_BUTTON_RIGHT] = 0x80;

				m_Radian = D3DXToRadian(JoypadState.rgdwPOV[0]);
			}
			if (JoypadState.rgdwPOV[0] == 31500)
			{// 十字キー左上
				JoypadState.rgbButtons[DIJS_BUTTON_UP] = 0x80;
				JoypadState.rgbButtons[DIJS_BUTTON_LEFT] = 0x80;

				m_Radian = D3DXToRadian(JoypadState.rgdwPOV[0]);
			}
			if (JoypadState.rgdwPOV[0] == 22500)
			{// 十字キー左下
				JoypadState.rgbButtons[DIJS_BUTTON_DOWN] = 0x80;
				JoypadState.rgbButtons[DIJS_BUTTON_LEFT] = 0x80;

				m_Radian = D3DXToRadian(JoypadState.rgdwPOV[0]);
			}

			for (nCntKey = 0; nCntKey < NUM_JOYPAD_MAX; nCntKey++)
			{
				m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ JoypadState.rgbButtons[nCntKey]) & JoypadState.rgbButtons[nCntKey];
				m_aKeyState[nCntKey] = JoypadState.rgbButtons[nCntKey];	// キーボード入力情報保存
			}
		}
		else
		{
			m_pDevice->Acquire();	// キーボードへのアクセス権を獲得
		}
	}
}

//=============================================================================
// キーボードの入力情報(プレス情報)を取得
//=============================================================================
bool CInputJoypad::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// キーボードの入力情報(トリガー情報)を取得
//=============================================================================
bool CInputJoypad::GetTrigger(DIJS_BUTTON button)
{
	return(m_aKeyStateTrigger[button] & 0x80) ? true : false;
}


//=============================================================================
// 左スティックの取得
//=============================================================================
float CInputJoypad::GetLeftAxiz()
{
	float Axiz = atan2f(m_LeftAxizX, m_LeftAxizY);

	return Axiz;
}

//=============================================================================
// 右スティックの取得
//=============================================================================
float CInputJoypad::GetRightAxiz()
{
	float Axiz = atan2f(m_RightAxizX, m_RightAxizY);

	return Axiz;
}

//=============================================================================
// 角度の取得
//=============================================================================
float CInputJoypad::GetRadian()
{
	return m_Radian / 100;
}

//=============================================================================
// コントローラーの入力情報(トリガー情報)を取得
//=============================================================================
bool CInputJoypad::GetAnyButton(int nNumber)
{
	if (nNumber == 0)
	{
		for (int nCnt = 0; nCnt < DIJS_BUTTON_MAX; nCnt++)
		{
			if (m_aKeyStateTrigger[nCnt] == 0x80)
			{
				return true;
			}
		}
	}
	return false;
}