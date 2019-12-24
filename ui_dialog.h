/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *General;
    QGroupBox *groupBox_2;
    QLabel *countInfo;
    QLineEdit *count;
    QLabel *expressionDirInfo;
    QLineEdit *expressionDir;
    QLabel *expressionListInfo;
    QLineEdit *expressionList;
    QLabel *expressionDirInfo_2;
    QLineEdit *blendShapeName;
    QLineEdit *rangeMin;
    QLabel *countInfo_2;
    QLineEdit *rangeMax;
    QLabel *countInfo_3;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *reset;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancel;
    QPushButton *save;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(434, 502);
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout_2 = new QGridLayout(Dialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        tabWidget = new QTabWidget(Dialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        General = new QWidget();
        General->setObjectName(QString::fromUtf8("General"));
        groupBox_2 = new QGroupBox(General);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 20, 381, 211));
        countInfo = new QLabel(groupBox_2);
        countInfo->setObjectName(QString::fromUtf8("countInfo"));
        countInfo->setGeometry(QRect(21, 42, 60, 16));
        count = new QLineEdit(groupBox_2);
        count->setObjectName(QString::fromUtf8("count"));
        count->setGeometry(QRect(135, 42, 133, 20));
        expressionDirInfo = new QLabel(groupBox_2);
        expressionDirInfo->setObjectName(QString::fromUtf8("expressionDirInfo"));
        expressionDirInfo->setGeometry(QRect(21, 94, 108, 16));
        expressionDir = new QLineEdit(groupBox_2);
        expressionDir->setObjectName(QString::fromUtf8("expressionDir"));
        expressionDir->setGeometry(QRect(135, 94, 133, 20));
        expressionListInfo = new QLabel(groupBox_2);
        expressionListInfo->setObjectName(QString::fromUtf8("expressionListInfo"));
        expressionListInfo->setGeometry(QRect(21, 68, 108, 16));
        expressionList = new QLineEdit(groupBox_2);
        expressionList->setObjectName(QString::fromUtf8("expressionList"));
        expressionList->setGeometry(QRect(135, 68, 133, 20));
        expressionDirInfo_2 = new QLabel(groupBox_2);
        expressionDirInfo_2->setObjectName(QString::fromUtf8("expressionDirInfo_2"));
        expressionDirInfo_2->setGeometry(QRect(21, 120, 78, 16));
        blendShapeName = new QLineEdit(groupBox_2);
        blendShapeName->setObjectName(QString::fromUtf8("blendShapeName"));
        blendShapeName->setGeometry(QRect(135, 120, 133, 20));
        rangeMin = new QLineEdit(groupBox_2);
        rangeMin->setObjectName(QString::fromUtf8("rangeMin"));
        rangeMin->setGeometry(QRect(135, 146, 133, 20));
        countInfo_2 = new QLabel(groupBox_2);
        countInfo_2->setObjectName(QString::fromUtf8("countInfo_2"));
        countInfo_2->setGeometry(QRect(21, 146, 96, 16));
        rangeMax = new QLineEdit(groupBox_2);
        rangeMax->setObjectName(QString::fromUtf8("rangeMax"));
        rangeMax->setGeometry(QRect(135, 172, 133, 20));
        countInfo_3 = new QLabel(groupBox_2);
        countInfo_3->setObjectName(QString::fromUtf8("countInfo_3"));
        countInfo_3->setGeometry(QRect(21, 172, 96, 16));
        tabWidget->addTab(General, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());

        gridLayout_2->addWidget(tabWidget, 1, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        reset = new QPushButton(Dialog);
        reset->setObjectName(QString::fromUtf8("reset"));

        horizontalLayout_2->addWidget(reset);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        cancel = new QPushButton(Dialog);
        cancel->setObjectName(QString::fromUtf8("cancel"));

        horizontalLayout_2->addWidget(cancel);

        save = new QPushButton(Dialog);
        save->setObjectName(QString::fromUtf8("save"));

        horizontalLayout_2->addWidget(save);


        gridLayout_2->addLayout(horizontalLayout_2, 2, 1, 1, 1);


        retranslateUi(Dialog);

        tabWidget->setCurrentIndex(0);
        save->setDefault(true);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Dialog", "file", nullptr));
        countInfo->setText(QCoreApplication::translate("Dialog", "\346\250\241\345\236\213\347\202\271\346\225\260\357\274\232", nullptr));
        expressionDirInfo->setText(QCoreApplication::translate("Dialog", "\350\241\250\346\203\205\346\250\241\345\236\213\350\276\223\345\207\272\350\267\257\345\276\204\357\274\232", nullptr));
        expressionListInfo->setText(QCoreApplication::translate("Dialog", "\350\241\250\346\203\205\345\220\215\347\247\260\350\276\223\345\207\272\350\267\257\345\276\204\357\274\232", nullptr));
        expressionDirInfo_2->setText(QCoreApplication::translate("Dialog", "blend shape\357\274\232", nullptr));
        blendShapeName->setText(QString());
        countInfo_2->setText(QCoreApplication::translate("Dialog", "\350\241\250\346\203\205\345\217\202\346\225\260\346\234\200\345\260\217\345\200\274\357\274\232", nullptr));
        countInfo_3->setText(QCoreApplication::translate("Dialog", "\350\241\250\346\203\205\345\217\202\346\225\260\346\234\200\345\244\247\345\200\274\357\274\232", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(General), QCoreApplication::translate("Dialog", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("Dialog", "Tab 2", nullptr));
        reset->setText(QCoreApplication::translate("Dialog", "Reset", nullptr));
        cancel->setText(QCoreApplication::translate("Dialog", "Cancel", nullptr));
        save->setText(QCoreApplication::translate("Dialog", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
