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
    connect(zsDirectoryEdit, SIGNAL(textChanged(QString)), this, SIGNAL(completeChanged()));
    this->registerField("pathLineEdit*", zsDirectoryEdit);
}


void ZSDirectoryWizardPage::slotSetZeroSyncDirectory()
{
    QString directoryPath = QFileDialog::getExistingDirectory(this, "Open Directory", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    zsDirectoryEdit->setText(directoryPath);
}

bool ZSDirectoryWizardPage::isComplete() const
{
    QDir checkDirectory(zsDirectoryEdit->text());
    if(zsDirectoryEdit->text().length() > 0 && checkDirectory.exists())
    {
        return true;
    }
    return false;
}
