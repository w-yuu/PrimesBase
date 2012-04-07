#include "SetObject.h"
#include <string>
#include <iostream>
//コンストラクタ
SetObject::SetObject(){ this->Init(); };

//デストラクタ
SetObject::~SetObject(){}


void SetObject::Init()
{

	if(InitFlag == false)//重複しないようにする
	{
		ID = 0;							//発行開始番号 1番目から始まる。
		EditNow = false;				//編集モードではない
		KeyCheck_Next = false;			//多重入力防止
		KeyCheck_Back = false;			//多重入力防止
		it =  Object_Storage.begin();//配列の先頭を指定
		this->Object_Data.reserve(1000);
		InitFlag = true;
		InputNow = false;
		Object = NULL;
		
	}
}

void SetObject::Edit(void)
{	
	
	EditNow = true;					//変更中であると伝える
	it = Object_Storage.begin();	//配列の先頭を指定
	//it == Object_Storage.end() ||
	if( Object_Storage.empty() )//キャラが登録されていない場合
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
void SetObject::EndEdit(void)
{
	
	EditNow = false;//編集モードを終わる

}


int SetObject::MakeID(void)
{	ID = ID+1;
OutputDebugString("\nMakeID\n");
return ID;//IDを発行し、1カウントを増やす

}
void SetObject::Delete(int ID)
{
	//if(Object_Storage[ID])//データがあれば
	//	Object_Storage.erase(ID);//指定されたIDのオブジェクトを削除する（ポインタの解除）

}

int SetObject::Add(BaseObject *chara)
{	
	chara->ID = MakeID();
	Object_Storage.insert( std::map<int,BaseObject*>::value_type( ID, chara ) );//ID,ポインタを登録
	OutputDebugString("\nAddObjectA\n");//Visual Studioの出力画面に追加されたことを通知
	return chara->ID;
}	

bool SetObject::Editing(void)
{

	return EditNow;//現在編集中かどうかをBOOL型で返す

}

bool SetObject::EditMode(void)
{
	return EditModeNow;
}
bool SetObject::EditMode(bool mode)
{
	EditModeNow = mode;
	return EditModeNow;
}

void  SetObject::Next(void)
{//||( !Object_Storage.empty() )

	if( Object_Storage.empty() ) return;
	if( it != Object_Storage.end()  )//最後のオブジェクトじゃなかったら処理をする
	{	
		Object = it->second;
		it++;

	}
}

void  SetObject::Back(void)
{
	if( Object_Storage.empty() ) return;
	//|| it != Object_Storage.end() || !Object_Storage.empty()
	if( it != Object_Storage.begin()  )//最初じゃなかったら処理をする
	{
		--it;
		Object = it->second;
	}
}

void SetObject::SelectedDelete()
{

	if(Object != NULL)
	{
		Object_Storage.erase(Object->ID);//現在編集中のキャラクタを開放する

		this->Edit();//Objectがないので、キャラクターを指定する。
	}
}

void SetObject::AllFilePut(string FileName)
{


	FILE *fp = NULL;
	fp = fopen(FileName.c_str(), "w");//ファイルパスは好きに変更する aで追記、wで削除して上書き
	if (fp == NULL) 
	{
		OutputDebugString("\nLocalDebugFile(Debug.txt) ReadErorr\n");

	}
	std::map<int,BaseObject*>::iterator its;
	its = Object_Storage.begin();

	bool flag = false;			//一度も書き込みがない場合、NoObjectを表示
	while( its != Object_Storage.end() )
	{
		flag = true;

		//書込み　ここは好きに変える
		fprintf(fp,"%d,%f,%f,%f,%f,%f,%d,%f,%d ",(*its).second->Type,(*its).second->Pos.x,(*its).second->Pos.y,(*its).second->Pos.z,(*its).second->RotX,(*its).second->RotY,(*its).second->Group,(*its).second->Scale,(*its).second->eventFlag);//書き込みたいデータを選択
		++its;
	}

	//デバッグ用。基本的に通らないはず。
	if(flag == false) fprintf(fp,"No_Object");//キャラがいなかった


	fclose(fp);

	Command("ファイルに出力しました",0);

}

void SetObject::SelectObject(int ID)
{
	//指定されたIDのオブジェクトをObjectに設定
	it = Object_Storage.find(ID);
	Object = it->second;
}


void SetObject::CreateObject(int ObjectType)
{
	int OldID;
	std::map<int,BaseObject*>::iterator it;
	float z = -5.0f;
	if(Object_Storage.empty() || Object == NULL)
	{
		OldID = 0;//現在存在しない
	}
	else
	{
		
		//OldID = Object->ID;//ひとつ前のキャラクタのID
		it = Object_Storage.end();
		it--;
		OldID = (*it).second->ID;
		//OldID =(Character_Storage.end())->second->ID;//ひとつ前のキャラクタのID
		
	}
	switch(ObjectType)
	{
		
	case BUTTON:
		
		this->Object_Data.push_back(  new Button() );
		it = Object_Storage.find(ID);
		it->second->Init();

		//キャラクタの出現座標を一つ前のオブジェクトと一緒にする
		if( OldID != 0)
		{
		 I_OBJECT_STORAGE it2 = Object_Storage.find(OldID);
		 it->second->Pos = it2->second->Pos;
		}
		 if( EDIT_C->Set_EXEPos == true)
		it->second->Pos = (*EDIT_C->Character_Storage.begin() ).second->Pos;
		 it->second->Pos.z += z;

		
		break;

	case DOOR:
		this->Object_Data.push_back(  new Door() );
		it = Object_Storage.find(ID);
		it->second->Init();

		//キャラクタの出現座標を一つ前のオブジェクトと一緒にする
		if( OldID != 0)
		{
		 I_OBJECT_STORAGE it2 = Object_Storage.find(OldID);
		 it->second->Pos = it2->second->Pos;
		}
		  if( EDIT_C->Set_EXEPos == true)
		it->second->Pos = (*EDIT_C->Character_Storage.begin() ).second->Pos;
		 it->second->Pos.z += z;
		
		break;

	case TAIMATU:
		this->Object_Data.push_back(  new Torch() );
		it = Object_Storage.find(ID);
		it->second->Init();

		//キャラクタの出現座標を一つ前のオブジェクトと一緒にする
		if( OldID != 0)
		{
		 I_OBJECT_STORAGE it2 = Object_Storage.find(OldID);
		 it->second->Pos = it2->second->Pos;
		}
		  if( EDIT_C->Set_EXEPos == true)
		it->second->Pos = (*EDIT_C->Character_Storage.begin() ).second->Pos;
		 it->second->Pos.z += z;
		break;

	case TATEFUDA:
		this->Object_Data.push_back(  new Tatefuda() );
		it = Object_Storage.find(ID);
		it->second->Init();

		//キャラクタの出現座標を一つ前のオブジェクトと一緒にする
		if( OldID != 0)
		{
		 I_OBJECT_STORAGE it2 = Object_Storage.find(OldID);
		 it->second->Pos = it2->second->Pos;
		}
		  if( EDIT_C->Set_EXEPos == true)
		it->second->Pos = (*EDIT_C->Character_Storage.begin() ).second->Pos;
		 it->second->Pos.z += z;
	break;

	case ROOMEVENT:
		this->Object_Data.push_back(  new RoomEvent() );
		it = Object_Storage.find(ID);
		it->second->Init();

		//キャラクタの出現座標を一つ前のオブジェクトと一緒にする
		if( OldID != 0)
		{
		 I_OBJECT_STORAGE it2 = Object_Storage.find(OldID);
		 it->second->Pos = it2->second->Pos;
		}
		  if( EDIT_C->Set_EXEPos == true)
		it->second->Pos = (*EDIT_C->Character_Storage.begin() ).second->Pos;
		 it->second->Pos.z += z;
	break;

	case WARP:
		this->Object_Data.push_back(  new WarpPoint() );
		it = Object_Storage.find(ID);
		it->second->Init();

		//キャラクタの出現座標を一つ前のオブジェクトと一緒にする
		if( OldID != 0)
		{
		 I_OBJECT_STORAGE it2 = Object_Storage.find(OldID);
		 it->second->Pos = it2->second->Pos;
		}
		  if( EDIT_C->Set_EXEPos == true)
		it->second->Pos = (*EDIT_C->Character_Storage.begin() ).second->Pos;
		 it->second->Pos.z += z;
		 break;
	default:
		OutputDebugString("No Select ObjectType.");
	}


}

void SetObject::ReleaseObject(int ID)
{
		if(Object_Storage[ID])//データがあれば
		Object_Storage.erase(ID);//指定されたIDのオブジェクトを削除する（ポインタの解

	//指定されたIDを検索し、ヒットしたら開放。そうでなければスルー
	I_OBJECT_DATA its;
	its = Object_Data.begin();
	for(int i = 0;i < Object_Data.size();i++ )
	{
		if(Object_Data[i]->ID == ID)
		{
			if(Object_Data[i])
			{

				if(Object != NULL)
				if(ID == Object->ID){Edit();}//編集中の場合バグるかもしれないので一応初期化

				delete Object_Data[i];//指定されたIDのオブジェクトを削除する
				Object_Data.erase(its);//不正なアドレスを削除する
				break;
			}
		}
		its++;
	}

}

void SetObject::Command(char * CharData,int dwData)
{

	std::string Data;
	Data = CharData;
	//0は普通のコマンド
	if( dwData == 21)//描画のON/OFF
	{
		if(Data =="")return;
		I_OBJECT_STORAGE ith;
		ith = this->Object_Storage.begin();
		int intdata = atoi(Data.c_str());
		while( ith != Object_Storage.end() )
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


	if( dwData == OBJECT_ID + 2)//ファイルデータから読み込み
	{
		ReadObjectFile(Data.c_str());
		return;
	}

	if( dwData == OBJECT_ID + 3)
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
		
		I_OBJECT_STORAGE ith;
		while( fscanf(fp,"%d,%f,%f,%f,%f,%f,%d,%f,%d ",&type,&x,&y,&z,&rotx,&roty,&group,&scale,&flag)  != EOF )
		{


			//　ここは好きに変える

			CreateObject(type);

			ith = Object_Storage.find(ID);
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

	if(dwData == OBJECT_ID + 4)
	{
		this->AllFilePut(Data);
		return;
	}
	if(dwData == OBJECT_ID + 5)
	{
		if(Object == NULL)return;
		if(Data =="")return;
		this->SelectObject( atoi(Data.c_str() ) );
		return;
	}
	if(dwData == OBJECT_ID + 6)//キャラデータを取得して上書き
	{
		//sscanfをつかう
		
		int _id=0,_type=0,_group=0,_flag=0;
		float _x=0,_y=0,_z=0,_rotx=0,_roty=0,_scale=0;
		//"%d,%f,%f,%f,%f,%f,%d ",&type,&x,&y,&z,&rotx,&roty,&group
		sscanf(Data.c_str(),"%d %d %f %f %f %f %f %d %f %d",&_id,&_type,&_x,&_y,&_z,&_rotx,&_roty,&_group,&_scale,&_flag);
		//sscanf(Data.c_str(),"%d%d",&SelectID,&SelectGroup);
		EDIT_O->Object_Storage[_id]->Type	= _type;
		EDIT_O->Object_Storage[_id]->Pos.x = _x;
		EDIT_O->Object_Storage[_id]->Pos.y = _y;
		EDIT_O->Object_Storage[_id]->Pos.z = _z;
		EDIT_O->Object_Storage[_id]->RotX	= _rotx;
		EDIT_O->Object_Storage[_id]->RotY	= _roty;
		EDIT_O->Object_Storage[_id]->Group = _group;
		EDIT_O->Object_Storage[_id]->Scale = _scale;
			EDIT_O->Object_Storage[_id]->eventFlag = _flag;


	}

	if(dwData ==  OBJECT_ID+9)//ファイルからオブジェクト解放
	{
		this->DieFileName(Data);
	}

	if(Data =="start_OBJ")//編集の開始
	{
		Edit();
	}
	else if(Data =="release_OBJ")//編集中のオブジェクトの開放
	{
		if(Object == NULL)
		{
			SendCommand("解放するオブジェクト対象が不正です",0);
			return;
		}
		else
		{
		//ReleaseObject(Object->ID);
			Die(Object->ID);
		}
	}
	else if(Data =="release_all_OBJ")//すべてのオブジェクトを開放
	{
		this->ReleaseAllObject();
	}
	else if(Data =="end_OBJ")//編集の終了
	{
		EndEdit();
	}
	else if(Data =="door_OBJ")//ドアの生成
	{
		CreateObject(DOOR);

	}else if(Data =="button_OBJ")//ボタンの生成
	{
		CreateObject(BUTTON);
	}else if(Data =="next_OBJ")//次のオブジェクトにアクセス
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
	}
	else if(Data =="torch_OBJ")//蜀台の生成
	{
		CreateObject(TAIMATU);
	}
	else if(Data =="tatefuda_OBJ")//看板の生成
	{
		CreateObject(TATEFUDA);
	}
	else if(Data =="warp_OBJ")//看板の生成
	{
		CreateObject(WARP);
	}
	else if(Data =="roomevent_OBJ")//看板の生成
	{
		CreateObject(ROOMEVENT);
	}
	else if(Data =="back_OBJ")//前のオブジェクトにアクセス
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

	}else if(Data =="delete_OBJ")//編集中のオブジェクトを抹消
	{
		SelectedDelete();
		EditMode(false);
	}else if(Data =="okinput_OBJ")//移動操作の有効
	{
		EDIT_O->Edit();
		InputNow = true;
	}

	else if(Data =="list_OBJ")//ツールにオブジェクト情報を一斉送信
	{
		std::string data;
		I_OBJECT_STORAGE ith;
		ith = this->Object_Storage.begin();
		while( ith != Object_Storage.end() )
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
			data += t_charscale;//追加
			
			data += ",";
			data += t_charflag;//追加

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

bool SetObject::Input(void)
{
	return InputNow;
}

void SetObject::SendCommand(std::string buffer,int Type)
{
	COPYDATASTRUCT cd;

	HWND hwnd;
	cd.dwData = Type;
	cd.cbData = (buffer.length())+1;
	cd.lpData = (PVOID)buffer.c_str();

	hwnd = FindWindow(NULL,"オブジェクト管理ツール");//変更しないこと
	SendMessage(hwnd,WM_COPYDATA,(WPARAM)NULL,(LPARAM)&cd);
}

void SetObject::CommandParser(string command, int &type, float &x, float &y, float &z, std::string &CommandCode)
{
}

void SetObject::CommandParser(string FileName, string command, int &type, float &x, float &y, float &z, std::string &CommandCode)
{


}

void SetObject::ReleaseAllObject()
{
	//指定されたIDを検索し、ヒットしたら開放。そうでなければスルー
	I_OBJECT_DATA its;
	
	//this->EndEdit();
	//for(int i = 0;i < Object_Data.size();i++ )
	//{
	//
	//	if(Object_Data.empty() == true )
	//		return;
	//	its = Object_Data.begin();
	//	its++;
	//	//if(Object_Data[i])
	//	//{
	//	//	if(Object != NULL)
	//	//	if(ID == Object->ID){Edit();}//編集中の場合バグるかもしれないので一応初期化
	//	Object_Data.c
	//	delete Object_Data[i];//指定されたIDのオブジェクトを削除する
	//	Object_Data.erase(its);//不正なアドレスを削除する

	//	//}

	//	if(Object_Data.empty() == true )
	//		return;
	//	
	//}
	for(its = Object_Data.begin();its != Object_Data.end();++its)
	{
		delete (*its);
	}
	Object_Data.clear();
}

void SetObject::Replace(string filename)
{
		std::map<int,BaseObject*>::iterator itc;

		itc = EDIT_O->Object_Storage.begin();

		while( itc != EDIT_O->Object_Storage.end() )
		{
		
				 EDIT_O->Die((*itc).second->ID);//ファイル名が違ったら削除する
				++itc;
			
		}
		if(filename == "")return;
		EDIT_O->ReadObjectFile(filename);

}
void  SetObject::ReadObjectFile(string filename)
{
	FILE *fp = NULL;
		fp = fopen(filename.c_str(), "r");//ファイルパスは好きに変更する aで追記、wで削除して上書き
		if (fp == NULL) 
		{
			SendCommand("ファイルの読み込みに失敗しました");
			return ;
		}

		int type =0,flag = 0;
		float x=0,y=0,z=0,rotx=0,roty=0,scale=0;
		I_OBJECT_STORAGE ith;
		int group=0;
		while( fscanf(fp,"%d,%f,%f,%f,%f,%f,%d,%f,%d ",&type,&x,&y,&z,&rotx,&roty,&group,&scale,&flag)  != EOF )
		{


			//　ここは好きに変える

			CreateObject(type);

			ith = Object_Storage.find(ID);
			(*ith).second->Pos.x = x;
			(*ith).second->Pos.y = y;
			(*ith).second->Pos.z = z;
			(*ith).second->RotX = rotx;
			(*ith).second->RotY = roty;
			(*ith).second->Group = group;
			(*ith).second->Scale = scale;
			(*ith).second->eventFlag = flag;
			(*ith).second->FileGroup = filename;
			
			//stage name

			if( filename == "")
			(*ith).second->StageName = STAGE_STAGE; 
			//----------------------
			if( filename == "")
			(*ith).second->StageName = STAGE_NORMAL; 
			

			//----------
		}
}



void  SetObject::Die(int ID)
{
	//std::vector<int>::iterator it;
	 Die_Data.push_back( ID );
	//it.push_back( ID );
}
void  SetObject::Die()
{std::vector<int>::iterator it;
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

void SetObject::DieFileName(std::string filename)
{
I_OBJECT_STORAGE ith;
		ith = this->Object_Storage.begin();
		while( ith != Object_Storage.end() )
		{
			if( (*ith).second->FileGroup == filename )
			Die( (*ith).second->ID);
			++ith;
		}
}