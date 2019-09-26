//=============================================================================
//
// �f�ފǗ��������� [resource.h]
// Author : ���R���
//
//=============================================================================
#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//========================================
// �N���X�̒�`
//========================================
//=====================
// �f�ރN���X
//=====================
class CResource
{
public:
	typedef enum // cpp�̂�Ɛ��ƕ��т𑵂���
	{
		MODEL_BLOCK = 0,	// �u���b�N
		MODEL_WOODBLOCK,	// �؃u���b�N
		MODEL_IRONBLOCK,	// �S�u���b�N
		MODEL_DEBRIS,		// �؂̔j�Ѓp�[�e�B�N��
		MODEL_COIN,			// �R�C��
		MODEL_GEM,			// ���
		MODEL_PEBBLE,		// ����
		MODEL_GOAL,			// �S�[��
		MODEL_OBSTACLE,		// ��Q��
		MODEL_BULLET,		// �e
		MODEL_MEGURO,		// �ڍ�
	} MODEL;

	typedef enum // cpp�̂�Ɛ��ƕ��т𑵂���
	{
		TEXTURE_ANYBUTTON = 0,	// �v���X�G�j�[�{�^��
		TEXTURE_ENTER,			// �G���^�[�{�^��
		TEXTURE_FIELD,			// �n��
		TEXTURE_PARTICLE2D,		// 2D�p�[�e�B�N��
		TEXTURE_CLOUD,			// ���p�[�e�B�N��
		TEXTURE_LOGOBACK,		// �w�i���S
		TEXTURE_SCORE,			// �X�R�A���S
		TEXTURE_BLOCK,			// �u���b�N���S
		TEXTURE_LIFE,			// �c�@���S
		TEXTURE_BLOCKCROSS,		// �u���b�N�̌����S
		TEXTURE_PLAYERCROSS,	// �v���C���[�̌����S
		TEXTURE_MOVE,			// �ړ����@
		TEXTURE_JUMP,			// �W�����v���@
		TEXTURE_SET,			// �ݒu���@
		TEXTURE_DESTROY,		// �j����@
		TEXTURE_END,			// �I��
		TEXTURE_NUMBER,			// ����
		TEXTURE_BULLET,			// �e
		TEXTURE_HEALTH,			// �̗�
		TEXTURE_TITLELOGO,		// �^�C�g�����S �|���ǉ�
		TEXTURE_TUTORIALLOGO,	// �`���[�g���A�����S �|���ǉ�
		TEXTURE_ONARAREMAIN,	// ���Ȃ�c�@ �|���ǉ�
		TEXTURE_HE,				// ��
		TEXTURE_RANKINGLOGO,	// �����L���O���S�|���ǉ�
		TEXTURE_RANKINGRANK,	// �����L���O�����N
	} TEXTURE;

	CResource();		// �R���X�g���N�^
	~CResource();	// �f�X�g���N�^

	static HRESULT LoadModel(void);
	static void UnloadModel(void);
	static HRESULT LoadTex(void);
	static void UnloadTex(void);

	static LPD3DXMESH GetMesh(int nIdx);
	static LPD3DXBUFFER GetBuffMat(int nIdx);
	static DWORD GetNumMat(int nIdx);
	static LPDIRECT3DTEXTURE9 GetTexture(int nIdx);

private:
	static LPDIRECT3DTEXTURE9	*m_pTexture;					// �e�N�X�`���ւ̃|�C���^
	static LPD3DXMESH		*m_pMesh;		// ���b�V�����i���_���j�ւ̃|�C���^
	static LPD3DXBUFFER		*m_pBuffMat;		// �}�e���A�����ւ̃|�C���^
	static DWORD			*m_nNumMat;		// �}�e���A�����̐�
	static const char *m_apModelFilename[];
	static const char *m_apTexFilename[];
};

#endif