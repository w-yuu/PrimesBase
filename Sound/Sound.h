/*
//=========================================
■SOUNDクラスの使い方
//=========================================
1.まずゲーム開始時にデバイス関係を初期化する
SOUND->Init(hwnd);

2.曲をロードする。
SOUND->LoadWAVE( SOUND->Object[0], "Test.WAV" );

3.曲を再生する。
SOUND->Object[0]->Play(0,0,0);
Play引数は0を３つにしておく。（DirectXの仕様）

4.曲の一時停止。
SOUND->Object[0]->STOP();
一時停止のみ。Play関数を呼ぶと続きから再生される。

5.曲テンポの変更。
SOUND->Object[0]->SetFrequency( SOUND->Hz );//通常スピード
SOUND->Object[0]->SetFrequency( SOUND->Hz*2 );//二倍早く
SOUND->Object[0]->SetFrequency( SOUND->Hz/2 );//半分の速度

6.音の大きさを変更。
SOUND->Object[0]->SetVolume( SOUND->Vol += 50 );//50%大きく

7.パンを変更。
SOUND->Object[0]->SetPan( SOUND->Pan += 50 );//50%大きく

8.連続再生をする準備。
SOUND->ResetSuccession(0);//Object０番が裏方の配列にコピーされる。

9.連続再生に対応。
SOUND->PlaySuccession(0);//
再生要求が来たらObject０番の曲をMUSIC_NUM_SUCCESSION回まで再生対応。
※再生したいObjectにSOUND->ResetSuccessionが適応されていなければ
エラーとなる。１回でもしていれば前にSOUND->ResetSuccessionした曲が再生される。

10.曲を変える。
2番と同じように指定するだけ。ファイルの解放やインスタンスの破棄は
一切しなくてよい。また再生中にロードしてもよい。

11.ゲーム終了時の処理
SOUND->DestoryDevice();//サウンドデバイスの解放。



*/





#pragma once
#include<dsound.h>

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")
//#pragma comment(lib, "libcp.lib")

//=========================================
//ユーザが設定すべきデータ
#define MUSIC_NUM 29//利用したい曲数
#define MUSIC_NUM_SUCCESSION 15//連続再生の許可数
//=========================================




#define  SOUND SoundSingleton::GetInstance()//インスタンス取得が長いので省略。

//無視してOK----------------------------------------------------------------------------START
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


};//無視してOK-------------------------------------------------------------------------------------------END


//シングルトンクラス
class SoundSingleton{
public:
	LPDIRECTSOUNDBUFFER8 Object[MUSIC_NUM];//再生する曲の入れ物Userはこれを利用する
	 long Vol;
	 long Pan;
	 DWORD Hz,Hz2;
	// 唯一のアクセス経路
	static SoundSingleton* GetInstance()
	{
		static SoundSingleton instance;  // 唯一のインスタンス
		return &instance;
	}

	void PlaySuccession(int number);//連続再生を許可した曲再生メソッド
	void Init(HWND hwnd);
	
	void LoadWAVE(LPDIRECTSOUNDBUFFER8 &pDSData,char *fname);//曲の読み込み
	void DestoryDevice();//デバイスの解放　ゲーム終了時に実行すること
	void ResetSuccession(int number);
	void Stop(int number);
	~SoundSingleton();

private:
	LPDIRECTSOUNDBUFFER8 ObjectSuccession[MUSIC_NUM][MUSIC_NUM_SUCCESSION];//連続再生用
	//bool ObjectSuccessionFlag[MUSIC_NUM][MUSIC_NUM_SUCCESSION];//連続再生用の再生中などのフラグ状態
	//int SuccessionCheck(int number);//再生可能なObjectSuccession番号を返すメソッド
	LPDIRECTSOUND8 lpDSound;	//DirectSoundオブジェクト
	LPDIRECTSOUNDBUFFER lpSPrimary;
	
	

	//コピーとかさせない
	SoundSingleton();
	SoundSingleton(const SoundSingleton& rhs);
	SoundSingleton& operator=(const SoundSingleton& rhs);
};


