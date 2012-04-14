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
	//�ő吔�𒴂��Ă����ꍇ
	//�����ĂȂɂ����Ȃ��ł���

}

void SoundSingleton::ResetSuccession(int number)
{
	LPDIRECTSOUNDBUFFER lpSTmp;
	int i;
	for(i = 0; i< MUSIC_NUM_SUCCESSION; i++){//�A�������̋ȃ|�C���^���A�w�肵���Ȃ̃|�C���^(Object)�ɏ���������
		lpDSound->DuplicateSoundBuffer(Object[number],&lpSTmp);
		lpSTmp->QueryInterface(IID_IDirectSoundBuffer8,(LPVOID *)&ObjectSuccession[number][i]);
		lpSTmp->Release();
	}
}
//�f�o�C�X�̉���@�v���O�����I�����ɌĂяo���B
void SoundSingleton::DestoryDevice()
{

	lpSPrimary->Release();
	lpDSound->Release();
}


void SoundSingleton::Init(HWND hwnd)//�e�X�g�p�B�폜OK
{	
	Vol = 0;
	Pan = 0;
	//---------------------DirectSound�֘A-----------------------
	DirectSoundCreate8(NULL, &lpDSound, NULL);

	//�������x����ݒ�
	lpDSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);

	// �v���C�}���E�o�b�t�@�̍쐬
	// DSBUFFERDESC�\���̂�ݒ�
	DSBUFFERDESC dsbdesc; 
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC); 
	// �v���C�}���E�o�b�t�@���w��
	dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_PRIMARYBUFFER;
	dsbdesc.dwBufferBytes = 0;
	dsbdesc.lpwfxFormat = NULL;


	// �o�b�t�@�����
	lpDSound->CreateSoundBuffer(&dsbdesc, &lpSPrimary, NULL); 

	// �v���C�}���E�o�b�t�@��Wave�t�H�[�}�b�g��ݒ�
	// �@�@�@�D�拦�����x���ȏ�̋������x�����ݒ肳��Ă���K�v������܂��D
	WAVEFORMATEX pcmwf; 
	ZeroMemory(&pcmwf, sizeof(WAVEFORMATEX)); 
	pcmwf.wFormatTag = WAVE_FORMAT_PCM; 
	pcmwf.nChannels = 2;		// �Q�`�����l���i�X�e���I�j
	pcmwf.nSamplesPerSec = 44100;	// �T���v�����O�E���[�g�@44.1kHz
	pcmwf.nBlockAlign = 4;
	pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign; 
	pcmwf.wBitsPerSample = 16;		// 16�r�b�g
	lpSPrimary->SetFormat(&pcmwf);


	
	//���y�p�@�����̒l�ŉ��ʂȂǂ͑���ł��Ȃ��I
	long Vol;
	long Pan;

	lpSPrimary->GetVolume( &Vol );
	lpSPrimary->GetPan( &Pan );
	//lpSSecond->GetFrequency(&Hz);
	//lpSSecond2->GetFrequency(&Hz2);

	lpSPrimary->SetVolume(Vol);
	lpSPrimary->SetPan(Pan);
}

//Private:�T�E���h�̃��[�h�B----------------------------------------------START
void SoundSingleton::LoadWAVE(LPDIRECTSOUNDBUFFER8 &pDSData,char *fname)
{
	HRESULT hr;

	// WAVE�t�@�C�����J��
	CWaveSoundRead WaveFile;
	WaveFile.Open(fname);

	// �Z�J���_���E�o�b�t�@���쐬����
	// DSBUFFERDESC�\���̂�ݒ�
	DSBUFFERDESC dsbdesc; 
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC); 

	dsbdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS |
		DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY;
	dsbdesc.dwBufferBytes = WaveFile.m_ckIn.cksize;
	dsbdesc.lpwfxFormat = WaveFile.m_pwfx;

	// �o�b�t�@�����
	LPDIRECTSOUNDBUFFER pDSTmp;
	//	lpDSound->CreateSoundBuffer(&dsbdesc, &pDSData, NULL); 
	lpDSound->CreateSoundBuffer(&dsbdesc, &pDSTmp, NULL); 
	pDSTmp->QueryInterface(IID_IDirectSoundBuffer8,(LPVOID*)&pDSData);
	pDSTmp->Release();

	// �Z�J���_���E�o�b�t�@��Wave�f�[�^����������
	LPVOID lpvPtr1;		// �ŏ��̃u���b�N�̃|�C���^
	DWORD dwBytes1;		// �ŏ��̃u���b�N�̃T�C�Y
	LPVOID lpvPtr2;		// �Q�Ԗڂ̃u���b�N�̃|�C���^
	DWORD dwBytes2;		// �Q�Ԗڂ̃u���b�N�̃T�C�Y

	hr = pDSData->Lock(0, WaveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0); 

	// DSERR_BUFFERLOST���Ԃ��ꂽ�ꍇ�CRestore���\�b�h���g���ăo�b�t�@�𕜌�����
	if(DSERR_BUFFERLOST == hr)
	{
		pDSData->Restore();
		hr = pDSData->Lock(0, WaveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
	} 
	if (SUCCEEDED(hr))
	{
		// ���b�N����

		// �����ŁC�o�b�t�@�ɏ�������
		// �o�b�t�@�Ƀf�[�^���R�s�[����
		UINT rsize;
		WaveFile.Read(dwBytes1, (LPBYTE)lpvPtr1, &rsize);
		if ( 0 != dwBytes2 )
			WaveFile.Read(dwBytes2, (LPBYTE)lpvPtr2, &rsize);

		// �������݂��I������炷����Unlock����D
		hr = pDSData->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2); 
	}
}//Private:�T�E���h�̃��[�h--------------------------------------------------------------------------------------END




//�R�s�[�Ƃ������Ȃ�-----------------------START

//�R���X�g���N�^
SoundSingleton::SoundSingleton(){};

//�f�X�g���N�^
SoundSingleton::~SoundSingleton(){}
//�R�s�[�Ƃ������Ȃ�-----------------------END