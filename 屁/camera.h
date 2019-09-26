//=============================================================================
//
// �J�������� [camera.h]
// Author : ���R���
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//========================================
// �N���X�̒�`
//========================================
//=====================
// �J�����N���X
//=====================
class CCamera
{
public:

	CCamera();		// �R���X�g���N�^
	~CCamera();		// �f�X�g���N�^

	void Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	void PlayerCamera(void);
	void SetAngle(void);

	D3DXVECTOR3 GetRot(void);						// �ʒu�̎擾

private:
	D3DXVECTOR3 m_posV;				// ���_
	D3DXVECTOR3 m_posR;				// �����_
	D3DXVECTOR3 m_posVDest;			// �ړI�̎��_
	D3DXVECTOR3 m_posRDest;			// �ړI�̒����_
	D3DXVECTOR3 m_recU;				// ������x�N�g��
	D3DXVECTOR3 m_rot;				// ����
	D3DXVECTOR3 m_rotDest;			// �ڕW�̌���
	D3DXVECTOR3 m_DiffAngle;			// �p�x�̍���
	float m_fLength;				// �����_����̋���
	int m_nGemTimer;				// �J�������[�N�Ɏg���J�E���^�[
	//float fAngle;				
	D3DXMATRIX	m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX	m_mtxView;			// �r���[�}�g���b�N�X
};

#endif