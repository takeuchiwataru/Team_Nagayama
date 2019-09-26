//=============================================================================
//
// �~���̃|���S������ [meshCylinder.h]
// Author :  ���R���
//
//=============================================================================
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHCYLINDER_TEXTURENAME		 "data\\TEXTURE\\sky.jpg"	//�e�N�X�`���̃t�@�C����
#define TEX_POS_X_INIT			(1.0f)								//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)								//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)								//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)								//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)								//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)								//�e�N�X�`�����WV��
#define FIELD_SIZE				(400.0f)							//�n�ʂ̑傫��
#define X_CYLINDERPOSSIZE		(100)								//X�̑傫��
#define Y_CYLINDERPOSSIZE		(100)								//Z�̑傫��
#define CYLINDER_X				(60)								// �|���S���̐��iX�j
#define CYLINDER_Y				(200)									// �|���S���̐��iZ�j
#define NUM_CYLINDER_POLYGON				(10000)							// ���b�V���t�B�[���h�̑傫��

//========================================
// �N���X�̒�`
//========================================
//=========================
// ���b�V���V�����_�[�N���X
//=========================
class CMeshCylinder : public CScene
{
public:
	CMeshCylinder(int nPriority = 3, OBJTYPE objType = OBJTYPE_MESHCYLINDER);	// �R���X�g���N�^
	~CMeshCylinder();														// �f�X�g���N�^

	static CMeshCylinder *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);							// �I�u�W�F�N�g�̐���

	HRESULT Init(void);													// ���b�V���V�����_�[����������
	void Uninit(void);													// ���b�V���V�����_�[�I������
	void Update(void);													// ���b�V���V�����_�[�X�V����
	void Draw(void);													// ���b�V���V�����_�[�`�揈��

	void SetNor(void);													// �@���̐ݒ�

private:
	LPDIRECT3DTEXTURE9		m_pTexture;									// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;									// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;									// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX				m_mtxWorld;									// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_pos;										// �|���S���̈ʒu
	D3DXVECTOR3				m_rot;										// �|���S���̌���
	D3DXVECTOR3				m_aNor[NUM_CYLINDER_POLYGON];
	float m_fSizeX;
	float m_fSizeY;
	int						m_nNumVerTex;								// ���_��
	int						m_nNumIndex;								// �C���f�b�N�X��
	int						m_nNumPolygon;								// �|���S����
	bool					m_bLand;									// �|���S���ɏ���Ă���
};

#endif
