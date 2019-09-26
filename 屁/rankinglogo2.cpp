//=============================================================================
//
// �����L���O���S2�̏��� [rankinglogo2.cpp]
// Author : �|���j
//
//=============================================================================
#include "rankinglogo2.h"
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
CRankingLogo2 *CRankingLogo2::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType)
{
	CRankingLogo2 *pRankingLogo2 = NULL;

	if (pRankingLogo2 == NULL)
	{
		// �^�C�g�����S�N���X�̐���
		pRankingLogo2 = new CRankingLogo2;

		if (pRankingLogo2 != NULL)
		{
			pRankingLogo2->SetPosition(pos);
			pRankingLogo2->SetWidth(fWidth);
			pRankingLogo2->SetHeight(fHeight);
			pRankingLogo2->Init();
			pRankingLogo2->BindTexture(CResource::GetTexture(nType));
		}
	}

	return pRankingLogo2;
}

//=============================================================================
// �^�C�g�����S�N���X�̃R���X�g���N�^
//=============================================================================
CRankingLogo2::CRankingLogo2()
{
}

//=============================================================================
// �^�C�g�����S�N���X�̃f�X�g���N�^
//=============================================================================
CRankingLogo2::~CRankingLogo2()
{
}

//=============================================================================
// �^�C�g�����S����������
//=============================================================================
HRESULT CRankingLogo2::Init(void)
{
	// 2D�I�u�W�F�N�g����������
	CLogo::Init();


	CLogo::SetCol(BUTTON_COLOR);

	return S_OK;
}

//=============================================================================
// �^�C�g�����S�I������
//=============================================================================
void CRankingLogo2::Uninit(void)
{
	// 2D�I�u�W�F�N�g�I������
	CLogo::Uninit();
}

//=============================================================================
// �^�C�g�����S�X�V����
//=============================================================================
void CRankingLogo2::Update(void)
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
void CRankingLogo2::Draw(void)
{
	// 2D�I�u�W�F�N�g�`�揈��
	CLogo::Draw();
}