#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QMap>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    QIcon icon(":/images/logo.png");
    QWidget::setWindowIcon(icon);
    ui->textedit_editor->setReadOnly(true);
    ui->plaintextedit_log->setReadOnly(true);
    ui->tablewidget_regfile->setColumnCount(1);
    ui->tablewidget_regfile->setRowCount(32);
    ui->tablewidget_regfile->setHorizontalHeaderItem(0, new QTableWidgetItem("Content"));
    for(int i=0; i<ui->tablewidget_regfile->rowCount(); i++){
        ui->tablewidget_regfile->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i)));
    }
    ui->tablewidget_memory->setColumnCount(1);
    ui->tablewidget_memory->setRowCount(32);
    ui->tablewidget_memory->setHorizontalHeaderItem(0, new QTableWidgetItem("Content"));
    for(int i=0; i<ui->tablewidget_memory->rowCount(); i++){
        ui->tablewidget_memory->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i)));
    }
    ui->tablewidget_pipeline->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tablewidget_pipeline->setColumnCount(1);
    ui->tablewidget_pipeline->setHorizontalHeaderItem(0, new QTableWidgetItem("Instruction"));
    //ui->tablewidget_pipeline->setShowGrid(false);
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
    QMap<QString, int> map;
    QMap<QString, QColor> color;
    map.insert("IF", 0); color.insert("IF",QColor::fromRgb(0,0,0));
    map.insert("ID", 1); color.insert("ID", QColor::fromRgb(0,0,204));
    map.insert("EX", 2); color.insert("EX", QColor::fromRgb(255,0,0));
    map.insert("MEM", 3); color.insert("MEM", QColor::fromRgb(0,204,0));
    map.insert("WB", 4); color.insert("WB", QColor::fromRgb(255,255,0));
    QTableWidgetItem *item;
    QFont font("Helvetica", 10, QFont::Bold);
    for(int i=0; i<ui->tablewidget_regfile->rowCount(); i++){
        item = new QTableWidgetItem(QString::number(rand()%100));
        item->setTextAlignment(Qt::AlignCenter);
        ui->tablewidget_regfile->setItem(i, 0, item);
    }
    for(int i=0; i<ui->tablewidget_memory->rowCount(); i++){
        item = new QTableWidgetItem(QString::number(rand()%100));
        item->setTextAlignment(Qt::AlignCenter);
        ui->tablewidget_memory->setItem(i, 0, item);
    }
    bool is_stall;
    int pc, stall_count, column_count;
    static int cycle = 0;
    is_stall = false;
    stall_count = -1;
    column_count = 5;
    pc = 0;
    QVector<QString> inst;
    inst.push_back("XOR 1,2,3");
    ui->tablewidget_pipeline->insertColumn(ui->tablewidget_pipeline->columnCount());
    ui->tablewidget_pipeline->setHorizontalHeaderItem(ui->tablewidget_pipeline->columnCount()-1, new QTableWidgetItem("Cycle " + QString::number(++cycle)));
    if(!is_stall){
        ui->tablewidget_pipeline->insertRow(ui->tablewidget_pipeline->rowCount());
        item = new QTableWidgetItem(inst[pc]);
        ui->tablewidget_pipeline->setItem(ui->tablewidget_pipeline->rowCount()-1, 0, item);
        item = new QTableWidgetItem(map.key(0));
        item->setTextAlignment(Qt::AlignCenter);
        item->setFont(font);
        ui->tablewidget_pipeline->setItem(ui->tablewidget_pipeline->rowCount()-1, cycle, item);
    }
    for(int i=0; i<column_count; i++){
        if(ui->tablewidget_pipeline->rowCount()-1-i-1 < 0) break;
        item = new QTableWidgetItem(map.key(map[ui->tablewidget_pipeline->item(ui->tablewidget_pipeline->rowCount()-1-i-1, cycle-1)->text()]+1));
        item->setTextAlignment(Qt::AlignCenter);
        item->setFont(font);
        item->setForeground(color[map.key(map[ui->tablewidget_pipeline->item(ui->tablewidget_pipeline->rowCount()-1-i-1, cycle-1)->text()]+1)]);
        ui->tablewidget_pipeline->setItem(ui->tablewidget_pipeline->rowCount()-1-i-1, cycle, item);
    }
    QString message = "-Step. Cycle: " + QString::number(cycle) + " Rows: " + QString::number(ui->tablewidget_pipeline->rowCount()) + + " Columns: " + QString::number(ui->tablewidget_pipeline->columnCount());
    ui->plaintextedit_log->appendPlainText(message);
}
