#include "employeeinfo.h"
#include "ui_employeeinfo.h"
#include<QMessageBox>


EmployeeInfo::EmployeeInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeInfo)
{
    ui->setupUi(this);
    Login conn;
            if(!conn.connOpen())
                ui->label_sec_status->setText("Database açılamadı...");
            else
                ui->label_sec_status->setText("Data'ya Bağlandı");

}

EmployeeInfo::~EmployeeInfo()
{
    delete ui;
}

void EmployeeInfo::on_pushButton_clicked()
{
    Login conn;
    QString eid,modeladi,km,plaka,fiyat;
    eid=ui->txt_eid->text();
    modeladi=ui->txt_modeladi->text();
    plaka=ui->txt_plaka->text();
    km=ui->txt_km->text();


    if(!conn.connOpen()) {
        qDebug()<<"Database açılamadı...";
        return;
    }
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("insert into employeeinfo (eid,modeladi,plaka,km) values ('"+eid+"','"+modeladi+"','"+plaka+"','"+km+"')");

    if(qry.exec())
    {
        QMessageBox::critical(this,tr("KAYDET"),tr("KAYDEDİLDİ"));
        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}

void EmployeeInfo::on_pushButton_Edit_clicked()
{
    Login conn;
    QString eid,modeladi,km,plaka;
    eid=ui->txt_eid->text();
    modeladi=ui->txt_modeladi->text();
    plaka=ui->txt_plaka->text();
    km=ui->txt_km->text();

    if(!conn.connOpen()) {
        qDebug()<<"Database açılamadı...";
        return;
    }
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("update employeeinfo set eid='"+eid+"',modeladi='"+modeladi+"',plaka='"+plaka+"',km='"+km+"' where eid='"+eid+"'");

    if(qry.exec())
    {
        QMessageBox::critical(this,tr("DÜZENLE"),tr("GÜNCELLENDİ"));
        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}

void EmployeeInfo::on_pushButton_delete_clicked()
{
    Login conn;
    QString eid,modeladi,km,plaka;
    eid=ui->txt_eid->text();
    modeladi=ui->txt_modeladi->text();
    plaka=ui->txt_plaka->text();
    km=ui->txt_km->text();

    if(!conn.connOpen()) {
        qDebug()<<"Database açılamadı...";
        return;
    }
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("Delete from employeeinfo where eid='"+eid+"'");

    if(qry.exec())
    {
        QMessageBox::critical(this,tr("SİL"),tr("SİLİNDİ"));
        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}

void EmployeeInfo::on_pushButton_load_tbl_clicked()
{
    Login conn;
    QSqlQueryModel * modal=new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery* qry=new QSqlQuery(conn.mydb);

    qry->prepare("select eid,modeladi,plaka,km from employeeinfo");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    ui->comboBox->setModel(modal);
    conn.connClose();
    qDebug() <<(modal->rowCount());
}

void EmployeeInfo::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QString eid=ui->comboBox->currentText();

    Login conn;

    if(!conn.connOpen()) {
        qDebug()<<"Database açılamadı...";
        return;
    }
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from employeeinfo where eid='"+eid+"'");

    if(qry.exec())
    {
        while (qry.next()) {
            ui->txt_eid->setText(qry.value(0).toString());
            ui->txt_modeladi->setText(qry.value(1).toString());
            ui->txt_plaka->setText(qry.value(2).toString());
            ui->txt_km->setText(qry.value(3).toString());
        }
        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }

}

void EmployeeInfo::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();

    Login conn;
    if(!conn.connOpen()) {
        qDebug()<<"Database açılamadı...";
        return;
    }
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from employeeinfo where eid='"+val+"' or modeladi='"+val+"' or plaka='"+val+"' or km='"+val+"'");

    if(qry.exec())
    {
        while (qry.next()) {
            ui->txt_eid->setText(qry.value(0).toString());
            ui->txt_modeladi->setText(qry.value(1).toString());
            ui->txt_plaka->setText(qry.value(2).toString());
            ui->txt_km->setText(qry.value(3).toString());
        }
        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}

void EmployeeInfo::on_pushButton_Edit__clicked()
{
    Login conn;
    ui->txt_eid->clear();
    ui->txt_modeladi->clear();
    ui->txt_plaka->clear();
    ui->txt_km->clear();
}
