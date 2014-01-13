#ifndef ZSCONNECTOR_H
#define ZSCONNECTOR_H

#include <QObject>
#include <cstdint>
#include <cstdlib>
#include <cstdio>



class ZSConnector : public QObject
{

public:
    explicit ZSConnector(QObject *parent = 0);

private:

    static void get_update();
    static void pass_update();
    static void get_chunk();
    static void pass_chunk();
    static void get_current_state();

signals:

public slots:

};

#endif // ZSCONNECTOR_H
