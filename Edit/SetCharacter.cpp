#include "SetCharacter.h"
#include <string>
#include <iostream>
//コンストラクタ
SetCharacter::SetCharacter(){this->Init();};

//デストラクタ
SetCharacter::~SetCharacter(){}


void SetCharacter::Init()
{

	if(InitFlag == false)//重複しないようにする
	{
		ID = 0;							//発行開始番号 1番目から始まる。
		EditNow = false;				//編集モードではない
		KeyCheck_Next = false;			//多重入力防止
		KeyCheck_Back = false;			//多重入力防止
		it =  Character_Storage.begin();//配列の先頭を指定
		this->Character_Data.reserve(1000);
		InitFlag = true;
		InputNow = false;
		this->CameraSelected = true;
		this->GroupMoveID = GROUPMOVENULL;
		this->GroupMoveFlag = false;
		Object = NULL;
		Set_EXEPos = true;
	}
}

void SetCharacter::Edit(void)
{	
	EDIT_O->Edit();
	EditNow = true;					//変更中であると伝える
	it = Character_Storage.begin();	//配列の先頭を指定
	//it == Character_Storage.end() ||
	if( Character_Storage.empty() )//キャラが登録されていない場合
	{
		Object = NULL;//キャラがいないので念のためNULL
		EditNow = false;//オブジェクトがなにも入っていないと編集モードではない

		OutputDebugString("\nNo_ObjectA\n");
	}
	else//キャラクターが入っているのでObjectに配列の先頭のキャラを設定
	{

		Object = it->second;//オブジェクトにデータを入れる
	}

	//debug



}
void SetCharacter::EndEdit(void)
{
	EDIT_O->EndEdit();
	EditNow = false;//編集モードを終わる

}


int SetCharacter::MakeID(void)
{	ID = ID+1;
OutputDebugString("\nMakeID\n");
return ID;//IDを発行し、1カウントを増やす

}
void SetCharacter::Delete(int ID)
{
	

}

int SetCharacter::Add(BaseCharacter *chara)
{	
	chara->ID = MakeID();
	Character_Storage.insert( std::map<int,BaseCharacter*>::value_type( ID, chara ) );//ID,ポインタを登録
	OutputDebugString("\nAddObjectA\n");//Visual Studioの出力画面に追加されたことを通知
	return chara->ID;
}	

bool SetCharacter::Editing(void)
{

	return EditNow;//現在編集中かどうかをBOOL型で返す

}

bool SetCharacter::EditMode(void)
{
	return EditModeNow;
}
bool SetCharacter::EditMode(bool mode)
{
	EditModeNow = mode;
	return EditModeNow;
}

void  SetCharacter::Next(void)
{//||( !Character_Storage.empty() )

	if( Character_Storage.empty() ) return;
	if( it != Character_Storage.end()  )//最後のオブジェクトじゃなかったら処理をする
	{	
		Object = it->second;
		it++;

	}
}

void  SetCharacter::Back(void)
{
	if( Character_Storage.empty() ) return;
	//|| it != Character_Storage.end() || !Character_Storage.empty()
	if( it != Character_Storage.begin()  )//最初じゃなかったら処理をする
	{
		--it;
		Object = it->second;
	}
}

void SetCharacter::SelectedDelete()
{

	if(Object != NULL)
	{
		Character_Storage.erase(Object->ID);//現在編集中のキャラクタを開放する

		this->Edit();//Objectがないので、キャラクターを指定する。
	}
}

void SetCharacter::AllFilePut(string FileName)
{


	FILE *fp = NULL;
	fp = fopen(FileName.c_str(), "w");//ファイルパスは好きに変更する aで追記、wで削除して上書き
	if (fp == NULL) 
	{
		OutputDebugString("\nLocalDebugFile(Debug.txt) ReadErorr\n");

	}
	std::map<int,BaseCharacter*>::iterator its;
	its = Character_Storage.begin();

	bool flag = false;			//一度も書き込みがない場合、NoObjectを表示
	while( its != Character_Storage.end() )
	{
		flag = true;
			
		//書込み　ここは好きに変える
		if( (*its).second->Type != PLAYER )//プレイヤーは書き出さない
		fprintf(fp,"%d,%f,%f,%f,%f,%f,%d,%f,%d ",(*its).second->Type,(*its).second->Pos.x,(*its).second->Pos.y,(*its).second->Pos.z,(*its).second->RotX,(*its).second->RotY,(*its).second->Group,(*its).second->Scale,(*its).second->eventFlag);//書き込みたいデータを選択
		++its;
	}
	fclose(fp);
	//デバッグ用。基本的に通らないはず。
	if(flag == false)SendCommand("データがありませんでした",0);//キャラがいなかった


	

	SendCommand("ファイルに出力しました",0);

}

