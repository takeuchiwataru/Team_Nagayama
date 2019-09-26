//=============================================================================
//
// �`���[�g���A�����S�̏��� [tutoriallogo.h]
// Author : �|���j
//
//=============================================================================
#ifndef _TUTORIALLOGO_H_
#define _TUTORIALLOGO_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=========================
// �`���[�g���A�����S�N���X
//=========================
class CTutorialLogo : public CLogo
{
public:

	CTutorialLogo();															// �R���X�g���N�^
	~CTutorialLogo();															// �f�X�g���N�^

	static CTutorialLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);	// �I�u�W�F�N�g�̐���

	HRESULT Init(void);															// �`���[�g���A�����S����������
	void Uninit(void);															// �`���[�g���A�����S�I������
	void Update(void);															// �`���[�g���A�����S�X�V����
	void Draw(void);															// �`���[�g���A�����S�`�揈��

private:
};

#endif