#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include<QtSql>
#include<QDebug>
#include<QFileInfo>
#include"employeeinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase mydb;
    void connClose()
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen()
    {
        mydb=QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("/Users/zehrasarac/Desktop/database.db");

        if(!mydb.open()){
            qDebug()<<("Database açılamadı...");
            return false;
        }
        else{
            qDebug()<<("Data'ya Bağlandı");
            return true;
        }
    }


public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Login *ui;

};
#endif // LOGIN_H
