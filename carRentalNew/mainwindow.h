#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlResult>
#include <iostream>
#include <QMessageBox>
#include <QSqlError>
#include <QTableView>
#include <QString>
#include <QFileInfo>
#include <QStandardPaths>

#include "QtWidgets/qapplication.h"
#include "QtGui/qguiapplication.h"
#include "QtCore/qcoreapplication.h"
#include "customsqlmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase db;

    void connectionClose()
    {
        db.close();
        db.removeDatabase(QSqlDatabase::defaultConnection);
        qDebug()<<("Connection to database closed");
    }
    bool connectionOpen()
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

        //try to find local path for database
        //QString path_db = QStandardPaths::locate(QStandardPaths::AppDataLocation, "carRentalDb.sqlite");

        QMessageBox msgBox_path;
        msgBox_path.setText(QStandardPaths::locate(QStandardPaths::AppDataLocation, "carRentalDb.sqlite"));
        msgBox_path.exec();
        //QString dbPath = QCoreApplication::applicationDirPath() + "/carRentalDb.sqlite";
        //db.setDatabaseName(dbPath);


        db.setDatabaseName("/Users/terje/source/repos/Qt/carRentalProject/carRentalNew/carRentalDb.sqlite"); // Database-path Terje

        if (!db.open()) {
            qDebug()<<("Cannot open database");
            return false;
        } else {
            qDebug()<<("Connected to database");
            return true;
        }
    }

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
    void on_pushButton_customer_listAll_clicked();
    void on_pushButton_customer_add_clicked();
    void on_lineEdit_textEdited(const QString &arg1);
    void on_tableView_customer_activated(const QModelIndex &index);
    void on_pushButton_customer_update_clicked();
    void on_pushButton_customer_delete_clicked();

    void on_pushButton_car_listAll_clicked();
    void on_pushButton_car_add_clicked();


protected:
    Ui::MainWindow *ui_main;




private slots:
    void on_tableView_car_activated(const QModelIndex &index);
    void on_pushButton_car_update_clicked();
    void on_pushButton_car_delete_clicked();
    void on_lineEdit_car_search_textEdited(const QString &arg1);
};
#endif // MAINWINDOW_H
