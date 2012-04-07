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




	std::string FileGroup;//�ǂ̃t�@�C���ɍ��݂��܂ꂽ���B�����l�� ""

	//�J����������p�B
	D3DXMATRIX mCamWorld;
	float CamRotX,CamRotY;

	float Tool_MoveValue;

	virtual void Init(void){};
	virtual void Move(void){};
	virtual void Draw(void){};
	virtual void Event(int flag){};





	void Tool_Move(void)
	{

		// ���@�ړ�
		if( GetAsyncKeyState('Z') & 0x8000 ){//�A�b�v
			D3DXVECTOR3 Fow;
			D3DXVec3TransformCoord( &Fow, &D3DXVECTOR3( 0, Tool_MoveValue, 0 ), &mRot );
			//Pos = ray.RayWALL(Pos, Fow, 4);
			Pos += Fow;
		}

		else if( GetAsyncKeyState('X') & 0x8000 ){//�_�E��
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


		D3DXMatrixTranslation(&mTrans, Pos.x, Pos.y, Pos.z);		//�ʒu
		D3DXMatrixRotationY(&mRot, D3DXToRadian(CamRotY));				//��]

		mCamWorld =  mRot * mTrans;							//�s�񍇐�

	};//Move�Ɠ��������ŕӂ蔻����폜�B Tool�p�B



	int ID;
	int Type;//ENEMY EXE
	bool Visible;//�\�����邩���Ȃ����@�����ltrue�B
	int Group;//New�Ő�������Ƃ��Ƀt�@�C���f�[�^����O���[�vID��ǉ�����B




	BaseObject(){Group=1; CamRotX = 0; CamRotY = 0; Scale=1; RotX=0;RotY=0; Tool_MoveValue = 1.0f;eventFlag = 0; FileGroup = ""; Stateflg = 0; StageName=0;};
	virtual ~BaseObject(){};

private:
};


//BasCharacter==========================================================================
class BaseCharacter
{
public:
	//C_Character���玝���Ă���---

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
	

	//�J����������p�B
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

		// ���@�ړ�
		if( GetAsyncKeyState('Z') & 0x8000 ){//�A�b�v
			D3DXVECTOR3 Fow;
			D3DXVec3TransformCoord( &Fow, &D3DXVECTOR3( 0, Tool_MoveValue, 0 ), &mRot );
			//Pos = ray.RayWALL(Pos, Fow, 4);
			Pos += Fow;
		}
		else if
			( GetAsyncKeyState('X') & 0x8000 ){//�_�E��
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

		D3DXMatrixTranslation(&mTrans, Pos.x, Pos.y, Pos.z);		//�ʒu
		D3DXMatrixRotationY(&mRot, D3DXToRadian(CamRotY));				//��]

		mCamWorld =  mRot * mTrans;							//�s�񍇐�

	};//Move�Ɠ��������ŕӂ蔻����폜�B Tool�p�B

	int ID;
	int Type;//ENEMY EXE
	bool Visible;//�\�����邩���Ȃ����@�����ltrue�B
	int Group;//New�Ő�������Ƃ��Ƀt�@�C���f�[�^����O���[�vID��ǉ�����B




	BaseCharacter(){Group=1; Scale=1; CamRotX = 0; CamRotY = 0; Tool_MoveValue=1.0f; eventFlag = 0; FileGroup = ""; Stateflg = 0; StageName=0;};
	virtual ~BaseCharacter(){};

private:
};

#endif