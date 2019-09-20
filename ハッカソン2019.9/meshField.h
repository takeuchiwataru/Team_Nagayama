//=============================================================================
//
// ���b�V���t�B�[���h�̏��� [meshFiled.h]
// Author : ���R���
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHFIELD_TEXTURE_NAME	"data\\TEXTURE\\soil.jpg"	// �n�ʂ̃e�N�X�`����
#define	SOIL_FILENAME			"data\\TEXT\\soil.bin"					// �c�[���̃e�L�X�g
#define POLYGON_X				(50)								// �|���S���̐��iX�j
#define POLYGON_Z				(50)							// �|���S���̐��iZ�j
#define MESHFIELD_SIZE			(35.0f)						// �|���S���̑傫��
#define MESHFIELD_WIDTH			(MESHFIELD_SIZE * POLYGON_X)	// ���b�V���t�B�[���h�̑傫��(��)
#define MESHFIELD_DEPTH			(MESHFIELD_SIZE * POLYGON_Z)	// ���b�V���t�B�[���h�̑傫��(���s)
#define NUM_POLYGON				(10000)							// ���b�V���t�B�[���h�̑傫��

//========================================
// �N���X�̒�`
//========================================
//=========================
// ���b�V���t�B�[���h�N���X
//=========================
class CMeshField : public CScene
{
public:
	CMeshField(int nPriority = MESHFIELD_PRIORITY, OBJTYPE objType = OBJTYPE_MESHFIELD);	// �R���X�g���N�^
	~CMeshField();														// �f�X�g���N�^

	static CMeshField *Create(D3DXVECTOR3 pos);							// �I�u�W�F�N�g�̐���

	HRESULT Init(void);													// ���b�V���t�B�[���h����������
	void Uninit(void);													// ���b�V���t�B�[���h�I������
	void Update(void);													// ���b�V���t�B�[���h�X�V����
	void Draw(void);													// ���b�V���t�B�[���h�`�揈��

	void SetNor(void);													// �@���̐ݒ�
	float GetHeight(D3DXVECTOR3 pos);									// �����̎擾
	bool GetLand(void);													// ����Ă��邩�ǂ����̎擾
	void LoadHeight(void);												// �����̃��[�h

private:
	LPDIRECT3DTEXTURE9		m_pTexture;									// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;									// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;									// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX				m_mtxWorld;									// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_pos;										// �|���S���̈ʒu
	D3DXVECTOR3				m_rot;										// �|���S���̌���
	D3DXVECTOR3				m_aNor[NUM_POLYGON];
	float					m_aHeight[POLYGON_Z + 1][POLYGON_X + 1];
	int						m_nNumVerTex;								// ���_��
	int						m_nNumIndex;								// �C���f�b�N�X��
	int						m_nNumPolygon;								// �|���S����
	bool					m_bLand;									// �|���S���ɏ���Ă���
};

#endif