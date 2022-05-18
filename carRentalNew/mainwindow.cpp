#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "customsqlmodel.h"
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_main(new Ui::MainWindow)
{
    ui_main->setupUi(this);


    if (!connectionOpen()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
            QObject::tr("Unable to establish a database connection.\n"
                        "Click Cancel."), QMessageBox::Cancel);
    }

    on_pushButton_customer_listAll_clicked();
    on_pushButton_car_listAll_clicked();
}

MainWindow::~MainWindow()
{
    connectionClose();
    delete ui_main;
}



// Customer
void MainWindow::on_pushButton_customer_listAll_clicked()
{
    connectionOpen();
    QSqlQueryModel *customermodel= new QSqlQueryModel;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Customer");
    if(query.exec()){
        customermodel->setQuery(std::move(query));
        ui_main->tableView_customer->setModel(customermodel);
    }
    qDebug() << "Displaying" << (customermodel->rowCount()) << "rows";
    connectionClose();
}

void MainWindow::on_pushButton_customer_add_clicked()
{
    connectionOpen();

    QSqlQuery query(db);
    query.prepare("INSERT INTO Customer(name, email, phone)"
                  "VALUES(:name, :email, :phone)");
    query.bindValue(":name", ui_main->LineEdit_customer_name->text());
    query.bindValue(":email", ui_main->LineEdit_customer_email->text());
    query.bindValue(":phone", ui_main->LineEdit_customer_phone->text());

    if(query.exec()){
        qDebug()<<("Customer added");
        connectionClose();
    } else {
        QMessageBox::critical(this,tr("error::"),query.lastError().text());
        qDebug()<<("Add customer failed");
    }


    on_pushButton_customer_listAll_clicked();
}

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{

    // ta inn hver karakter og oppdater søket fra databasen fortløpende

}

void MainWindow::on_tableView_customer_activated(const QModelIndex &index)
{
    QString row = ui_main->tableView_customer->model()->data(index).toString();
    connectionOpen();
    qDebug() << row;


    QSqlQuery query(db);
    query.prepare("SELECT * FROM Customer WHERE id = :id OR name = :name OR email = :email OR phone = :phone"); //Må være på samme rad !!??

    query.bindValue(":id", row);
    query.bindValue(":name", row);
    query.bindValue(":email", row);
    query.bindValue(":phone", row);


    if(query.exec()){
       while(query.next())
       {
           qDebug() << query.value(0).toInt();
           ui_main->LineEdit_customer_id->setText(query.value(0).toString());
           qDebug() << query.value(1).toString();
           ui_main->LineEdit_customer_name->setText(query.value(1).toString());
           qDebug() << query.value(2).toString();
           ui_main->LineEdit_customer_email->setText(query.value(2).toString());
           qDebug() << query.value(3).toString();
           ui_main->LineEdit_customer_phone->setText(query.value(3).toString());
       }
        connectionClose();
    } else {
        QMessageBox::critical(this,tr("error::"),query.lastError().text());
        qDebug()<<("Marked customer failed");
    }
}

void MainWindow::on_pushButton_customer_update_clicked()
{
    connectionOpen();

    QSqlQuery query(db);
    query.prepare("UPDATE Customer SET name = :name, email = :email, phone = :phone WHERE id = :id"); //Må være på samme rad !!??

    query.bindValue(":id", ui_main->LineEdit_customer_id->text().toInt());
    query.bindValue(":name", ui_main->LineEdit_customer_name->text());
    query.bindValue(":email", ui_main->LineEdit_customer_email->text());
    query.bindValue(":phone", ui_main->LineEdit_customer_phone->text());




    if(query.exec()){
        qDebug()<<("Customer edited");
    } else {
        QMessageBox::critical(this,tr("error::"),query.lastError().text());
        qDebug()<<("Edit customer failed");
    }
    connectionClose();


    on_pushButton_customer_listAll_clicked();
}

void MainWindow::on_pushButton_customer_delete_clicked()
{
    connectionOpen();

    QSqlQuery query(db);
    query.prepare("DELETE FROM Customer WHERE id = :id"); //Må være på samme rad !!??

    query.bindValue(":id", ui_main->LineEdit_customer_id->text().toInt());

    if(query.exec()){
        qDebug()<<("Customer removed");
    } else {
        QMessageBox::critical(this,tr("error::"),query.lastError().text());
        qDebug()<<("Delete customer failed");
    }
    connectionClose();

    on_pushButton_customer_listAll_clicked();
}




