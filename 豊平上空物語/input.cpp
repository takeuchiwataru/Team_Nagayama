//=============================================================================
//
// ���͏��� [input.cpp]
// Author :�@���R���
//
//=============================================================================
#include "input.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CInput::~CInput()
{
}

//=============================================================================
// ���͏���������
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		// DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//=============================================================================
// ���͏I������
//=============================================================================
void CInput::Uninit(void)
{
	// DirectInput�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}

	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();	// �L�[�{�[�h�ւ̃A�N�Z�X�������
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//=============================================================================
// �L�[�{�[�h���͂̃R���X�g���N�^
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
// �L�[�{�[�h���͂̃f�X�g���N�^
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{
}

//=============================================================================
// �L�[�{�[�h���͏���������
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// �L�[�{�[�h���͏I������
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	// ���͏I������
	CInput::Uninit();
}

//=============================================================================
// �L�[�{�[�h���͍X�V����
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	// �L�[�{�[�h�̓��͏��
	int nCntKey;

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];	// �L�[�{�[�h���͏��ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//=============================================================================
// �L�[�{�[�h�̓��͏��(�v���X���)���擾
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �W���C�p�b�g���͂̃R���X�g���N�^
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
// �W���C�p�b�g���͂̃f�X�g���N�^
//=============================================================================
CInputJoypad::~CInputJoypad()
{
}

//=============================================================================
// �W���C�p�b�g���͏���������
//=============================================================================
HRESULT CInputJoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_Joystick, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIJoystick)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	if (m_pDevice != NULL)
	{// �����ł���
		DIPROPRANGE diprg;

		// ���̒l�͈̔͂�ݒ�
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = -DI_JOY_I_INPUT;
		diprg.lMax = DI_JOY_I_INPUT;

		// ���̐ݒ�
		// ���A�i���O�X�e�B�b�N
		diprg.diph.dwObj = DIJOFS_X;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Y;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Z;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �E�A�i���O�X�e�B�b�N
		diprg.diph.dwObj = DIJOFS_RX;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RY;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RZ;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// ?
		//diprg.diph.dwObj = DIJOFS_SLIDER(0);
		//g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �\���L�[(���0�x�Ƃ����v���Ɋp�x * 100)
		diprg.diph.dwObj = DIJOFS_POV(0);
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �W���C�X�e�B�b�N�ւ̃A�N�Z�X�����l��(���͐���J�n)
		m_pDevice->Acquire();
	}


	return S_OK;
}

//=============================================================================
// �W���C�p�b�g���͏I������
//=============================================================================
void CInputJoypad::Uninit(void)
{
	// ���͏I������
	CInput::Uninit();
}

