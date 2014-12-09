#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QMap>
#include <cmath>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    QIcon icon(":/images/logo.png");
    QWidget::setWindowIcon(icon);
    QFont font("Helvetica", 10);

    ui->textedit_log->setReadOnly(true);
    ui->textedit_editor->setReadOnly(true);
    ui->textedit_editor->setTabStopWidth(30);
    ui->textedit_editor->setFont(font);

    ui->tablewidget_regfile->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tablewidget_regfile->setColumnCount(1);
    ui->tablewidget_regfile->setRowCount(32);
    ui->tablewidget_regfile->setHorizontalHeaderItem(0, new QTableWidgetItem("Content"));
    for(int i=0; i<ui->tablewidget_regfile->rowCount(); i++)
        ui->tablewidget_regfile->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i)));

    ui->tablewidget_memory->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tablewidget_memory->setColumnCount(1);
    ui->tablewidget_memory->setRowCount(32);
    ui->tablewidget_memory->setHorizontalHeaderItem(0, new QTableWidgetItem("Content"));
    for(int i=0; i<ui->tablewidget_memory->rowCount(); i++)
        ui->tablewidget_memory->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i)));

    ui->tablewidget_pipeline->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tablewidget_pipeline->setColumnCount(0);
    ui->tablewidget_pipeline->setShowGrid(false);

    QVector<QString> IFID_labels = {"Mnemonic", "Rs", "Rt", "Td", "Imm", "Jaddr"};
    InitializeBuffer(ui->tablewidget_IFID,IFID_labels);

    QVector<QString> IDEX_labels = {"WE", "WAddr", "Data", "MemRW", "ALUMem", "ALUOp", "Op1", "Op2"};
    InitializeBuffer(ui->tablewidget_IDEX,IDEX_labels);

    QVector<QString> EXMEM_labels = {"WE", "WAddr", "WData", "MemRW", "ALUMem", "MemAddr"};
    InitializeBuffer(ui->tablewidget_EXMEM,EXMEM_labels);

    QVector<QString> MEMWB_labels = {"WE", "WAddr", "WData"};
    InitializeBuffer(ui->tablewidget_MEMWB,MEMWB_labels);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::InitializeBuffer(QTableWidget* buffer, QVector<QString> labels){
    QTableWidgetItem *item;
    QFont font("Helvetica", 9, QFont::Bold);
    buffer->setEditTriggers(QAbstractItemView::NoEditTriggers);
    buffer->verticalHeader()->hide();
    buffer->setRowCount(4);
    buffer->setColumnCount(4);
    for (int i=0; i<labels.size(); i++){
        item = new QTableWidgetItem(labels[i]);
        item->setForeground(QColor::fromRgb(255,0,0));
        item->setFont(font);
        item->setTextAlignment(Qt::AlignCenter);
        if(i<4) buffer->setItem(0, i, item);
        else buffer->setItem(2, i-4, item);
    }
    for(int i=0; i<4; i++) buffer->setColumnWidth(i, 69);
}

void MainWindow::SetBuffer(QTableWidget* buffer, QVector<QString> values)
{
    QTableWidgetItem *item;
    for (int i=0; i<values.size(); i++){
        item = new QTableWidgetItem(values[i]);
        item->setTextAlignment(Qt::AlignCenter);
        if(i<4) buffer->setItem(1, i, item);
        else buffer->setItem(3, i-4, item);
    }
}

void MainWindow::on_actionOpen_triggered(){
    QString path = QFileDialog::getOpenFileName(this, "Open File");
    file.setFileName(path);
    if(file.open(QFile::ReadOnly)){
        QTextStream stream(&file);
        QString content, message;
        while(!stream.atEnd()) content.append(stream.readLine() + '\n');
        ui->textedit_editor->setText(content);
        file.close();

        message = "-File at path: " + path + " has been successfully opened.";
        ui->textedit_log->setTextColor(QColor::fromRgb(0,0,102));
        ui->textedit_log->append(message);
    }
}

void MainWindow::on_actionCompile_triggered(){
    try{
        instructions = parser.parse(file);
    }catch(QString error){
        QString message = "-File has failed to compile\n" + error;
        ui->textedit_log->setTextColor(QColor::fromRgb(204,0,0));
        ui->textedit_log->append(message);
        return;
    };

    file.close();
    ui->textedit_editor->clear();
    QString comma = ",  ";
    for(int i=0; i<instructions.size(); i++){
        QString row = instructions[i].RawInst.simplified();
        QStringList elements = row.split(" ");
        ui->textedit_editor->moveCursor (QTextCursor::End);
        ui->textedit_editor->insertHtml("<span style='color:red'>" + elements[0] + "</span>");
        ui->textedit_editor->insertPlainText("\t");
        ui->textedit_editor->moveCursor (QTextCursor::End);
        row = "";
        for(int i=1; i<elements.size(); i++){
            row = row + elements[i];
            if(i != elements.size()-1) row += ",";
        }
        elements = row.split(",", QString::SkipEmptyParts);
        for(int j=0; j<elements.size(); j++){
            ui->textedit_editor->moveCursor (QTextCursor::End);
            ui->textedit_editor->insertHtml("<span style='color:black'>" + elements[j] + "</span>");
            ui->textedit_editor->moveCursor (QTextCursor::End);
            if(j == elements.size()-1){
                ui->textedit_editor->append("");
                break;
            }
            ui->textedit_editor->moveCursor (QTextCursor::End);
            ui->textedit_editor->insertHtml("<span style='color:red'>" + comma + "</span>");
            ui->textedit_editor->moveCursor (QTextCursor::End);
        }
    }

    QString message = "-File has been successfully compiled";
    ui->textedit_log->setTextColor(QColor::fromRgb(0,102,0));
    ui->textedit_log->append(message);

    cpu.SetVector(instructions);
    fun();
}

