/********************************************************************************
** Form generated from reading UI file 'gamedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEDIALOG_H
#define UI_GAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_GameDialog
{
public:
    QGraphicsView *graphicsView;

    void setupUi(QDialog *GameDialog)
    {
        if (GameDialog->objectName().isEmpty())
            GameDialog->setObjectName(QStringLiteral("GameDialog"));
        GameDialog->resize(400, 300);
        graphicsView = new QGraphicsView(GameDialog);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 400, 300));

        retranslateUi(GameDialog);

        QMetaObject::connectSlotsByName(GameDialog);
    } // setupUi

    void retranslateUi(QDialog *GameDialog)
    {
        GameDialog->setWindowTitle(QApplication::translate("GameDialog", "GameDialog", 0));
    } // retranslateUi

};

namespace Ui {
    class GameDialog: public Ui_GameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEDIALOG_H
