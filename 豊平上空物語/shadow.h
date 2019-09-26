//=============================================================================
//
// �e����
// Author :  ���R���
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"
#include "scene.h"
#include "sceneX.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SHADOW	(124)	// �e�̍ő吔

//*********************************************************************
//�v���C���[�̉e�̒�`
//*********************************************************************
class CShadow : public CSceneX//�h���N���X
{
public:
	CShadow();
	~CShadow();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);
	static CShadow *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void UnLoad(void);

	//�����o�ϐ�
private:
	LPDIRECT3DVERTEXBUFFER9				m_pVtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
	static LPDIRECT3DTEXTURE9			m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	static LPD3DXMESH		m_pMesh;		// ���b�V�����i���_���j�ւ̃|�C���^
	static LPD3DXBUFFER		m_pBuffMat;		// �}�e���A�����ւ̃|�C���^
	static DWORD			m_nNumMat;		// �}�e���A�����̐�
	float								m_Height;
	D3DXVECTOR3							m_pos;							//�ʒu
	D3DXVECTOR3							m_rot;							//����
	D3DXCOLOR							m_col;
	D3DXMATRIX							m_mtxWorld;						//���[���h�}�g���b�N�X
};
#endif