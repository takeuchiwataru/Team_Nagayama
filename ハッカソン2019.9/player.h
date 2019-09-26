//=============================================================================
//
// �v���C���[���� [player.h]
// Author : ���R���
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene.h"
#include "model.h"

//=============================================================================
// �O���錾
//=============================================================================
class CShadow;

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_PLAYER			(10)									//�v���C���[�̃p�[�c�̐�
#define PARTICLE_ROT		((rand() % 628) / 100.0f)				//�S����
#define PLAYER_HEIGHT		(50.0f)										// �v���C���[�̐g��
#define	MOTION_FILENAME		"data\\TEXT\\motion.txt"				// �c�[���̃e�L�X�g
#define	NUMMODEL			"NUM_MODEL = "							
#define	MODEL_FILE			"MODEL_FILENAME = "						
#define	CHARACTER_SET		"CHARACTERSET"							
#define	END_CHARACTER_SET	"END_CHARACTERSET"						
#define	NUM_PARTS			"NUM_PARTS = "							
#define	PARTSSET			"PARTSSET"								
#define	END_PARTSSET		"END_PARTSSET"							
#define	INDEX				"INDEX = "								
#define	PARENT				"PARENT = "								
#define	POS					"POS = "								
#define	ROT					"ROT = "								
#define	MOTIONSET			"MOTIONSET"								
#define	END_MOTIONSET		"END_MOTIONSET"							
#define	LOOP				"LOOP = "								
#define	NUM_KEY				"NUM_KEY = "							
#define	KEYSET				"KEYSET"								
#define	END_KEYSET			"END_KEYSET"							
#define	FRAME				"FRAME = "								
#define PLAYER_HEAD			"data\\MODEL\\gentleman\\head000.x"		// ���̃��f����
#define PLAYER_BODY			"data\\MODEL\\gentleman\\body001.x"		// �̂̃��f����
#define PLAYER_R_ARM		"data\\MODEL\\gentleman\\rightarm.x"	// �E�r�̃��f����
#define PLAYER_R_HAND		"data\\MODEL\\gentleman\\righthand.x"	// �E��̃��f����
#define PLAYER_L_ARM		"data\\MODEL\\gentleman\\leftarm.x"		// ���r�̃��f����
#define PLAYER_L_HAND		"data\\MODEL\\gentleman\\lefthand.x"	// ����̃��f����
#define PLAYER_R_LEG		"data\\MODEL\\gentleman\\rightleg.x"	// �E�ڂ̃��f����
#define PLAYER_R_FOOT		"data\\MODEL\\gentleman\\rightfoot.x"	// �E���̃��f����
#define PLAYER_L_LEG		"data\\MODEL\\gentleman\\leftleg.x"		// ���ڂ̃��f����
#define PLAYER_L_FOOT		"data\\MODEL\\gentleman\\leftfoot.x"	// �����̃��f����

//========================================
// �N���X�̒�`
//========================================
//=====================
// �v���C���[�N���X
//=====================
class CPlayer : public CScene
{
public:
	typedef enum
	{// �v���C���[�̏��
		STATE_NORMAL = 0,	// �ʏ���
		STATE_WALK,		// �ړ����
		STATE_BREAK,	// �j����
		STATE_UPBREAK,	// ��j����
		STATE_JUMP,		// �W�����v���
		STATE_BLOCK,	// �u���b�N�ݒu���
		STATE_LAND,		// ���n���
		STATE_MAX		// �v���C���[�̎�ނ̑���
	} STATE;

	typedef struct
	{// �L�[�v�f
		float fPosX;
		float fPosY;
		float fPosZ;
		float fRotX;
		float fRotY;
		float fRotZ;
	} KEY;

	typedef struct
	{
		int nFrame;				// �t���[����
		KEY aKey[MAX_PLAYER];
	} KEY_INFO;

	typedef struct
	{// ���[�V�������
		bool bLoop;						// ���[�v���邩���Ȃ���
		int nNumKey;					// �L�[�̐�
		KEY_INFO aKeyInfo[STATE_MAX];
	} MOTION_INFO;

	CPlayer();																							// �R���X�g���N�^
	~CPlayer();																							// �f�X�g���N�^

	HRESULT Init(void);																					// �v���C���[����������
	void Uninit(void);																					// �v���C���[�I������
	void Update(void);																					// �v���C���[�X�V����
	void Draw(void);																					// �v���C���[�`�揈��
	
	void SetVtx(void);																					// ���_���W�̐ݒ�
	void Move(void);																					// �v���C���[����������
	void Action(void);
	void Life(void);																					// �c�@����
	void Health(void);																					// �̗͏���
	void OnaraRemain(void);
	void SetBlock(void);																				// �u���b�N�̐ݒu
	bool GetRTriangle(void);																			// �E�̃|���S���ɏ���Ă��邩�ǂ������擾
	void UpdateMotion(void);																			// ���[�V�����̍X�V����
	static CPlayer *Create(D3DXVECTOR3 pos);															// �I�u�W�F�N�g�̐���
	void LoadMotion(void);																				// �����̃��[�h

