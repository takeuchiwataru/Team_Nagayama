//=============================================================================
//
// �����L���O���S2�̏��� [rankinglogo2.h]
// Author : �|���j
//
//=============================================================================
#ifndef _RAKINGLOG02_H_
#define _RAKINGLOGO2_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=========================
// �^�C�g�����S�N���X
//=========================
class CRankingLogo2: public CLogo
{
public:

	CRankingLogo2();															// �R���X�g���N�^
	~CRankingLogo2();															// �f�X�g���N�^

	static CRankingLogo2 *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);	// �I�u�W�F�N�g�̐���

	HRESULT Init(void);															// �^�C�g�����S����������
	void Uninit(void);															// �^�C�g�����S�I������
	void Update(void);															// �^�C�g�����S�X�V����
	void Draw(void);															// �^�C�g�����S�`�揈��

private:
};

#endif