void SetCharacter::SelectObject(int ID)
{
	//指定されたIDのオブジェクトをObjectに設定
	it = Character_Storage.find(ID);
	Object = it->second;
}


void SetCharacter::CreateObject(int ObjectType)
{
	int OldID;
	std::map<int,BaseCharacter*>::iterator it;
	float z = -5.0f;
	if(Character_Storage.empty() || Object == NULL)
	{
		OldID = 0;//現在存在しない
	}
	else
	{
		
		//OldID = Object->ID;//ひとつ前のキャラクタのID

		if( Set_EXEPos == true)
		{
		it = Character_Storage.begin();
		OldID = (*it).second->ID;
		}
		else
		{
		it = Character_Storage.end();
		it--;
		OldID = (*it).second->ID;
		}
	
		//OldID =(Character_Storage.end())->second->ID;//ひとつ前のキャラクタのID
	}
	switch(ObjectType)
	{
		
	case PLAYER:
		
		this->Character_Data.push_back(  new  SkinPlayer() );
		it = Character_Storage.find(ID);
		it->second->Init();

		//キャラクタの出現座標を一つ前のオブジェクトと一緒にする
		if( OldID != 0)
		{
		 I_CHARA_STORAGE it2 = Character_Storage.find(OldID);
		 it->second->Pos = it2->second->Pos;
		 it->second->Pos.z += z;
		}
		break;

	case HOUDAI:
		
		this->Character_Data.push_back(  new Houdai() );
		it = Character_Storage.find(ID);
		it->second->Init();

		//キャラクタの出現座標を一つ前のオブジェクトと一緒にする
		if( OldID != 0)
		{
		 I_CHARA_STORAGE it2 = Character_Storage.find(OldID);
		 it->second->Pos = it2->second->Pos;
		  it->second->Pos.z += z;
		}
		break;

		case YUUREI:
		
		this->Character_Data.push_back(  new Yuurei() );
		it = Character_Storage.find(ID);
		it->second->Init();

		//キャラクタの出現座標を一つ前のオブジェクトと一緒にする
		if( OldID != 0)
		{
		 I_CHARA_STORAGE it2 = Character_Storage.find(OldID);
		 it->second->Pos = it2->second->Pos;
		  it->second->Pos.z += z;
		}
		break;

		case ENEMY:
		
		this->Character_Data.push_back(  new Enemy() );
		it = Character_Storage.find(ID);
		it->second->Init();

		//キャラクタの出現座標を一つ前のオブジェクトと一緒にする
		if( OldID != 0)
		{
		 I_CHARA_STORAGE it2 = Character_Storage.find(OldID);
		 it->second->Pos = it2->second->Pos;
		  it->second->Pos.z += z;
		}
		break;

		case FANBEAM:
		
		this->Character_Data.push_back(  new FanBeam() );
		it = Character_Storage.find(ID);
		it->second->Init();

		//キャラクタの出現座標を一つ前のオブジェクトと一緒にする
		if( OldID != 0)
		{
		 I_CHARA_STORAGE it2 = Character_Storage.find(OldID);
		 it->second->Pos = it2->second->Pos;
		  it->second->Pos.z += z;
		}
		break;

		case MUMMY:
		
		this->Character_Data.push_back(  new Mummy() );
		it = Character_Storage.find(ID);
		it->second->Init();

		//キャラクタの出現座標を一つ前のオブジェクトと一緒にする
		if( OldID != 0)
		{
		 I_CHARA_STORAGE it2 = Character_Storage.find(OldID);
		 it->second->Pos = it2->second->Pos;
		  it->second->Pos.z += z;
		}
		break;
	default:
		SendCommand("No Select ObjectType.");
	}


}

void SetCharacter::ReleaseObject(int ID)
{
	if(Character_Storage[ID])//データがあれば
		Character_Storage.erase(ID);//指定されたIDのオブジェクトを削除する（ポインタの解除）

	//指定されたIDを検索し、ヒットしたら開放。そうでなければスルー
	I_CHARA_DATA its;
	its = Character_Data.begin();
	for(int i = 0;i < Character_Data.size();i++ )
	{
		if(Character_Data[i]->ID == ID)
		{
			if(Character_Data[i])
			{

				if(Object != NULL)
				if(ID == Object->ID){Edit();}//編集中の場合バグるかもしれないので一応初期化

				delete Character_Data[i];//指定されたIDのオブジェクトを削除する
				Character_Data.erase(its);//不正なアドレスを削除する
				break;
			}
		}
		its++;
	}

}

