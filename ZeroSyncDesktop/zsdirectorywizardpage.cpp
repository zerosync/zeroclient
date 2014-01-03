#include "zsdirectorywizardpage.h"

ZSDirectoryWizardPage::ZSDirectoryWizardPage() :
    QWizardPage()
{
    this->setTitle("Setting the ZeroSync directory");
    this->setSubTitle("All files in this directory will be synchronized with other peers.");
    zsDirectoryEdit = new QLineEdit();
    zsDirectoryChooser = new QPushButton("Choose Folder");
    layout = new QGridLayout();
    layout->addWidget(zsDirectoryEdit, 0, 0);
    layout->addWidget(zsDirectoryChooser, 0, 1);
    this->setLayout(layout);
    connect(zsDirectoryChooser, SIGNAL(clicked()), this, SLOT(slotSetZeroSyncDirectory()));
    this->registerField("pathLineEdit*", zsDirectoryEdit);
}


void ZSDirectoryWizardPage::slotSetZeroSyncDirectory()
{
    QString directoryPath = QFileDialog::getExistingDirectory(this, "Open Directory", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QDir checkDirectory(directoryPath);

    if(directoryPath.length() > 0 && checkDirectory.exists())
    {
        zsDirectoryEdit->setText(directoryPath);
    }
    else
    {
        QMessageBox::warning(0, "ZeroSync", "Please create or choose a correct folder!", QMessageBox::Ok, QMessageBox::Ok);
    }
}
