#include "SetCharacter.h"
#include <string>
#include <iostream>
//�R���X�g���N�^
SetCharacter::SetCharacter(){this->Init();};

//�f�X�g���N�^
SetCharacter::~SetCharacter(){}


void SetCharacter::Init()
{

	if(InitFlag == false)//�d�����Ȃ��悤�ɂ���
	{
		ID = 0;							//���s�J�n�ԍ� 1�Ԗڂ���n�܂�B
		EditNow = false;				//�ҏW���[�h�ł͂Ȃ�
		KeyCheck_Next = false;			//���d���͖h�~
		KeyCheck_Back = false;			//���d���͖h�~
		it =  Character_Storage.begin();//�z��̐擪���w��
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
	EditNow = true;					//�ύX���ł���Ɠ`����
	it = Character_Storage.begin();	//�z��̐擪���w��
	//it == Character_Storage.end() ||
	if( Character_Storage.empty() )//�L�������o�^����Ă��Ȃ��ꍇ
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
void SetCharacter::EndEdit(void)
{
	EDIT_O->EndEdit();
	EditNow = false;//�ҏW���[�h���I���

}


int SetCharacter::MakeID(void)
{	ID = ID+1;
OutputDebugString("\nMakeID\n");
return ID;//ID�𔭍s���A1�J�E���g�𑝂₷

}
void SetCharacter::Delete(int ID)
{
	

}

int SetCharacter::Add(BaseCharacter *chara)
{	
	chara->ID = MakeID();
	Character_Storage.insert( std::map<int,BaseCharacter*>::value_type( ID, chara ) );//ID,�|�C���^��o�^
	OutputDebugString("\nAddObjectA\n");//Visual Studio�̏o�͉�ʂɒǉ����ꂽ���Ƃ�ʒm
	return chara->ID;
}	

bool SetCharacter::Editing(void)
{

	return EditNow;//���ݕҏW�����ǂ�����BOOL�^�ŕԂ�

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
	if( it != Character_Storage.end()  )//�Ō�̃I�u�W�F�N�g����Ȃ������珈��������
	{	
		Object = it->second;
		it++;

	}
}

void  SetCharacter::Back(void)
{
	if( Character_Storage.empty() ) return;
	//|| it != Character_Storage.end() || !Character_Storage.empty()
	if( it != Character_Storage.begin()  )//�ŏ�����Ȃ������珈��������
	{
		--it;
		Object = it->second;
	}
}

void SetCharacter::SelectedDelete()
{

	if(Object != NULL)
	{
		Character_Storage.erase(Object->ID);//���ݕҏW���̃L�����N�^���J������

		this->Edit();//Object���Ȃ��̂ŁA�L�����N�^�[���w�肷��B
	}
}

void SetCharacter::AllFilePut(string FileName)
{


	FILE *fp = NULL;
	fp = fopen(FileName.c_str(), "w");//�t�@�C���p�X�͍D���ɕύX���� a�ŒǋL�Aw�ō폜���ď㏑��
	if (fp == NULL) 
	{
		OutputDebugString("\nLocalDebugFile(Debug.txt) ReadErorr\n");

	}
	std::map<int,BaseCharacter*>::iterator its;
	its = Character_Storage.begin();

	bool flag = false;			//��x���������݂��Ȃ��ꍇ�ANoObject��\��
	while( its != Character_Storage.end() )
	{
		flag = true;
			
		//�����݁@�����͍D���ɕς���
		if( (*its).second->Type != PLAYER )//�v���C���[�͏����o���Ȃ�
		fprintf(fp,"%d,%f,%f,%f,%f,%f,%d,%f,%d ",(*its).second->Type,(*its).second->Pos.x,(*its).second->Pos.y,(*its).second->Pos.z,(*its).second->RotX,(*its).second->RotY,(*its).second->Group,(*its).second->Scale,(*its).second->eventFlag);//�������݂����f�[�^��I��
		++its;
	}
	fclose(fp);
	//�f�o�b�O�p�B��{�I�ɒʂ�Ȃ��͂��B
	if(flag == false)SendCommand("�f�[�^������܂���ł���",0);//�L���������Ȃ�����


	

	SendCommand("�t�@�C���ɏo�͂��܂���",0);

}

void SetCharacter::SelectObject(int ID)
{
	//�w�肳�ꂽID�̃I�u�W�F�N�g��Object�ɐݒ�
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
		OldID = 0;//���ݑ��݂��Ȃ�
	}
	else
	{
		
		//OldID = Object->ID;//�ЂƂO�̃L�����N�^��ID

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
	
		//OldID =(Character_Storage.end())->second->ID;//�ЂƂO�̃L�����N�^��ID
	}
	switch(ObjectType)
	{
		
	case PLAYER:
		
		this->Character_Data.push_back(  new  SkinPlayer() );
		it = Character_Storage.find(ID);
		it->second->Init();

		//�L�����N�^�̏o�����W����O�̃I�u�W�F�N�g�ƈꏏ�ɂ���
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

		//�L�����N�^�̏o�����W����O�̃I�u�W�F�N�g�ƈꏏ�ɂ���
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

		//�L�����N�^�̏o�����W����O�̃I�u�W�F�N�g�ƈꏏ�ɂ���
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

		//�L�����N�^�̏o�����W����O�̃I�u�W�F�N�g�ƈꏏ�ɂ���
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

		//�L�����N�^�̏o�����W����O�̃I�u�W�F�N�g�ƈꏏ�ɂ���
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

		//�L�����N�^�̏o�����W����O�̃I�u�W�F�N�g�ƈꏏ�ɂ���
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
	if(Character_Storage[ID])//�f�[�^�������
		Character_Storage.erase(ID);//�w�肳�ꂽID�̃I�u�W�F�N�g���폜����i�|�C���^�̉����j

	//�w�肳�ꂽID���������A�q�b�g������J���B�����łȂ���΃X���[
	I_CHARA_DATA its;
	its = Character_Data.begin();
	for(int i = 0;i < Character_Data.size();i++ )
	{
		if(Character_Data[i]->ID == ID)
		{
			if(Character_Data[i])
			{

				if(Object != NULL)
				if(ID == Object->ID){Edit();}//�ҏW���̏ꍇ�o�O�邩������Ȃ��̂ňꉞ������

				delete Character_Data[i];//�w�肳�ꂽID�̃I�u�W�F�N�g���폜����
				Character_Data.erase(its);//�s���ȃA�h���X���폜����
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
	//0�͕��ʂ̃R�}���h
	if( dwData == 1)//�`���ON/OFF
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


	if( dwData == 2)//�t�@�C���f�[�^����ǂݍ���
	{
		ReadObjectFile(Data.c_str());
		return;
	}

	if( dwData == 3)
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
		I_CHARA_STORAGE ith;
		while( fscanf(fp,"%d,%f,%f,%f,%f,%f,%d,%f,%d ",&type,&x,&y,&z,&rotx,&roty,&group,&scale,&flag)  != EOF )
		{


			//�@�����͍D���ɕς���

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
	if(dwData == 6)//�L�����f�[�^���擾���ď㏑��
	{
		//sscanf������
		
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

	if(dwData == 7)//�O���[�v�ړ����s
	{
		//this->GroupMoveID = Data;//�ړ�ID�̎w��
		//this->GroupMoveFlag = true;//���s
	}

	if(dwData == 8)//�O���[�v�ړ���~
	{
		this->GroupMoveFlag = false;//��~
	}


	if(dwData == 9)//�t�@�C������I�u�W�F�N�g���
	{
		this->DieFileName(Data);
	}

	if(Data =="start")//�ҏW�̊J�n
	{
		Edit();
	}
	else if(Data =="release")//�ҏW���̃I�u�W�F�N�g�̊J��
	{
			if(Object == NULL)
		{
			SendCommand("�������L�����N�^�[�Ώۂ��s���ł�",0);
			return;
		}
		else
		{
		//ReleaseObject(Object->ID);
			Die(Object->ID);//���S�ɉ���ł���悤�ɂȂ�
		}
	}
	else if(Data =="release_all")//���ׂẴI�u�W�F�N�g���J��
	{
		this->ReleaseAllObject();
	}
	else if(Data =="end")//�ҏW�̏I��
	{
		EndEdit();
	}
	//else if(Data =="enemy")//�G�̐���
	//{
	//	CreateObject(ENEMY);
	//}

	else if(Data =="player")//�v���C���[�̐���
	{
		CreateObject(PLAYER);
	}
	else if(Data =="houdai")//�v���C���[�̐���
	{
		CreateObject(HOUDAI);
	}
	else if(Data =="yuurei")//�v���C���[�̐���
	{
		CreateObject(YUUREI);
	}
	else if(Data =="fanbeam")//�v���C���[�̐���
	{
		CreateObject(FANBEAM);
	}
	else if(Data =="enemy")//�v���C���[�̐���
	{
		CreateObject(ENEMY);
	}
	else if(Data =="mummy")//�v���C���[�̐���
	{
		CreateObject(MUMMY);
	}
	else if(Data =="next")//���̃I�u�W�F�N�g�ɃA�N�Z�X
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
	}else if(Data =="back")//�O�̃I�u�W�F�N�g�ɃA�N�Z�X
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

	}else if(Data =="delete")//�ҏW���̃I�u�W�F�N�g�𖕏�
	{
		SelectedDelete();
		EDIT_C->EndEdit();
		EditMode(false);
	}else if(Data =="noinput")//�ړ�����̖���
	{
		InputNow = false;
	}else if(Data =="okinput")//�ړ�����̗L��
	{
		EDIT_C->Edit();
		InputNow = true;
	}

	else if(Data =="list")//�c�[���ɃI�u�W�F�N�g������đ��M
	{
		std::string data;
		I_CHARA_STORAGE ith;
		ith = this->Character_Storage.begin();
		while( ith != Character_Storage.end() )
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
			data += t_charscale;
			data += ",";
			data += t_charflag;

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

	hwnd = FindWindow(NULL,"�I�u�W�F�N�g�Ǘ��c�[��");//�ύX���Ȃ�����
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
	//if(Character_Storage[ID])//�f�[�^�������
	//	Character_Storage.erase(ID);//�w�肳�ꂽID�̃I�u�W�F�N�g���폜����i�|�C���^�̉����j

	////�w�肳�ꂽID���������A�q�b�g������J���B�����łȂ���΃X���[
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
	////	//	if(ID == Object->ID){Edit();}//�ҏW���̏ꍇ�o�O�邩������Ȃ��̂ňꉞ������
	////	Character_Data.c
	////	delete Character_Data[i];//�w�肳�ꂽID�̃I�u�W�F�N�g���폜����
	////	Character_Data.erase(its);//�s���ȃA�h���X���폜����

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
			
				EDIT_C->Die((*itc).second->ID);//�t�@�C�������������폜����
				++itc;
			
		}
		EDIT_C->ReadObjectFile(filename);

}

void  SetCharacter::ReadObjectFile(string filename)
{
	FILE *fp = NULL;
		fp = fopen(filename.c_str(), "r");//�t�@�C���p�X�͍D���ɕύX���� a�ŒǋL�Aw�ō폜���ď㏑��
		if (fp == NULL) 
		{
			SendCommand("�t�@�C���̓ǂݍ��݂Ɏ��s���܂���");
		return;
		}

		int type =0,flag=0;
		float x=0,y=0,z=0,rotx=0,roty=0,scale=0;
		I_CHARA_STORAGE ith;
		int group=0;
		while( fscanf(fp,"%d,%f,%f,%f,%f,%f,%d,%f,%d ",&type,&x,&y,&z,&rotx,&roty,&group,&scale,&flag)  != EOF )
		{


			//�@�����͍D���ɕς���

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
	if( ID == 1) return;//player�Ȃ�폜���Ȃ�
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
	//	DeletedID.push_back( (*it) );//���ID�̃��X�g�����
		
		++it;
	}
Die_Data.clear();//�폜���X�g�̃N���A


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