//=============================================================================
//
// �^�C�g�����S�̏��� [titlelogo.h]
// Author : �|���j
//
//=============================================================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=========================
// �^�C�g�����S�N���X
//=========================
class CTitleLogo : public CLogo
{
public:

	CTitleLogo();															// �R���X�g���N�^
	~CTitleLogo();															// �f�X�g���N�^

	static CTitleLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);	// �I�u�W�F�N�g�̐���

	HRESULT Init(void);															// �^�C�g�����S����������
	void Uninit(void);															// �^�C�g�����S�I������
	void Update(void);															// �^�C�g�����S�X�V����
	void Draw(void);															// �^�C�g�����S�`�揈��

private:
};

#endif