//=============================================================================
//
// �ǂ̏��� [billboard.h]
// Author :  ���R���
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BILLBOARD_TEXTURENAME	 "data\\TEXTURE\\tree000.png"	//�e�N�X�`���̃t�@�C����
#define TEX_POS_X_INIT			(1.0f)							//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)							//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)							//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)							//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)							//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)							//�e�N�X�`�����WV��

//========================================
// �N���X�̒�`
//========================================
//=====================
// �I�u�W�F�N�g�N���X
//=====================
class CBillboard : public CScene
{
public:
	CBillboard(int nPriority = 3, OBJTYPE objType = OBJTYPE_BILLBOARD);	// �R���X�g���N�^
	~CBillboard();														// �f�X�g���N�^

	HRESULT Init(void);													// 3D�I�u�W�F�N�g����������
	void Uninit(void);													// 3D�I�u�W�F�N�g�I������
	void Update(void);													// 3D�I�u�W�F�N�g�X�V����
	void Draw(void);													// 3D�I�u�W�F�N�g�`�揈��

	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void);							// ���_�o�b�t�@�̎擾
	void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 VtxBuff);	// ���_�o�b�t�@�̐ݒ�

	D3DXVECTOR3 GetPosition(void);						// �ʒu���擾
	void SetPosition(D3DXVECTOR3 pos);					// �ʒu��ݒ�
	D3DXVECTOR3 GetRot(void);						// �������擾
	void SetRot(D3DXVECTOR3 rot);					// ������ݒ�
	float GetWidth(void);													// �����擾
	void SetWidth(float fWidth);											// ����ݒ�
	float GetHeight(void);													// �������擾
	void SetHeight(float fHeight);											// ������ݒ�

	void SetCol(D3DXCOLOR col);												// �F�̐ݒ�

	void BindTexture(LPDIRECT3DTEXTURE9	Texture);	// ���L�e�N�X�`�������蓖�Ă�

	static CBillboard *Create(D3DXVECTOR3 pos);							// �I�u�W�F�N�g�̐���
	void SetAnimation(int m_PatternAnim, float fUV_U, float fUV_V);

private:
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ��]
	D3DXMATRIX	m_mtxWorld;				// ���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9	m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	float m_fWidth;
	float m_fHeight;
};

#endif