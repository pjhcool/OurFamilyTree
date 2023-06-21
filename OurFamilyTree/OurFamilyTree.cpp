#include "OurFamilyTree.h"


//#########################################################################
//读入数据
//把node结点加入根节点
void addNode(treenode*& root, treenode* node,treenode* parent = NULL) {
    if (root == NULL) {
        root = node;
        node->parent = parent;
        return;
    }

    if (root->depth == node->depth - 1) {
        addNode(root->leftchild, node,root);
    } else {
        addNode(root->rightbrother, node,parent);
    }
}

// 从字符串流中读入日期数据
void parseDate(stringstream& fin, Date& date) {
    fin >> date.year >> date.month >> date.day;
}

// 传入 txt 文档中的一行数据，最后以一个成员节点返回
treenode* parseLine(string& line) {
    stringstream ss(line);
    treenode* node = new treenode();

    ss >> node->depth >> node->personMessage.name;
    parseDate(ss, node->personMessage.birthday);
    ss >> node->personMessage.IsMarried >> node->personMessage.address >> node->personMessage.IsAlive;
    parseDate(ss, node->personMessage.deathday);
    getline(ss, node->personMessage.remarks);  // 读取该行余下的部分 给 remarks

    node->leftchild = node->rightbrother = node->parent = NULL;

    return node;
}

// 读取文件，并建立一颗树
treenode* buildTree(string filename) {
    ifstream fin(filename);
    if (!fin) {
        qDebug() << "Could not open file\n";
        return NULL;
    }

    string line;
    getline(fin, line);
    treenode* root = parseLine(line);
    while (getline(fin, line)) {
        addNode(root, parseLine(line));
    }

    fin.close();
    return root;
}



//#########################################################################





//设置父节点
void SetParent(treenode*& root, treenode*& parent)
{
    root->parent = parent;
    if (root->leftchild != NULL)
    {
        SetParent(root->leftchild, root);
    }
    if (root->rightbrother != NULL)
    {
        SetParent(root->rightbrother, parent);
    }

}

//打印家谱所有成员信息
QString PrintAllMessage(treenode* root)
{
    QString qstr = "";
    if (root != NULL)
    {
       qstr+= PrintMessage(root);
    }
    if (root->leftchild != NULL)
    {
        qstr+=PrintAllMessage(root->leftchild);
    }
    if (root->rightbrother != NULL)
    {
       qstr+= PrintAllMessage(root->rightbrother);
    }
    return qstr;
}

//打印家谱某成员信息
QString PrintMessage(treenode* target)
{
    QString qstr = "";
//	cout << "姓名:" << target->personMessage.name<<"  ";
//	cout << "家谱中第" << target->depth << "代人" << "  ";
    qstr = QString::fromStdString("姓名:" + (target->personMessage.name) + "  "+"家谱中第" + to_string(target->depth)+"代人"+"  ");
    if (target->personMessage.IsMarried == "已婚")
    {
//        cout << "婚姻状况:已婚" << endl;
        qstr += QString::fromStdString("婚姻状况:已婚\n");
    }
    else if (target->personMessage.IsMarried == "未婚")
    {
//        cout << "婚姻状况:未婚" << endl;
        qstr += "婚姻状况: 未婚\n";
    }

//    cout << "出生日期:" << target->personMessage.birthday.year << "年" << target->personMessage.birthday.month << "月" << target->personMessage.birthday.day << "日" << endl;
//    cout << "地址:" << target->personMessage.address << endl;
    qstr += QString("出生日期: %1年%2月%3日\n").arg(target->personMessage.birthday.year).arg(target->personMessage.birthday.month).arg(target->personMessage.birthday.day);
    qstr += QString("地址: %1\n").arg(QString::fromStdString(target->personMessage.address));

    if (target->personMessage.IsAlive == "离世")
    {
//        cout << "逝世日期:" << target->personMessage.deathday.year << "年" << target->personMessage.deathday.month << "月" << target->personMessage.deathday.day << "日" << endl;
    qstr += QString("逝世日期: %1年%2月%3日\n").arg(target->personMessage.deathday.year).arg(target->personMessage.deathday.month).arg(target->personMessage.deathday.day);
    }
//    cout << "备注:" << target->personMessage.remarks << endl;
//    cout << endl;
//    cout << endl;
    qstr += QString("备注: %1\n\n\n").arg(QString::fromStdString(target->personMessage.remarks));
    return qstr;
}

