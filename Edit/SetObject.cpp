#include "SetObject.h"
#include <string>
#include <iostream>
//�R���X�g���N�^
SetObject::SetObject(){ this->Init(); };

//�f�X�g���N�^
SetObject::~SetObject(){}


void SetObject::Init()
{

	if(InitFlag == false)//�d�����Ȃ��悤�ɂ���
	{
		ID = 0;							//���s�J�n�ԍ� 1�Ԗڂ���n�܂�B
		EditNow = false;				//�ҏW���[�h�ł͂Ȃ�
		KeyCheck_Next = false;			//���d���͖h�~
		KeyCheck_Back = false;			//���d���͖h�~
		it =  Object_Storage.begin();//�z��̐擪���w��
		this->Object_Data.reserve(1000);
		InitFlag = true;
		InputNow = false;
		Object = NULL;
		
	}
}

void SetObject::Edit(void)
{	
	
	EditNow = true;					//�ύX���ł���Ɠ`����
	it = Object_Storage.begin();	//�z��̐擪���w��
	//it == Object_Storage.end() ||
	if( Object_Storage.empty() )//�L�������o�^����Ă��Ȃ��ꍇ
	{
		Object = NULL;//�L���������Ȃ��̂ŔO�̂���NULL
		EditNow = false;//�I�u�W�F�N�g���Ȃɂ������Ă��Ȃ��ƕҏW���[�h�ł͂Ȃ�

		OutputDebugString("\nNo_ObjectA\n");
	}
	else//�L�����N�^�[�������Ă���̂�Object�ɔz��̐擪�̃L������ݒ�
	{

		Object = it->second;//�I�u�W�F�N�g�Ƀf�[�^������
	}

	//debug



}
void SetObject::EndEdit(void)
{
	
	EditNow = false;//�ҏW���[�h���I���

}


int SetObject::MakeID(void)
{	ID = ID+1;
OutputDebugString("\nMakeID\n");
return ID;//ID�𔭍s���A1�J�E���g�𑝂₷

}
void SetObject::Delete(int ID)
{
	//if(Object_Storage[ID])//�f�[�^�������
	//	Object_Storage.erase(ID);//�w�肳�ꂽID�̃I�u�W�F�N�g���폜����i�|�C���^�̉����j

}

int SetObject::Add(BaseObject *chara)
{	
	chara->ID = MakeID();
	Object_Storage.insert( std::map<int,BaseObject*>::value_type( ID, chara ) );//ID,�|�C���^��o�^
	OutputDebugString("\nAddObjectA\n");//Visual Studio�̏o�͉�ʂɒǉ����ꂽ���Ƃ�ʒm
	return chara->ID;
}	

bool SetObject::Editing(void)
{

	return EditNow;//���ݕҏW�����ǂ�����BOOL�^�ŕԂ�

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
	if( it != Object_Storage.end()  )//�Ō�̃I�u�W�F�N�g����Ȃ������珈��������
	{	
		Object = it->second;
		it++;

	}
}

void  SetObject::Back(void)
{
	if( Object_Storage.empty() ) return;
	//|| it != Object_Storage.end() || !Object_Storage.empty()
	if( it != Object_Storage.begin()  )//�ŏ�����Ȃ������珈��������
	{
		--it;
		Object = it->second;
	}
}

void SetObject::SelectedDelete()
{

	if(Object != NULL)
	{
		Object_Storage.erase(Object->ID);//���ݕҏW���̃L�����N�^���J������

		this->Edit();//Object���Ȃ��̂ŁA�L�����N�^�[���w�肷��B
	}
}

void SetObject::AllFilePut(string FileName)
{


	FILE *fp = NULL;
	fp = fopen(FileName.c_str(), "w");//�t�@�C���p�X�͍D���ɕύX���� a�ŒǋL�Aw�ō폜���ď㏑��
	if (fp == NULL) 
	{
		OutputDebugString("\nLocalDebugFile(Debug.txt) ReadErorr\n");

	}
	std::map<int,BaseObject*>::iterator its;
	its = Object_Storage.begin();

	bool flag = false;			//��x���������݂��Ȃ��ꍇ�ANoObject��\��
	while( its != Object_Storage.end() )
	{
		flag = true;

		//�����݁@�����͍D���ɕς���
		fprintf(fp,"%d,%f,%f,%f,%f,%f,%d,%f,%d ",(*its).second->Type,(*its).second->Pos.x,(*its).second->Pos.y,(*its).second->Pos.z,(*its).second->RotX,(*its).second->RotY,(*its).second->Group,(*its).second->Scale,(*its).second->eventFlag);//�������݂����f�[�^��I��
		++its;
	}

	//�f�o�b�O�p�B��{�I�ɒʂ�Ȃ��͂��B
	if(flag == false) fprintf(fp,"No_Object");//�L���������Ȃ�����


	fclose(fp);

	Command("�t�@�C���ɏo�͂��܂���",0);

}