void MainWindow::on_actionStep_triggered(){ //Dummy
    QMap<QString, QString> map;
    QMap<QString, QColor> color;
    map.insert("IF", "ID"); color.insert("IF",QColor::fromRgb(0,0,0));
    map.insert("ID", "EX"); color.insert("ID", QColor::fromRgb(0,0,204));
    map.insert("EX", "MEM"); color.insert("EX", QColor::fromRgb(255,0,0));
    map.insert("MEM", "WB"); color.insert("MEM", QColor::fromRgb(0,204,0));
    map.insert("WB", " "); color.insert("WB", QColor::fromRgb(255,255,0));
    map.insert(" ", " "); color.insert(" ", QColor::fromRgb(255,255,255));
    map.insert("IDLE", "IDLE"); color.insert("IDLE", QColor::fromRgb(102,51,0));
    QTableWidgetItem *item;
    QFont font("Helvetica", 10, QFont::Bold);
    bool is_stall, is_branch;
    int pc, column_count;
    static int cycle = -1;
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
    QVector<QString> IFID_values = {"ADD", "2", "3", "5", "25", "1"};
    if(cycle%2) IFID_values = {"ADD", "2", "3", "5", "25", "1"};
    else IFID_values = {"SUB", "4", "12", "9", "5", "124"};
    SetBuffer(ui->tablewidget_IFID,IFID_values);
    QVector<QString> IDEX_values = {"1", "9", "21", "1", "0", "2", "10", "15"};
    SetBuffer(ui->tablewidget_IDEX,IDEX_values);
    QVector<QString> EXMEM_values = {"1", "9", "21", "1", "0", "5"};
    SetBuffer(ui->tablewidget_EXMEM,EXMEM_values);
    QVector<QString> MEMWB_values = {"1", "9", "21"};
    SetBuffer(ui->tablewidget_MEMWB,MEMWB_values);
    is_stall = false;
    is_branch = false;
    column_count = 5;
    pc = 0;
    if (cycle == 7) is_stall = true;
    if (cycle == 11) is_branch = true;
    QVector<QString> inst;
    inst.push_back("XOR 1,2,3");
    ui->tablewidget_pipeline->insertColumn(ui->tablewidget_pipeline->columnCount());
    ui->tablewidget_pipeline->setHorizontalHeaderItem(ui->tablewidget_pipeline->columnCount()-1, new QTableWidgetItem("Cyc " + QString::number((++cycle + 1))));
    if(!is_stall){
        ui->tablewidget_pipeline->insertRow(ui->tablewidget_pipeline->rowCount());
        item = new QTableWidgetItem(inst[pc]);
        ui->tablewidget_pipeline->setVerticalHeaderItem(ui->tablewidget_pipeline->rowCount()-1, item);
        item = new QTableWidgetItem("IF");
        item->setData(Qt::UserRole, QVariant(-1));
        item->setTextAlignment(Qt::AlignCenter);
        item->setFont(font);
        ui->tablewidget_pipeline->setItem(ui->tablewidget_pipeline->rowCount()-1, cycle, item);
    }
    for(int i=0;; i++){
        if(ui->tablewidget_pipeline->rowCount()-1-i-(!is_stall) < 0) break;
        QString text = (i >= 2 || !is_stall) ? map[ui->tablewidget_pipeline->item(ui->tablewidget_pipeline->rowCount()-1-i-(!is_stall), cycle-1)->text()] : ui->tablewidget_pipeline->item(ui->tablewidget_pipeline->rowCount()-1-i-(!is_stall), cycle-1)->text();
        int idle_count = ui->tablewidget_pipeline->item(ui->tablewidget_pipeline->rowCount()-1-i-(!is_stall), cycle-1)->data(Qt::UserRole).toInt();
        if(idle_count == 0) text = " ";
        else if(idle_count != -1) {
            idle_count--;
            text = "IDLE";
        }
        if(is_branch && i == 0){
            text = "IDLE";
            idle_count = 3;
        }
        item = new QTableWidgetItem(text);
        item->setData(Qt::UserRole, QVariant(idle_count));
        item->setTextAlignment(Qt::AlignCenter);
        item->setFont(font);
        item->setForeground(color[text]);
        if(i < 2 && is_stall) item->setBackgroundColor(QColor::fromRgb(224,224,224));
        ui->tablewidget_pipeline->setItem(ui->tablewidget_pipeline->rowCount()-1-i-(!is_stall), cycle, item);
    }
    ui->tablewidget_pipeline->resizeColumnsToContents();
    QString message = "-Step: Executing cycle number: " + QString::number(cycle+1);
    ui->textedit_log->setTextColor(QColor::fromRgb(204,0,0));
    ui->textedit_log->append(message);
}

