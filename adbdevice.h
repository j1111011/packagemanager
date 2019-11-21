#ifndef ADBDEVICE_H
#define ADBDEVICE_H
#include "device.h"

class AdbDevice : public Device
{
public:
    AdbDevice();

    // Device interface
public:
    virtual void connect();
    virtual bool online();
    virtual void disconnect();
    virtual void remove(const char *pkg);
    virtual void exp(const char *savedir, const char *pkg);
    virtual void refresh();
    virtual QStringList list();
private:
    QStringList m_pkg_list;

};

#endif // ADBDEVICE_H
