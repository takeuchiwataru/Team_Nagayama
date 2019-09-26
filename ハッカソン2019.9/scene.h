//=============================================================================
//
// �V�[������ [scene.h]
// Author : ���R���
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_OBJECT				(1024)	// �e�N�X�`���̐�
#define NUM_PRIORITY			(8)		// �D�揇�ʂ̐�
#define SCENEOBJ_PRIORITY		(2)		// �ݒu����I�u�W�F�N�g�̗D�揇��
#define OBJ_PRIORITY			(4)		// �I�u�W�F�N�g�̗D�揇��
#define OBSTACLE_PRIORITY		(3)		// ��Q���̗D�揇��
#define GOAL_PRIORITY			(1)		// �S�[���̗D�揇��
#define SCENEX_PRIORITY			(2)		// ���f���̗D�揇��
#define MESHFIELD_PRIORITY		(3)		// ���b�V���t�B�[���h�̗D�揇��
#define POLYGON_PRIORITY		(3)		// ���̗D�揇��
#define SCENE3D_PRIORITY		(3)		// ��̗D�揇��
#define	PLAYER_PRIORITY			(5)		// �v���C���[�̗D�揇��
#define	SHADOW_PRIORITY			(6)		// �e�̗D�揇��
#define	PARTICLE_PRIORITY		(5)		// �p�[�e�B�N���̗D�揇��
#define COIN_PRIORITY			(4)		// �R�C���̗D�揇��
#define LOGO_PRIORITY			(6)		// ���S�̗D�揇��
#define LOGOBACK_PRIORITY		(4)		// �w�i���S�̗D�揇��
#define HOLE_PRIORITY			(4)		// �n�ʑS�̗̂D�揇��
#define TUTORIALLOGO_PRIORITY	(3)		// �`���[�g���A�����S�̗D�揇��
#define GEM_PRIORITY			(4)
#define BLOCKPOS_PRIORITY		(6)
#define BULLET_PRIORITY			(5)
#define HEALTH_PRIORITY			(5)

//========================================
// �N���X�̒�`
//========================================
//=====================
// �I�u�W�F�N�g�N���X
//=====================
class CScene
{
public:
	typedef enum
	{// �I�u�W�F�N�g�̎��
		OBJTYPE_NONE = 0,
		OBJTYPE_SCENE2D,	// 2D�|���S��
		OBJTYPE_SCENE3D,	// 3D�|���S��
		OBJTYPE_SCENEX,		// ���f��
		OBJTYPE_POLYGON,	// �|���S��
		OBJTYPE_FIELD,	// �n��
		OBJTYPE_BILLBOARD,	// �r���{�[�h
		OBJTYPE_LOGO,		// ���S
		OBJTYPE_LOGOBACK,		// �w�i���S
		OBJTYPE_MESHFIELD,	// ���b�V���t�B�[���h
		OBJTYPE_MESHCYLINDER,	// ���b�V���V�����_�[
		OBJTYPE_PLAYER,		// �v���C���[
		OBJTYPE_BLOCK,		// �u���b�N
		OBJTYPE_WOODBLOCK,	// �؃u���b�N
		OBJTYPE_IRONBLOCK,		// �S���b�N
		OBJTYPE_GOAL,		// �S�[��
		OBJTYPE_COIN,		// �R�C��
		OBJTYPE_GEM,		// ���
		OBJTYPE_OBSTACLE,	// ��Q��
		OBJTYPE_PAUSE,		// �|�[�Y
		OBJTYPE_SCORE,		// �X�R�A
		OBJTYPE_NUMBLOCK,		// �u���b�N�̐�
		OBJTYPE_PARTICLE,	// �p�[�e�B�N��
		OBJTYPE_PEBBLE,		// ����
		OBJTYPE_SETOBJECT,	// �ݒu����I�u�W�F�N�g
		OBJTYPE_OBJECT,		// �؂�ւ��I�u�W�F�N�g
		OBJTYPE_BLOCKPOS,		// �u���b�N�̏o���ʒu
		OBJTYPE_SHADOW,		// �e
		OBJTYPE_BULLET,		// �e
		OBJTYPE_EFFECT,		// �e
		OBJTYPE_MAX			// ����
	} OBJTYPE;

	CScene(int nPriority = 3, OBJTYPE objType = OBJTYPE_NONE);	// �R���X�g���N�^
	virtual ~CScene();											// �f�X�g���N�^

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void ReleseAll(void);								// �S�ẴI�u�W�F�N�g�̉��
	static void UpdeteAll(void);								// �S�ẴI�u�W�F�N�g�̍X�V
	static void DrawAll(void);									// �S�ẴI�u�W�F�N�g�̕`��
	static CScene *GetTop(int nPriority);						// �擪�̃I�u�W�F�N�g���擾
	CScene *GetNext(void);										// ���̃I�u�W�F�N�g�̃|�C���^���擾
	bool GetDeath(void);										// ���S�t���O���擾
	void SetObjType(OBJTYPE objType);							// �I�u�W�F�N�g�̎�ނ̐ݒ�
	OBJTYPE GetObjType(void);									// �I�u�W�F�N�g�̎�ނ̎擾
	int GetPriority(void);										// �D�揇�ʂ̎擾
	void SetPriority(int nPriority);							// �D�揇�ʂ̐ݒ�

protected:
	void Release(void);											// ���S�t���O�𗧂Ă�

private:
	void DeleteAll(void);										// ���S�t���O���������I�u�W�F�N�g������

	static CScene *m_apTop[NUM_PRIORITY];						// �擪�I�u�W�F�N�g�ւ̃|�C���^
	static CScene *m_apCur[NUM_PRIORITY];						// ���݁i�Ō���j�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pPrev;											// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pNext;											// ���̃I�u�W�F�N�g�ւ̃|�C���^
	bool m_bDeath;												// ���S�t���O
	static int m_nNumAll;										// �G�̑��� �w�ÓI�����o�ϐ��x
	int m_nID;													// �������g��ID
	int m_nPriority;											// �D�揇�ʂ̔ԍ�
	static int m_nNumPriority[NUM_PRIORITY];					// ���̗D�揇�ʂɂ���I�u�W�F�N�g�̐�
	OBJTYPE m_objType;											// �I�u�W�F�N�g�̎��
};

#endif