void SetObject::SelectObject(int ID)
{
	//�w�肳�ꂽID�̃I�u�W�F�N�g��Object�ɐݒ�
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
		OldID = 0;//���ݑ��݂��Ȃ�
	}
	else
	{
		
		//OldID = Object->ID;//�ЂƂO�̃L�����N�^��ID
		it = Object_Storage.end();
		it--;
		OldID = (*it).second->ID;
		//OldID =(Character_Storage.end())->second->ID;//�ЂƂO�̃L�����N�^��ID
		
	}
	switch(ObjectType)
	{
		
	case BUTTON:
		
		this->Object_Data.push_back(  new Button() );
		it = Object_Storage.find(ID);
		it->second->Init();

		//�L�����N�^�̏o�����W����O�̃I�u�W�F�N�g�ƈꏏ�ɂ���
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

		//�L�����N�^�̏o�����W����O�̃I�u�W�F�N�g�ƈꏏ�ɂ���
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

		//�L�����N�^�̏o�����W����O�̃I�u�W�F�N�g�ƈꏏ�ɂ���
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

		//�L�����N�^�̏o�����W����O�̃I�u�W�F�N�g�ƈꏏ�ɂ���
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

		//�L�����N�^�̏o�����W����O�̃I�u�W�F�N�g�ƈꏏ�ɂ���
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

		//�L�����N�^�̏o�����W����O�̃I�u�W�F�N�g�ƈꏏ�ɂ���
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
		if(Object_Storage[ID])//�f�[�^�������
		Object_Storage.erase(ID);//�w�肳�ꂽID�̃I�u�W�F�N�g���폜����i�|�C���^�̉�

	//�w�肳�ꂽID���������A�q�b�g������J���B�����łȂ���΃X���[
	I_OBJECT_DATA its;
	its = Object_Data.begin();
	for(int i = 0;i < Object_Data.size();i++ )
	{
		if(Object_Data[i]->ID == ID)
		{
			if(Object_Data[i])
			{

				if(Object != NULL)
				if(ID == Object->ID){Edit();}//�ҏW���̏ꍇ�o�O�邩������Ȃ��̂ňꉞ������

				delete Object_Data[i];//�w�肳�ꂽID�̃I�u�W�F�N�g���폜����
				Object_Data.erase(its);//�s���ȃA�h���X���폜����
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
	//0�͕��ʂ̃R�}���h
	if( dwData == 21)//�`���ON/OFF
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


	if( dwData == OBJECT_ID + 2)//�t�@�C���f�[�^����ǂݍ���
	{
		ReadObjectFile(Data.c_str());
		return;
	}

	if( dwData == OBJECT_ID + 3)
	{
		ReleaseAllObject();//���ׂč폜
		FILE *fp = NULL;
		fp = fopen(Data.c_str(), "r");//�t�@�C���p�X�͍D���ɕύX���� a�ŒǋL�Aw�ō폜���ď㏑��
		if (fp == NULL) 
		{
			SendCommand("�t�@�C����ǂݍ��݂Ɏ��s���܂���");
			return;

		}

		int type =0,flag=0;
		float x=0,y=0,z=0,rotx=0,roty=0,scale=0;
		int group=0;
		
		I_OBJECT_STORAGE ith;
		while( fscanf(fp,"%d,%f,%f,%f,%f,%f,%d,%f,%d ",&type,&x,&y,&z,&rotx,&roty,&group,&scale,&flag)  != EOF )
		{


			//�@�����͍D���ɕς���

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
	if(dwData == OBJECT_ID + 6)//�L�����f�[�^���擾���ď㏑��
	{
		//sscanf������
		
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

	if(dwData ==  OBJECT_ID+9)//�t�@�C������I�u�W�F�N�g���
	{
		this->DieFileName(Data);
	}

	if(Data =="start_OBJ")//�ҏW�̊J�n
	{
		Edit();
	}
	else if(Data =="release_OBJ")//�ҏW���̃I�u�W�F�N�g�̊J��
	{
		if(Object == NULL)
		{
			SendCommand("�������I�u�W�F�N�g�Ώۂ��s���ł�",0);
			return;
		}
		else
		{
		//ReleaseObject(Object->ID);
			Die(Object->ID);
		}
	}
	else if(Data =="release_all_OBJ")//���ׂẴI�u�W�F�N�g���J��
	{
		this->ReleaseAllObject();
	}
	else if(Data =="end_OBJ")//�ҏW�̏I��
	{
		EndEdit();
	}
	else if(Data =="door_OBJ")//�h�A�̐���
	{
		CreateObject(DOOR);

	}else if(Data =="button_OBJ")//�{�^���̐���
	{
		CreateObject(BUTTON);
	}else if(Data =="next_OBJ")//���̃I�u�W�F�N�g�ɃA�N�Z�X
	{
		Next();
		//-----------------------------------ID��string��
		if(Object == NULL)return;
		string data;
		char t_char[20];//�P�O���炢�ł�OK
		sprintf_s(t_char,"%d",Object->ID);
		data = t_char;
		//-----------------------------------
		SendCommand(data,2);//�c�[���Ɍ��ݑI�𒆂�ID�𑗂�
	}
	else if(Data =="torch_OBJ")//冑�̐���
	{
		CreateObject(TAIMATU);
	}
	else if(Data =="tatefuda_OBJ")//�Ŕ̐���
	{
		CreateObject(TATEFUDA);
	}
	else if(Data =="warp_OBJ")//�Ŕ̐���
	{
		CreateObject(WARP);
	}
	else if(Data =="roomevent_OBJ")//�Ŕ̐���
	{
		CreateObject(ROOMEVENT);
	}
	else if(Data =="back_OBJ")//�O�̃I�u�W�F�N�g�ɃA�N�Z�X
	{
		Back();
		//-----------------------------------ID��string��
		if(Object == NULL)return;
		string data;
		char t_char[20];//�P�O���炢�ł�OK
		sprintf_s(t_char,"%d",Object->ID);
		data = t_char;
		//-----------------------------------
		SendCommand(data,2);//�c�[���Ɍ��ݑI�𒆂�ID�𑗂�

	}else if(Data =="delete_OBJ")//�ҏW���̃I�u�W�F�N�g�𖕏�
	{
		SelectedDelete();
		EditMode(false);
	}else if(Data =="okinput_OBJ")//�ړ�����̗L��
	{
		EDIT_O->Edit();
		InputNow = true;
	}

	else if(Data =="list_OBJ")//�c�[���ɃI�u�W�F�N�g������đ��M
	{
		std::string data;
		I_OBJECT_STORAGE ith;
		ith = this->Object_Storage.begin();
		while( ith != Object_Storage.end() )
		{
			//int��float��string�ɕϊ��ł��Ȃ��̂ŁA��Uchar�ɕϊ����Ă���string�ɂ���B
			//int����char�Achar����string�̔���
			char t_char[20];//�P�O���炢�ł�OK
			sprintf_s(t_char,"%d",(*ith).second->ID);

			data += t_char;//ID�ǉ�
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

			data += t_charx;//�ǉ�
			data += ",";
			data += t_chary;//�ǉ�
			data += ",";
			data += t_charz;//�ǉ�
			data += ",";

			data += t_charvisible;
			data += ",";

			data += t_charrx;//�ǉ�
			data += ",";
			data += t_charry;//�ǉ�
			data += ",";

			
			
			data += t_chargroup;//�ǉ�

			data += ",";
			data += t_charscale;//�ǉ�
			
			data += ",";
			data += t_charflag;//�ǉ�

			data += " ";//�I��
			ith++;
		}
		SendCommand(data,1);

		//-----------------------------------ID��string��
		if(Object == NULL)return;
		string d;
		char t_char[20];//�P�O���炢�ł�OK
		sprintf_s(t_char,"%d",Object->ID);
		d = t_char;
		//-----------------------------------
		SendCommand(d,2);//�c�[���Ɍ��ݑI�𒆂�ID�𑗂�

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

	hwnd = FindWindow(NULL,"�I�u�W�F�N�g�Ǘ��c�[��");//�ύX���Ȃ�����
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
	//�w�肳�ꂽID���������A�q�b�g������J���B�����łȂ���΃X���[
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
	//	//	if(ID == Object->ID){Edit();}//�ҏW���̏ꍇ�o�O�邩������Ȃ��̂ňꉞ������
	//	Object_Data.c
	//	delete Object_Data[i];//�w�肳�ꂽID�̃I�u�W�F�N�g���폜����
	//	Object_Data.erase(its);//�s���ȃA�h���X���폜����

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
		
				 EDIT_O->Die((*itc).second->ID);//�t�@�C�������������폜����
				++itc;
			
		}
		if(filename == "")return;
		EDIT_O->ReadObjectFile(filename);

}
void  SetObject::ReadObjectFile(string filename)
{
	FILE *fp = NULL;
		fp = fopen(filename.c_str(), "r");//�t�@�C���p�X�͍D���ɕύX���� a�ŒǋL�Aw�ō폜���ď㏑��
		if (fp == NULL) 
		{
			SendCommand("�t�@�C���̓ǂݍ��݂Ɏ��s���܂���");
			return ;
		}

		int type =0,flag = 0;
		float x=0,y=0,z=0,rotx=0,roty=0,scale=0;
		I_OBJECT_STORAGE ith;
		int group=0;
		while( fscanf(fp,"%d,%f,%f,%f,%f,%f,%d,%f,%d ",&type,&x,&y,&z,&rotx,&roty,&group,&scale,&flag)  != EOF )
		{


			//�@�����͍D���ɕς���

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
	//	DeletedID.push_back( (*it) );//���ID�̃��X�g�����
		
		++it;
	}
Die_Data.clear();//�폜���X�g�̃N���A


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