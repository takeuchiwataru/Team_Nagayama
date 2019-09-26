//=============================================================================
//
// �p�[�e�B�N���̏��� [particleX.h]
// Author : ���R���
//
//=============================================================================
#ifndef _PARTICLEX_H_
#define _PARTICLEX_H_

#include "main.h"
#include "sceneX.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PARTICLE3D		(256)							// �p�[�e�B�N���̐�
#define MAX_TEXTURE			(2)								// �p�[�e�B�N���̐�

//========================================
// �N���X�̒�`
//========================================
//=====================
// �p�[�e�B�N���N���X
//=====================
class CParticleX : public CSceneX
{
public:
	typedef enum
	{// �L�[�v�f
		TYPE_NORMAL = 0,	// �ʏ���
		TYPE_UP,			// �㏸���
		TYPE_DOWN,			// ���~���
		PARTICLESTATE_MAX			// �v���C���[�̎�ނ̑���
	} PARTICLE_TYPE;

	CParticleX();	// �R���X�g���N�^
	~CParticleX();	// �f�X�g���N�^

	HRESULT Init(void);	// �v���C���[����������
	void Uninit(void);	// �v���C���[�I������
	void Update(void);	// �v���C���[�X�V����
	void Draw(void);	// �v���C���[�`�揈��

	static CParticleX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int nLife, PARTICLE_TYPE type);	// �I�u�W�F�N�g�̐���

	static HRESULT LoadMat(void);				// �}�e���A���ǂݍ���
	static void UnloadMat(void);				// �}�e���A�����

private:
	static LPDIRECT3DTEXTURE9	*m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX				m_mtxWorld;		// ���[���h�}�g���b�N�X
	int m_nLife;
	D3DXVECTOR3 m_move;
	PARTICLE_TYPE m_ParticleType;
};

#endif