// Car
void MainWindow::on_pushButton_car_listAll_clicked()
{
    connectionOpen();
    QSqlQueryModel *carmodel= new QSqlQueryModel;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Car");
    if(query.exec()){
        carmodel->setQuery(std::move(query));
        ui_main->tableView_car->setModel(carmodel);
    }
    qDebug() << "Displaying" << (carmodel->rowCount()) << "rows";
    connectionClose();
}

void MainWindow::on_pushButton_car_add_clicked()
{
    connectionOpen();

    QSqlQuery query(db);
    query.prepare("INSERT INTO Car(reg_nr, brand, model, year)"
                  "VALUES(:reg_nr, :brand, :model, :year)");
    query.bindValue(":reg_nr", ui_main->LineEdit_car_reg_nr->text());
    query.bindValue(":brand", ui_main->LineEdit_car_brand->text());
    query.bindValue(":model", ui_main->LineEdit_car_model->text());
    query.bindValue(":year", ui_main->LineEdit_car_year->text());

    if(query.exec()){
        qDebug()<<("Car added");
        connectionClose();
    } else {
        QMessageBox::critical(this,tr("error::"),query.lastError().text());
        qDebug()<<("Add car failed");
    }

    on_pushButton_car_listAll_clicked();
}

void MainWindow::on_lineEdit_car_search_textEdited(const QString &arg1)
{
     // ta inn hver karakter og oppdater søket fra databasen fortløpende
}

void MainWindow::on_tableView_car_activated(const QModelIndex &index)
{
    QString row = ui_main->tableView_car->model()->data(index).toString();
    connectionOpen();
    qDebug() << row;


    QSqlQuery query(db);
    query.prepare("SELECT * FROM Car WHERE reg_nr = :reg_nr OR brand = :brand OR model = :model OR year = :year"); //Må være på samme rad !!??

    query.bindValue(":reg_nr", row);
    query.bindValue(":brand", row);
    query.bindValue(":model", row);
    query.bindValue(":year", row);


    if(query.exec()){
       while(query.next())
       {
           qDebug() << query.value(0).toString();
           ui_main->LineEdit_car_reg_nr->setText(query.value(0).toString());
           qDebug() << query.value(1).toString();
           ui_main->LineEdit_car_brand->setText(query.value(1).toString());
           qDebug() << query.value(2).toString();
           ui_main->LineEdit_car_model->setText(query.value(2).toString());
           qDebug() << query.value(3).toString();
           ui_main->LineEdit_car_year->setText(query.value(3).toString());
       }
        connectionClose();
    } else {
        QMessageBox::critical(this,tr("error::"),query.lastError().text());
        qDebug()<<("Marked car failed");
    }
}

void MainWindow::on_pushButton_car_update_clicked()
{
    connectionOpen();

    QSqlQuery query(db);
    query.prepare("UPDATE Car SET brand = :brand, model = :model, year = :year WHERE reg_nr = :reg_nr"); //Må være på samme rad !!??

    query.bindValue(":reg_nr", ui_main->LineEdit_car_reg_nr->text());
    query.bindValue(":brand", ui_main->LineEdit_car_brand->text());
    query.bindValue(":model", ui_main->LineEdit_car_model->text());
    query.bindValue(":year", ui_main->LineEdit_car_year->text().toInt());

    if(query.exec()){
        qDebug()<<("Car edited");
    } else {
        QMessageBox::critical(this,tr("error::"),query.lastError().text());
        qDebug()<<("Edit car failed");
    }
    connectionClose();

    on_pushButton_car_listAll_clicked();
}

void MainWindow::on_pushButton_car_delete_clicked()
{
    connectionOpen();

    QSqlQuery query(db);
    query.prepare("DELETE FROM Car WHERE reg_nr = :reg_nr"); //Må være på samme rad !!??

    query.bindValue(":reg_nr", ui_main->LineEdit_car_reg_nr->text());

    if(query.exec()){
        qDebug()<<("Car removed");
    } else {
        QMessageBox::critical(this,tr("error::"),query.lastError().text());
        qDebug()<<("Delete car failed");
    }
    connectionClose();

    on_pushButton_car_listAll_clicked();
}


// Order
