#include"Groval.h"

LRESULT APIENTRY WndFunc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg){
		case WM_COPYDATA:  //�ǉ�
			 {  
				// COPYDATASTRUCT * const pData = reinterpret_cast<COPYDATASTRUCT *>(lp);  
				// wstring str;  
				// 
				// str.assign(reinterpret_cast<wchar_t *>(pData->lpData), pData->cbData/sizeof(wchar_t)); 
				 
				 COPYDATASTRUCT *pCD = (COPYDATASTRUCT*)lParam;
			
				//MessageBox(hwnd,(char *)pCD->lpData,"�ʐM",MB_OK);
				 

				 /*�J��������
				 ============================================*/
				 if(pCD->dwData == 100)
				 {
					 std::string _string;
					 _string =  (char *)pCD->lpData;
					 if( _string == "1")//�I�u�W�F�N�g�ɕύX
					 {
					 EDIT_C->CameraSelected = false;
					 }
					 else
					 {
						  EDIT_C->CameraSelected = true;
					 }
				 }

				 /*EDIT_C->Set_EXEPos�̗L���E����
				 =============================================*/
				 if(pCD->dwData == 200)
				 {
					 std::string _string;
					 _string =  (char *)pCD->lpData;
					 if( _string == "1")//�I�u�W�F�N�g�ɕύX
					 {
					 EDIT_C->Set_EXEPos = true;
					 }
					 else
					 {
						  EDIT_C->Set_EXEPos = false;
					 }
				 }

				 if(pCD->dwData >= OBJECT_ID )//�I�u�W�F�N�g���ʔԍ��̏ꍇ�̓I�u�W�F�N�g�Ɣ��f
				 {
				 EDIT_O->Command((char *)pCD->lpData,pCD->dwData);//�I�u�W�F�N�g�}�l�[�W���[�֑��M
				 }else
				 {
				 EDIT_C->Command((char *)pCD->lpData,pCD->dwData);//�L�����N�^�[�}�l�[�W���[�֑��M
				 }
			 }  
			 break;  
case WM_DESTROY:
	PostQuitMessage(0);
	return 0;
case WM_KEYDOWN:
	switch(wParam){
case VK_ESCAPE:
	PostQuitMessage(0);
	return 0;
	}
	return 0;

	}
	return DefWindowProc(hwnd,msg,wParam,lParam);

}

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrev,
				   LPSTR lpszCmdParam,int nCmdshow)
{
	MSG msg;

	HWND hwnd;
	WNDCLASS wc;
	char szAppName[]="Generic Game SDK Window";

	wc.style=CS_DBLCLKS;
	wc.lpfnWndProc=WndFunc;
	wc.cbClsExtra=0;
	wc.cbWndExtra=0;
	wc.hInstance=hInst;
	wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName=NULL;
	wc.lpszClassName=szAppName;

	RegisterClass(&wc);

	hwnd=CreateWindowEx(
		//		WS_EX_TOPMOST,
		0,
		szAppName,
		"���@���@��@��",
		//		WS_VISIBLE|WS_POPUP,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCRW,SCRH,
		NULL,NULL,hInst,
		NULL);

	if(!hwnd)return FALSE;

	ShowWindow(hwnd,nCmdshow);
	UpdateWindow(hwnd);
	SetFocus(hwnd);
	if(FULLSCREEN){
		ShowCursor(FALSE);
	}else{
		RECT rc={0,0,SCRW,SCRH};
		AdjustWindowRect(&rc,WS_OVERLAPPEDWINDOW,FALSE);
		SetWindowPos(hwnd,NULL,0,0,rc.right-rc.left,rc.bottom-rc.top,SWP_SHOWWINDOW|SWP_NOMOVE|SWP_NOZORDER);
	}

	//-------------------------------�T�E���h�̏�����--------------------------------
	SOUND->Init(hwnd);
	SOUND->LoadWAVE( SOUND->Object[0], "Sound/�^�C�g��.WAV" );
	SOUND->LoadWAVE( SOUND->Object[1], "Sound/�Q�[���V�[��.WAV" );
	SOUND->LoadWAVE( SOUND->Object[2], "Sound/�U���󂯂���.WAV" );
	SOUND->LoadWAVE( SOUND->Object[3], "Sound/�a����.WAV" );
	SOUND->LoadWAVE( SOUND->Object[4], "Sound/�e����.WAV" );
	SOUND->LoadWAVE( SOUND->Object[5], "Sound/�Q�[���I�[�o�[.WAV" );
	SOUND->LoadWAVE( SOUND->Object[6], "Sound/�{�X��.WAV" );
	SOUND->LoadWAVE( SOUND->Object[7], "Sound/�{�X���o.WAV" );
	SOUND->LoadWAVE( SOUND->Object[8], "Sound/�^�C�g�����o.WAV" );
	SOUND->LoadWAVE( SOUND->Object[9], "Sound/���U��.WAV" );
	SOUND->LoadWAVE( SOUND->Object[10], "Sound/��C.WAV" );
	SOUND->LoadWAVE( SOUND->Object[11], "Sound/����.WAV" );
	SOUND->LoadWAVE( SOUND->Object[12], "Sound/���[�v��.WAV" );
	SOUND->LoadWAVE( SOUND->Object[13], "Sound/����.WAV" );
	SOUND->LoadWAVE( SOUND->Object[14], "Sound/�Ō㔚��.WAV" );
	SOUND->LoadWAVE( SOUND->Object[15], "Sound/��������.WAV" );
	SOUND->LoadWAVE( SOUND->Object[16], "Sound/���[�U�[.WAV" );
	SOUND->LoadWAVE( SOUND->Object[17], "Sound/��.WAV" );
	SOUND->LoadWAVE( SOUND->Object[18], "Sound/�Q�[���N���A.WAV" );
	SOUND->LoadWAVE( SOUND->Object[19], "Sound/�o���A.WAV" );
	SOUND->LoadWAVE( SOUND->Object[20], "Sound/�o���A�e��.WAV" );
	SOUND->LoadWAVE( SOUND->Object[21], "Sound/���܂�.WAV" );
	SOUND->LoadWAVE( SOUND->Object[22], "Sound/�H�쐺.WAV" );
	SOUND->LoadWAVE( SOUND->Object[23], "Sound/���n��.WAV" );
	SOUND->LoadWAVE( SOUND->Object[24], "Sound/����.WAV" );
	SOUND->LoadWAVE( SOUND->Object[25], "Sound/�W�����v.WAV" );
	SOUND->LoadWAVE( SOUND->Object[26], "Sound/�j�̃X�e�[�W.WAV" );
	SOUND->LoadWAVE( SOUND->Object[27], "Sound/�X�C�b�`��.WAV" );
	SOUND->LoadWAVE( SOUND->Object[28], "Sound/���J��.WAV" );
	SOUND->ResetSuccession(4);
	SOUND->ResetSuccession(9);
	SOUND->ResetSuccession(10);
	SOUND->ResetSuccession(13);

	//---------------------DirectX Graphics�֘A-----------------------

	// Direct3D �I�u�W�F�N�g���쐬
	lpD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!lpD3D)
	{
		// �I�u�W�F�N�g�쐬���s
		MessageBox(NULL,"Direct3D �̍쐬�Ɏ��s���܂����B","ERROR",MB_OK | MB_ICONSTOP);
		// �I������
		return 0;
	}
	// �g�p����A�_�v�^�ԍ�
	adapter = 0;

	// �E�C���h�E�̍쐬�����������̂ŁADirect3D ������������
	ZeroMemory(&d3dpp,sizeof(D3DPRESENT_PARAMETERS));
	// Direct3D �������p�����[�^�̐ݒ�
	if (FULLSCREEN)
	{
		// �t���X�N���[�� : �قƂ�ǂ̃A�_�v�^�ŃT�|�[�g����Ă���t�H�[�}�b�g���g�p
		//		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		// �E�C���h�E : ���݂̉�ʃ��[�h���g�p
		D3DDISPLAYMODE disp;
		// ���݂̉�ʃ��[�h���擾
		lpD3D->GetAdapterDisplayMode(adapter,&disp);
		d3dpp.BackBufferFormat = disp.Format;
	}
	// �\���̈�T�C�Y�̐ݒ�
	d3dpp.BackBufferWidth = SCRW;
	d3dpp.BackBufferHeight = SCRH;
	d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;

	if (!FULLSCREEN)
	{
		// �E�C���h�E���[�h
		d3dpp.Windowed = 1;
	}

	// Z �o�b�t�@�̎����쐬
	d3dpp.EnableAutoDepthStencil = 1;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	//�ޯ��ޯ̧��ۯ��\�ɂ���(GetDC���\�ɂȂ�)
	d3dpp.Flags=D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	// �f�o�C�X�̍쐬 - T&L HAL
	if (FAILED(lpD3D->CreateDevice(adapter,D3DDEVTYPE_HAL,hwnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3dpp,&lpD3DDevice)))
	{
		// ���s�����̂� HAL �Ŏ��s
		if (FAILED(lpD3D->CreateDevice(adapter,D3DDEVTYPE_HAL,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&lpD3DDevice)))
		{
			// ���s�����̂� REF �Ŏ��s
			if (FAILED(lpD3D->CreateDevice(adapter,D3DDEVTYPE_REF,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&lpD3DDevice)))
			{
				// ���ǎ��s����
				MessageBox(NULL,"DirectX9���������ł��܂���B\n���Ή��̃p�\�R���Ǝv���܂��B","ERROR",MB_OK | MB_ICONSTOP);
				lpD3D->Release();
				// �I������
				return 0;
			}
		}
	}

	// �����_�����O�E�X�e�[�g��ݒ�
	// Z �o�b�t�@�L����->�O��֌W�̌v�Z�𐳊m�ɂ��Ă����
	lpD3DDevice->SetRenderState(D3DRS_ZENABLE,D3DZB_TRUE);
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);

	// �A���t�@�u�����f�B���O�L����
	lpD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);

	// �A���t�@�u�����f�B���O���@��ݒ�
	lpD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	//// �����_�����O���̃A���t�@�l�̌v�Z���@�̐ݒ�
	//lpD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	//// �e�N�X�`���̐F���g�p
	//lpD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	//// ���_�̐F���g�p
	//lpD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE);
	//// �����_�����O���̐F�̌v�Z���@�̐ݒ�
	//lpD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);

	//���ʃJ�����O
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);

	// �t�B���^�ݒ�
	lpD3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_LINEAR);
	lpD3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	lpD3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);

	// ���C�g
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING,FALSE);

	lpD3DDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&lpBackbuffer);

	// ���_�t�H�[�}�b�g�̐ݒ�
	lpD3DDevice->SetFVF(FVF_VERTEX);

	timeBeginPeriod(1);


	// ���C�g�̏�����
	D3DLIGHT9 Light;	// ���C�g�p�̌^
	ZeroMemory(&Light, sizeof(Light));	// �ϐ��̏������i�O�j
	Light.Type = D3DLIGHT_DIRECTIONAL;

	Light.Diffuse.r = 1.0f;
	Light.Diffuse.g = 1.0f;
	Light.Diffuse.b = 1.0f;

	//Light.Specular.r = 1.0f;
	//Light.Specular.g = 1.0f;
	//Light.Specular.b = 1.0f;

	Light.Direction = D3DXVECTOR3(1.0f, -1.0f, 0.0f);	// ����𖾂邭����
	//Light.Direction = D3DXVECTOR3(0, -5.0f, -2.0f);	// ����𖾂邭����

	lpD3DDevice->SetLight(0, &Light);	// �o�^

	lpD3DDevice->LightEnable(0, TRUE);	// ���C�g�̂n�m�A�n�e�e

	lpD3DDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&lpBackbuffer);

	//������
	Init();
	
	EDIT_O->ReadObjectFile("StartStage.txt");
	EDIT_O->ReadObjectFile("NormalStage.txt");
	EDIT_O->ReadObjectFile("YukaStage.txt");
	EDIT_O->ReadObjectFile("HariStage.txt");
	EDIT_O->ReadObjectFile("OBJ1Stage.txt");
	EDIT_O->ReadObjectFile("OBJ2Stage.txt");
	EDIT_O->ReadObjectFile("OBJ3Stage.txt");
	EDIT_O->ReadObjectFile("FIREStage.txt");
	EDIT_O->ReadObjectFile("DUMMYStage.txt");
	EDIT_O->ReadObjectFile("ATARIStage.txt");

	//EDIT_C->ReadObjectFile("NormalEnemy.txt");
	//EDIT_C->ReadObjectFile("YukaEnemy.txt");
	//EDIT_C->ReadObjectFile("NoEnemy.txt");

	while(1){
		if(PeekMessage(&msg,NULL,0,0,PM_NOREMOVE))
		{
			if(!GetMessage(&msg,NULL,0,0))
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}else{
			NowScene = NextScene;
			switch(NowScene){
				case TITLE_INIT:
					title.Init();
					SOUND->Stop(1);		//�Q�[���V�[���̉��X�g�b�v
					SOUND->Stop(5);		//�Q�[���I�[�o�[�̉��X�g�b�v
					SOUND->Stop(18);	//�Q�[���N���A�̉��X�g�b�v
					SOUND->Object[0]->Play(0,0,DSBPLAY_LOOPING);//�^�C�g���̃��[�v�Đ�
					break;
				case TITLE_RUN:
					title.Run();
					break;
				case TITLE_RELEASE:
					title.Release();
					break;
				case GAME_INIT:
					game.Init();
					SOUND->Stop(0);		//�^�C�g���̉��X�g�b�v
					SOUND->Stop(5);		//�Q�[���I�[�o�[�̉��X�g�b�v
					SOUND->Object[1]->Play(0,0,DSBPLAY_LOOPING);//BGM�̃��[�v�Đ�
					break;
				case GAME_RUN:
					game.Run();
					break;
				case GAME_RELEASE:
					game.Release();
					break;
				case CLEAR_INIT:
					clear.Init();
					SOUND->Stop(1);	
					SOUND->Stop(17);
					SOUND->Stop(16);
					SOUND->Stop(19);
					SOUND->Stop(6);
					SOUND->Object[18]->Play(0,0,DSBPLAY_LOOPING);
					break;
				case CLEAR_RUN:
					clear.Run();
					break;
				case CLEAR_RELEASE:
					clear.Release();
					break;
				case GAMEOVER_INIT:
					//EDIT_C->ReadObjectFile("NormalEnemy.txt");
					gameover.Init();
					SOUND->Stop(26);
					SOUND->Stop(1);		//�Q�[���V�[���̉��X�g�b�v
					//�{�X���ɃQ�[���I�[�o�[�ɂȂ����特������
					SOUND->Stop(17);
					SOUND->Stop(16);
					SOUND->Stop(19);
					SOUND->Stop(6);
					SOUND->Object[5]->Play(0,0,DSBPLAY_LOOPING);	//�Q�[���I�[�o�[�̉��Đ�
					break;
				case GAMEOVER_RUN:
					gameover.Run();
					break;
				case GAMEOVER_RELEASE:
					gameover.Release();
					break;
			}
		}
	}

	//���
	Release();

	
	timeEndPeriod(1);


	lpBackbuffer->Release();

	SOUND->DestoryDevice();//�T�E���h�f�o�C�X�̉��

	// Direct3D �I�u�W�F�N�g�����
	lpD3DDevice->Release();
	lpD3D->Release();

	return msg.wParam;
}