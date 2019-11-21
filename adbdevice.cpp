#include "adbdevice.h"

#include <qmath.h>
#include <QDebug>
#include <QDateTime>
#include <QThread>

const auto adb = "adb.exe";
AdbDevice::AdbDevice()
{
    refresh();
}

void AdbDevice::connect()
{

}

bool AdbDevice::online()
{
    //adb devices
    return true;
}

void AdbDevice::disconnect()
{
    // none.
}

void AdbDevice::remove(const char *pkg)
{
    // adb uninstall pkg
    m_pkg_list.removeAll(pkg);
}

void AdbDevice::exp(const char *savedir, const char *pkg)
{
    // adb pull pkg_loc savedir
    qDebug() << savedir << pkg;
}
QString random_string(int len)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());
    QString str = "";
    char minCh = 'a';
    char maxCh = 'Z';
    for(auto it = 0;it != len;++it)
    {
        char ch = minCh + qrand() % (maxCh - minCh);
        str.append(ch);
    }
    return str;
}
void AdbDevice::refresh()
{
    m_pkg_list.clear();
    for(auto it = 0;it != 20;++it)
    {
        QString pkg = "com." + random_string(5) + "." + random_string(10);
        QThread::currentThread()->msleep(2);
        m_pkg_list.append(pkg);
    }
}

QStringList AdbDevice::list()
{
    return m_pkg_list;
}
