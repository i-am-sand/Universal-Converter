/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *inputEdit;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QLineEdit *fromBaseEdit;
    QLineEdit *toBaseEdit;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *convertButton;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QTextEdit *outputEdit;
    QLabel *errorLabel;
    QMenuBar *menubar;
    QMenu *menuConverter;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1048, 663);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        inputEdit = new QLineEdit(centralwidget);
        inputEdit->setObjectName("inputEdit");
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(inputEdit->sizePolicy().hasHeightForWidth());
        inputEdit->setSizePolicy(sizePolicy);
        inputEdit->setMinimumSize(QSize(0, 50));
        QFont font;
        font.setPointSize(14);
        inputEdit->setFont(font);

        verticalLayout_2->addWidget(inputEdit);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        fromBaseEdit = new QLineEdit(centralwidget);
        fromBaseEdit->setObjectName("fromBaseEdit");
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(fromBaseEdit->sizePolicy().hasHeightForWidth());
        fromBaseEdit->setSizePolicy(sizePolicy1);
        fromBaseEdit->setMinimumSize(QSize(400, 50));
        fromBaseEdit->setFont(font);

        verticalLayout->addWidget(fromBaseEdit);

        toBaseEdit = new QLineEdit(centralwidget);
        toBaseEdit->setObjectName("toBaseEdit");
        sizePolicy1.setHeightForWidth(toBaseEdit->sizePolicy().hasHeightForWidth());
        toBaseEdit->setSizePolicy(sizePolicy1);
        toBaseEdit->setMinimumSize(QSize(400, 50));
        toBaseEdit->setFont(font);

        verticalLayout->addWidget(toBaseEdit);


        horizontalLayout_3->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        convertButton = new QPushButton(centralwidget);
        convertButton->setObjectName("convertButton");
        sizePolicy1.setHeightForWidth(convertButton->sizePolicy().hasHeightForWidth());
        convertButton->setSizePolicy(sizePolicy1);
        convertButton->setMinimumSize(QSize(200, 100));
        convertButton->setFont(font);

        horizontalLayout->addWidget(convertButton);

        loadButton = new QPushButton(centralwidget);
        loadButton->setObjectName("loadButton");
        sizePolicy1.setHeightForWidth(loadButton->sizePolicy().hasHeightForWidth());
        loadButton->setSizePolicy(sizePolicy1);
        loadButton->setMinimumSize(QSize(200, 100));
        loadButton->setFont(font);

        horizontalLayout->addWidget(loadButton);

        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName("saveButton");
        sizePolicy1.setHeightForWidth(saveButton->sizePolicy().hasHeightForWidth());
        saveButton->setSizePolicy(sizePolicy1);
        saveButton->setMinimumSize(QSize(200, 100));
        saveButton->setFont(font);

        horizontalLayout->addWidget(saveButton);


        horizontalLayout_3->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(horizontalLayout_3);

        outputEdit = new QTextEdit(centralwidget);
        outputEdit->setObjectName("outputEdit");
        outputEdit->setFont(font);
        outputEdit->setReadOnly(true);

        verticalLayout_2->addWidget(outputEdit);

        errorLabel = new QLabel(centralwidget);
        errorLabel->setObjectName("errorLabel");
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(errorLabel->sizePolicy().hasHeightForWidth());
        errorLabel->setSizePolicy(sizePolicy2);
        errorLabel->setMinimumSize(QSize(100, 100));
        errorLabel->setFont(font);

        verticalLayout_2->addWidget(errorLabel);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1048, 23));
        menuConverter = new QMenu(menubar);
        menuConverter->setObjectName("menuConverter");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuConverter->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        inputEdit->setText(QString());
        inputEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\207\320\270\321\201\320\273\320\276", nullptr));
        fromBaseEdit->setText(QString());
        fromBaseEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\270\321\201\321\205\320\276\320\264\320\275\321\203\321\216 \321\201\320\270\321\201\321\202\320\265\320\274\321\203 \321\201\321\207\320\270\321\201\320\273\320\265\320\275\320\270\321\217", nullptr));
        toBaseEdit->setText(QString());
        toBaseEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\206\320\265\320\273\320\265\320\262\321\203\321\216 \321\201\320\270\321\201\321\202\320\265\320\274\321\203 \321\201\321\207\320\270\321\201\320\273\320\265\320\275\320\270\321\217", nullptr));
        convertButton->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\275\320\262\320\265\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        loadButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        outputEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Ubuntu Sans'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        outputEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\262\320\276\320\264", nullptr));
        errorLabel->setText(QCoreApplication::translate("MainWindow", "\320\236\321\210\320\270\320\261\320\272\320\270:", nullptr));
        menuConverter->setTitle(QCoreApplication::translate("MainWindow", "Converter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
