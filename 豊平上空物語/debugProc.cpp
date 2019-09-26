//=============================================================================
//
// �f�o�b�N�\������ [debugProc.cpp]
// Author : ���R���
//
//=============================================================================
#include "debugProc.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPD3DXFONT CDebugProc::m_pFont = NULL;
char CDebugProc::m_aStr[1024] = {};

//=============================================================================
// �f�o�b�N�\���N���X�̃R���X�g���N�^
//=============================================================================
CDebugProc::CDebugProc()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CDebugProc::~CDebugProc()
{
}

//=============================================================================
// �f�o�b�N�\���̏���������
//=============================================================================
void CDebugProc::Init(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

}

//=============================================================================
// �f�o�b�N�\���̏I������
//=============================================================================
void CDebugProc::Uninit(void)
{
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}

//=============================================================================
// �f�o�b�N�\���̕\������
//=============================================================================
void CDebugProc::Print(char *fmt, ...)
{
	int nNum = 0;
	double fNum = 0.0f;
	char cNum[1024];

	// �C�ӌ̈������P�̕ϐ��ɕϊ�
	va_list ap;

	// �ϒ��������P�̕ϐ��ɂ܂Ƃ߂�
	va_start(ap, fmt);

	while (*fmt)
	{
		switch (*fmt)
		{
		case 'c':	// char�^
			strcat(m_aStr, va_arg(ap, char*));	// ���X�g�̒��̃L�����^�����o���āAm_aStr�ɓ����
			break;

		case 'n':	// int�^
			nNum = va_arg(ap, int);		// ���X�g�̒���int�^�����������o��

			sprintf(cNum, "%d", nNum);	// %d�ɓ���int�^��cNum�̃L�����^�ɓ����

			strcat(m_aStr, cNum);		// �����̃f�[�^��int�^�̐���������

			break;

		case 'f':	// float�^
			fNum = va_arg(ap, double);		// ���X�g�̒���float�^�����������o��

			sprintf(cNum, "%.1f", fNum);	// %.1f�ɓ���float�^��cNum�̃L�����^�ɓ����

			strcat(m_aStr, cNum);			// �����̃f�[�^��float�^�̐���������

			break;
		}

		fmt++;	// �t�H�[�}�b�g�̕������P�����i�߂�
	}


	strcat(m_aStr, "\n");

	va_end(ap);
}

//=============================================================================
// �f�o�b�N�\���̍폜����
//=============================================================================
void CDebugProc::ReleseStr(void)
{
	for (int nCntStr = 0; nCntStr < 1024; nCntStr++)
	{
		if (m_aStr[nCntStr] != NULL)
		{
			m_aStr[nCntStr] = NULL;
		}
	}
}

//=============================================================================
// �f�o�b�N�\���̕\������
//=============================================================================
void CDebugProc::Draw(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, m_aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}