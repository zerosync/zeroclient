#include "zsdirectorywizardpage.h"

ZSDirectoryWizardPage::ZSDirectoryWizardPage() :
    QWizardPage()
{
    this->setTitle("Setting the ZeroSync directory");
    this->setSubTitle("All files in this directory will be synchronized with other peers.");
    zsDirectoryLabel = new QLabel("Path:");
    zsDirectoryEdit = new QLineEdit();
    zsDirectoryChooser = new QPushButton();
    layout = new QGridLayout();
    layout->addWidget(zsDirectoryLabel, 0, 0);
    layout->addWidget(zsDirectoryEdit, 0, 1);
    layout->addWidget(zsDirectoryChooser, 0, 2);
    this->setLayout(layout);
    connect(zsDirectoryChooser, SIGNAL(clicked()), this, SLOT(slotSetZeroSyncDirectory()));
    this->registerField("pathLineEdit*", zsDirectoryEdit);
}


void ZSDirectoryWizardPage::slotSetZeroSyncDirectory()
{
    QString directoryPath = QFileDialog::getExistingDirectory(this, "Open Directory", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QDir checkDirectoryToWatch(directoryPath);

    if(directoryPath.length() > 0 && checkDirectoryToWatch.exists())
    {
        qDebug() << "Test: Directory Set";
    }
}