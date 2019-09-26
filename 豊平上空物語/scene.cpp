//=============================================================================
//
// �V�[������ [scene.h]
// Author : ���R���
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "debugProc.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
int CScene::m_nNumAll = 0;
int CScene::m_nNumPriority[NUM_PRIORITY] = {};
CScene *CScene::m_apTop[NUM_PRIORITY] = {};
CScene *CScene::m_apCur[NUM_PRIORITY] = {};

//=============================================================================
// �V�[���N���X�̃R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority, OBJTYPE objType)
{
	// �l�̃N���A
	m_nID = 0;
	m_pPrev = NULL;
	m_pNext = NULL;
	m_bDeath = false;
	
	if (m_apCur[nPriority] == NULL)
	{// �J�����g��NULL�Ȃ猻�݂̈ʒu���擪
		m_apTop[nPriority] = this;
	}
	else
	{// �J�����g��NULL����Ȃ�������
	 // �O���Scene��m_pNext�ɍ������Scene������
		m_apCur[nPriority]->m_pNext = this;
	}

	m_pPrev = m_apCur[nPriority];	// �������Scene��m_pPrev�ɑO���Scene������
	m_pNext = NULL;					// ���̃V�[���͂܂�����Ă��Ȃ�����NULL
	m_apCur[nPriority] = this;		// �J�����g�̈ʒu���������Scene�Ɉړ�����
	m_nPriority = nPriority;		// �v���C�I���e�B��ۑ�
	m_objType = objType;			// �I�u�W�F�N�g�̎�ނ�ۑ�
	m_nNumPriority[nPriority]++;

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
// �S�ẴI�u�W�F�N�g�̉������
//=============================================================================
void CScene::ReleseAll(void)
 {
	CScene *pScene = NULL;

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{// �D�揇�ʂ̐����J��Ԃ�
		// �擪���擾����
		pScene = m_apTop[nCntPriority];

		while (pScene != NULL)
		{// ��ɂȂ�܂ŃA�b�v�f�[�g����
		 // Update�̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
			CScene *pSceneNext = pScene->m_pNext;

			// �X�V
			pScene->Uninit();

			// ���̃V�[���ɐi�߂�
			pScene = pSceneNext;
		}
	}

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{// �D�揇�ʂ̐����J��Ԃ�
		pScene = m_apTop[nCntPriority];

		while (pScene != NULL)
		{
			// Update�̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
			CScene *pSceneNext = pScene->m_pNext;

			if (pScene->m_bDeath == true)
			{
				// �t���O�������Ă���I�u�W�F�N�g�������Ă���
				pScene->DeleteAll();
			}

			// ���̃V�[���ɐi�߂�
			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// �S�ẴI�u�W�F�N�g�̍X�V����
//=============================================================================
void CScene::UpdeteAll(void)
{
	CScene *pScene = NULL;

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{// �D�揇�ʂ̐����J��Ԃ�
		// �擪���擾����
		pScene = m_apTop[nCntPriority];

		while (pScene != NULL)
		{// ��ɂȂ�܂ŃA�b�v�f�[�g����

			// Update�̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
			CScene *pSceneNext = pScene->m_pNext;

			// �X�V
			pScene->Update();

			// ���̃V�[���ɐi�߂�
			pScene = pSceneNext;
		}
	}

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{// �D�揇�ʂ̐����J��Ԃ�
		pScene = m_apTop[nCntPriority];

		while (pScene != NULL)
		{
			// Update�̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
			CScene *pSceneNext = pScene->m_pNext;

			if (pScene->m_bDeath == true)
			{
				// �t���O�������Ă���I�u�W�F�N�g�������Ă���
				pScene->DeleteAll();
			}

			// ���̃V�[���ɐi�߂�
			pScene = pSceneNext;
		}
	}

#ifdef _DEBUG
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{// �D�揇�ʂ̐����J��Ԃ�
		// �f�o�b�N�\���̍X�V
		CDebugProc::Print("ncn", nCntPriority, " : ", m_nNumPriority[nCntPriority]);
	}
#endif
}

//=============================================================================
// �S�ẴI�u�W�F�N�g�̕`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	CScene *pScene = NULL;

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{// �D�揇�ʂ̐����J��Ԃ�
		// �擪�̏ꏊ���擾
		pScene = m_apTop[nCntPriority];

		while (pScene != NULL)
		{// ��ɂȂ�܂ŕ`�悷��
			// Draw�̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
			CScene *pSceneNext = pScene->m_pNext;

			// �`��
			pScene->Draw();

			// ���̃V�[���ɐi�߂�
			pScene = pSceneNext;
		}
	}

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{// �D�揇�ʂ̐����J��Ԃ�
		pScene = m_apTop[nCntPriority];

		while (pScene != NULL)
		{
			// Update�̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
			CScene *pSceneNext = pScene->m_pNext;

			if (pScene->m_bDeath == true)
			{
				// �t���O�������Ă���I�u�W�F�N�g�������Ă���
				pScene->DeleteAll();
			}

			// ���̃V�[���ɐi�߂�
			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�̉������
//=============================================================================
void CScene::Release(void)
{
	// ���S�t���O�𗧂Ă�
	m_bDeath = true;
}

//=============================================================================
// �t���O���������I�u�W�F�N�g�̉������
//=============================================================================
void CScene::DeleteAll(void)
{
	int nPriority;
	nPriority = m_nPriority;

	// ������I�u�W�F�N�g�̑O�����邩�ǂ���
	if (m_pPrev == NULL)
	{// �O�����Ȃ���
	 // �擪�����ɂ��炷
		m_apTop[nPriority] = m_pNext;
	}
	else
	{// �O�����鎞
	 // �O�̃I�u�W�F�N�g�ɂ��鎩���̏������̃I�u�W�F�N�g�ɓn��
		m_pPrev->m_pNext = m_pNext;
	}

	// ������I�u�W�F�N�g�̎������邩�ǂ���
	if (m_pNext == NULL)
	{// �������Ȃ���
	 // ���݁i�Ō���j�̃I�u�W�F�N�g��O�̃I�u�W�F�N�g�ɓn��
		m_apCur[nPriority] = m_pPrev;
	}
	else
	{// �������鎞
	 // ���ɂ���I�u�W�F�N�g�ɂ��鎩���̏���O�̃I�u�W�F�N�g�ɓn��
		m_pNext->m_pPrev = m_pPrev;
	}

	// ����������
	delete this;

	m_nNumPriority[nPriority]--;
}

//=============================================================================
// �I�u�W�F�N�g�̎�ނ̐ݒ�
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//=============================================================================
// �I�u�W�F�N�g�̎�ނ̎擾
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//=============================================================================
// �D�揇�ʂ̎擾
//=============================================================================
int CScene::GetPriority(void)
{
	return m_nPriority;
}

//=============================================================================
// �D�揇�ʂ̐ݒ�
//=============================================================================
void CScene::SetPriority(int nPriority)
{
	m_nPriority = nPriority;
}

//=============================================================================
// �擪�̃I�u�W�F�N�g���擾
//=============================================================================
CScene *CScene::GetTop(int nPriority)
{
	return m_apTop[nPriority];
}

//=============================================================================
// ���̃I�u�W�F�N�g�̃|�C���^���擾
//=============================================================================
CScene *CScene::GetNext(void)
{
	return m_pNext;
}

//=============================================================================
// ���S�t���O���擾
//=============================================================================
bool CScene::GetDeath(void)
{
	return m_bDeath;
}