//=============================================================================
//
// ���S�̏��� [logo.h]
// Author : ���R���
//
//=============================================================================
#ifndef _LOGO_H_
#define _LOGO_H_

#include "main.h"
#include "scene.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RESULT_LOGO_NAME		"data/TEXTURE/resultLogo.png"		// ���U���g���S�̃e�N�X�`����
#define PRESSENTER_LOGO_NAME	"data/TEXTURE/press_enter.png"		// �v���X�G���^�[���S�̃e�N�X�`����
#define RANKING_NUMBER_NAME		"data/TEXTURE/RANKING/ranking.png"			// �v���X�G���^�[���S�̃e�N�X�`����
#define A_LOGO_NAME				"data/TEXTURE/ALogo.png"			// �v���XA���S�̃e�N�X�`����
#define PICKUP_LOGO_NAME		"data/TEXTURE/pickup.png"			// �s�b�N�A�b�v���S�̃e�N�X�`����
#define SCOREUP_LOGO_NAME		"data/TEXTURE/ScoreUp.png"			// �X�R�A�A�b�v���S�̃e�N�X�`����
#define GAMESTART_LOGO_NAME		"data/TEXTURE/GameStart.png"		// �Q�[���X�^�[�g���S�̃e�N�X�`����
#define STARTSKIP_LOGO_NAME		"data/TEXTURE/startskip.png"		// �X�^�[�g�X�L�b�v���S�̃e�N�X�`����

//========================================
// �N���X�̒�`
//========================================
//=====================
// ���S�N���X
//=====================
class CLogo : public CScene
{
public:
	CLogo(int nPriority = LOGO_PRIORITY, OBJTYPE objType = OBJTYPE_LOGO);			// �R���X�g���N�^
	~CLogo();															// �f�X�g���N�^

	void BindTexture(LPDIRECT3DTEXTURE9	Texture);						// ���L�e�N�X�`�������蓖�Ă�

	virtual HRESULT Init(void);											// ���S����������
	virtual void Uninit(void);											// ���S�I������
	virtual void Update(void);											// ���S�X�V����
	virtual void Draw(void);											// ���S�`�揈��
	void SetCol(D3DXCOLOR col);											// ���S�̐F�̐ݒ�

	D3DXVECTOR3 GetPosition(void);										// �ʒu�̎擾
	void SetPosition(D3DXVECTOR3 pos);									// �ʒu�̐ݒ�
	float GetWidth(void);												// ���̎擾
	void SetWidth(float fWidth);										// ���̐ݒ�
	float GetHeight(void);												// �����̎擾
	void SetHeight(float fHeight);										// �����̐ݒ�

private:
	LPDIRECT3DTEXTURE9		m_pTexture;									// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				m_Pos;										// �|���S���̈ʒu
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;									// ���_�o�b�t�@�ւ̃|�C���^
	float					m_fWidth;									// �I�u�W�F�N�g�̕�
	float					m_fHeight;									// �I�u�W�F�N�g�̍���
};

#endif