//=============================================================================
//
// �X�|�b�g���C�g/�|�C���g���C�g���� [performLight.h]
// Author : ���R���
//
//=============================================================================
#ifndef _PERFORMLIGHT_H_
#define _PERFORMLIGHT_H_

#include "main.h"

//========================================
// �N���X�̒�`
//========================================
//=====================
// ���C�g�N���X
//=====================
class CPerformLight
{
public:
	typedef enum
	{// ���
		TYPE_POINT = 0,											// �X�|�b�g���C�g
		TYPE_SPOT,												// �|�C���g���C�g
		TYPE_MAX
	} TYPE;

	CPerformLight();											// �R���X�g���N�^
	~CPerformLight();											// �f�X�g���N�^

	static CPerformLight *Create(D3DXVECTOR3 pos, TYPE type);	// ���C�g�̐���

	void Init(void);											// ������
	void Uninit(void);											// �I��
	void Update(void);											// �X�V

private:
	D3DLIGHT9 m_light;											// ���C�g�̏��
	D3DXVECTOR3 m_pos;											// ���C�g�̈ʒu
	TYPE m_type;												// ���C�g�̎��
};

#endif