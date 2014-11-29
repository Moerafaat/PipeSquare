#include "mainwindow.h"
#include <time.h>
#include <QApplication>
#include <QTextStream>

int main(int argc, char *argv[]){
    srand (time(NULL));
    QApplication a(argc, argv);
    QFile file(":/qss/styles.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream styleSheet(&file);
    qApp->setStyleSheet(styleSheet.readAll());
    MainWindow w;
    w.show();

    return a.exec();
}
