#ifndef ZSSYNCWIZARDPAGE_H
#define ZSSYNCWIZARDPAGE_H

#include <QObject>
#include <QWizardPage>
#include <QLabel>
#include <QGridLayout>
#include <QtDebug>
#include <QSlider>

class ZSSyncWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit ZSSyncWizardPage();

private:
    QLabel *syncIntervalLabel;
    QLabel *labelSyncIntervalMin;
    QLabel *labelSyncIntervalMax;
    QLabel *labelSyncIntervalValue;
    QGridLayout *layout;
    QSlider *sliderSyncInterval;

signals:

public slots:

private slots:
    void slotSliderSyncIntervalChanged(int);

};

#endif // ZSSYNCWIZARDPAGE_H
