/********************************************************************************
** Form generated from reading UI file 'Clangtesting.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLANGTESTING_H
#define UI_CLANGTESTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClangtestingClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ClangtestingClass)
    {
        if (ClangtestingClass->objectName().isEmpty())
            ClangtestingClass->setObjectName(QString::fromUtf8("ClangtestingClass"));
        ClangtestingClass->resize(600, 400);
        menuBar = new QMenuBar(ClangtestingClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        ClangtestingClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ClangtestingClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ClangtestingClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ClangtestingClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        ClangtestingClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ClangtestingClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ClangtestingClass->setStatusBar(statusBar);

        retranslateUi(ClangtestingClass);

        QMetaObject::connectSlotsByName(ClangtestingClass);
    } // setupUi

    void retranslateUi(QMainWindow *ClangtestingClass)
    {
        ClangtestingClass->setWindowTitle(QCoreApplication::translate("ClangtestingClass", "Clangtesting", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClangtestingClass: public Ui_ClangtestingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLANGTESTING_H
