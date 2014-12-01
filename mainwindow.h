#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "parser.h"
#include "cpu.h"
#include <QFile>

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
    Ui::MainWindow *ui;
    Parser parser;
    CPU cpu;
    QFile file;
    QVector<Instruction> instructions;

};

#endif // MAINWINDOW_H
