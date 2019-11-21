#ifndef DEVICEDISCOVER_H
#define DEVICEDISCOVER_H

#include <QObject>

class DeviceDiscover : public QObject
{
    Q_OBJECT
public:
    explicit DeviceDiscover(QObject *parent = nullptr);
    int found();
signals:

public slots:
};

#endif // DEVICEDISCOVER_H
