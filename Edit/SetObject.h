#pragma once
#include "../Groval.h"
#include <map>
#include <vector>

using namespace std;
/*■使い方■
■使用前の条件
Groval.hにコンパイラの警告を無視する命令をインクルードガード下に記述する。（コンパイルが速くなる）
#pragma warning(disable:4018)//signedとunsignedの比較
#pragma warning(disable:4200)//配列の警告
#pragma warning(disable:4819)//文字コードの警告
#pragma warning(disable:4244)//intからFLOAT変換
#pragma warning(disable:4996)//fopenの警告

■オブジェクトの生成
まずキャラクタ・アイテム・トラップはすべてBaseObjectを継承すること。
基底であるBaseObjectはPosやカメラ処理、Draw,Move,AI(純粋仮想関数)などの最低限の機能だけでいい。
管理してほしいオブジェクトのクラスのコンストラクタにEDIT_O->Add(this->ID);を記述。
開放されたときに自動的に登録が解除されるよう、デストラクタにEDIT_O->Delete(this->ID);を追加。

■オブジェクトの管理
①グローバル変数にべた書き。コンストラクタに書いてあるので自動的に登録される。ただし、オブジェクトの管理は自己責任。
②

int ID,Type;を操りたいクラスに持たせておく。（今回はBaseObjectクラス）
Typeは敵かどこのイベントかアイテムかなど好きに定義しておく。これでファイル

BaseObjectのコンストラクタでEDIT_O->Init()を呼ぶ。
※グローバル変数にキャラが作成されると初期化前に生成されるので、BaseObjectで初期化している

サブクラスのコンストラクタ（メソッドでもよい）に

を付ける。これでオブジェクトが作られた瞬間にIDとマネージャーに登録される。(最大３万５千体)



デバッグモードの実行：　EDIT_O->Edit();
デバッグモードの終了：　EDIT_O->EndEdit();

現在編集モードに入っているかチェックする
if( EDIT_O->Editing() )
{
//デバッグ実行
}

②使い方
次のオブジェクトに変更する： EDIT_O->Next();
前のオブジェクトに変更する： EDIT_O->Back();

オブジェクトの登録を破棄する：EDIT_O->Delete( test.ID );//IDを教える。）
現在変更しているオブジェクトを破棄する：EDIT_O->SelectedDelete();ひとつの登録が消える


すべてのオブジェクトのデータを出力
EDIT_O->AllFilePut();

配列でキャラを制御したい場合
最初のキャラのIDを覚えておき、配列の最後のキャラのIDをまでforで回す。もしキャラがいない場合そのIDはスルーされる。

※ローカル変数で生成されたインスタンスをDeleteAllObjectなどで解放すると落ちる

*/



/*定数*/

#define  EDIT_O SetObject::GetInstance()	//インスタンス取得が長いので省略。
#define	 I_OBJECT_DATA std::vector<BaseObject*>::iterator
#define	 I_OBJECT_STORAGE std::map<int,BaseObject*>::iterator
#define	 DEBUGSTRING EDIT_O->SendMessage


//====================================================================================

/*イベント処理は各クラスがObjectデータのGroupNameから推測し処理する*/

//====================================================================================




//SetObject===========================================================================

class SetObject
{
public:
	//-------------------------------------------------------
	static SetObject* GetInstance()
	{
		static SetObject instance;		//唯一のインスタンス
		return &instance;
	}
	//-------------------------------------------------------
	
	int		ID;							//発行するIDの最新状態
	bool KeyCheck_Next;					//Nextを使う場合、連続入力防止するための変数。初期値false。
	bool KeyCheck_Back;					//Backを使う場合、連続入力防止するための変数。初期値false。
	


	void Init(void);					//ゲーム中に１度しか呼ばない。
	void Edit(void);					//編集を開始。[注]もしキャラが登録されていなければObjectはNULLになり、編集を終了する。
	
	int Add(BaseObject *chara);			//キャラクタを登録。IDを返す。
	void Delete(int ID );				//登録を抹消。CreateObject以外で生成したオブジェクトに使用することを推奨。
	bool Editing(void);					//現在オブジェクトの編集中か取得する。編集中ならtrue。そうでなければfalse。
	bool EditMode(void);				//このエディット（デバッグモード）かどうかを取得する。編集中であればtrue。クラスに影響しないのでユーザーが自由に使える。
	bool EditMode(bool);				//EditMode()のオーバーロード。ユーザーが値を変更できる。
	void EndEdit(void);					//編集状態を終わる
	void Next(void);					//次のオブジェクトにアクセス
	void Back(void);					//前のオブジェクトにアクセス
	void SelectedDelete(void);			//現在編集しているオブジェクトの登録を抹消。CreateObject以外で生成したオブジェクトに使用することを推奨。
	void ReadObjectFile(string filename);		//指定されたファイルからオブジェクト情報を読み込む
	void Replace(string filename);		//既に読み込まれているファイルを削除して、指定されたファイルを読み込む
	void AllFilePut(string);			//読み込まれたデータをすべて出力
	void SelectObject(int ID);			//指定したIDのオブジェクトを編集対象にする。一致しない場合は一番最後に登録されたオブジェクトを指定する。
	void CreateObject(int ObjectType);	//指定したキャラクターを生成する

	void Command(char *,int dwData);	//送られてきたコマンドを処理。このメソッドは所定場所以外で呼ばないこと！
	bool Input(void);					//キー入力が制限される。 操作を拒否している場合はtrue。
	void Die(int ID);					//削除するIDを登録
	void Die();							//削除の実行
	void DieFileName(std::string filename); //指定したファイル名から読み込まれたオブジェクトを解放
	
	BaseObject *Object;				//編集時のキャラクターデータ	

		std::vector<int> Die_Data;		//削除するキャラIDを格納
	std::vector<BaseObject*> Object_Data;		//CreateObjectで生成したキャラが入る
	std::map<int,BaseObject*> Object_Storage;	//実体のアドレスを格納
	
	//特殊な関数
	void SendCommand(std::string,int Type = 0);		//コマンドをツールに返す
private:
		void ReleaseObject(int ID);			//CreateObjectで生成したオブジェクトを開放する。
	void ReleaseAllObject();			//CreateObjectで生成したオブジェクトすべてを開放する。
	
	bool EditNow;						//現在編集中か。状態の取得はEditingで行う。
	bool EditModeNow;					//現在エディットモードかどうか。状態の取得はEditModeで行う。
	bool InputNow;					//現在キー入力を拒否するかどうか。状態の取得はNoInputで行う。
	
	int	 MakeID(void);					//識別番号を発行
	
	void CommandParser(string command,int &type,float &x,float &y, float &z,std::string &CommandCode);//文字列からコマンドなどを読み取る
	void CommandParser(string FileName,string command,int &type,float &x,float &y, float &z,std::string &CommandCode);//ファイルからコマンドを読み取る
	bool InitFlag;

	std::map<int,BaseObject*>::iterator it;		//Object_Storageのイテレータ
	
	//Privateにすることで完全シングルトンにする
	SetObject();
	~SetObject();
	SetObject(const SetObject& rhs);
	SetObject& operator=(const SetObject& rhs);
};
//=================================================================================================