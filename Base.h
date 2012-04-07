#ifndef _Base_
#define _Base_
#pragma once
#include "Groval.h"



using namespace std;
//BaseObject==========================================================================
class BaseObject
{
public:
	D3DXVECTOR3 Pos;
	D3DXMATRIX mTrans;
	D3DXMATRIX mRot;
	D3DXMATRIX mScale;
	D3DXMATRIX mWorld;
	float RotX, RotY,Scale;




	std::string FileGroup;//どのファイルに込みこまれたか。初期値は ""

	//カメラ処理専用。
	D3DXMATRIX mCamWorld;
	float CamRotX,CamRotY;

	float Tool_MoveValue;

	virtual void Init(void){};
	virtual void Move(void){};
	virtual void Draw(void){};
	virtual void Event(int flag){};





	void Tool_Move(void)
	{

		// 自機移動
		if( GetAsyncKeyState('Z') & 0x8000 ){//アップ
			D3DXVECTOR3 Fow;
			D3DXVec3TransformCoord( &Fow, &D3DXVECTOR3( 0, Tool_MoveValue, 0 ), &mRot );
			//Pos = ray.RayWALL(Pos, Fow, 4);
			Pos += Fow;
		}

		else if( GetAsyncKeyState('X') & 0x8000 ){//ダウン
			D3DXVECTOR3 Fow;
			D3DXVec3TransformCoord( &Fow, &D3DXVECTOR3( 0, -Tool_MoveValue, 0 ), &mRot );
			//Pos = ray.RayWALL(Pos, Fow, 4);
			Pos += Fow;
		}

		else if( GetAsyncKeyState('A') & 0x8000 ){
			D3DXVECTOR3 Fow;
			D3DXVec3TransformCoord( &Fow, &D3DXVECTOR3( -Tool_MoveValue, 0, 0 ), &mRot );
			//Pos = ray.RayWALL(Pos, Fow, 4);
			Pos += Fow;
		}
		else if( GetAsyncKeyState('D') & 0x8000 ){
			D3DXVECTOR3 Fow;
			D3DXVec3TransformCoord( &Fow, &D3DXVECTOR3( Tool_MoveValue, 0, 0 ), &mRot );
			/*Pos = ray.RayWALL(Pos, Fow, 4);*/
			Pos += Fow;
		}

		if( GetAsyncKeyState('W') & 0x8000 ){
			D3DXVECTOR3 Fow;
			D3DXVec3TransformCoord( &Fow, &D3DXVECTOR3( 0, 0, Tool_MoveValue ), &mRot );
			/*Pos = ray.RayWALL(Pos, Fow, 4);*/
			Pos += Fow;
		}

		else if( GetAsyncKeyState('S') & 0x8000 ){
			D3DXVECTOR3 Fow;
			D3DXVec3TransformCoord( &Fow, &D3DXVECTOR3( 0, 0, -Tool_MoveValue ), &mRot );
			/*Pos = ray.RayWALL(Pos, Fow, 4);*/
			Pos += Fow;
		}

		if(GetAsyncKeyState(VK_UP) & 0x8000){
			CamRotY += 0.7f;
		}
		if(GetAsyncKeyState(VK_DOWN) & 0x8000){
			CamRotY -= 0.7f;
		}

		if(GetAsyncKeyState(VK_RIGHT) & 0x8000){
			RotY += 0.7f;
		}

		if(GetAsyncKeyState(VK_LEFT) & 0x8000){
			RotY -= 0.7f;
		}


		D3DXMatrixTranslation(&mTrans, Pos.x, Pos.y, Pos.z);		//位置
		D3DXMatrixRotationY(&mRot, D3DXToRadian(CamRotY));				//回転

		mCamWorld =  mRot * mTrans;							//行列合成

	};//Moveと同じ動きで辺り判定を削除。 Tool用。



	int ID;
	int Type;//ENEMY EXE
	bool Visible;//表示するかしないか　初期値true。
	int Group;//Newで生成するときにファイルデータからグループIDを追加する。




	BaseObject(){Group=1; CamRotX = 0; CamRotY = 0; Scale=1; RotX=0;RotY=0; Tool_MoveValue = 1.0f;eventFlag = 0; FileGroup = ""; Stateflg = 0; StageName=0;};
	virtual ~BaseObject(){};

private:
};


