//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

class CSound
{
public:
	//*************************************
	// �T�E���h�t�@�C��
	//*************************************
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,	// BGM0 (OP)
		SOUND_LABEL_BGM_TUTORIAL,	// BGM1	(TUTORIAL)
		SOUND_LABEL_BGM_TUTORIAL0,	// BGM1	(TUTORIAL)
		SOUND_LABEL_BGM_RESULTCLEAR,		// BGM3	(RESULT)
		SOUND_LABEL_BGM_RESULTOVER,		// BGM3	(RESULT)
		SOUND_LABEL_BGM_RANKING,	// BGM4	(RANKING)

		SOUND_LABEL_SE_BREAK,		// �u���b�N�j��
		SOUND_LABEL_SE_BLOCKSET,	// �u���b�N�ݒu��
		SOUND_LABEL_SE_IRON,		// �S�u���b�N��
		SOUND_LABEL_SE_JUMP,		// �W�����v��
		SOUND_LABEL_SE_COIN,		// �R�C����
		SOUND_LABEL_SE_ENTER,		// ���艹
		SOUND_LABEL_SE_SELECT,		// �Z���N�g��
		SOUND_LABEL_SE_SELECTENTER,	// �Z���N�g����
		SOUND_LABEL_SE_PAUSE,		// �|�[�Y��
		SOUND_LABEL_SE_TIMEGEM,		// ����悤�ɂȂ������̉�
		SOUND_LABEL_SE_WATER,		// ���ɗ��������̉�
		SOUND_LABEL_SE_ATTACK,		// ���ɗ��������̉�
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//*****************************************************************************
	// �p�����[�^�\���̒�`
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
	} SOUNDPARAM;

	CSound();
	~CSound();
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X�ւ̃|�C���^
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X�ւ̃|�C���^
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�ւ̃|�C���^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

	// �e���f�ނ̃p�����[�^
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{
		{ "data/BGM/title.wav", -1 },		// BGM0 (OP)
		{ "data/BGM/GameBgm.wav", -1 },	// BGM1	(TUTORIAL / GAME)
		{ "data/BGM/tutorial.wav", -1 },	// BGM1	(TUTORIAL / GAME)
		{ "data/BGM/gameclear.wav", -1 },		// BGM3	(RESULT)
		{ "data/BGM/gameover.wav", -1 },		// BGM4	(RESULT)
		{ "data/BGM/ranking.wav", -1 },		// BGM4	(RANKING)

		{ "data/SE/break000.wav", 0 },		// �u���b�N�j��
		{ "data/SE/blockset.wav", 0 },		// �u���b�N�ݒu��
		{ "data/SE/iron.wav", 0 },			// �S�u���b�N�ݒu��
		{ "data/SE/jump000.wav", 0 },		// �W�����v��
		{ "data/SE/coin.wav", 0 },			// �R�C����
		{ "data/SE/enter000.wav", 0 },		// �R�C����
		{ "data/SE/select.wav", 0 },			// �Z���N�g��
		{ "data/SE/selectEnter.wav", 0 },	// �Z���N�g����
		{ "data/SE/pause.wav", 0 },			// �|�[�Y��
		{ "data/SE/timegem.wav", 0 },			// ��΂�����悤�ɂȂ������̉�
		{ "data/SE/water.wav", 0 },			// ���ɗ��������̉�
		{ "data/SE/attack.wav", 0 },			// ���ɗ��������̉�
	};
};
#endif
