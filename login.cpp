#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);


    if(!connOpen())
        ui->label->setText("Database açılamadı...");
    else
        ui->label->setText("Data'ya Bağlandı");

}

Login::~Login()
{
    delete ui;
}


void Login::on_pushButton_clicked()
{
    QString username,password;
    username=ui->lineEdit_username->text();
    password=ui->lineEdit_Password->text();

    if(!connOpen()) {
        qDebug()<<"Database açılamadı...";
        return;
    }
    connOpen();
    QSqlQuery qry;
    qry.prepare("select * from employeeinfo where username='"+username +"' and password='"+password+"'");

    if(qry.exec())
    {
        int count=0;
        while (qry.next())
        {
            count++;
        }
        if(count==1){
            ui->label->setText("Kullanıcı adı ve şifre doğru...");
            connClose();
            this->hide();
            EmployeeInfo employeeinfo;
            employeeinfo.setModal(true);
            employeeinfo.exec();
        }
        if(count>1)
            ui->label->setText("Yinelenen şifre...");
        if(count<1)
            ui->label->setText("Kullanıcı adı ve şifre yanlış...");
    }
}