//打印某层成员信息
QString PrintDepthMessage(treenode* root, int depth)
{
    QString qstr ="";
    if (root->depth == depth)
    {
        qstr+=PrintMessage(root);
    }
    if (root->leftchild != NULL)
    {
        qstr+=PrintDepthMessage(root->leftchild, depth);
    }
    if (root->rightbrother != NULL)
    {
        qstr+=PrintDepthMessage(root->rightbrother, depth);
    }
    return qstr;
}

//查找某姓名的信息
QString SearchName(treenode* root, string name,bool& IsFind)
{
    QString qstr ="";
    if (name == root->personMessage.name)
    {
        IsFind = true;
//        cout << "此人信息:" << endl;
//        PrintMessage(root);
        qstr += "此人信息:\n";
        qstr += PrintMessage(root);
        if (root->parent != NULL)
        {
//            cout << "其父亲信息:" << endl;
//            PrintMessage(root->parent);
            qstr += "其父亲信息:\n";
            qstr += PrintMessage(root->parent);
        }
        treenode* p = root;
        int childrennum = 0;
        if (p->leftchild != NULL)
        {
//            cout << "其孩子" << ++childrennum << "信息:" << endl;
//            p = p->leftchild;
//            PrintMessage(p);
            qstr += QString("其孩子%1信息:\n").arg(++childrennum);
            p = p->leftchild;
            qstr += PrintMessage(p);
            while (p->rightbrother != NULL)
            {
//                cout << "其孩子" << ++childrennum << "信息:" << endl;
//                p = p->rightbrother;
//                PrintMessage(p);
                qstr += QString("其孩子%1信息:\n").arg(++childrennum);
                p = p->rightbrother;
                qstr += PrintMessage(p);
            }
        }
    }
    if (root->leftchild != NULL)
    {
        qstr+=SearchName(root->leftchild, name, IsFind);
    }
    if (root->rightbrother != NULL)
    {
        qstr+=SearchName(root->rightbrother, name, IsFind);
    }
    return qstr;
}

//按姓名输出成员信息
QString PrintMessageByName(treenode* root,string name)
{
    QString qstr = "";
    bool IsFind = false;
    qstr = SearchName(root, name, IsFind);
    if (IsFind == false)
    {
        qstr += "家谱中无此名字的人!\n";
    }
    return qstr;
}


//查找某日期的信息
QString SearchBirthday(treenode* root, Date birthday,bool& IsFind)
{
    QString qstr = "";
    if ((birthday.day == root->personMessage.birthday.day)&& (birthday.month == root->personMessage.birthday.month)&& (birthday.year == root->personMessage.birthday.year))
    {
        IsFind = true;
//        cout << "此人信息:" << endl;
//        PrintMessage(root);
        qstr += "此人信息:\n";
        qstr += PrintMessage(root);
        if (root->parent != NULL)
        {
//            cout << "其父亲信息:" << endl;
//            PrintMessage(root->parent);
            qstr += "其父亲信息:\n";
            qstr += PrintMessage(root->parent);
        }
        treenode* p = root;
        int childrennum = 0;
        if (p->leftchild != NULL)
        {
//            cout << "其孩子" << ++childrennum << "信息:" << endl;
            qstr += QString("其孩子%1信息:\n").arg(++childrennum);
            p = p->leftchild;
            qstr+=PrintMessage(p);
            while (p->rightbrother != NULL)
            {
//                cout << "其孩子" << ++childrennum << "信息:" << endl;
                qstr += QString("其孩子%1信息:\n").arg(++childrennum);
                p = p->rightbrother;
                qstr+=PrintMessage(p);
            }
        }
    }
    if (root->leftchild != NULL)
    {
        qstr+=SearchBirthday(root->leftchild, birthday, IsFind);
    }
    if (root->rightbrother != NULL)
    {
       qstr+= SearchBirthday(root->rightbrother, birthday, IsFind);
    }
    return qstr;
}

//按出生日期输出成员信息
QString PrintMessageByBirthday(treenode* root,Date date)
{
    QString qstr = "";


    bool IsFind = false;
    qstr = SearchBirthday(root, date, IsFind);

    if (IsFind == false)
    {
        qstr += "家谱中无此出生日期的人!\n";
    }

    return qstr;
}

//#################################################################
// 在家谱树中，寻找一个指定的人名，并返回其指针
treenode* findPersonByName(treenode* node, string name) {
    if (node == NULL) {
        return NULL;
    }

    if (node->personMessage.name == name) {
        return node;
    }

    treenode* found = findPersonByName(node->leftchild, name);
    if (found != NULL) {
        return found;
    }

    return findPersonByName(node->rightbrother, name);
}
//#################################################################

