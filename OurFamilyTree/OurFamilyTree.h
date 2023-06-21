#ifndef OURFAMILYTREE_H
#define OURFAMILYTREE_H
#include <iostream>
#include <QInputDialog>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <QString>
#include <QTextStream>
#include <QDebug>

using namespace std;


typedef struct {
    int year;
    int month;
    int day;
}Date;
typedef struct {
    string name;		//名字
    // int depth;			//代数
    Date birthday;		//出生日期
    string IsMarried;	//是否已婚
    string address;		//地址
    string IsAlive;		//是否在世
    Date deathday;		//死亡日期
    string remarks;		//备注

}PersonMessage;

typedef struct treenode {
    PersonMessage personMessage;
    treenode* leftchild;		//左孩子
    treenode* rightbrother;		//右兄弟
    treenode* parent;			//父节点
    int depth;					//代数
}treenode;

//声明自定义数据类型
Q_DECLARE_METATYPE(Date)
Q_DECLARE_METATYPE(PersonMessage)
Q_DECLARE_METATYPE(treenode)
Q_DECLARE_METATYPE(treenode*)


void addNode(treenode*& , treenode*,treenode* );
void parseDate(stringstream& , Date&);
treenode* parseLine(string&);
treenode* buildTree(string filename);

void CreateGengalogyFile(treenode*&,fstream&,int );
void SetParent(treenode*& , treenode*&);

QString PrintAllMessage(treenode*);
QString PrintMessage(treenode* );
QString PrintDepthMessage(treenode* , int );
QString SearchName(treenode* , string,bool&);
QString PrintMessageByName(treenode*,string);
QString SearchBirthday(treenode*, Date,bool&);
QString PrintMessageByBirthday(treenode*,Date);
treenode* findPersonByName(treenode*, string);

void ReturnTreenodeByName(treenode*&, string,treenode*&);

QString JudgeRelationship(treenode*,QString,QString);
void ReturnTreenodeByNameAndBirthday(treenode*&, string, treenode*&);
QString InsertChild(treenode*&,string,PersonMessage);
void DeleteMember(treenode*&);
QString ModifyMember(treenode*&,string,PersonMessage);
void SaveFile(treenode*, fstream&);

//自写文件保存代码块
void writeDate(ofstream& fout, const Date& date);
void writePerson(ofstream& fout, const PersonMessage& person);
void saveTree(treenode* node, ofstream& fout);
QString saveTreeToFile(string filename, treenode* root);
















#endif // OURFAMILYTREE_H
