//=============================================================================
//
// �S�[������ [block.h]
// Author : ���R���
//
//=============================================================================
#ifndef _GOAL_H_
#define _GOAL_H_

#include "main.h"
#include "sceneX.h"

//========================================
// �N���X�̒�`
//========================================
//=====================
// �u���b�N�N���X
//=====================
class CGoal : public CSceneX
{
public:
	CGoal();								// �R���X�g���N�^
	~CGoal();								// �f�X�g���N�^

	HRESULT Init(void);						// �v���C���[����������
	void Uninit(void);						// �v���C���[�I������
	void Update(void);						// �v���C���[�X�V����
	void Draw(void);						// �v���C���[�`�揈��

	static CGoal *Create(D3DXVECTOR3 pos);	// �I�u�W�F�N�g�̐���

	bool Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius);	// �����蔻��

private:
	D3DXVECTOR3				m_rot;				// ����
	LPDIRECT3DTEXTURE9		m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX				m_mtxWorld;		// ���[���h�}�g���b�N�X
};

#endif