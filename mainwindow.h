#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QVector>
#include <QTableWidget>
#include "parser.h"
#include "cpu.h"

namespace Ui{
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionCompile_triggered();
    void on_actionStep_triggered();

private:
    void InitializeBuffer(QTableWidget*,QVector<QString>);
    void SetBuffer(QTableWidget*, QVector<QString>);
    Ui::MainWindow *ui;
    Parser parser;
    CPU cpu;
    QFile file;
    QVector<Instruction> instructions;
    QVector<QString> regfile, memory, IF_ID, ID_EX, EX_MEM, MEM_WB;
};

#endif // MAINWINDOW_H