void ReturnTreenodeByName(treenode*& root, string name,treenode*& target)
{
    if (root->personMessage.name == name)
    {
        target = root;
    }
    if (root->leftchild != NULL)
    {
        ReturnTreenodeByName(root->leftchild, name, target);
    }
    if (root->rightbrother != NULL)
    {
        ReturnTreenodeByName(root->rightbrother, name, target);
    }
}

//判断两人关系
QString JudgeRelationship(treenode* root,QString member1,QString member2)
{
    QString qstr = "";

    treenode* Person1 = NULL;
    treenode* Person2 = NULL;
    ReturnTreenodeByName(root, member1.toStdString(), Person1);
    ReturnTreenodeByName(root, member2.toStdString(), Person2);

    if (Person1 == NULL)
    {
        qstr += "家谱中没有" + member1 + "这个人\n";
        return qstr;
    }

    if (Person2 == NULL)
    {
        qstr += "家谱中没有" + member2 + "这个人\n";
        return qstr;
    }

    int depth1 = Person1->depth;
    int depth2 = Person2->depth;

    if (depth1 == depth2)
    {
        qstr += member1 + "和" + member2 + "为兄弟关系\n";
        return qstr;
    }

    if (depth1 - depth2 == -1)
    {
        if (Person2->parent == Person1)
        {
            qstr += member1 + "是" + member2 + "的父亲\n";
            return qstr;
        }
        else
        {
            qstr += member1 + "是" + member2 + "的叔叔\n";
        }
    }

    if (depth1 - depth2 == 1)
    {
        if (Person1->parent == Person2)
        {
            qstr += member2 + "是" + member1 + "的父亲\n";
            return qstr;
        }
        else
        {
            qstr += member2 + "是" + member1 + "的叔叔\n";
            return qstr;
        }
    }

    if (depth1 - depth2 == -2)
    {
        qstr += member1 + "是" + member2 + "的爷爷\n";
        return qstr;
    }

    if (depth1 - depth2 == 2)
    {
        qstr += member2 + "是" + member1 + "的爷爷\n";
        return qstr;
    }

    if (depth1 - depth2 < -2)
    {
        qstr += member1 + "是" + member2 + "的祖先\n";
        return qstr;
    }

    if (depth2 - depth1 < -2)
    {
        qstr += member2 + "是" + member1 + "的祖先\n";
        return qstr;
    }

    return qstr;
}


void ReturnTreenodeByNameAndBirthday(treenode*& root, string name, treenode*& target)
{
    if ((root->personMessage.name == name) )
    {
        target = root;
        return ;
    }
    if (root->leftchild != NULL)
    {
        ReturnTreenodeByNameAndBirthday(root->leftchild, name, target);
    }
    if (root->rightbrother != NULL)
    {
        ReturnTreenodeByNameAndBirthday(root->rightbrother, name, target);
    }
}

