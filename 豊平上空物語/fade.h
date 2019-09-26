//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : ���R���
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "manager.h"
#include "scene2D.h"

//========================================
// �N���X�̒�`
//========================================
//=====================
// �t�F�[�h�N���X
//=====================
class CFade
{
public:
	typedef enum
	{// �t�F�[�h�̏��
		FADE_NONE = 0,												// �������Ă��Ȃ����
		FADE_IN,													// �t�F�[�h�C�����
		FADE_OUT,													// �t�F�[�h�A�E�g���
		FADE_MAX
	} FADE;

	CFade();	// �R���X�g���N�^
	~CFade();														// �f�X�g���N�^

	static CFade *Create();					// �I�u�W�F�N�g�̐���

	HRESULT Init(D3DXVECTOR3 pos);		// �t�F�[�h����������
	void Uninit(void);												// �t�F�[�h�I������
	void Update(void);												// �t�F�[�h�X�V����
	void Draw(void);												// �t�F�[�h�`�揈��
	static FADE GetFade(void);										// �t�F�[�h�̎擾
	static void SetFade(CManager::MODE modeNext, FADE fade);		// �t�F�[�h�̎擾

private:
	//LPDIRECT3DTEXTURE9		m_pTexture;								// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;								// ���_�o�b�t�@�ւ̃|�C���^
	static FADE m_fade;												// �t�F�[�h���
	static CManager::MODE m_modeNext;
	static D3DXCOLOR m_colorFade;
};

#endif