/*
//=========================================
��SOUND�N���X�̎g����
//=========================================
1.�܂��Q�[���J�n���Ƀf�o�C�X�֌W������������
SOUND->Init(hwnd);

2.�Ȃ����[�h����B
SOUND->LoadWAVE( SOUND->Object[0], "Test.WAV" );

3.�Ȃ��Đ�����B
SOUND->Object[0]->Play(0,0,0);
Play������0���R�ɂ��Ă����B�iDirectX�̎d�l�j

4.�Ȃ̈ꎞ��~�B
SOUND->Object[0]->STOP();
�ꎞ��~�̂݁BPlay�֐����ĂԂƑ�������Đ������B

5.�ȃe���|�̕ύX�B
SOUND->Object[0]->SetFrequency( SOUND->Hz );//�ʏ�X�s�[�h
SOUND->Object[0]->SetFrequency( SOUND->Hz*2 );//��{����
SOUND->Object[0]->SetFrequency( SOUND->Hz/2 );//�����̑��x

6.���̑傫����ύX�B
SOUND->Object[0]->SetVolume( SOUND->Vol += 50 );//50%�傫��

7.�p����ύX�B
SOUND->Object[0]->SetPan( SOUND->Pan += 50 );//50%�傫��

8.�A���Đ������鏀���B
SOUND->ResetSuccession(0);//Object�O�Ԃ������̔z��ɃR�s�[�����B

9.�A���Đ��ɑΉ��B
SOUND->PlaySuccession(0);//
�Đ��v����������Object�O�Ԃ̋Ȃ�MUSIC_NUM_SUCCESSION��܂ōĐ��Ή��B
���Đ�������Object��SOUND->ResetSuccession���K������Ă��Ȃ����
�G���[�ƂȂ�B�P��ł����Ă���ΑO��SOUND->ResetSuccession�����Ȃ��Đ������B

10.�Ȃ�ς���B
2�ԂƓ����悤�Ɏw�肷�邾���B�t�@�C���̉����C���X�^���X�̔j����
��؂��Ȃ��Ă悢�B�܂��Đ����Ƀ��[�h���Ă��悢�B

11.�Q�[���I�����̏���
SOUND->DestoryDevice();//�T�E���h�f�o�C�X�̉���B



*/





#pragma once
#include<dsound.h>

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")
//#pragma comment(lib, "libcp.lib")

//=========================================
//���[�U���ݒ肷�ׂ��f�[�^
#define MUSIC_NUM 29//���p�������Ȑ�
#define MUSIC_NUM_SUCCESSION 15//�A���Đ��̋���
//=========================================




#define  SOUND SoundSingleton::GetInstance()//�C���X�^���X�擾�������̂ŏȗ��B

//��������OK----------------------------------------------------------------------------START
//-----------------------------------------------------------------------------
// File: WavRead.cpp
//
// Desc: Wave file support for loading and playing Wave files using DirectSound 
//       buffers.
//
// Copyright (c) 1999 Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------
#include <mmsystem.h>
#include <mmreg.h>


//-----------------------------------------------------------------------------
// Name: class CWaveSoundRead
// Desc: A class to read in sound data from a Wave file
//-----------------------------------------------------------------------------


class CWaveSoundRead
{
public:
	WAVEFORMATEX* m_pwfx;        // Pointer to WAVEFORMATEX structure
	HMMIO         m_hmmioIn;     // MM I/O handle for the WAVE
	MMCKINFO      m_ckIn;        // Multimedia RIFF chunk
	MMCKINFO      m_ckInRiff;    // Use in opening a WAVE file

public:
	CWaveSoundRead();
	~CWaveSoundRead();

	HRESULT Open( CHAR* strFilename );
	HRESULT Reset();
	HRESULT Read( UINT nSizeToRead, BYTE* pbData, UINT* pnSizeRead );
	HRESULT Close();


};//��������OK-------------------------------------------------------------------------------------------END


//�V���O���g���N���X
class SoundSingleton{
public:
	LPDIRECTSOUNDBUFFER8 Object[MUSIC_NUM];//�Đ�����Ȃ̓��ꕨUser�͂���𗘗p����
	 long Vol;
	 long Pan;
	 DWORD Hz,Hz2;
	// �B��̃A�N�Z�X�o�H
	static SoundSingleton* GetInstance()
	{
		static SoundSingleton instance;  // �B��̃C���X�^���X
		return &instance;
	}

	void PlaySuccession(int number);//�A���Đ����������ȍĐ����\�b�h
	void Init(HWND hwnd);
	
	void LoadWAVE(LPDIRECTSOUNDBUFFER8 &pDSData,char *fname);//�Ȃ̓ǂݍ���
	void DestoryDevice();//�f�o�C�X�̉���@�Q�[���I�����Ɏ��s���邱��
	void ResetSuccession(int number);
	void Stop(int number);
	~SoundSingleton();

private:
	LPDIRECTSOUNDBUFFER8 ObjectSuccession[MUSIC_NUM][MUSIC_NUM_SUCCESSION];//�A���Đ��p
	//bool ObjectSuccessionFlag[MUSIC_NUM][MUSIC_NUM_SUCCESSION];//�A���Đ��p�̍Đ����Ȃǂ̃t���O���
	//int SuccessionCheck(int number);//�Đ��\��ObjectSuccession�ԍ���Ԃ����\�b�h
	LPDIRECTSOUND8 lpDSound;	//DirectSound�I�u�W�F�N�g
	LPDIRECTSOUNDBUFFER lpSPrimary;
	
	

	//�R�s�[�Ƃ������Ȃ�
	SoundSingleton();
	SoundSingleton(const SoundSingleton& rhs);
	SoundSingleton& operator=(const SoundSingleton& rhs);
};


