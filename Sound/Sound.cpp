#include "Sound.h"




void SoundSingleton::Stop(int number)
{
	Object[number]->Stop();
	Object[number]->SetCurrentPosition(0);
}

void SoundSingleton::PlaySuccession(int number)
{
	DWORD SFlg;
	int i;
	for(i = 0;i < MUSIC_NUM_SUCCESSION ;i++)
	{

		SOUND->ObjectSuccession[number][i]->GetStatus(&SFlg);
		if( (SFlg & DSBSTATUS_PLAYING) == 0 )

		{
			this->ObjectSuccession[number][i]->Play(0,0,0);
			break;
		}
		
	}
	//最大数を超えていた場合
	//あえてなにもしないでおく

}

void SoundSingleton::ResetSuccession(int number)
{
	LPDIRECTSOUNDBUFFER lpSTmp;
	int i;
	for(i = 0; i< MUSIC_NUM_SUCCESSION; i++){//連続数分の曲ポインタを、指定した曲のポインタ(Object)に初期化する
		lpDSound->DuplicateSoundBuffer(Object[number],&lpSTmp);
		lpSTmp->QueryInterface(IID_IDirectSoundBuffer8,(LPVOID *)&ObjectSuccession[number][i]);
		lpSTmp->Release();
	}
}
//デバイスの解放　プログラム終了時に呼び出す。
void SoundSingleton::DestoryDevice()
{

	lpSPrimary->Release();
	lpDSound->Release();
}


void SoundSingleton::Init(HWND hwnd)//テスト用。削除OK
{	
	Vol = 0;
	Pan = 0;
	//---------------------DirectSound関連-----------------------
	DirectSoundCreate8(NULL, &lpDSound, NULL);

	//協調レベルを設定
	lpDSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);

	// プライマリ・バッファの作成
	// DSBUFFERDESC構造体を設定
	DSBUFFERDESC dsbdesc; 
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC); 
	// プライマリ・バッファを指定
	dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_PRIMARYBUFFER;
	dsbdesc.dwBufferBytes = 0;
	dsbdesc.lpwfxFormat = NULL;


	// バッファを作る
	lpDSound->CreateSoundBuffer(&dsbdesc, &lpSPrimary, NULL); 

	// プライマリ・バッファのWaveフォーマットを設定
	// 　　　優先協調レベル以上の協調レベルが設定されている必要があります．
	WAVEFORMATEX pcmwf; 
	ZeroMemory(&pcmwf, sizeof(WAVEFORMATEX)); 
	pcmwf.wFormatTag = WAVE_FORMAT_PCM; 
	pcmwf.nChannels = 2;		// ２チャンネル（ステレオ）
	pcmwf.nSamplesPerSec = 44100;	// サンプリング・レート　44.1kHz
	pcmwf.nBlockAlign = 4;
	pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign; 
	pcmwf.wBitsPerSample = 16;		// 16ビット
	lpSPrimary->SetFormat(&pcmwf);


	
	//音楽用　※この値で音量などは操作できない！
	long Vol;
	long Pan;

	lpSPrimary->GetVolume( &Vol );
	lpSPrimary->GetPan( &Pan );
	//lpSSecond->GetFrequency(&Hz);
	//lpSSecond2->GetFrequency(&Hz2);

	lpSPrimary->SetVolume(Vol);
	lpSPrimary->SetPan(Pan);
}

//Private:サウンドのロード。----------------------------------------------START
void SoundSingleton::LoadWAVE(LPDIRECTSOUNDBUFFER8 &pDSData,char *fname)
{
	HRESULT hr;

	// WAVEファイルを開く
	CWaveSoundRead WaveFile;
	WaveFile.Open(fname);

	// セカンダリ・バッファを作成する
	// DSBUFFERDESC構造体を設定
	DSBUFFERDESC dsbdesc; 
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC); 

	dsbdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS |
		DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY;
	dsbdesc.dwBufferBytes = WaveFile.m_ckIn.cksize;
	dsbdesc.lpwfxFormat = WaveFile.m_pwfx;

	// バッファを作る
	LPDIRECTSOUNDBUFFER pDSTmp;
	//	lpDSound->CreateSoundBuffer(&dsbdesc, &pDSData, NULL); 
	lpDSound->CreateSoundBuffer(&dsbdesc, &pDSTmp, NULL); 
	pDSTmp->QueryInterface(IID_IDirectSoundBuffer8,(LPVOID*)&pDSData);
	pDSTmp->Release();

	// セカンダリ・バッファにWaveデータを書き込む
	LPVOID lpvPtr1;		// 最初のブロックのポインタ
	DWORD dwBytes1;		// 最初のブロックのサイズ
	LPVOID lpvPtr2;		// ２番目のブロックのポインタ
	DWORD dwBytes2;		// ２番目のブロックのサイズ

	hr = pDSData->Lock(0, WaveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0); 

	// DSERR_BUFFERLOSTが返された場合，Restoreメソッドを使ってバッファを復元する
	if(DSERR_BUFFERLOST == hr)
	{
		pDSData->Restore();
		hr = pDSData->Lock(0, WaveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
	} 
	if (SUCCEEDED(hr))
	{
		// ロック成功

		// ここで，バッファに書き込む
		// バッファにデータをコピーする
		UINT rsize;
		WaveFile.Read(dwBytes1, (LPBYTE)lpvPtr1, &rsize);
		if ( 0 != dwBytes2 )
			WaveFile.Read(dwBytes2, (LPBYTE)lpvPtr2, &rsize);

		// 書き込みが終わったらすぐにUnlockする．
		hr = pDSData->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2); 
	}
}//Private:サウンドのロード--------------------------------------------------------------------------------------END




//コピーとかさせない-----------------------START

//コンストラクタ
SoundSingleton::SoundSingleton(){};

//デストラクタ
SoundSingleton::~SoundSingleton(){}
//コピーとかさせない-----------------------END