//BasCharacter==========================================================================
class BaseCharacter
{
public:
	//C_Characterから持ってきた---

	D3DXVECTOR3 Pos;
	D3DXMATRIX mTrans;
	D3DXMATRIX mRot;
	D3DXMATRIX mScale;
	D3DXMATRIX mWorld;
	float RotX, RotY;
	float Scale;
	int Hp;
	int eventFlag;
	std::string FileGroup;
	

	//カメラ処理専用。
	D3DXMATRIX mCamWorld;
	float CamRotX,CamRotY;

	float Tool_MoveValue;

	virtual void Init(void){}
	virtual void Move(void){}
	virtual void Attack(void){}
	virtual void Draw(void){}
	virtual void Event(int flag){}



	void Tool_Move(void)
	{

		// 自機移動
		if( GetAsyncKeyState('Z') & 0x8000 ){//アップ
			D3DXVECTOR3 Fow;
			D3DXVec3TransformCoord( &Fow, &D3DXVECTOR3( 0, Tool_MoveValue, 0 ), &mRot );
			//Pos = ray.RayWALL(Pos, Fow, 4);
			Pos += Fow;
		}
		else if
			( GetAsyncKeyState('X') & 0x8000 ){//ダウン
				D3DXVECTOR3 Fow;
				D3DXVec3TransformCoord( &Fow, &D3DXVECTOR3( 0, -Tool_MoveValue, 0 ), &mRot );
				//Pos = ray.RayWALL(Pos, Fow, 4);
				Pos += Fow;
		}

		else if( GetAsyncKeyState('A') & 0x8000 ){
			D3DXVECTOR3 Fow;
			D3DXVec3TransformCoord( &Fow, &D3DXVECTOR3( -Tool_MoveValue, 0, 0 ), &mRot );
			/*Pos = ray.RayWALL(Pos, Fow, 4);*/
			Pos += Fow;
		}
		else if( GetAsyncKeyState('D') & 0x8000 ){
			D3DXVECTOR3 Fow;
			D3DXVec3TransformCoord( &Fow, &D3DXVECTOR3( Tool_MoveValue, 0, 0 ), &mRot );
			/*Pos = ray.RayWALL(Pos, Fow, 4);*/
			Pos += Fow;
		}

		if( GetAsyncKeyState('W') & 0x8000 ){
			D3DXVECTOR3 Fow;
			D3DXVec3TransformCoord( &Fow, &D3DXVECTOR3( 0, 0, Tool_MoveValue ), &mRot );
			/*Pos = ray.RayWALL(Pos, Fow, 4);*/
			Pos += Fow;
		}

		else if( GetAsyncKeyState('S') & 0x8000 ){
			D3DXVECTOR3 Fow;
			D3DXVec3TransformCoord( &Fow, &D3DXVECTOR3( 0, 0, -Tool_MoveValue ), &mRot );
			/*Pos = ray.RayWALL(Pos, Fow, 4);*/
			Pos += Fow;
		}

		if(GetAsyncKeyState(VK_UP) & 0x8000){
			CamRotY += 0.7f;
		}
		if(GetAsyncKeyState(VK_DOWN) & 0x8000){
			CamRotY -= 0.7f;
		}

		if(GetAsyncKeyState(VK_RIGHT) & 0x8000){
			RotY += 0.7f;
		}

		if(GetAsyncKeyState(VK_LEFT) & 0x8000){
			RotY -= 0.7f;
		}

		D3DXMatrixTranslation(&mTrans, Pos.x, Pos.y, Pos.z);		//位置
		D3DXMatrixRotationY(&mRot, D3DXToRadian(CamRotY));				//回転

		mCamWorld =  mRot * mTrans;							//行列合成

	};//Moveと同じ動きで辺り判定を削除。 Tool用。

	int ID;
	int Type;//ENEMY EXE
	bool Visible;//表示するかしないか　初期値true。
	int Group;//Newで生成するときにファイルデータからグループIDを追加する。




	BaseCharacter(){Group=1; Scale=1; CamRotX = 0; CamRotY = 0; Tool_MoveValue=1.0f; eventFlag = 0; FileGroup = ""; Stateflg = 0; StageName=0;};
	virtual ~BaseCharacter(){};

private:
};

#endif