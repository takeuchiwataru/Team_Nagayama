//=============================================================================
//
// サウンド処理 [sound.h]
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
	// サウンドファイル
	//*************************************
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,	// BGM0 (OP)
		SOUND_LABEL_BGM_TUTORIAL,	// BGM1	(TUTORIAL)
		SOUND_LABEL_BGM_TUTORIAL0,	// BGM1	(TUTORIAL)
		SOUND_LABEL_BGM_RESULTCLEAR,		// BGM3	(RESULT)
		SOUND_LABEL_BGM_RESULTOVER,		// BGM3	(RESULT)
		SOUND_LABEL_BGM_RANKING,	// BGM4	(RANKING)

		SOUND_LABEL_SE_BREAK,		// ブロック破壊音
		SOUND_LABEL_SE_BLOCKSET,	// ブロック設置音
		SOUND_LABEL_SE_IRON,		// 鉄ブロック音
		SOUND_LABEL_SE_JUMP,		// ジャンプ音
		SOUND_LABEL_SE_COIN,		// コイン音
		SOUND_LABEL_SE_ENTER,		// 決定音
		SOUND_LABEL_SE_SELECT,		// セレクト音
		SOUND_LABEL_SE_SELECTENTER,	// セレクト決定
		SOUND_LABEL_SE_PAUSE,		// ポーズ音
		SOUND_LABEL_SE_TIMEGEM,		// 取れるようになった時の音
		SOUND_LABEL_SE_WATER,		// 水に落ちた時の音
		SOUND_LABEL_SE_ATTACK,		// 水に落ちた時の音
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//*****************************************************************************
	// パラメータ構造体定義
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント(-1でループ再生)
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

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2オブジェクトへのポインタ
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// マスターボイスへのポインタ
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイスへのポインタ
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータへのポインタ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

	// 各音素材のパラメータ
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{
		{ "data/BGM/title.wav", -1 },		// BGM0 (OP)
		{ "data/BGM/GameBgm.wav", -1 },	// BGM1	(TUTORIAL / GAME)
		{ "data/BGM/tutorial.wav", -1 },	// BGM1	(TUTORIAL / GAME)
		{ "data/BGM/gameclear.wav", -1 },		// BGM3	(RESULT)
		{ "data/BGM/gameover.wav", -1 },		// BGM4	(RESULT)
		{ "data/BGM/ranking.wav", -1 },		// BGM4	(RANKING)

		{ "data/SE/break000.wav", 0 },		// ブロック破壊音
		{ "data/SE/blockset.wav", 0 },		// ブロック設置音
		{ "data/SE/iron.wav", 0 },			// 鉄ブロック設置音
		{ "data/SE/jump000.wav", 0 },		// ジャンプ音
		{ "data/SE/coin.wav", 0 },			// コイン音
		{ "data/SE/enter000.wav", 0 },		// コイン音
		{ "data/SE/select.wav", 0 },			// セレクト音
		{ "data/SE/selectEnter.wav", 0 },	// セレクト決定
		{ "data/SE/pause.wav", 0 },			// ポーズ音
		{ "data/SE/timegem.wav", 0 },			// 宝石が取れるようになった時の音
		{ "data/SE/water.wav", 0 },			// 水に落ちた時の音
		{ "data/SE/attack.wav", 0 },			// 水に落ちた時の音
	};
};
#endif
