#ifndef DEVICE_H
#define DEVICE_H

#include <QStringList>

class Device
{
public:
    Device();
    virtual void connect() = 0;
    virtual bool online() = 0;
    virtual void disconnect() = 0;
    virtual void remove(const char* pkg) = 0;
    virtual void exp(const char* savedir,const char* pkg) = 0;
    virtual void refresh() = 0;
    virtual QStringList list() = 0;
};

#endif // DEVICE_H
