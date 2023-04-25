/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_text_cryptage;
    QPlainTextEdit *plainTextEdit_cryptage;
    QPushButton *pushButton_write_document;
    QPushButton *pushButton_cryptage;
    QPushButton *pushButton_passphrase;
    QVBoxLayout *verticalLayout;
    QLabel *label_text_decryptage;
    QPlainTextEdit *plainTextEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_clear;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QSpinBox *spinBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(510, 487);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_text_cryptage = new QLabel(centralWidget);
        label_text_cryptage->setObjectName(QString::fromUtf8("label_text_cryptage"));

        verticalLayout_3->addWidget(label_text_cryptage);

        plainTextEdit_cryptage = new QPlainTextEdit(centralWidget);
        plainTextEdit_cryptage->setObjectName(QString::fromUtf8("plainTextEdit_cryptage"));
        plainTextEdit_cryptage->setReadOnly(false);

        verticalLayout_3->addWidget(plainTextEdit_cryptage);

        pushButton_write_document = new QPushButton(centralWidget);
        pushButton_write_document->setObjectName(QString::fromUtf8("pushButton_write_document"));

        verticalLayout_3->addWidget(pushButton_write_document);

        pushButton_cryptage = new QPushButton(centralWidget);
        pushButton_cryptage->setObjectName(QString::fromUtf8("pushButton_cryptage"));

        verticalLayout_3->addWidget(pushButton_cryptage);

        pushButton_passphrase = new QPushButton(centralWidget);
        pushButton_passphrase->setObjectName(QString::fromUtf8("pushButton_passphrase"));

        verticalLayout_3->addWidget(pushButton_passphrase);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_text_decryptage = new QLabel(centralWidget);
        label_text_decryptage->setObjectName(QString::fromUtf8("label_text_decryptage"));

        verticalLayout->addWidget(label_text_decryptage);

        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setReadOnly(true);

        verticalLayout->addWidget(plainTextEdit);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_clear = new QPushButton(centralWidget);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));

        verticalLayout->addWidget(pushButton_clear);


        gridLayout->addLayout(verticalLayout, 1, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        verticalLayout_2->addWidget(spinBox);


        gridLayout->addLayout(verticalLayout_2, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 510, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label_text_cryptage->setText(QApplication::translate("MainWindow", "Message \303\240 cacher :", nullptr));
        plainTextEdit_cryptage->setPlainText(QApplication::translate("MainWindow", "NONE", nullptr));
        pushButton_write_document->setText(QApplication::translate("MainWindow", "Ecrire le message \303\240 cacher dans le document", nullptr));
        pushButton_cryptage->setText(QApplication::translate("MainWindow", "Choisir l'image \303\240 crypter", nullptr));
        pushButton_passphrase->setText(QApplication::translate("MainWindow", "PassPhrase", nullptr));
        label_text_decryptage->setText(QApplication::translate("MainWindow", "Code trouv\303\251 :", nullptr));
        plainTextEdit->setPlainText(QApplication::translate("MainWindow", "NONE", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Choisir l'image \303\240 d\303\251crypter", nullptr));
        pushButton_clear->setText(QApplication::translate("MainWindow", "Clear", nullptr));
        label->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
