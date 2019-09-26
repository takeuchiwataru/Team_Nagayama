//=============================================================================
//
// �S�[������ [goal.cpp]
// Author : ���R���
//
//=============================================================================
#include "goal.h"
#include "manager.h"
#include "debugProc.h"
#include "camera.h"
#include "scene3D.h"
#include "meshField.h"
#include "player.h"
#include "game.h"
#include "renderer.h"
#include "resource.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GOAL_SIZE	(5.0f)					// �S�[���̑傫���̔�����

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �S�[���N���X�̃R���X�g���N�^
//=============================================================================
CGoal::CGoal() : CSceneX(GOAL_PRIORITY)
{
	// �l���N���A
	m_pTexture = NULL;						// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMatrixIdentity(&m_mtxWorld);		// ���[���h�}�g���b�N�X
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGoal::~CGoal()
{
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CGoal *CGoal::Create(D3DXVECTOR3 pos)
{
	CGoal *pGoal = NULL;

	if (pGoal == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pGoal = new CGoal;

		if (pGoal != NULL)
		{
			pGoal->SetPosition(pos);
			pGoal->BindModel(CResource::GetBuffMat(CResource::MODEL_GOAL), CResource::GetNumMat(CResource::MODEL_GOAL), CResource::GetMesh(CResource::MODEL_GOAL));
			pGoal->Init();
		}
	}

	return pGoal;
}

//=============================================================================
// �S�[������������
//=============================================================================
HRESULT CGoal::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_GOAL);

	CSceneX::Init();

	return S_OK;
}

//=============================================================================
// �S�[���I������
//=============================================================================
void CGoal::Uninit(void)
{
	CSceneX::Uninit();

	// �v���C���[���̂̉��
	Release();
}

//=============================================================================
// �S�[���X�V����
//=============================================================================
void CGoal::Update(void)
{
}

//=============================================================================
// �S�[���`�揈��
//=============================================================================
void CGoal::Draw(void)
{
	CSceneX::Draw();
}

//=============================================================================
// �S�[���Ƃ̓����蔻�菈��
//=============================================================================
bool CGoal::Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius)
{
	bool bGoal = false;	// �S�[�����Ă��Ȃ����

	D3DXVECTOR3 GoalPos = CSceneX::GetPosition();
	D3DXVECTOR3 GoalMax = CSceneX::GetVtxMax();
	D3DXVECTOR3 GoalMin = CSceneX::GetVtxMin();

	if (pos->y <= GoalPos.y + GoalMax.y - GOAL_SIZE && pos->y + radius.y >= GoalPos.y + GoalMax.y - GOAL_SIZE
		|| pos->y + radius.y >= GoalPos.y + GoalMin.y && pos->y <= GoalPos.y + GoalMin.y
		|| pos->y + radius.y <= GoalPos.y + GoalMax.y - GOAL_SIZE && pos->y >= GoalPos.y + GoalMin.y)
	{// y�͈̔͂̒�
		if (pos->z - radius.z <= GoalPos.z + GoalMax.z && pos->z + radius.z >= GoalPos.z + GoalMin.z)
		{// z�͈̔͂̒�
			if (posOld->x + radius.x <= GoalPos.x + GoalMin.x
				&& pos->x + radius.x > GoalPos.x + GoalMin.x)
			{// X���W�̒��ɍ����������
				bGoal = true;
				pos->x = posOld->x;
				move->x = 0.0f;
			}
			else if (posOld->x - radius.x >= GoalPos.x + GoalMax.x
				&& pos->x - radius.x < GoalPos.x + GoalMax.x)
			{// X���W�̒��ɉE���������
				bGoal = true;
				pos->x = posOld->x;
				move->x = 0.0f;
			}
		}
		if (pos->x - radius.x <= GoalPos.x + GoalMax.x && pos->x + radius.x >= GoalPos.x + GoalMin.x)
		{// x�͈̔͂̒�
			if (posOld->z + radius.z <= GoalPos.z + GoalMin.z
				&& pos->z + radius.z > GoalPos.z + GoalMin.z)
			{// Z���W�̒��Ɏ�O���������
				bGoal = true;
				pos->z = posOld->z;
				move->z = 0.0f;
			}
			else if (posOld->z - radius.z >= GoalPos.z + GoalMax.z
				&& pos->z - radius.z < GoalPos.z + GoalMax.z)
			{// Z���W�̒��Ɍ�납�������
				bGoal = true;
				pos->z = posOld->z;
				move->z = 0.0f;
			}
		}
	}

	if (pos->x - radius.x < GoalPos.x + GoalMax.x - GOAL_SIZE && pos->x + radius.x > GoalPos.x + GoalMin.x + GOAL_SIZE
		&& pos->z - radius.z <= GoalPos.z + GoalMax.z - GOAL_SIZE && pos->z + radius.x >= GoalPos.z + GoalMin.z + GOAL_SIZE)
	{// ��Q���̓����ɏ����
		if (posOld->y >= GoalPos.y + GoalMax.y && pos->y < GoalPos.y + GoalMax.y
			|| pos->y <= GoalPos.y + GoalMax.y && posOld->y > GoalPos.y + GoalMax.y)
		{// �ォ��u���b�N�ɓ��������Ƃ�
			bGoal = true;
			pos->y = GoalPos.y + GoalMax.y;
			move->y = 0.0f;  // �ړ��ʂ��Ȃ���
		}

		if (posOld->y + radius.y < GoalPos.y + GoalMin.y && pos->y + radius.y >= GoalPos.y + GoalMin.y
			|| pos->y + radius.y > GoalPos.y + GoalMin.y && posOld->y + radius.y <= GoalPos.y + GoalMin.y)
		{// ������u���b�N�ɓ��������Ƃ�
			bGoal = true;
			pos->y = GoalPos.y + GoalMin.y - radius.y;
			move->y = 0.0f;  // �ړ��ʂ��Ȃ���
		}
	}

	return bGoal;	// �u���b�N�ɏ���Ă��邩�ǂ�����Ԃ�
}