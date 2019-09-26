//=============================================================================
//
// �p�[�e�B�N���̏��� [particle2D.h]
// Author : ���R���
//
//=============================================================================
#ifndef _PARTICLE2D_H_
#define _PARTICLE2D_H_

#include "main.h"
#include "scene2D.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PARTICLE2D	(126)							// �p�[�e�B�N���̐�

//========================================
// �N���X�̒�`
//========================================
//=====================
// �p�[�e�B�N���N���X
//=====================
class CParticle2D : public CScene2D
{
public:
	CParticle2D(int nPriority = PARTICLE_PRIORITY, OBJTYPE objType = OBJTYPE_PARTICLE);	// �R���X�g���N�^
	~CParticle2D();	// �f�X�g���N�^

	HRESULT Init(void);	// �v���C���[����������
	void Uninit(void);	// �v���C���[�I������
	void Update(void);	// �v���C���[�X�V����
	void Draw(void);	// �v���C���[�`�揈��

	static CParticle2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fWidth, float fHeight);	// �I�u�W�F�N�g�̐���

private:
	int m_nLife;
	D3DXCOLOR m_col;
	D3DXVECTOR3 m_move;
};

#endif