//添加孩子
QString InsertChild(treenode*& root,string father,PersonMessage childl)
{
    QString qstr = "";

    treenode* person = NULL;
    ReturnTreenodeByName(root, father, person);
    if (person == NULL)
    {
        qstr += "输入信息有误!\n";
        return qstr;
    }

    treenode* child = new treenode;
    child->depth = person->depth + 1;

//    qstr += "请输入姓名:\n";
//    QTextStream(stdout) << qstr;
//    child->personMessage.name = (QInputDialog::getText(nullptr, "输入姓名", "请输入孩子的姓名:")).toStdString();

//    qstr += "请输入生日(年,月,日):\n";
//    QTextStream(stdout) << qstr;
//    child->personMessage.birthday.year = QInputDialog::getInt(nullptr, "输入年份", "请输入孩子的出生年份:");
//    child->personMessage.birthday.month = QInputDialog::getInt(nullptr, "输入月份", "请输入孩子的出生月份:");
//    child->personMessage.birthday.day = QInputDialog::getInt(nullptr, "输入日期", "请输入孩子的出生日期:");

//    qstr += "请输入地址:\n";
//    QTextStream(stdout) << qstr;
//    child->personMessage.address = (QInputDialog::getText(nullptr, "输入地址", "请输入孩子的地址:")).toStdString();

//    qstr += "请输入婚姻状况，已婚输入0，未婚输入1:\n";
//    QTextStream(stdout) << qstr;
//    int IsMarried = QInputDialog::getInt(nullptr, "输入婚姻状况", "已婚输入0，未婚输入1:");
    while (childl.IsMarried != "0" && childl.IsMarried != "1")
    {
        qstr += "输入数据非法，请重新输入:\n";
//        QTextStream(stdout) << qstr;
//        IsMarried = QInputDialog::getInt(nullptr, "输入婚姻状况", "已婚输入0，未婚输入1:");
    }
    child->personMessage.IsMarried = (childl.IsMarried == "0") ? "已婚" : "未婚";

//    qstr += "该人是否在世，如果在世输入0，已去世输入1:\n";
//    QTextStream(stdout) << qstr;
//    int IsAlive = QInputDialog::getInt(nullptr, "输入在世状态", "在世输入0，已去世输入1:");
//    while (IsAlive != 0 && IsAlive != 1)
//    {
//        qstr += "输入数据非法，请重新输入:\n";
//        QTextStream(stdout) << qstr;
//        IsAlive = QInputDialog::getInt(nullptr, "输入在世状态", "在世输入0，已去世输入1:");
//    }
//    child->personMessage.IsAlive = (IsAlive == 0) ? "在世" : "离世";

//    if (child->personMessage.IsAlive == "离世")
//    {
//        qstr += "请输入去世日期(年,月,日):\n";
//        QTextStream(stdout) << qstr;
//        child->personMessage.deathday.year = QInputDialog::getInt(nullptr, "输入年份", "请输入孩子的去世年份:");
//        child->personMessage.deathday.month = QInputDialog::getInt(nullptr, "输入月份", "请输入孩子的去世月份:");
//        child->personMessage.deathday.day = QInputDialog::getInt(nullptr, "输入日期", "请输入孩子的去世日期:");
//    }

//    qstr += "请输入备注:\n";
//    QTextStream(stdout) << qstr;
//    child->personMessage.remarks = (QInputDialog::getText(nullptr, "输入备注", "请输入孩子的备注:")).toStdString();

    if (person->leftchild == NULL)
    {
        person->leftchild = child;
        child->parent = person;
        child->leftchild = NULL;
        child->rightbrother = NULL;
        child->depth = person->depth + 1;
    }
    else
    {
        treenode* p = person->leftchild;
        while (p->rightbrother != NULL)
        {
            p = p->rightbrother;
        }
        p->rightbrother = child;
        child->parent = person;
        child->leftchild = NULL;
        child->rightbrother = NULL;
        child->depth = person->depth + 1;
    }

    return qstr;
}



//删除某成员 (因双亲节点没有正常保存下来,这个功能未实现,待改进)
//void DeleteMember(treenode*& root)
//{
//    string name;
//    Date birthday;
//    cout << "请输入该成员的姓名" << endl;
//    cin >> name;
//    cin.ignore();
//    treenode* person = NULL;
//    ReturnTreenodeByName(root, name, person);
//    // person = findPersonByName(root,name);
//    if (person == NULL)
//    {
//        cout << "输入信息有误，家谱中没有这个人" << endl;
//        return;
//    }
//    //cout<< person->personMessage.name << "的爸爸是:" << person->parent->personMessage.name ;
//    if (person->parent != NULL)
//    {
//        treenode* p = person->parent;
//        if (p->leftchild == person)
//        {
//            p->leftchild = person->rightbrother;
//            delete person;
//            person = NULL;
//        }
//        else
//        {
//            treenode* p1 = p->leftchild;
//            while (p1->rightbrother != p)
//            {
//                p1 = p1->rightbrother;
//            }
//            p1->rightbrother = person->rightbrother;
//            delete person;
//            person = NULL;

//        }
//    }
//    else
//    {
//        cout << "它是第一代人,无法删除!" << endl;
//    }
//}

