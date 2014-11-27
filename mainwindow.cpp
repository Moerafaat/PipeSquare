#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->textedit_editor->setReadOnly(true);
    ui->plaintextedit_log->setReadOnly(true);
    ui->tablewidget_regfile->setColumnCount(1);
    ui->tablewidget_regfile->setRowCount(32);
    ui->tablewidget_regfile->setHorizontalHeaderItem(0, new QTableWidgetItem("Content"));
    for(int i=0; i<ui->tablewidget_regfile->rowCount(); i++){
        ui->tablewidget_regfile->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i)));
    }
    for(int i=0; i<ui->tablewidget_memory->rowCount(); i++){
        ui->tablewidget_memory->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i)));
    }
    ui->tablewidget_memory->setColumnCount(1);
    ui->tablewidget_memory->setRowCount(32);
    ui->tablewidget_memory->setHorizontalHeaderItem(0, new QTableWidgetItem("Content"));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_actionOpen_triggered(){
    QString path = QFileDialog::getOpenFileName(this, "Open File");
    file.setFileName(path);
    if(file.open(QFile::ReadOnly)){
        QTextStream stream(&file);
        QString content, message;
        while(!stream.atEnd()){
            content.append(stream.readLine() + '\n');
        }
        message = "-File at path: " + path + " has been successfully opened.";
        ui->textedit_editor->setText(content);
        ui->plaintextedit_log->appendPlainText(message);
        file.close();
    }
}

void MainWindow::on_actionCompile_triggered(){
    instructions = parser.parse(file);
    QString message = "-File has been successfully compiled";
    ui->plaintextedit_log->appendPlainText(message);
}

void MainWindow::on_actionStep_triggered(){
    QTableWidgetItem *item;
    for(int i=0; i<ui->tablewidget_regfile->rowCount(); i++){
        item = new QTableWidgetItem(QString::number(rand()%100));
        ui->tablewidget_regfile->setItem(i, 0, item);
    }
    for(int i=0; i<ui->tablewidget_memory->rowCount(); i++){
        item = new QTableWidgetItem(QString::number(rand()%100));
        ui->tablewidget_memory->setItem(i, 0, item);
    }
    QString message = "-Step";
    ui->plaintextedit_log->appendPlainText(message);
}