	void CollisonAll(void);																				// �����蔻��
	void CollisonModel(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius);	// ���f���Ƃ̓����蔻��
	void CollisonCoin(D3DXVECTOR3 *pos, float fRadius);											// �R�C���̓����蔻��
	void CollisonPolygon(D3DXVECTOR3 *pos, D3DXVECTOR3 fRadius);											// �|���S���Ƃ̔���
	void CollisionField(void);																			// ���Ƃ̓����蔻��
	void CollisionGoal(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius);	// �S�[���Ƃ̓����蔻��
	void CollisonObstacle(D3DXVECTOR3 *pos, float fRadius);												// �e�Ƃ̔���

	D3DXVECTOR3 GetPos(void);																			// �ʒu�̎擾
	D3DXVECTOR3 *GetPosOld(void);																		// 1�t���[���O�̈ʒu���擾
	D3DXVECTOR3 GetMove(void);																			// �ړ��ʂ̎擾
	D3DXVECTOR3 GetRot(void);																			// �����̎擾
	void SetJump(bool bJump);																			// �v���C���[���W�����v���Ă��邩�ǂ�����ݒ�
	D3DXVECTOR3 GetBlockPos(void);																			// �u���b�N�̈ʒu�̎擾
	bool GetJump(void);																					// �v���C���[���W�����v���Ă��邩�ǂ������擾
	static bool GetGoal(void);																			// �v���C���[���S�[�����Ă��邩�ǂ������擾
	static bool GetGameOver(void);																		// �v���C���[���Q�[���I�[�o�[���ǂ������擾
	void SetState(STATE state);
	static void MinusNumBlock(void) { m_nNumBlock--; }

private:
	CModel					*m_apModel[MAX_PLAYER];
	static LPD3DXMESH		m_apMesh[MAX_PLAYER];									// ���b�V�����i���_���j�ւ̃|�C���^
	static LPD3DXBUFFER		m_apBuffMat[MAX_PLAYER];								// �}�e���A�����ւ̃|�C���^
	static DWORD			m_anNumMat[MAX_PLAYER];									// �}�e���A�����̐�
	static STATE m_State;															// �v���C���[�̏��
	static bool				m_bGoal;					// �S�[�����Ă��邩�ǂ���
	static bool				m_bGameOver;				// �Q�[���I�[�o�[���ǂ���
	static int				m_nNumBlock;				// �ݒu�����u���b�N�̐�
	static CShadow *m_pShadow;

	D3DXMATRIX				m_mtxWorld;					// ���[���h�}�g���b�N�X

	D3DXVECTOR3				m_move;						// �v���C���[�̈ړ���
	D3DXVECTOR3				m_pos;						// �v���C���[�̈ʒu
	D3DXVECTOR3				m_posOld;					// �v���C���[�̑O�̃t���[���̈ʒu
	D3DXVECTOR3				m_aPosOffset[MAX_PLAYER];	// ���f���̃I�t�Z�b�g
	D3DXVECTOR3				m_rot;						// �v���C���[�̌���
	D3DXVECTOR3				m_BlockPos;					// �u���b�N�̈ʒu�̕ۑ��p
	D3DXVECTOR3				m_SetBlockPos;				// �u���b�N��ݒu����ʒu
	float					m_fDestAngle;				// �ړI�̊p�x
	float					m_fDiffAngle;				// �p�x�̍���
	bool					m_bRTriangle;				// �E���ɂ��邩�ǂ���
	bool					m_bJump;					// �W�����v���Ă��邩�ǂ���
	bool					m_bLand;					// ���f���ɏ���Ă��邩�ǂ���
	bool					m_bPolygonLand;				// �n�ʂɏ���Ă��邩�ǂ���
	bool					m_bIronSound;				// �S�̉���炷���ǂ���
	bool					m_bWaterSound;				// ���̉���炷���ǂ���
	bool					m_bAttackSound;				// �U���̉���炷���ǂ���
	bool					m_bBulletHit;				// �e�Ɠ������Ă��邩
	int						m_nBulletTimer;				// ���G����
	int						m_nDisTimer;				// �_�ł����鎞��
	int						m_nNumParts;				// �p�[�c�̐�
	int						m_WalkTimer;				// �����Ă���Ƃ��ɏo��p�[�e�B�N���Ɏg��
	int						m_nLife;					// �c�@
	D3DXVECTOR3				m_aVtxMin[MAX_PLAYER], m_aVtxMax[MAX_PLAYER];			// �v���C���[�̍ŏ��l�A�ő�l
	int						m_nOnaraRemain;	// ���Ȃ�c�@

	KEY_INFO *m_pKeyInfo;								// �L�[���ւ̃|�C���^
	int m_nKey;											// ���݂̃L�[�i���o�[
	int m_nCountMotion;									// ���[�V�����J�E���^�[
	MOTION_INFO m_aMotionInfo[STATE_MAX];
};
#endif