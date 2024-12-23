/********************************************************************************
** Form generated from reading UI file 'chatbox.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATBOX_H
#define UI_CHATBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Chatbox
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *lbName;
    QComboBox *cbStatus;
    QListWidget *lstMessages;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lnMessage;
    QPushButton *btnSend;

    void setupUi(QMainWindow *Chatbox)
    {
        if (Chatbox->objectName().isEmpty())
            Chatbox->setObjectName(QString::fromUtf8("Chatbox"));
        Chatbox->resize(800, 600);
        centralwidget = new QWidget(Chatbox);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lbName = new QLabel(centralwidget);
        lbName->setObjectName(QString::fromUtf8("lbName"));

        horizontalLayout->addWidget(lbName);

        cbStatus = new QComboBox(centralwidget);
        cbStatus->setObjectName(QString::fromUtf8("cbStatus"));

        horizontalLayout->addWidget(cbStatus);


        verticalLayout->addLayout(horizontalLayout);

        lstMessages = new QListWidget(centralwidget);
        lstMessages->setObjectName(QString::fromUtf8("lstMessages"));

        verticalLayout->addWidget(lstMessages);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lnMessage = new QLineEdit(centralwidget);
        lnMessage->setObjectName(QString::fromUtf8("lnMessage"));

        horizontalLayout_2->addWidget(lnMessage);

        btnSend = new QPushButton(centralwidget);
        btnSend->setObjectName(QString::fromUtf8("btnSend"));

        horizontalLayout_2->addWidget(btnSend);


        verticalLayout->addLayout(horizontalLayout_2);

        Chatbox->setCentralWidget(centralwidget);

        retranslateUi(Chatbox);

        QMetaObject::connectSlotsByName(Chatbox);
    } // setupUi

    void retranslateUi(QMainWindow *Chatbox)
    {
        Chatbox->setWindowTitle(QCoreApplication::translate("Chatbox", "Chatbox", nullptr));
        lbName->setText(QCoreApplication::translate("Chatbox", "TextLabel", nullptr));
        btnSend->setText(QCoreApplication::translate("Chatbox", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Chatbox: public Ui_Chatbox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATBOX_H
