//=============================================================================
//
// �c�@���� [life.h]
// Author : ���R���
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_NUMLIFE	(1)	// �e�N�X�`���̐�

//=============================================================================
// �O���錾
//=============================================================================
class CNumber;

//========================================
// �N���X�̒�`
//========================================
//=====================
// �c�@�̐��N���X
//=====================
class CLife : public CScene
{
public:
	CLife(int nPriority = 5, OBJTYPE objType = OBJTYPE_SCORE);	// �R���X�g���N�^
	~CLife();													// �f�X�g���N�^

	static CLife *Create(D3DXVECTOR3 pos, float fSize);

	HRESULT Init(void);							// �c�@�̐��̏���������
	void Uninit(void);							// �c�@�̐��̏I������
	void Update(void);							// �c�@�̐��̍X�V����
	void Draw(void);							// �c�@�̐��̕`�揈��

	void SetLife(int nScore);					// �c�@�̐��̐ݒ�
	int GetLife(void);							// �c�@�̐��̎擾
	void AddLife(int nValue);					// �c�@�̐����Z
	void SetColor(D3DXCOLOR color);				// �F�̐ݒ�

private:
	CNumber *m_apLife[MAX_NUMLIFE];
	D3DXVECTOR3 m_pos;
	int m_nNumLife;
	float m_fSize;
};

#endif