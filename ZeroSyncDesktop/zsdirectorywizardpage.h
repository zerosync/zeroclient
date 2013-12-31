#ifndef ZSDIRECTORYWIZARDPAGE_H
#define ZSDIRECTORYWIZARDPAGE_H

#include <QObject>
#include <QWizardPage>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QDir>
#include <QFileDialog>
#include <QtDebug>

class ZSDirectoryWizardPage : public QWizardPage
{

public:
    explicit ZSDirectoryWizardPage();
    QLabel *zsDirectoryLabel;
    QLineEdit *zsDirectoryEdit;
    QPushButton *zsDirectoryChooser;
    QGridLayout *layout;

signals:

public slots:

private slots:
    void slotSetZeroSyncDirectory();

};

#endif // ZSDIRECTORYWIZARDPAGE_H
