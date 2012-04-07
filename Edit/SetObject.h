#pragma once
#include "../Groval.h"
#include <map>
#include <vector>

using namespace std;
/*���g������
���g�p�O�̏���
Groval.h�ɃR���p�C���̌x���𖳎����閽�߂��C���N���[�h�K�[�h���ɋL�q����B�i�R���p�C���������Ȃ�j
#pragma warning(disable:4018)//signed��unsigned�̔�r
#pragma warning(disable:4200)//�z��̌x��
#pragma warning(disable:4819)//�����R�[�h�̌x��
#pragma warning(disable:4244)//int����FLOAT�ϊ�
#pragma warning(disable:4996)//fopen�̌x��

���I�u�W�F�N�g�̐���
�܂��L�����N�^�E�A�C�e���E�g���b�v�͂��ׂ�BaseObject���p�����邱�ƁB
���ł���BaseObject��Pos��J���������ADraw,Move,AI(�������z�֐�)�Ȃǂ̍Œ���̋@�\�����ł����B
�Ǘ����Ăق����I�u�W�F�N�g�̃N���X�̃R���X�g���N�^��EDIT_O->Add(this->ID);���L�q�B
�J�����ꂽ�Ƃ��Ɏ����I�ɓo�^�����������悤�A�f�X�g���N�^��EDIT_O->Delete(this->ID);��ǉ��B

���I�u�W�F�N�g�̊Ǘ�
�@�O���[�o���ϐ��ɂׂ������B�R���X�g���N�^�ɏ����Ă���̂Ŏ����I�ɓo�^�����B�������A�I�u�W�F�N�g�̊Ǘ��͎��ȐӔC�B
�A

int ID,Type;�𑀂肽���N���X�Ɏ������Ă����B�i�����BaseObject�N���X�j
Type�͓G���ǂ��̃C�x���g���A�C�e�����ȂǍD���ɒ�`���Ă����B����Ńt�@�C��

BaseObject�̃R���X�g���N�^��EDIT_O->Init()���ĂԁB
���O���[�o���ϐ��ɃL�������쐬�����Ə������O�ɐ��������̂ŁABaseObject�ŏ��������Ă���

�T�u�N���X�̃R���X�g���N�^�i���\�b�h�ł��悢�j��

��t����B����ŃI�u�W�F�N�g�����ꂽ�u�Ԃ�ID�ƃ}�l�[�W���[�ɓo�^�����B(�ő�R���T���)



�f�o�b�O���[�h�̎��s�F�@EDIT_O->Edit();
�f�o�b�O���[�h�̏I���F�@EDIT_O->EndEdit();

���ݕҏW���[�h�ɓ����Ă��邩�`�F�b�N����
if( EDIT_O->Editing() )
{
//�f�o�b�O���s
}

�A�g����
���̃I�u�W�F�N�g�ɕύX����F EDIT_O->Next();
�O�̃I�u�W�F�N�g�ɕύX����F EDIT_O->Back();

�I�u�W�F�N�g�̓o�^��j������FEDIT_O->Delete( test.ID );//ID��������B�j
���ݕύX���Ă���I�u�W�F�N�g��j������FEDIT_O->SelectedDelete();�ЂƂ̓o�^��������


���ׂẴI�u�W�F�N�g�̃f�[�^���o��
EDIT_O->AllFilePut();

�z��ŃL�����𐧌䂵�����ꍇ
�ŏ��̃L������ID���o���Ă����A�z��̍Ō�̃L������ID���܂�for�ŉ񂷁B�����L���������Ȃ��ꍇ����ID�̓X���[�����B

�����[�J���ϐ��Ő������ꂽ�C���X�^���X��DeleteAllObject�Ȃǂŉ������Ɨ�����

*/



/*�萔*/

#define  EDIT_O SetObject::GetInstance()	//�C���X�^���X�擾�������̂ŏȗ��B
#define	 I_OBJECT_DATA std::vector<BaseObject*>::iterator
#define	 I_OBJECT_STORAGE std::map<int,BaseObject*>::iterator
#define	 DEBUGSTRING EDIT_O->SendMessage


//====================================================================================

/*�C�x���g�����͊e�N���X��Object�f�[�^��GroupName���琄������������*/

//====================================================================================




//SetObject===========================================================================

class SetObject
{
public:
	//-------------------------------------------------------
	static SetObject* GetInstance()
	{
		static SetObject instance;		//�B��̃C���X�^���X
		return &instance;
	}
	//-------------------------------------------------------
	
	int		ID;							//���s����ID�̍ŐV���
	bool KeyCheck_Next;					//Next���g���ꍇ�A�A�����͖h�~���邽�߂̕ϐ��B�����lfalse�B
	bool KeyCheck_Back;					//Back���g���ꍇ�A�A�����͖h�~���邽�߂̕ϐ��B�����lfalse�B
	