//=============================================================================
// �W���C�p�b�g���͍X�V����
//=============================================================================
void CInputJoypad::Update(void)
{
	DIJOYSTATE JoypadState;	// �W���C�p�b�g�̓��͏��
	int nCntKey;

	if (m_pDevice != NULL)
	{
		m_pDevice->Poll();

		// ���̓f�o�C�X����f�[�^���擾
		if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIJOYSTATE), &JoypadState)))
		{
			m_LeftAxizX = (float)JoypadState.lX;
			m_LeftAxizY = (float)JoypadState.lY;
			m_RightAxizX = (float)JoypadState.lZ;
			m_RightAxizY = (float)JoypadState.lRz;

			if (m_LeftAxizY <= -100)
			{// ���X�e�B�b�N�̏�
				JoypadState.rgbButtons[DIJS_BUTTON_LS_UP] = 0x80;
			}
			if (m_LeftAxizY >= 100)
			{// ���X�e�B�b�N�̉�
				JoypadState.rgbButtons[DIJS_BUTTON_LS_DOWN] = 0x80;
			}
			if (m_LeftAxizX <= -100)
			{// ���X�e�B�b�N�̉E
				JoypadState.rgbButtons[DIJS_BUTTON_LS_RIGHT] = 0x80;
			}
			if (m_LeftAxizX >= 100)
			{// ���X�e�B�b�N�̍�
				JoypadState.rgbButtons[DIJS_BUTTON_LS_LEFT] = 0x80;
			}

			if (m_RightAxizY <= -100)
			{// �E�X�e�B�b�N�̏�
				JoypadState.rgbButtons[DIJS_BUTTON_RS_UP] = 0x80;
			}
			if (m_RightAxizY >= 100)
			{// �E�X�e�B�b�N�̉�
				JoypadState.rgbButtons[DIJS_BUTTON_RS_DOWN] = 0x80;
			}
			if (m_RightAxizX <= -100)
			{// �E�X�e�B�b�N�̉E
				JoypadState.rgbButtons[DIJS_BUTTON_RS_RIGHT] = 0x80;
			}
			if (m_RightAxizX >= 100)
			{// �E�X�e�B�b�N�̍�
				JoypadState.rgbButtons[DIJS_BUTTON_RS_LEFT] = 0x80;
			}

			if (JoypadState.rgdwPOV[0] == 0)
			{// �\���L�[��
				JoypadState.rgbButtons[DIJS_BUTTON_UP] = 0x80;

				m_Radian = D3DXToRadian(JoypadState.rgdwPOV[0]);
			}
			if (JoypadState.rgdwPOV[0] == 18000)
			{// �\���L�[��
				JoypadState.rgbButtons[DIJS_BUTTON_DOWN] = 0x80;

				m_Radian = D3DXToRadian(JoypadState.rgdwPOV[0]);
			}
			if (JoypadState.rgdwPOV[0] == 9000)
			{// �\���L�[�E
				JoypadState.rgbButtons[DIJS_BUTTON_RIGHT] = 0x80;

				m_Radian = D3DXToRadian(JoypadState.rgdwPOV[0]);
			}
			if (JoypadState.rgdwPOV[0] == 27000)
			{// �\���L�[��
				JoypadState.rgbButtons[DIJS_BUTTON_LEFT] = 0x80;

				m_Radian = D3DXToRadian(JoypadState.rgdwPOV[0]);
			}
			if (JoypadState.rgdwPOV[0] == 4500)
			{// �\���L�[�E��
				JoypadState.rgbButtons[DIJS_BUTTON_UP] = 0x80;
				JoypadState.rgbButtons[DIJS_BUTTON_RIGHT] = 0x80;

				m_Radian = D3DXToRadian(JoypadState.rgdwPOV[0]);
			}
			if (JoypadState.rgdwPOV[0] == 13500)
			{// �\���L�[�E��
				JoypadState.rgbButtons[DIJS_BUTTON_DOWN] = 0x80;
				JoypadState.rgbButtons[DIJS_BUTTON_RIGHT] = 0x80;

				m_Radian = D3DXToRadian(JoypadState.rgdwPOV[0]);
			}
			if (JoypadState.rgdwPOV[0] == 31500)
			{// �\���L�[����
				JoypadState.rgbButtons[DIJS_BUTTON_UP] = 0x80;
				JoypadState.rgbButtons[DIJS_BUTTON_LEFT] = 0x80;

				m_Radian = D3DXToRadian(JoypadState.rgdwPOV[0]);
			}
			if (JoypadState.rgdwPOV[0] == 22500)
			{// �\���L�[����
				JoypadState.rgbButtons[DIJS_BUTTON_DOWN] = 0x80;
				JoypadState.rgbButtons[DIJS_BUTTON_LEFT] = 0x80;

				m_Radian = D3DXToRadian(JoypadState.rgdwPOV[0]);
			}

			for (nCntKey = 0; nCntKey < NUM_JOYPAD_MAX; nCntKey++)
			{
				m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ JoypadState.rgbButtons[nCntKey]) & JoypadState.rgbButtons[nCntKey];
				m_aKeyState[nCntKey] = JoypadState.rgbButtons[nCntKey];	// �L�[�{�[�h���͏��ۑ�
			}
		}
		else
		{
			m_pDevice->Acquire();	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
		}
	}
}

//=============================================================================
// �L�[�{�[�h�̓��͏��(�v���X���)���擾
//=============================================================================
bool CInputJoypad::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool CInputJoypad::GetTrigger(DIJS_BUTTON button)
{
	return(m_aKeyStateTrigger[button] & 0x80) ? true : false;
}


//=============================================================================
// ���X�e�B�b�N�̎擾
//=============================================================================
float CInputJoypad::GetLeftAxiz()
{
	float Axiz = atan2f(m_LeftAxizX, m_LeftAxizY);

	return Axiz;
}

//=============================================================================
// �E�X�e�B�b�N�̎擾
//=============================================================================
float CInputJoypad::GetRightAxiz()
{
	float Axiz = atan2f(m_RightAxizX, m_RightAxizY);

	return Axiz;
}

//=============================================================================
// �p�x�̎擾
//=============================================================================
float CInputJoypad::GetRadian()
{
	return m_Radian / 100;
}

//=============================================================================
// �R���g���[���[�̓��͏��(�g���K�[���)���擾
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