#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"

#include <QMessageBox>

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
//    this->setWindowTitle("家谱管理系统");
//    this->setAttribute(Qt::WA_TranslucentBackground, true);
//    this->ui->pushButton->setAttribute(Qt::WA_TranslucentBackground, true);
//    this->ui->pushButton_2->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->label_bgp->setScaledContents(true);
    QPixmap pic("../OurFamilyTree/bgp6");
    ui->label_bgp->setPixmap(pic);
    ui->lineEdit_password->setEchoMode(QLineEdit::EchoMode::Password);
}

login::~login()
{
    delete ui;
}



//登录按钮
void login::on_pushButton_clicked()
{
    QString userName=this->ui->lineEdit_user->text();
    QString pwd=this->ui->lineEdit_password->text();
    if(userName=="admin"&&pwd=="123456")
    {
        qDebug()<<"登录成功";
         QMessageBox::information(this,"提示","登录成功");
    }
    else
    {
        QMessageBox::critical(this,"提示","信息错误！");
        return;
    }
    MainWindow *mainWindow = new MainWindow();
    mainWindow->setWindowTitle("家谱管理系统");
    mainWindow->setWindowIcon(QIcon(":/images/fa.png"));  //更改页面的图标
    mainWindow->show();
    this->hide();
}


//退出按钮
void login::on_pushButton_2_clicked()
{
    int res = QMessageBox::question(this,"提示","是否要关闭窗口？");  //弹出对话框进行确认是否退出
    if (res == QMessageBox::Yes){
        this->close();
        exit(0);
    }
    else {
        this->show();
    }
}