/*void MainWindow::on_actionStep_triggered(){ //Actual
    QMap<QString, QString> map;
    QMap<QString, QColor> color;
    map.insert("IF", "ID"); color.insert("IF",QColor::fromRgb(0,0,0));
    map.insert("ID", "EX"); color.insert("ID", QColor::fromRgb(0,0,204));
    map.insert("EX", "MEM"); color.insert("EX", QColor::fromRgb(255,0,0));
    map.insert("MEM", "WB"); color.insert("MEM", QColor::fromRgb(0,204,0));
    map.insert("WB", " "); color.insert("WB", QColor::fromRgb(255,255,0));
    map.insert(" ", " "); color.insert(" ", QColor::fromRgb(255,255,255));
    map.insert("IDLE", "IDLE"); color.insert("IDLE", QColor::fromRgb(102,51,0));
    QTableWidgetItem *item;
    QFont font("Helvetica", 10, QFont::Bold);

    for(int i=0; i<ui->tablewidget_regfile->rowCount(); i++){
        item = new QTableWidgetItem(QString::number(regfile[i]));
        item->setTextAlignment(Qt::AlignCenter);
        ui->tablewidget_regfile->setItem(i, 0, item);
    }

    for(int i=0; i<ui->tablewidget_memory->rowCount(); i++){
        item = new QTableWidgetItem(QString::number(memory[i]));
        item->setTextAlignment(Qt::AlignCenter);
        ui->tablewidget_memory->setItem(i, 0, item);
    }

    SetBuffer(ui->tablewidget_IFID,IF_ID);
    SetBuffer(ui->tablewidget_IDEX,ID_EX);
    SetBuffer(ui->tablewidget_IDEX,EX_MEM);
    SetBuffer(ui->tablewidget_IDEX,MEM_WB);
    ui->tablewidget_pipeline->insertColumn(ui->tablewidget_pipeline->columnCount());
    ui->tablewidget_pipeline->setHorizontalHeaderItem(ui->tablewidget_pipeline->columnCount()-1, new QTableWidgetItem("Cyc " + QString::number((cycles))));

    if(!IsStall){
        ui->tablewidget_pipeline->insertRow(ui->tablewidget_pipeline->rowCount());
        item = new QTableWidgetItem(instructions[pc]);
        ui->tablewidget_pipeline->setVerticalHeaderItem(ui->tablewidget_pipeline->rowCount()-1, item);
        item = new QTableWidgetItem("IF");
        item->setData(Qt::UserRole, QVariant(-1));
        item->setTextAlignment(Qt::AlignCenter);
        item->setFont(font);
        ui->tablewidget_pipeline->setItem(ui->tablewidget_pipeline->rowCount()-1, cycle, item);
    }

    for(int i=0;; i++){
        if(ui->tablewidget_pipeline->rowCount()-1-i-(!IsStall) < 0) break;
        QString text = (i >= 2 || !IsStall) ? map[ui->tablewidget_pipeline->item(ui->tablewidget_pipeline->rowCount()-1-i-(!IsStall), cycle-1)->text()] : ui->tablewidget_pipeline->item(ui->tablewidget_pipeline->rowCount()-1-i-(!IsStall), cycle-1)->text();
        int idle_count = ui->tablewidget_pipeline->item(ui->tablewidget_pipeline->rowCount()-1-i-(!is_stall), cycle-1)->data(Qt::UserRole).toInt();
        if(idle_count == 0) text = " ";
        else if(idle_count != -1) {
            idle_count--;
            text = "IDLE";
        }
        if(is_branch && i == 0){
            text = "IDLE";
            idle_count = 3;
        }
        item = new QTableWidgetItem(text);
        item->setData(Qt::UserRole, QVariant(idle_count));
        item->setTextAlignment(Qt::AlignCenter);
        item->setFont(font);
        item->setForeground(color[text]);
        if (i < 2 && IsStall) item->setBackgroundColor(QColor::fromRgb(224,224,224));
        ui->tablewidget_pipeline->setItem(ui->tablewidget_pipeline->rowCount()-1-i-(!IsStall), cycle, item);
    }
    ui->tablewidget_pipeline->resizeColumnsToContents();
}*/