void SetCharacter::Command(char * CharData,int dwData)
{

	std::string Data;
	Data = CharData;
	//0は普通のコマンド
	if( dwData == 1)//描画のON/OFF
	{
		if(Data =="")return;
		I_CHARA_STORAGE ith;
		ith = this->Character_Storage.begin();
		int intdata = atoi(Data.c_str());
		while( ith != Character_Storage.end() )
		{
			if((*ith).second->ID == intdata){
				if( (*ith).second->Visible == true )
				{
					(*ith).second->Visible = false;
				}else
				{
					(*ith).second->Visible = true;
				}
				break;
			}
			ith++;
		}
		return;
	}


	if( dwData == 2)//ファイルデータから読み込み
	{
		ReadObjectFile(Data.c_str());
		return;
	}

	if( dwData == 3)
	{
		ReleaseAllObject();//すべて削除
		FILE *fp = NULL;
		fp = fopen(Data.c_str(), "r");//ファイルパスは好きに変更する aで追記、wで削除して上書き
		if (fp == NULL) 
		{
			SendCommand("ファイルを読み込みに失敗しました");
			return;

		}

		int type =0,flag=0;
		float x=0,y=0,z=0,rotx=0,roty=0,scale=0;
		int group=0;
		I_CHARA_STORAGE ith;
		while( fscanf(fp,"%d,%f,%f,%f,%f,%f,%d,%f,%d ",&type,&x,&y,&z,&rotx,&roty,&group,&scale,&flag)  != EOF )
		{


			//　ここは好きに変える

			CreateObject(type);

			ith = Character_Storage.find(ID);
			(*ith).second->Pos.x = x;
			(*ith).second->Pos.y = y;
			(*ith).second->Pos.z = z;
			(*ith).second->RotX = rotx;
			(*ith).second->RotY = roty;
			(*ith).second->Group = group;
			(*ith).second->Scale = scale;
			(*ith).second->eventFlag = flag;

		}

		fclose(fp);
		return;


	}

	if(dwData == 4)
	{
		this->AllFilePut(Data);
		return;
	}
	if(dwData == 5)
	{
		if(Object == NULL)return;
		if(Data =="")return;
		this->SelectObject( atoi(Data.c_str() ) );
		return;
	}
	if(dwData == 6)//キャラデータを取得して上書き
	{
		//sscanfをつかう
		
		int _id=0,_type=0,_group=0,_flag=0;
		float _x=0,_y=0,_z=0,_rotx=0,_roty=0,_scale;
		//"%d,%f,%f,%f,%f,%f,%d ",&type,&x,&y,&z,&rotx,&roty,&group
		sscanf(Data.c_str(),"%d %d %f %f %f %f %f %d %f %d",&_id,&_type,&_x,&_y,&_z,&_rotx,&_roty,&_group,&_scale,&_flag);
		//sscanf(Data.c_str(),"%d%d",&SelectID,&SelectGroup);
		EDIT_C->Character_Storage[_id]->Type	= _type;
		EDIT_C->Character_Storage[_id]->Pos.x = _x;
		EDIT_C->Character_Storage[_id]->Pos.y = _y;
		EDIT_C->Character_Storage[_id]->Pos.z = _z;
		EDIT_C->Character_Storage[_id]->RotX	= _rotx;
		EDIT_C->Character_Storage[_id]->RotY	= _roty;
		EDIT_C->Character_Storage[_id]->Group = _group;
		EDIT_C->Character_Storage[_id]->Scale = _scale;
		EDIT_C->Character_Storage[_id]->eventFlag = _flag;


	}

	if(dwData == 7)//グループ移動実行
	{
		//this->GroupMoveID = Data;//移動IDの指定
		//this->GroupMoveFlag = true;//実行
	}

	if(dwData == 8)//グループ移動停止
	{
		this->GroupMoveFlag = false;//停止
	}


	if(dwData == 9)//ファイルからオブジェクト解放
	{
		this->DieFileName(Data);
	}

	if(Data =="start")//編集の開始
	{
		Edit();
	}
	else if(Data =="release")//編集中のオブジェクトの開放
	{
			if(Object == NULL)
		{
			SendCommand("解放するキャラクター対象が不正です",0);
			return;
		}
		else
		{
		//ReleaseObject(Object->ID);
			Die(Object->ID);//安全に解放できるようになる
		}
	}
	else if(Data =="release_all")//すべてのオブジェクトを開放
	{
		this->ReleaseAllObject();
	}
	else if(Data =="end")//編集の終了
	{
		EndEdit();
	}
	//else if(Data =="enemy")//敵の生成
	//{
	//	CreateObject(ENEMY);
	//}

	else if(Data =="player")//プレイヤーの生成
	{
		CreateObject(PLAYER);
	}
	else if(Data =="houdai")//プレイヤーの生成
	{
		CreateObject(HOUDAI);
	}
	else if(Data =="yuurei")//プレイヤーの生成
	{
		CreateObject(YUUREI);
	}
	else if(Data =="fanbeam")//プレイヤーの生成
	{
		CreateObject(FANBEAM);
	}
	else if(Data =="enemy")//プレイヤーの生成
	{
		CreateObject(ENEMY);
	}
	else if(Data =="mummy")//プレイヤーの生成
	{
		CreateObject(MUMMY);
	}
	else if(Data =="next")//次のオブジェクトにアクセス
	{
		Next();
		//-----------------------------------IDをstringへ
		if(Object == NULL)return;
		string data;
		char t_char[20];//１０ぐらいでもOK
		sprintf_s(t_char,"%d",Object->ID);
		data = t_char;
		//-----------------------------------
		SendCommand(data,2);//ツールに現在選択中のIDを送る
	}else if(Data =="back")//前のオブジェクトにアクセス
	{
		Back();
		//-----------------------------------IDをstringへ
		if(Object == NULL)return;
		string data;
		char t_char[20];//１０ぐらいでもOK
		sprintf_s(t_char,"%d",Object->ID);
		data = t_char;
		//-----------------------------------
		SendCommand(data,2);//ツールに現在選択中のIDを送る

	}else if(Data =="delete")//編集中のオブジェクトを抹消
	{
		SelectedDelete();
		EDIT_C->EndEdit();
		EditMode(false);
	}else if(Data =="noinput")//移動操作の無効
	{
		InputNow = false;
	}else if(Data =="okinput")//移動操作の有効
	{
		EDIT_C->Edit();
		InputNow = true;
	}

	else if(Data =="list")//ツールにオブジェクト情報を一斉送信
	{
		std::string data;
		I_CHARA_STORAGE ith;
		ith = this->Character_Storage.begin();
		while( ith != Character_Storage.end() )
		{
			//intやfloatはstringに変換できないので、一旦charに変換してからstringにする。
			//intからchar、charからstringの箱へ
			char t_char[20];//１０ぐらいでもOK
			sprintf_s(t_char,"%d",(*ith).second->ID);

			data += t_char;//ID追加
			data += ",";

			char t_chartype[20];
			sprintf_s(t_chartype,"%d",(*ith).second->Type);
			data += t_chartype;
			data += ",";

			char t_charx[20];
			char t_chary[20];
			char t_charz[20];
			char t_charrx[20];
			char t_charry[20];
			char t_charvisible[20];
			char t_chargroup[20];
			char t_charscale[20];
			char t_charflag[20];
			
		
			sprintf_s(t_charx,"%f",(*ith).second->Pos.x);
			sprintf_s(t_chary,"%f",(*ith).second->Pos.y);
			sprintf_s(t_charz,"%f",(*ith).second->Pos.z);
			sprintf_s(t_charrx,"%f",(*ith).second->RotX);
			sprintf_s(t_charry,"%f",(*ith).second->RotY);
			sprintf_s(t_charvisible,"%d",(*ith).second->Visible);
			sprintf_s(t_chargroup,"%d",(*ith).second->Group);
			sprintf_s(t_charscale,"%f",(*ith).second->Scale);
			sprintf_s(t_charflag,"%d",(*ith).second->eventFlag);

			data += t_charx;//追加
			data += ",";
			data += t_chary;//追加
			data += ",";
			data += t_charz;//追加
			data += ",";

			data += t_charvisible;
			data += ",";

			data += t_charrx;//追加
			data += ",";
			data += t_charry;//追加
			data += ",";

			
			
			data += t_chargroup;//追加
			data += ",";
			data += t_charscale;
			data += ",";
			data += t_charflag;

			data += " ";//終了
			ith++;
		}
		SendCommand(data,1);

		//-----------------------------------IDをstringへ
		if(Object == NULL)return;
		string d;
		char t_char[20];//１０ぐらいでもOK
		sprintf_s(t_char,"%d",Object->ID);
		d = t_char;
		//-----------------------------------
		SendCommand(d,2);//ツールに現在選択中のIDを送る

	}

}