//修改某成员信息
QString ModifyMember(treenode*& root,string name,PersonMessage personMessage)
{
    QString qstr = "";


    treenode* member = NULL;
    ReturnTreenodeByNameAndBirthday(root, name, member);
    if (member == NULL)
    {
        qstr = "输入信息有误!\n";
        return qstr;
    }

//    qstr += "请按下列指引修改信息!\n";
//    qstr += "请输入姓名:\n";
//    QTextStream(stdout) << qstr;
//    member->personMessage.name = (QInputDialog::getText(nullptr, "输入姓名", "请输入成员的姓名:")).toStdString();

//    qstr += "请输入生日(年,月,日):\n";
//    QTextStream(stdout) << qstr;
//    member->personMessage.birthday.year = QInputDialog::getInt(nullptr, "输入年份", "请输入成员的出生年份:");
//    member->personMessage.birthday.month = QInputDialog::getInt(nullptr, "输入月份", "请输入成员的出生月份:");
//    member->personMessage.birthday.day = QInputDialog::getInt(nullptr, "输入日期", "请输入成员的出生日期:");

//    qstr += "请输入地址:\n";
//    QTextStream(stdout) << qstr;
//    member->personMessage.address = (QInputDialog::getText(nullptr, "输入地址", "请输入成员的地址:")).toStdString();

//    qstr += "请输入婚姻状况，已婚输入0，未婚输入1:\n";
//    QTextStream(stdout) << qstr;
//    int IsMarried = QInputDialog::getInt(nullptr, "输入婚姻状况", "已婚输入0，未婚输入1:");
//    while (IsMarried != 0 && IsMarried != 1)
//    {
//        qstr += "输入数据非法，请重新输入:\n";
//        QTextStream(stdout) << qstr;
//        IsMarried = QInputDialog::getInt(nullptr, "输入婚姻状况", "已婚输入0，未婚输入1:");
//    }
//    member->personMessage.IsMarried = (IsMarried == 0) ? "已婚" : "未婚";

//    qstr += "该人是否在世，如果在世输入0，已去世输入1:\n";
//    QTextStream(stdout) << qstr;
//    int IsAlive = QInputDialog::getInt(nullptr, "输入在世状态", "在世输入0，已去世输入1:");
//    while (IsAlive != 0 && IsAlive != 1)
//    {
//        qstr += "输入数据非法，请重新输入:\n";
//        QTextStream(stdout) << qstr;
//        IsAlive = QInputDialog::getInt(nullptr, "输入在世状态", "在世输入0，已去世输入1:");
//    }
//    member->personMessage.IsAlive = (IsAlive == 0) ? "在世" : "离世";

//    if (member->personMessage.IsAlive == "离世")
//    {
//        qstr += "请输入去世日期(年,月,日):\n";
//        QTextStream(stdout) << qstr;
//        member->personMessage.deathday.year = QInputDialog::getInt(nullptr, "输入年份", "请输入成员的去世年份:");
//        member->personMessage.deathday.month = QInputDialog::getInt(nullptr, "输入月份", "请输入成员的去世月份:");
//        member->personMessage.deathday.day = QInputDialog::getInt(nullptr, "输入日期", "请输入成员的去世日期:");
//    }

//    qstr += "请输入备注:\n";
//    QTextStream(stdout) << qstr;
//    member->personMessage.remarks = (QInputDialog::getText(nullptr, "输入备注", "请输入成员的备注:")).toStdString();

    member->personMessage.name = personMessage.name;
    member->personMessage.birthday = personMessage.birthday;
    member->personMessage.address = personMessage.address;
    member->personMessage.IsMarried = personMessage.IsMarried;
    member->personMessage.remarks = personMessage.remarks;

    return ("信息修改成功！");
}



//先序遍历把树中元素存在文件中
void SaveFile(treenode* root, fstream& file)
{
    if (root != NULL)
    {
        file << root->depth;
        file << " ";
        file << root->personMessage.name;
        file << " ";
        file << root->personMessage.birthday.year;
        file << " ";
        file << root->personMessage.birthday.month;
        file << " ";
        file << root->personMessage.birthday.day;
        file << " ";
        file << root->personMessage.IsMarried;
        file << " ";
        file << root->personMessage.address;
        file << " ";
        file << root->personMessage.IsAlive;
        file << " ";
        file << root->personMessage.deathday.year;
        file << " ";
        file << root->personMessage.deathday.month;
        file << " ";
        file << root->personMessage.deathday.day;
        file << " ";
        file << root->personMessage.remarks;
        file << '\n';
    }
    if (root->leftchild != NULL)
    {
        SaveFile(root->leftchild, file);

    }
    if (root->rightbrother != NULL)
    {
        SaveFile(root->rightbrother, file);
    }
}

void writeDate(ofstream& fout, const Date& date) {
    fout << date.year << " " << date.month << " " << date.day << " ";
}

void writePerson(ofstream& fout, const PersonMessage& person) {
    fout << person.name << " ";
    writeDate(fout, person.birthday);
    fout << person.IsMarried << " " << person.address << " " << person.IsAlive << " ";
    writeDate(fout, person.deathday);
    fout << person.remarks << "\n";
}

void saveTree(treenode* node, ofstream& fout) {
    if (node == NULL) {
        return;
    }

    fout << node->depth << " ";
    writePerson(fout, node->personMessage);

    saveTree(node->leftchild, fout);
    saveTree(node->rightbrother, fout);
}

QString saveTreeToFile(string filename, treenode* root) {
    QString qstr;
    ofstream fout(filename);
    if (!fout) {
        qstr ="信息保存失败，文件未能正常打开\n";
        return qstr;
    }

    saveTree(root, fout);

    fout.close();

    return "信息保存成功";
}



