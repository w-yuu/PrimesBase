#include"Groval.h"

LRESULT APIENTRY WndFunc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg){
		case WM_COPYDATA:  //追加
			 {  
				// COPYDATASTRUCT * const pData = reinterpret_cast<COPYDATASTRUCT *>(lp);  
				// wstring str;  
				// 
				// str.assign(reinterpret_cast<wchar_t *>(pData->lpData), pData->cbData/sizeof(wchar_t)); 
				 
				 COPYDATASTRUCT *pCD = (COPYDATASTRUCT*)lParam;
			
				//MessageBox(hwnd,(char *)pCD->lpData,"通信",MB_OK);
				 

				 /*カメラ制御
				 ============================================*/
				 if(pCD->dwData == 100)
				 {
					 std::string _string;
					 _string =  (char *)pCD->lpData;
					 if( _string == "1")//オブジェクトに変更
					 {
					 EDIT_C->CameraSelected = false;
					 }
					 else
					 {
						  EDIT_C->CameraSelected = true;
					 }
				 }

				 /*EDIT_C->Set_EXEPosの有効・無効
				 =============================================*/
				 if(pCD->dwData == 200)
				 {
					 std::string _string;
					 _string =  (char *)pCD->lpData;
					 if( _string == "1")//オブジェクトに変更
					 {
					 EDIT_C->Set_EXEPos = true;
					 }
					 else
					 {
						  EDIT_C->Set_EXEPos = false;
					 }
				 }

				 if(pCD->dwData >= OBJECT_ID )//オブジェクト識別番号の場合はオブジェクトと判断
				 {
				 EDIT_O->Command((char *)pCD->lpData,pCD->dwData);//オブジェクトマネージャーへ送信
				 }else
				 {
				 EDIT_C->Command((char *)pCD->lpData,pCD->dwData);//キャラクターマネージャーへ送信
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
		"次　元　戦　争",
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

	//-------------------------------サウンドの初期化--------------------------------
	SOUND->Init(hwnd);
	SOUND->LoadWAVE( SOUND->Object[0], "Sound/タイトル.WAV" );
	SOUND->LoadWAVE( SOUND->Object[1], "Sound/ゲームシーン.WAV" );
	SOUND->LoadWAVE( SOUND->Object[2], "Sound/攻撃受けた時.WAV" );
	SOUND->LoadWAVE( SOUND->Object[3], "Sound/斬撃音.WAV" );
	SOUND->LoadWAVE( SOUND->Object[4], "Sound/銃発射.WAV" );
	SOUND->LoadWAVE( SOUND->Object[5], "Sound/ゲームオーバー.WAV" );
	SOUND->LoadWAVE( SOUND->Object[6], "Sound/ボス戦.WAV" );
	SOUND->LoadWAVE( SOUND->Object[7], "Sound/ボス演出.WAV" );
	SOUND->LoadWAVE( SOUND->Object[8], "Sound/タイトル演出.WAV" );
	SOUND->LoadWAVE( SOUND->Object[9], "Sound/剣振る.WAV" );
	SOUND->LoadWAVE( SOUND->Object[10], "Sound/大砲.WAV" );
	SOUND->LoadWAVE( SOUND->Object[11], "Sound/抜刀.WAV" );
	SOUND->LoadWAVE( SOUND->Object[12], "Sound/ワープ音.WAV" );
	SOUND->LoadWAVE( SOUND->Object[13], "Sound/爆発.WAV" );
	SOUND->LoadWAVE( SOUND->Object[14], "Sound/最後爆発.WAV" );
	SOUND->LoadWAVE( SOUND->Object[15], "Sound/たたきつけ.WAV" );
	SOUND->LoadWAVE( SOUND->Object[16], "Sound/レーザー.WAV" );
	SOUND->LoadWAVE( SOUND->Object[17], "Sound/岩.WAV" );
	SOUND->LoadWAVE( SOUND->Object[18], "Sound/ゲームクリア.WAV" );
	SOUND->LoadWAVE( SOUND->Object[19], "Sound/バリア.WAV" );
	SOUND->LoadWAVE( SOUND->Object[20], "Sound/バリア弾き.WAV" );
	SOUND->LoadWAVE( SOUND->Object[21], "Sound/扉閉まる.WAV" );
	SOUND->LoadWAVE( SOUND->Object[22], "Sound/幽霊声.WAV" );
	SOUND->LoadWAVE( SOUND->Object[23], "Sound/着地音.WAV" );
	SOUND->LoadWAVE( SOUND->Object[24], "Sound/足音.WAV" );
	SOUND->LoadWAVE( SOUND->Object[25], "Sound/ジャンプ.WAV" );
	SOUND->LoadWAVE( SOUND->Object[26], "Sound/針のステージ.WAV" );
	SOUND->LoadWAVE( SOUND->Object[27], "Sound/スイッチ音.WAV" );
	SOUND->LoadWAVE( SOUND->Object[28], "Sound/扉開く.WAV" );
	SOUND->ResetSuccession(4);
	SOUND->ResetSuccession(9);
	SOUND->ResetSuccession(10);
	SOUND->ResetSuccession(13);

	//---------------------DirectX Graphics関連-----------------------

	// Direct3D オブジェクトを作成
	lpD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!lpD3D)
	{
		// オブジェクト作成失敗
		MessageBox(NULL,"Direct3D の作成に失敗しました。","ERROR",MB_OK | MB_ICONSTOP);
		// 終了する
		return 0;
	}
	// 使用するアダプタ番号
	adapter = 0;

	// ウインドウの作成が完了したので、Direct3D を初期化する
	ZeroMemory(&d3dpp,sizeof(D3DPRESENT_PARAMETERS));
	// Direct3D 初期化パラメータの設定
	if (FULLSCREEN)
	{
		// フルスクリーン : ほとんどのアダプタでサポートされているフォーマットを使用
		//		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		// ウインドウ : 現在の画面モードを使用
		D3DDISPLAYMODE disp;
		// 現在の画面モードを取得
		lpD3D->GetAdapterDisplayMode(adapter,&disp);
		d3dpp.BackBufferFormat = disp.Format;
	}
	// 表示領域サイズの設定
	d3dpp.BackBufferWidth = SCRW;
	d3dpp.BackBufferHeight = SCRH;
	d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;

	if (!FULLSCREEN)
	{
		// ウインドウモード
		d3dpp.Windowed = 1;
	}

	// Z バッファの自動作成
	d3dpp.EnableAutoDepthStencil = 1;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	//ﾊﾞｯｸﾊﾞｯﾌｧをﾛｯｸ可能にする(GetDCも可能になる)
	d3dpp.Flags=D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	// デバイスの作成 - T&L HAL
	if (FAILED(lpD3D->CreateDevice(adapter,D3DDEVTYPE_HAL,hwnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3dpp,&lpD3DDevice)))
	{
		// 失敗したので HAL で試行
		if (FAILED(lpD3D->CreateDevice(adapter,D3DDEVTYPE_HAL,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&lpD3DDevice)))
		{
			// 失敗したので REF で試行
			if (FAILED(lpD3D->CreateDevice(adapter,D3DDEVTYPE_REF,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&lpD3DDevice)))
			{
				// 結局失敗した
				MessageBox(NULL,"DirectX9が初期化できません。\n未対応のパソコンと思われます。","ERROR",MB_OK | MB_ICONSTOP);
				lpD3D->Release();
				// 終了する
				return 0;
			}
		}
	}

	// レンダリング・ステートを設定
	// Z バッファ有効化->前後関係の計算を正確にしてくれる
	lpD3DDevice->SetRenderState(D3DRS_ZENABLE,D3DZB_TRUE);
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);

	// アルファブレンディング有効化
	lpD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);

	// アルファブレンディング方法を設定
	lpD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	//// レンダリング時のアルファ値の計算方法の設定
	//lpD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	//// テクスチャの色を使用
	//lpD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	//// 頂点の色を使用
	//lpD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE);
	//// レンダリング時の色の計算方法の設定
	//lpD3DDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);

	//裏面カリング
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);

	// フィルタ設定
	lpD3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_LINEAR);
	lpD3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	lpD3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);

	// ライト
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING,FALSE);

	lpD3DDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&lpBackbuffer);

	// 頂点フォーマットの設定
	lpD3DDevice->SetFVF(FVF_VERTEX);

	timeBeginPeriod(1);


	// ライトの初期化
	D3DLIGHT9 Light;	// ライト用の型
	ZeroMemory(&Light, sizeof(Light));	// 変数の初期化（０）
	Light.Type = D3DLIGHT_DIRECTIONAL;

	Light.Diffuse.r = 1.0f;
	Light.Diffuse.g = 1.0f;
	Light.Diffuse.b = 1.0f;

	//Light.Specular.r = 1.0f;
	//Light.Specular.g = 1.0f;
	//Light.Specular.b = 1.0f;

	Light.Direction = D3DXVECTOR3(1.0f, -1.0f, 0.0f);	// 左上を明るくする
	//Light.Direction = D3DXVECTOR3(0, -5.0f, -2.0f);	// 左上を明るくする

	lpD3DDevice->SetLight(0, &Light);	// 登録

	lpD3DDevice->LightEnable(0, TRUE);	// ライトのＯＮ、ＯＦＦ

	lpD3DDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&lpBackbuffer);

	//初期化
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
					SOUND->Stop(1);		//ゲームシーンの音ストップ
					SOUND->Stop(5);		//ゲームオーバーの音ストップ
					SOUND->Stop(18);	//ゲームクリアの音ストップ
					SOUND->Object[0]->Play(0,0,DSBPLAY_LOOPING);//タイトルのループ再生
					break;
				case TITLE_RUN:
					title.Run();
					break;
				case TITLE_RELEASE:
					title.Release();
					break;
				case GAME_INIT:
					game.Init();
					SOUND->Stop(0);		//タイトルの音ストップ
					SOUND->Stop(5);		//ゲームオーバーの音ストップ
					SOUND->Object[1]->Play(0,0,DSBPLAY_LOOPING);//BGMのループ再生
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
					SOUND->Stop(1);		//ゲームシーンの音ストップ
					//ボス中にゲームオーバーになったら音を消す
					SOUND->Stop(17);
					SOUND->Stop(16);
					SOUND->Stop(19);
					SOUND->Stop(6);
					SOUND->Object[5]->Play(0,0,DSBPLAY_LOOPING);	//ゲームオーバーの音再生
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

	//解放
	Release();

	
	timeEndPeriod(1);


	lpBackbuffer->Release();

	SOUND->DestoryDevice();//サウンドデバイスの解放

	// Direct3D オブジェクトを解放
	lpD3DDevice->Release();
	lpD3D->Release();

	return msg.wParam;
}