bool SetCharacter::Input(void)
{
	return InputNow;
}

void SetCharacter::SendCommand(std::string buffer,int Type)
{
	COPYDATASTRUCT cd;

	HWND hwnd;
	cd.dwData = Type;
	cd.cbData = (buffer.length())+1;
	cd.lpData = (PVOID)buffer.c_str();

	hwnd = FindWindow(NULL,"オブジェクト管理ツール");//変更しないこと
	SendMessage(hwnd,WM_COPYDATA,(WPARAM)NULL,(LPARAM)&cd);
}

void SetCharacter::CommandParser(string command, int &type, float &x, float &y, float &z, std::string &CommandCode)
{
}

void SetCharacter::CommandParser(string FileName, string command, int &type, float &x, float &y, float &z, std::string &CommandCode)
{


}

void SetCharacter::ReleaseAllObject()
{
	//if(Character_Storage[ID])//データがあれば
	//	Character_Storage.erase(ID);//指定されたIDのオブジェクトを削除する（ポインタの解除）

	////指定されたIDを検索し、ヒットしたら開放。そうでなければスルー
	//I_CHARA_DATA its;
	//
	////this->EndEdit();
	////for(int i = 0;i < Character_Data.size();i++ )
	////{
	////
	////	if(Character_Data.empty() == true )
	////		return;
	////	its = Character_Data.begin();
	////	its++;
	////	//if(Character_Data[i])
	////	//{
	////	//	if(Object != NULL)
	////	//	if(ID == Object->ID){Edit();}//編集中の場合バグるかもしれないので一応初期化
	////	Character_Data.c
	////	delete Character_Data[i];//指定されたIDのオブジェクトを削除する
	////	Character_Data.erase(its);//不正なアドレスを削除する

	////	//}

	////	if(Character_Data.empty() == true )
	////		return;
	////	
	////}
	//for(its = Character_Data.begin();its != Character_Data.end();++its)
	//{
	//	delete (*its);
	//}
	//Character_Data.clear();
}

