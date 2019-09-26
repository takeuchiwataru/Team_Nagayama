//=============================================================================
//
// �v���X�G�j�[�{�^���̏��� [pressAnyButton.h]
// Author : ���R���
//
//=============================================================================
#ifndef _PRESSANYBUTTON_H_
#define _PRESSANYBUTTON_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=========================
// �v���X�G�j�[�{�^�����S�N���X
//=========================
class CPressAnyButton : public CLogo
{
public:

	CPressAnyButton();															// �R���X�g���N�^
	~CPressAnyButton();															// �f�X�g���N�^

	static CPressAnyButton *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);	// �I�u�W�F�N�g�̐���

	HRESULT Init(void);															// �v���X�G�j�[�{�^�����S����������
	void Uninit(void);															// �v���X�G�j�[�{�^�����S�I������
	void Update(void);															// �v���X�G�j�[�{�^�����S�X�V����
	void Draw(void);															// �v���X�G�j�[�{�^�����S�`x�揈��

private:
	int	m_nCntEnter;
	float m_fEnterTimer;
	bool m_bPress;
};

#endif