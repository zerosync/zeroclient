/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuitZeroSync;
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *labelZeroSyncDirectory;
    QLineEdit *lineEditDirectoryPath;
    QPushButton *buttonSetDirectory;
    QPushButton *buttonSave;
    QPushButton *buttonReset;
    QFrame *line;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QSlider *sliderSyncInterval;
    QLabel *labelSyncIntervalMax;
    QLabel *labelSyncIntervalMin;
    QLabel *labelSyncIntervalValue;
    QLabel *labelSynchronization;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(426, 239);
        MainWindow->setMinimumSize(QSize(426, 239));
        MainWindow->setMaximumSize(QSize(426, 239));
        actionQuitZeroSync = new QAction(MainWindow);
        actionQuitZeroSync->setObjectName(QStringLiteral("actionQuitZeroSync"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 411, 75));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        labelZeroSyncDirectory = new QLabel(verticalLayoutWidget);
        labelZeroSyncDirectory->setObjectName(QStringLiteral("labelZeroSyncDirectory"));

        verticalLayout->addWidget(labelZeroSyncDirectory);

        lineEditDirectoryPath = new QLineEdit(verticalLayoutWidget);
        lineEditDirectoryPath->setObjectName(QStringLiteral("lineEditDirectoryPath"));

        verticalLayout->addWidget(lineEditDirectoryPath);

        buttonSetDirectory = new QPushButton(verticalLayoutWidget);
        buttonSetDirectory->setObjectName(QStringLiteral("buttonSetDirectory"));

        verticalLayout->addWidget(buttonSetDirectory);

        buttonSave = new QPushButton(centralWidget);
        buttonSave->setObjectName(QStringLiteral("buttonSave"));
        buttonSave->setGeometry(QRect(340, 210, 80, 23));
        buttonReset = new QPushButton(centralWidget);
        buttonReset->setObjectName(QStringLiteral("buttonReset"));
        buttonReset->setGeometry(QRect(250, 210, 80, 23));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 90, 431, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 110, 411, 80));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        sliderSyncInterval = new QSlider(gridLayoutWidget);
        sliderSyncInterval->setObjectName(QStringLiteral("sliderSyncInterval"));
        sliderSyncInterval->setMaximum(3600000);
        sliderSyncInterval->setSingleStep(10000);
        sliderSyncInterval->setPageStep(60000);
        sliderSyncInterval->setOrientation(Qt::Horizontal);
        sliderSyncInterval->setTickPosition(QSlider::TicksBothSides);
        sliderSyncInterval->setTickInterval(60000);

        gridLayout->addWidget(sliderSyncInterval, 3, 1, 1, 1);

        labelSyncIntervalMax = new QLabel(gridLayoutWidget);
        labelSyncIntervalMax->setObjectName(QStringLiteral("labelSyncIntervalMax"));

        gridLayout->addWidget(labelSyncIntervalMax, 3, 2, 1, 1);

        labelSyncIntervalMin = new QLabel(gridLayoutWidget);
        labelSyncIntervalMin->setObjectName(QStringLiteral("labelSyncIntervalMin"));

        gridLayout->addWidget(labelSyncIntervalMin, 3, 0, 1, 1);

        labelSyncIntervalValue = new QLabel(gridLayoutWidget);
        labelSyncIntervalValue->setObjectName(QStringLiteral("labelSyncIntervalValue"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        labelSyncIntervalValue->setFont(font);
        labelSyncIntervalValue->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelSyncIntervalValue, 2, 1, 1, 1);

        labelSynchronization = new QLabel(gridLayoutWidget);
        labelSynchronization->setObjectName(QStringLiteral("labelSynchronization"));

        gridLayout->addWidget(labelSynchronization, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ZeroSync Options", 0));
        actionQuitZeroSync->setText(QApplication::translate("MainWindow", "Quit", 0));
        labelZeroSyncDirectory->setText(QApplication::translate("MainWindow", "Your current local Zerosync folder:", 0));
        buttonSetDirectory->setText(QApplication::translate("MainWindow", "Change Directory", 0));
        buttonSave->setText(QApplication::translate("MainWindow", "Save", 0));
        buttonReset->setText(QApplication::translate("MainWindow", "Reset", 0));
        labelSyncIntervalMax->setText(QApplication::translate("MainWindow", "60 Minutes", 0));
        labelSyncIntervalMin->setText(QApplication::translate("MainWindow", "Manual", 0));
        labelSyncIntervalValue->setText(QApplication::translate("MainWindow", "Manual", 0));
        labelSynchronization->setText(QApplication::translate("MainWindow", "Choose synchronization interval:", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
