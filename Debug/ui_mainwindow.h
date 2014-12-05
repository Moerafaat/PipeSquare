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
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
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
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_editor;
    QTextEdit *textedit_editor;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QTextEdit *textedit_log;
    QFrame *line;
    QFrame *line_2;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_pipeline;
    QTableWidget *tablewidget_pipeline;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_regfile;
    QTableWidget *tablewidget_regfile;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_memory;
    QTableWidget *tablewidget_memory;
    QTabWidget *tabWidget;
    QWidget *IF_ID;
    QTableWidget *tablewidget_IFID;
    QWidget *ID_EX;
    QTableWidget *tablewidget_IDEX;
    QWidget *EX_MEM;
    QTableWidget *tablewidget_EXMEM;
    QWidget *MEM_WB;
    QTableWidget *tablewidget_MEMWB;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1010, 686);
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
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 211, 421));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_editor = new QLabel(layoutWidget);
        label_editor->setObjectName(QStringLiteral("label_editor"));
        label_editor->setMargin(5);

        verticalLayout->addWidget(label_editor);

        textedit_editor = new QTextEdit(layoutWidget);
        textedit_editor->setObjectName(QStringLiteral("textedit_editor"));

        verticalLayout->addWidget(textedit_editor);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 440, 711, 171));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMargin(5);

        verticalLayout_2->addWidget(label_4);

        textedit_log = new QTextEdit(layoutWidget1);
        textedit_log->setObjectName(QStringLiteral("textedit_log"));

        verticalLayout_2->addWidget(textedit_log);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 420, 991, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(710, 10, 20, 591));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(210, 0, 501, 421));
        verticalLayout_5 = new QVBoxLayout(layoutWidget2);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_pipeline = new QLabel(layoutWidget2);
        label_pipeline->setObjectName(QStringLiteral("label_pipeline"));
        label_pipeline->setMargin(5);

        verticalLayout_5->addWidget(label_pipeline);

        tablewidget_pipeline = new QTableWidget(layoutWidget2);
        tablewidget_pipeline->setObjectName(QStringLiteral("tablewidget_pipeline"));
        tablewidget_pipeline->setMinimumSize(QSize(0, 0));

        verticalLayout_5->addWidget(tablewidget_pipeline);

        layoutWidget3 = new QWidget(centralWidget);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(730, 0, 281, 421));
        horizontalLayout = new QHBoxLayout(layoutWidget3);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_regfile = new QLabel(layoutWidget3);
        label_regfile->setObjectName(QStringLiteral("label_regfile"));
        label_regfile->setMargin(5);

        verticalLayout_3->addWidget(label_regfile);

        tablewidget_regfile = new QTableWidget(layoutWidget3);
        tablewidget_regfile->setObjectName(QStringLiteral("tablewidget_regfile"));

        verticalLayout_3->addWidget(tablewidget_regfile);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_memory = new QLabel(layoutWidget3);
        label_memory->setObjectName(QStringLiteral("label_memory"));
        label_memory->setMargin(5);

        verticalLayout_4->addWidget(label_memory);

        tablewidget_memory = new QTableWidget(layoutWidget3);
        tablewidget_memory->setObjectName(QStringLiteral("tablewidget_memory"));

        verticalLayout_4->addWidget(tablewidget_memory);


        horizontalLayout->addLayout(verticalLayout_4);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(730, 440, 281, 171));
        IF_ID = new QWidget();
        IF_ID->setObjectName(QStringLiteral("IF_ID"));
        tablewidget_IFID = new QTableWidget(IF_ID);
        tablewidget_IFID->setObjectName(QStringLiteral("tablewidget_IFID"));
        tablewidget_IFID->setGeometry(QRect(0, 0, 281, 161));
        tabWidget->addTab(IF_ID, QString());
        ID_EX = new QWidget();
        ID_EX->setObjectName(QStringLiteral("ID_EX"));
        tablewidget_IDEX = new QTableWidget(ID_EX);
        tablewidget_IDEX->setObjectName(QStringLiteral("tablewidget_IDEX"));
        tablewidget_IDEX->setGeometry(QRect(0, 0, 281, 161));
        tabWidget->addTab(ID_EX, QString());
        EX_MEM = new QWidget();
        EX_MEM->setObjectName(QStringLiteral("EX_MEM"));
        tablewidget_EXMEM = new QTableWidget(EX_MEM);
        tablewidget_EXMEM->setObjectName(QStringLiteral("tablewidget_EXMEM"));
        tablewidget_EXMEM->setGeometry(QRect(0, 0, 281, 161));
        tabWidget->addTab(EX_MEM, QString());
        MEM_WB = new QWidget();
        MEM_WB->setObjectName(QStringLiteral("MEM_WB"));
        tablewidget_MEMWB = new QTableWidget(MEM_WB);
        tablewidget_MEMWB->setObjectName(QStringLiteral("tablewidget_MEMWB"));
        tablewidget_MEMWB->setGeometry(QRect(0, 0, 281, 161));
        tabWidget->addTab(MEM_WB, QString());
        MainWindow->setCentralWidget(centralWidget);
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        line->raise();
        line_2->raise();
        tabWidget->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1010, 21));
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
        label_editor->setText(QApplication::translate("MainWindow", "Editor", 0));
        label_4->setText(QApplication::translate("MainWindow", "Log", 0));
        label_pipeline->setText(QApplication::translate("MainWindow", "Pipeline Diagram", 0));
        label_regfile->setText(QApplication::translate("MainWindow", "Register File", 0));
        label_memory->setText(QApplication::translate("MainWindow", "Memory", 0));
        tabWidget->setTabText(tabWidget->indexOf(IF_ID), QApplication::translate("MainWindow", "IF/ID", 0));
        tabWidget->setTabText(tabWidget->indexOf(ID_EX), QApplication::translate("MainWindow", "ID/EX", 0));
        tabWidget->setTabText(tabWidget->indexOf(EX_MEM), QApplication::translate("MainWindow", "EX/MEM", 0));
        tabWidget->setTabText(tabWidget->indexOf(MEM_WB), QApplication::translate("MainWindow", "MEM/WB", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