void SetCharacter::Replace(string filename)
{
			std::map<int,BaseCharacter*>::iterator itc;

		itc = EDIT_C->Character_Storage.begin();

		while( itc != EDIT_C->Character_Storage.end() )
		{
			
				EDIT_C->Die((*itc).second->ID);//ファイル名が違ったら削除する
				++itc;
			
		}
		EDIT_C->ReadObjectFile(filename);

}

void  SetCharacter::ReadObjectFile(string filename)
{
	FILE *fp = NULL;
		fp = fopen(filename.c_str(), "r");//ファイルパスは好きに変更する aで追記、wで削除して上書き
		if (fp == NULL) 
		{
			SendCommand("ファイルの読み込みに失敗しました");
		return;
		}

		int type =0,flag=0;
		float x=0,y=0,z=0,rotx=0,roty=0,scale=0;
		I_CHARA_STORAGE ith;
		int group=0;
		while( fscanf(fp,"%d,%f,%f,%f,%f,%f,%d,%f,%d ",&type,&x,&y,&z,&rotx,&roty,&group,&scale,&flag)  != EOF )
		{


			//　ここは好きに変える

			CreateObject(type);

			ith = Character_Storage.find(ID);
			(*ith).second->Pos.x = x;
			(*ith).second->Pos.y = y;
			(*ith).second->Pos.z = z;
			(*ith).second->RotX = rotx;
			(*ith).second->RotY = roty;
			(*ith).second->Group = group;
			(*ith).second->Scale = scale;
			(*ith).second->eventFlag = flag;
			(*ith).second->FileGroup = filename;
		}
}


void  SetCharacter::Die(int ID)
{
	//std::vector<int>::iterator it;
	if( ID == 1) return;//playerなら削除しない
	 Die_Data.push_back( ID );
	//it.push_back( ID );
}
void  SetCharacter::Die()
{
	std::vector<int>::iterator it;
	std::vector<int>::iterator ituni = std::unique(Die_Data.begin(),Die_Data.end());
	//std::vector<int> DeletedID;

	Die_Data.erase(ituni,Die_Data.end() );
		it = Die_Data.begin();
	

	while( it != Die_Data.end() )
	{
		ReleaseObject( (*it) );
	//	DeletedID.push_back( (*it) );//後でIDのリストを解放
		
		++it;
	}
Die_Data.clear();//削除リストのクリア


}

void SetCharacter::DieFileName(std::string filename)
{
I_CHARA_STORAGE ith;
		ith = this->Character_Storage.begin();
		while( ith !=Character_Storage.end() )
		{
			if( (*ith).second->FileGroup == filename )
			Die( (*ith).second->ID);
			++ith;
		}
}