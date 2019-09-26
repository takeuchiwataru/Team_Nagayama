//=============================================================================
//
// ��Q���̏��� [obstacle.h]
// Author : ���R���
//
//=============================================================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "main.h"
#include "sceneX.h"
//=============================================================================
// �O���錾
//=============================================================================

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_BULLET	(256)	// �e�̐�
#define TEX_POS_X_INIT			(1.0f)									//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)									//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)									//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)									//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)									//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)									//�e�N�X�`�����WV��

//========================================
// �N���X�̒�`
//========================================
//=====================
// �v���C���[�N���X
//=====================
class CObstacle : public CSceneX
{
public:
	CObstacle();	// �R���X�g���N�^
	~CObstacle();	// �f�X�g���N�^

	HRESULT Init(void);	// �v���C���[����������
	void Uninit(void);	// �v���C���[�I������
	void Update(void);	// �v���C���[�X�V����
	void Draw(void);	// �v���C���[�`�揈��

	static CObstacle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col);	// �I�u�W�F�N�g�̐���
	bool CollisionPlayer(D3DXVECTOR3 *pos, float fRadius);	// �����蔻��
	bool GetDestroy(void) { return m_bDestroy; }	// �����t���O�̎擾

private:
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ����
	D3DXVECTOR3 m_move;					// �ړ���
	D3DXCOLOR m_col;							// �F
	int m_nLife;
	bool m_bHit;	// �����������ǂ���
	bool m_bDestroy;	// �������ǂ���
	D3DXMATRIX				m_mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_VtxMin, m_VtxMax;	// �u���b�N�̍ŏ��l�A�ő�l
};

#endif