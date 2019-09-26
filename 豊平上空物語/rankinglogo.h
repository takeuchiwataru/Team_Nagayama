//=============================================================================
//
// �����L���O���S�̏��� [rankinglogo.h]
// Author : �|���j
//
//=============================================================================
#ifndef _RAKINGLOGO_H_
#define _RAKINGLOGO_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=========================
// �^�C�g�����S�N���X
//=========================
class CRankingLogo : public CLogo
{
public:

	CRankingLogo();															// �R���X�g���N�^
	~CRankingLogo();															// �f�X�g���N�^

	static CRankingLogo *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);	// �I�u�W�F�N�g�̐���

	HRESULT Init(void);															// �^�C�g�����S����������
	void Uninit(void);															// �^�C�g�����S�I������
	void Update(void);															// �^�C�g�����S�X�V����
	void Draw(void);															// �^�C�g�����S�`�揈��

private:
};

#endif