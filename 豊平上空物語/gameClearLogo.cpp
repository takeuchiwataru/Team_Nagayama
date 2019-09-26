//=============================================================================
//
// �^�C�g�����S�̏��� [titlelogo.cpp]
// Author : �|���j
//
//=============================================================================
#include "gameClearLogo.h"
#include "renderer.h"
#include "fade.h"
#include "input.h"
#include "resource.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BUTTON_COLOR		(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))
#define BLINK_COUNT			(60)
#define BLINK_COUNT_FAST	(2)

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �^�C�g�����S�̐�������
//=============================================================================
CGameClearLogo *CGameClearLogo::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType)
{
	CGameClearLogo *pGameOverLogo = NULL;

	if (pGameOverLogo == NULL)
	{
		// �^�C�g�����S�N���X�̐���
		pGameOverLogo = new CGameClearLogo;

		if (pGameOverLogo != NULL)
		{
			pGameOverLogo->SetPosition(pos);
			pGameOverLogo->SetWidth(fWidth);
			pGameOverLogo->SetHeight(fHeight);
			pGameOverLogo->Init();
			pGameOverLogo->BindTexture(CResource::GetTexture(nType));
		}
	}

	return pGameOverLogo;
}

//=============================================================================
// �^�C�g�����S�N���X�̃R���X�g���N�^
//=============================================================================
CGameClearLogo::CGameClearLogo()
{
}

//=============================================================================
// �^�C�g�����S�N���X�̃f�X�g���N�^
//=============================================================================
CGameClearLogo::~CGameClearLogo()
{
}

//=============================================================================
// �^�C�g�����S����������
//=============================================================================
HRESULT CGameClearLogo::Init(void)
{
	// 2D�I�u�W�F�N�g����������
	CLogo::Init();


	CLogo::SetCol(BUTTON_COLOR);

	return S_OK;
}

//=============================================================================
// �^�C�g�����S�I������
//=============================================================================
void CGameClearLogo::Uninit(void)
{
	// 2D�I�u�W�F�N�g�I������
	CLogo::Uninit();
}

//=============================================================================
// �^�C�g�����S�X�V����
//=============================================================================
void CGameClearLogo::Update(void)
{
	//// ���͏����擾
	//CInputKeyboard *pInputKeyboard;
	//pInputKeyboard = CManager::GetInputKeyboard();

	//// ���͏����擾
	//CInputJoypad *pInputJoypad;
	//pInputJoypad = CManager::GetInputJoypad();

	//// �t�F�[�h�̏�Ԃ��擾
	//CFade::FADE fade;
	//fade = CFade::GetFade();
}

//=============================================================================
// �^�C�g�����S�`�揈��
//=============================================================================
void CGameClearLogo::Draw(void)
{
	// 2D�I�u�W�F�N�g�`�揈��
	CLogo::Draw();
}