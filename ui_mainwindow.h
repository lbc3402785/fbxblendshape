/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *setting;
    QAction *actionPOINTS;
    QAction *actionFACE;
    QAction *actionCONTOUR_LINE;
    QAction *actionFACE_CONTOUR_LINE;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QTreeView *treeView;
    QPushButton *save;
    QPushButton *load;
    QVBoxLayout *modelLayout;
    QHBoxLayout *horizontalLayout;
    QSlider *verticalSlider1;
    QSlider *verticalSlider2;
    QSlider *verticalSlider3;
    QSlider *verticalSlider4;
    QSlider *verticalSlider5;
    QSlider *verticalSlider6;
    QSlider *verticalSlider7;
    QSlider *verticalSlider8;
    QSlider *verticalSlider9;
    QSlider *verticalSlider10;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(716, 834);
        setting = new QAction(MainWindow);
        setting->setObjectName(QString::fromUtf8("setting"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/iconImage/img/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        setting->setIcon(icon);
        actionPOINTS = new QAction(MainWindow);
        actionPOINTS->setObjectName(QString::fromUtf8("actionPOINTS"));
        actionPOINTS->setCheckable(true);
        actionFACE = new QAction(MainWindow);
        actionFACE->setObjectName(QString::fromUtf8("actionFACE"));
        actionFACE->setCheckable(true);
        actionCONTOUR_LINE = new QAction(MainWindow);
        actionCONTOUR_LINE->setObjectName(QString::fromUtf8("actionCONTOUR_LINE"));
        actionCONTOUR_LINE->setCheckable(true);
        actionFACE_CONTOUR_LINE = new QAction(MainWindow);
        actionFACE_CONTOUR_LINE->setObjectName(QString::fromUtf8("actionFACE_CONTOUR_LINE"));
        actionFACE_CONTOUR_LINE->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        treeView = new QTreeView(centralWidget);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        gridLayout_2->addWidget(treeView, 3, 0, 1, 2);

        save = new QPushButton(centralWidget);
        save->setObjectName(QString::fromUtf8("save"));

        gridLayout_2->addWidget(save, 0, 1, 1, 1);

        load = new QPushButton(centralWidget);
        load->setObjectName(QString::fromUtf8("load"));

        gridLayout_2->addWidget(load, 0, 0, 1, 1);

        modelLayout = new QVBoxLayout();
        modelLayout->setSpacing(6);
        modelLayout->setObjectName(QString::fromUtf8("modelLayout"));

        gridLayout_2->addLayout(modelLayout, 1, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalSlider1 = new QSlider(centralWidget);
        verticalSlider1->setObjectName(QString::fromUtf8("verticalSlider1"));
        verticalSlider1->setMaximum(2999);
        verticalSlider1->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(verticalSlider1);

        verticalSlider2 = new QSlider(centralWidget);
        verticalSlider2->setObjectName(QString::fromUtf8("verticalSlider2"));
        verticalSlider2->setMaximum(2999);
        verticalSlider2->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(verticalSlider2);

        verticalSlider3 = new QSlider(centralWidget);
        verticalSlider3->setObjectName(QString::fromUtf8("verticalSlider3"));
        verticalSlider3->setMaximum(2999);
        verticalSlider3->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(verticalSlider3);

        verticalSlider4 = new QSlider(centralWidget);
        verticalSlider4->setObjectName(QString::fromUtf8("verticalSlider4"));
        verticalSlider4->setMaximum(2999);
        verticalSlider4->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(verticalSlider4);

        verticalSlider5 = new QSlider(centralWidget);
        verticalSlider5->setObjectName(QString::fromUtf8("verticalSlider5"));
        verticalSlider5->setMaximum(2999);
        verticalSlider5->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(verticalSlider5);

        verticalSlider6 = new QSlider(centralWidget);
        verticalSlider6->setObjectName(QString::fromUtf8("verticalSlider6"));
        verticalSlider6->setMaximum(2999);
        verticalSlider6->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(verticalSlider6);

        verticalSlider7 = new QSlider(centralWidget);
        verticalSlider7->setObjectName(QString::fromUtf8("verticalSlider7"));
        verticalSlider7->setMaximum(2999);
        verticalSlider7->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(verticalSlider7);

        verticalSlider8 = new QSlider(centralWidget);
        verticalSlider8->setObjectName(QString::fromUtf8("verticalSlider8"));
        verticalSlider8->setMaximum(2999);
        verticalSlider8->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(verticalSlider8);

        verticalSlider9 = new QSlider(centralWidget);
        verticalSlider9->setObjectName(QString::fromUtf8("verticalSlider9"));
        verticalSlider9->setMaximum(2999);
        verticalSlider9->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(verticalSlider9);

        verticalSlider10 = new QSlider(centralWidget);
        verticalSlider10->setObjectName(QString::fromUtf8("verticalSlider10"));
        verticalSlider10->setMaximum(2999);
        verticalSlider10->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(verticalSlider10);


        gridLayout_2->addLayout(horizontalLayout, 2, 0, 1, 2);

        gridLayout_2->setRowStretch(0, 1);
        gridLayout_2->setRowStretch(1, 3);
        gridLayout_2->setRowStretch(2, 1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 716, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(setting);
        menu_2->addAction(actionPOINTS);
        menu_2->addAction(actionFACE);
        menu_2->addAction(actionCONTOUR_LINE);
        menu_2->addAction(actionFACE_CONTOUR_LINE);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        setting->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        actionPOINTS->setText(QCoreApplication::translate("MainWindow", "POINTS", nullptr));
        actionFACE->setText(QCoreApplication::translate("MainWindow", "FACE", nullptr));
        actionCONTOUR_LINE->setText(QCoreApplication::translate("MainWindow", "CONTOUR_LINE", nullptr));
        actionFACE_CONTOUR_LINE->setText(QCoreApplication::translate("MainWindow", "FACE_CONTOUR_LINE", nullptr));
        save->setText(QCoreApplication::translate("MainWindow", "export npy", nullptr));
        load->setText(QCoreApplication::translate("MainWindow", "load fbx", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
