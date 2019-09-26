//=============================================================================
//
// �`���[�g���A�����S�̏��� [tutoriallogo.cpp]
// Author : �|���j
//
//=============================================================================
#include "tutoriallogo.h"
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
// �`���[�g���A�����S�̐�������
//=============================================================================
CTutorialLogo *CTutorialLogo::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType)
{
	CTutorialLogo *pTutorialLogo = NULL;

	if (pTutorialLogo == NULL)
	{
		// �`���[�g���A�����S�N���X�̐���
		pTutorialLogo = new CTutorialLogo;

		if (pTutorialLogo != NULL)
		{
			pTutorialLogo->SetPosition(pos);
			pTutorialLogo->SetWidth(fWidth);
			pTutorialLogo->SetHeight(fHeight);
			pTutorialLogo->Init();
			pTutorialLogo->BindTexture(CResource::GetTexture(nType));
		}
	}

	return pTutorialLogo;
}

//=============================================================================
// �`���[�g���A�����S�N���X�̃R���X�g���N�^
//=============================================================================
CTutorialLogo::CTutorialLogo()
{
}

//=============================================================================
// �`���[�g���A�����S�N���X�̃f�X�g���N�^
//=============================================================================
CTutorialLogo::~CTutorialLogo()
{
}

//=============================================================================
// �`���[�g���A�����S����������
//=============================================================================
HRESULT CTutorialLogo::Init(void)
{
	// 2D�I�u�W�F�N�g����������
	CLogo::Init();

	CLogo::SetCol(BUTTON_COLOR);

	return S_OK;
}

//=============================================================================
// �`���[�g���A�����S�I������
//=============================================================================
void CTutorialLogo::Uninit(void)
{
	// 2D�I�u�W�F�N�g�I������
	CLogo::Uninit();
}

//=============================================================================
// �`���[�g���A�����S�X�V����
//=============================================================================
void CTutorialLogo::Update(void)
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
// �`���[�g���A�����S�`�揈��
//=============================================================================
void CTutorialLogo::Draw(void)
{
	// 2D�I�u�W�F�N�g�`�揈��
	CLogo::Draw();
}