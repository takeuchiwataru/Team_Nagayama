//=============================================================================
//
// �|�[�Y�̏��� [pause.cpp]
// Author : ���R���
//
//=============================================================================
#include "pause.h"
#include "renderer.h"
#include "input.h"
#include "scene2D.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PAUSE_POS_X		((SCREEN_WIDTH / 2))		// �|�[�Y�̍���X���W
#define PAUSE_POS_Y		((SCREEN_HEIGHT / 2))		// �|�[�Y�̍���Y���W
#define PAUSE_WIDTH		((SCREEN_WIDTH / 2))		// �|�[�Y�̕�
#define PAUSE_HEIGHT	((SCREEN_HEIGHT / 2))		// �|�[�Y�̍���
#define PAUSE_SIZE		(200)						// �|�[�Y�̃T�C�Y

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CPause::m_apTexture[MAX_PAUSE_TEXTURE] = {};
CPause::MODE CPause::m_Mode = CPause::MODE_NONE;

//=============================================================================
// �|�[�Y�̐�������
//=============================================================================
CPause *CPause::Create(void)
{
	CPause *pPause = NULL;

	if (pPause == NULL)
	{
		// �w�i�N���X�̐���
		pPause = new CPause;

		if (pPause != NULL)
		{
			pPause->Load();
			pPause->Init();
		}
	}
	return pPause;
}

//=============================================================================
// �|�[�Y�N���X�̃R���X�g���N�^
//=============================================================================
CPause::CPause(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// �l���N���A
	for (int nCntPause = 0; nCntPause < MAX_PAUSE_TEXTURE; nCntPause++)
	{
		m_apScene2D[nCntPause] = NULL;
	}

	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		m_aCol[nCntPause] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}

	m_nSelect = 0;
}

//=============================================================================
// �|�[�Y�N���X�̃f�X�g���N�^
//=============================================================================
CPause::~CPause()
{
}

//=============================================================================
// �|�[�Y����������
//=============================================================================
HRESULT CPause::Init(void)
{
	m_nSelect = 0;
	m_Mode = MODE_NONE;

	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		m_aSelect[nCntPause] = SELECT_NONE;
		m_aCol[nCntPause] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);	// �^�񒆂̍��W��ݒ�

	// 2D�I�u�W�F�N�g����������
	m_apScene2D[0] = new CScene2D(7);
	m_apScene2D[0]->SetPosition(pos);
	m_apScene2D[0]->SetWidth(200.0f);
	m_apScene2D[0]->SetHeight(200.0f);
	m_apScene2D[0]->Init();
	m_apScene2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
	m_apScene2D[0]->BindTexture(m_apTexture[0]);

	// �R���e�B�j���[��I����Ԃɂ���
	m_aSelect[0] = SELECT_SELECT;

	for (int nCntPause = 0; nCntPause < MAX_PAUSE_TEXTURE - 1; nCntPause++)
	{
		m_apScene2D[nCntPause + 1] = new CScene2D(7);
		m_apScene2D[nCntPause + 1]->SetPosition(D3DXVECTOR3(pos.x, pos.y - 120 + (nCntPause * 120), 0.0f));
		m_apScene2D[nCntPause + 1]->SetWidth(120.0f);
		m_apScene2D[nCntPause + 1]->SetHeight(50.0f);
		m_apScene2D[nCntPause + 1]->Init();
		m_apScene2D[nCntPause + 1]->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		m_apScene2D[nCntPause + 1]->BindTexture(m_apTexture[nCntPause + 1]);
	}

	return S_OK;
}

//=============================================================================
// �|�[�Y�I������
//=============================================================================
void CPause::Uninit(void)
{
	Unload();
	// 2D�I�u�W�F�N�g�I������
	for (int nCntPause = 0; nCntPause < MAX_PAUSE_TEXTURE; nCntPause++)
	{
		if (m_apScene2D[nCntPause] != NULL)
		{
			m_apScene2D[nCntPause]->Uninit();
			m_apScene2D[nCntPause] = NULL;
		}
	}

	// �I�u�W�F�N�g�̉��
	Release();
}

//=============================================================================
// �|�[�Y�X�V����
//=============================================================================
void CPause::Update(void)
{
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ���͏����擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetInputJoypad();

	// ���y�����擾
	CSound *pSound;
	pSound = CManager::GetSound();

	if (pInputKeyboard->GetTrigger(DIK_DOWN) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_DOWN) == true
		|| pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_LS_DOWN) == true)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		m_aSelect[m_nSelect] = SELECT_NONE;
		m_nSelect = (m_nSelect + 1) % 3;
		m_aSelect[m_nSelect] = SELECT_SELECT;
	}
	if (pInputKeyboard->GetTrigger(DIK_UP) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_UP) == true
		|| pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_LS_UP) == true)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT);
		m_aSelect[m_nSelect] = SELECT_NONE;
		m_nSelect = (m_nSelect + 2) % 3;
		m_aSelect[m_nSelect] = SELECT_SELECT;
	}

	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		if (m_aSelect[nCntPause] == SELECT_SELECT)
		{// �I��
			m_aCol[m_nSelect] = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
		}
		else
		{// �I�����Ă��Ȃ�
			m_aCol[m_nSelect] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		if (m_apScene2D[nCntPause + 1] != NULL)
		{// ��񂪓����Ă�����F��ݒ肷��
			m_apScene2D[nCntPause + 1]->SetCol(m_aCol[m_nSelect]);
		}
	}
}

//=============================================================================
// �|�[�Y�`�揈��
//=============================================================================
void CPause::Draw(void)
{
}

//=============================================================================
// �|�[�Y�̃e�N�X�`���ǂݍ��ݏ���
//=============================================================================
HRESULT CPause::Load(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, PAUSE_NAME, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, PAUSET_TEXTURE_NAME0, &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, PAUSET_TEXTURE_NAME1, &m_apTexture[2]);
	D3DXCreateTextureFromFile(pDevice, PAUSET_TEXTURE_NAME2, &m_apTexture[3]);

	return S_OK;
}

//=============================================================================
// �|�[�Y�̃e�N�X�`���������
//=============================================================================
void CPause::Unload(void)
{
	for (int nCntPause = 0; nCntPause < MAX_PAUSE_TEXTURE; nCntPause++)
	{
		if (m_apTexture[nCntPause] != NULL)
		{// �e�N�X�`���̔j��
			m_apTexture[nCntPause]->Release();
			m_apTexture[nCntPause] = NULL;
		}
	}
}

//=============================================================================
// �|�[�Y�Z���N�g�̎擾
//=============================================================================
CPause::MODE CPause::GetMode(void)
{
	return m_Mode;
}

//=============================================================================
// �Z���N�g�̎擾
//=============================================================================
int CPause::GetSelect(void)
{
	return m_nSelect;
}