	void Init(void);					//�Q�[�����ɂP�x�����Ă΂Ȃ��B
	void Edit(void);					//�ҏW���J�n�B[��]�����L�������o�^����Ă��Ȃ����Object��NULL�ɂȂ�A�ҏW���I������B
	
	int Add(BaseObject *chara);			//�L�����N�^��o�^�BID��Ԃ��B
	void Delete(int ID );				//�o�^�𖕏��BCreateObject�ȊO�Ő��������I�u�W�F�N�g�Ɏg�p���邱�Ƃ𐄏��B
	bool Editing(void);					//���݃I�u�W�F�N�g�̕ҏW�����擾����B�ҏW���Ȃ�true�B�����łȂ����false�B
	bool EditMode(void);				//���̃G�f�B�b�g�i�f�o�b�O���[�h�j���ǂ������擾����B�ҏW���ł����true�B�N���X�ɉe�����Ȃ��̂Ń��[�U�[�����R�Ɏg����B
	bool EditMode(bool);				//EditMode()�̃I�[�o�[���[�h�B���[�U�[���l��ύX�ł���B
	void EndEdit(void);					//�ҏW��Ԃ��I���
	void Next(void);					//���̃I�u�W�F�N�g�ɃA�N�Z�X
	void Back(void);					//�O�̃I�u�W�F�N�g�ɃA�N�Z�X
	void SelectedDelete(void);			//���ݕҏW���Ă���I�u�W�F�N�g�̓o�^�𖕏��BCreateObject�ȊO�Ő��������I�u�W�F�N�g�Ɏg�p���邱�Ƃ𐄏��B
	void ReadObjectFile(string filename);		//�w�肳�ꂽ�t�@�C������I�u�W�F�N�g����ǂݍ���
	void Replace(string filename);		//���ɓǂݍ��܂�Ă���t�@�C�����폜���āA�w�肳�ꂽ�t�@�C����ǂݍ���
	void AllFilePut(string);			//�ǂݍ��܂ꂽ�f�[�^�����ׂďo��
	void SelectObject(int ID);			//�w�肵��ID�̃I�u�W�F�N�g��ҏW�Ώۂɂ���B��v���Ȃ��ꍇ�͈�ԍŌ�ɓo�^���ꂽ�I�u�W�F�N�g���w�肷��B
	void CreateObject(int ObjectType);	//�w�肵���L�����N�^�[�𐶐�����

	void Command(char *,int dwData);	//�����Ă����R�}���h�������B���̃��\�b�h�͏���ꏊ�ȊO�ŌĂ΂Ȃ����ƁI
	bool Input(void);					//�L�[���͂����������B ��������ۂ��Ă���ꍇ��true�B
	void Die(int ID);					//�폜����ID��o�^
	void Die();							//�폜�̎��s
	void DieFileName(std::string filename); //�w�肵���t�@�C��������ǂݍ��܂ꂽ�I�u�W�F�N�g�����
	
	BaseObject *Object;				//�ҏW���̃L�����N�^�[�f�[�^	

		std::vector<int> Die_Data;		//�폜����L����ID���i�[
	std::vector<BaseObject*> Object_Data;		//CreateObject�Ő��������L����������
	std::map<int,BaseObject*> Object_Storage;	//���̂̃A�h���X���i�[
	
	//����Ȋ֐�
	void SendCommand(std::string,int Type = 0);		//�R�}���h���c�[���ɕԂ�
private:
		void ReleaseObject(int ID);			//CreateObject�Ő��������I�u�W�F�N�g���J������B
	void ReleaseAllObject();			//CreateObject�Ő��������I�u�W�F�N�g���ׂĂ��J������B
	
	bool EditNow;						//���ݕҏW�����B��Ԃ̎擾��Editing�ōs���B
	bool EditModeNow;					//���݃G�f�B�b�g���[�h���ǂ����B��Ԃ̎擾��EditMode�ōs���B
	bool InputNow;					//���݃L�[���͂����ۂ��邩�ǂ����B��Ԃ̎擾��NoInput�ōs���B
	
	int	 MakeID(void);					//���ʔԍ��𔭍s
	
	void CommandParser(string command,int &type,float &x,float &y, float &z,std::string &CommandCode);//�����񂩂�R�}���h�Ȃǂ�ǂݎ��
	void CommandParser(string FileName,string command,int &type,float &x,float &y, float &z,std::string &CommandCode);//�t�@�C������R�}���h��ǂݎ��
	bool InitFlag;

	std::map<int,BaseObject*>::iterator it;		//Object_Storage�̃C�e���[�^
	
	//Private�ɂ��邱�ƂŊ��S�V���O���g���ɂ���
	SetObject();
	~SetObject();
	SetObject(const SetObject& rhs);
	SetObject& operator=(const SetObject& rhs);
};
//=================================================================================================