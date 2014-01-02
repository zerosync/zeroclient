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
#include <QMessageBox>

class ZSDirectoryWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit ZSDirectoryWizardPage();

private:
    QLineEdit *zsDirectoryEdit;
    QPushButton *zsDirectoryChooser;
    QGridLayout *layout;

signals:

public slots:

private slots:
    void slotSetZeroSyncDirectory();

};

#endif // ZSDIRECTORYWIZARDPAGE_H
