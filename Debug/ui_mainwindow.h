/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionStep;
    QAction *actionCompile;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *IF_ID;
    QTableWidget *tableWidget_3;
    QWidget *ID_EX;
    QTableWidget *tableWidget_4;
    QWidget *EX_MEM;
    QTableWidget *tableWidget_5;
    QWidget *MEM_WB;
    QTableWidget *tableWidget_6;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label_editor;
    QTextEdit *textedit_editor;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QPlainTextEdit *plaintextedit_log;
    QWidget *widget2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_memory;
    QTableWidget *tablewidget_memory;
    QWidget *widget3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_regfile;
    QTableWidget *tablewidget_regfile;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(775, 474);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QStringLiteral(""));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionStep = new QAction(MainWindow);
        actionStep->setObjectName(QStringLiteral("actionStep"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/step.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStep->setIcon(icon1);
        actionCompile = new QAction(MainWindow);
        actionCompile->setObjectName(QStringLiteral("actionCompile"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/compile.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCompile->setIcon(icon2);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(470, 280, 281, 111));
        IF_ID = new QWidget();
        IF_ID->setObjectName(QStringLiteral("IF_ID"));
        tableWidget_3 = new QTableWidget(IF_ID);
        tableWidget_3->setObjectName(QStringLiteral("tableWidget_3"));
        tableWidget_3->setGeometry(QRect(0, 0, 281, 91));
        tabWidget->addTab(IF_ID, QString());
        ID_EX = new QWidget();
        ID_EX->setObjectName(QStringLiteral("ID_EX"));
        tableWidget_4 = new QTableWidget(ID_EX);
        tableWidget_4->setObjectName(QStringLiteral("tableWidget_4"));
        tableWidget_4->setGeometry(QRect(0, 0, 281, 91));
        tabWidget->addTab(ID_EX, QString());
        EX_MEM = new QWidget();
        EX_MEM->setObjectName(QStringLiteral("EX_MEM"));
        tableWidget_5 = new QTableWidget(EX_MEM);
        tableWidget_5->setObjectName(QStringLiteral("tableWidget_5"));
        tableWidget_5->setGeometry(QRect(0, 0, 281, 91));
        tabWidget->addTab(EX_MEM, QString());
        MEM_WB = new QWidget();
        MEM_WB->setObjectName(QStringLiteral("MEM_WB"));
        tableWidget_6 = new QTableWidget(MEM_WB);
        tableWidget_6->setObjectName(QStringLiteral("tableWidget_6"));
        tableWidget_6->setGeometry(QRect(0, 0, 281, 91));
        tabWidget->addTab(MEM_WB, QString());
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 431, 261));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_editor = new QLabel(widget);
        label_editor->setObjectName(QStringLiteral("label_editor"));

        verticalLayout->addWidget(label_editor);

        textedit_editor = new QTextEdit(widget);
        textedit_editor->setObjectName(QStringLiteral("textedit_editor"));

        verticalLayout->addWidget(textedit_editor);

        widget1 = new QWidget(centralWidget);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(10, 290, 431, 101));
        verticalLayout_2 = new QVBoxLayout(widget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(widget1);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_2->addWidget(label_4);

        plaintextedit_log = new QPlainTextEdit(widget1);
        plaintextedit_log->setObjectName(QStringLiteral("plaintextedit_log"));

        verticalLayout_2->addWidget(plaintextedit_log);

        widget2 = new QWidget(centralWidget);
        widget2->setObjectName(QStringLiteral("widget2"));
        widget2->setGeometry(QRect(620, 10, 131, 261));
        verticalLayout_4 = new QVBoxLayout(widget2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_memory = new QLabel(widget2);
        label_memory->setObjectName(QStringLiteral("label_memory"));

        verticalLayout_4->addWidget(label_memory);

        tablewidget_memory = new QTableWidget(widget2);
        tablewidget_memory->setObjectName(QStringLiteral("tablewidget_memory"));

        verticalLayout_4->addWidget(tablewidget_memory);

        widget3 = new QWidget(centralWidget);
        widget3->setObjectName(QStringLiteral("widget3"));
        widget3->setGeometry(QRect(470, 10, 131, 261));
        verticalLayout_3 = new QVBoxLayout(widget3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_regfile = new QLabel(widget3);
        label_regfile->setObjectName(QStringLiteral("label_regfile"));

        verticalLayout_3->addWidget(label_regfile);

        tablewidget_regfile = new QTableWidget(widget3);
        tablewidget_regfile->setObjectName(QStringLiteral("tablewidget_regfile"));

        verticalLayout_3->addWidget(tablewidget_regfile);

        MainWindow->setCentralWidget(centralWidget);
        textedit_editor->raise();
        plaintextedit_log->raise();
        tabWidget->raise();
        tablewidget_memory->raise();
        tablewidget_regfile->raise();
        label_editor->raise();
        label_regfile->raise();
        label_memory->raise();
        label_4->raise();
        label_4->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 775, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setAutoFillBackground(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionCompile);
        menuFile->addAction(actionStep);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionCompile);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionStep);
        mainToolBar->addSeparator();

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionStep->setText(QApplication::translate("MainWindow", "Step", 0));
        actionCompile->setText(QApplication::translate("MainWindow", "Compile", 0));
        tabWidget->setTabText(tabWidget->indexOf(IF_ID), QApplication::translate("MainWindow", "IF/ID", 0));
        tabWidget->setTabText(tabWidget->indexOf(ID_EX), QApplication::translate("MainWindow", "ID/EX", 0));
        tabWidget->setTabText(tabWidget->indexOf(EX_MEM), QApplication::translate("MainWindow", "EX/MEM", 0));
        tabWidget->setTabText(tabWidget->indexOf(MEM_WB), QApplication::translate("MainWindow", "MEM/WB", 0));
        label_editor->setText(QApplication::translate("MainWindow", "Editor", 0));
        label_4->setText(QApplication::translate("MainWindow", "Log", 0));
        label_memory->setText(QApplication::translate("MainWindow", "Memory", 0));
        label_regfile->setText(QApplication::translate("MainWindow", "Register File", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
