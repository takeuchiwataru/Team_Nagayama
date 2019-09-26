//=============================================================================
//
// �p�[�e�B�N���̏��� [particle3D.h]
// Author : ���R���
//
//=============================================================================
#ifndef _PARTICLE3D_H_
#define _PARTICLE3D_H_

#include "main.h"
#include "billboard.h"
#include "particle2D.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PARTICLE3D		(256)							// �p�[�e�B�N���̐�
#define MAX_TEXTURE			(2)								// �p�[�e�B�N���̐�
#define EFFECT_CLOUD_NAME	"data/TEXTURE/cloud.png"		// ���G�t�F�N�g�̃e�N�X�`����

//========================================
// �N���X�̒�`
//========================================
//=====================
// �p�[�e�B�N���N���X
//=====================
class CParticle3D : public CBillboard
{
public:
	typedef enum
	{// �L�[�v�f
		TYPE_NORMAL = 0,	// �ʏ���
		TYPE_UP,			// �㏸���
		TYPE_DOWN,			// ���~���
		PARTICLESTATE_MAX			// �v���C���[�̎�ނ̑���
	} PARTICLE_TYPE;

	CParticle3D();	// �R���X�g���N�^
	~CParticle3D();	// �f�X�g���N�^

	HRESULT Init(void);	// 3D�p�[�e�B�N������������
	void Uninit(void);	// 3D�p�[�e�B�N���I������
	void Update(void);	// 3D�p�[�e�B�N���X�V����
	void Draw(void);	// 3D�p�[�e�B�N���`�揈��

	static CParticle3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fWidth, float fHeight, int nLife, PARTICLE_TYPE type, int nTexture);	// �I�u�W�F�N�g�̐���

private:
	int m_nLife;
	D3DXCOLOR m_col;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	PARTICLE_TYPE m_ParticleType;
};

#endif