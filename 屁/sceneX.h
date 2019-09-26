//=============================================================================
//
// 3D���f������ [sceneX.h]
// Author : ���R���
//
//=============================================================================
#ifndef _SCENEX_H_
#define _SCENEX_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//========================================
// �N���X�̒�`
//========================================
//=====================
// �I�u�W�F�N�g�N���X
//=====================
class CSceneX : public CScene
{
public:
	CSceneX(int nPriority = SCENEX_PRIORITY, OBJTYPE objType = OBJTYPE_SCENEX);					// �R���X�g���N�^
	~CSceneX();									// �f�X�g���N�^

	HRESULT Init(void);				// 3D�I�u�W�F�N�g����������
	void Uninit(void);							// 3D�I�u�W�F�N�g�I������
	void Update(void);							// 3D�I�u�W�F�N�g�X�V����
	void Draw(void);							// 3D�I�u�W�F�N�g�`�揈��

	static CSceneX *Create(D3DXVECTOR3 pos);	// �I�u�W�F�N�g�̐���

	D3DXVECTOR3 GetPosition(void);						// �ʒu�̎擾
	void SetPosition(D3DXVECTOR3 pos);					// �ʒu�̐ݒ�

	D3DXVECTOR3 GetRot(void);						// �����̎擾
	void SetRot(D3DXVECTOR3 rot);					// �����̐ݒ�

	D3DXVECTOR3 GetVtxMax(void);						// �ő�l�̎擾
	void SetVtxMax(D3DXVECTOR3 VtxMax);					// �ő�l�̐ݒ�

	D3DXVECTOR3 GetVtxMin(void);						// �ŏ��l�̎擾
	void SetVtxMin(D3DXVECTOR3 VtxMin);					// �ŏ��l�̐ݒ�

	D3DXMATRIX GetMtxWorld(void);						// ���[���h�}�g���b�N�X�擾
	void SetMtxWorld(D3DXMATRIX mtxWorld);				// ���[���h�}�g���b�N�X�̐ݒ�

	void BindModel(LPD3DXBUFFER pBuffMat, DWORD nNumMat, LPD3DXMESH pMesh);	// ���f�������蓖�Ă�
	void BindMat(LPDIRECT3DTEXTURE9	*m_pTexture);	// �e�N�X�`���}�e���A�������蓖�Ă�

	bool Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius);	// �����蔻��
	void SetVtx(void);																// ���_���W�̐ݒ�

private:
	LPDIRECT3DTEXTURE9		*m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	LPD3DXMESH				m_pMesh;			// ���b�V�����i���_���j�ւ̃|�C���^
	LPD3DXBUFFER			m_pBuffMat;			// �}�e���A�����ւ̃|�C���^
	D3DXMATRIX				m_mtxWorld;			// ���[���h�}�g���b�N�X
	DWORD					m_nNumMat;			// �}�e���A�����̐�
	D3DXVECTOR3				m_VtxMin, m_VtxMax;	// ���f���̍ŏ��l�A�ő�l
	
	D3DXVECTOR3				m_pos;				// �|���S���̈ʒu
	D3DXVECTOR3				m_rot;				// ������x�N�g��
};

#endif