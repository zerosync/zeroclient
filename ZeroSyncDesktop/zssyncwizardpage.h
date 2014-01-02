#ifndef ZSSYNCWIZARDPAGE_H
#define ZSSYNCWIZARDPAGE_H

#include <QObject>
#include <QRadioButton>
#include <QWizardPage>
#include <QLabel>
#include <QGridLayout>
#include <QButtonGroup>
#include <QtDebug>
#include <QAbstractSlider>

class ZSSyncWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit ZSSyncWizardPage();

private:
    QLabel *syncIntervalLabel;
    QGridLayout *layout;
    QButtonGroup *radioButtonGroup;
    QRadioButton *radioButtonManual;
    QRadioButton *radioButton15Sec;
    QRadioButton *radioButton1Min;
    QRadioButton *radioButton5Min;
    QAbstractSlider *abstractSliderToHoldValue;

signals:

public slots:

private slots:
    void slotSetRadioButtonChecked(int);

};

#endif // ZSSYNCWIZARDPAGE_H
