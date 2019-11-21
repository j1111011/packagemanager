#include "worker.h"
#include "devicediscover.h"
#include "deviceconnector.h"
#include "device.h"
#include "units.h"

#include <QMutex>
#include <QWaitCondition>
#include <QDebug>

Worker::Worker(QObject *parent) : QThread(parent)
{
    m_mtx = new QMutex();
    m_condition = new QWaitCondition();
    m_exit_flags = false;
}

Worker::~Worker()
{
    delete m_mtx;
    delete m_condition;
}

void Worker::run()
{
// loop
    // check connected
    // -- false connect
    // do somethings.
    DeviceDiscover discover;
    while(!m_exit_flags) {
        // block until found a device.
        auto type = discover.found();
        if(type < 0)
        {
            sleep(1);
            continue;
        }

        auto device = DeviceConnector::create((DeviceConnector::DeviceType)type);
        if(device == nullptr)
        {
            sleep(1);
            continue;
        }
        device->connect();
        m_device = device;
        emit connected();
        while(device->online() && !m_exit_flags)
        {
            if(!m_units.isEmpty())
            {
                m_mtx->lock();
                Units* unit = m_units.front();
                m_units.pop_front();
                m_mtx->unlock();
                qDebug() << "process: " << unit->type() << unit;
                switch (unit->type()) {
                case MSG_EXPORT:
                    device->exp(unit->getArg1().toString().toUtf8().data(),unit->getArg2().toString().toUtf8().data());
                    break;
                case MSG_REFRESH:
                    device->refresh();
                    break;
                case MSG_REMOVE:
                    device->remove(unit->getArg1().toString().toUtf8().data());
                    break;
                default:
                    break;
                }
                emit unit_processed(unit->id());
            }
            else
            {
                qDebug() << "wait...";
                QMutexLocker locker(m_mtx);
                m_condition->wait(m_mtx);
            }
        }
        emit disconnected();
    }
}

void Worker::add(Units *unit)
{
    QMutexLocker locker(m_mtx);
    m_units.append(unit);
    m_condition->wakeAll();
}

void Worker::quit()
{
    m_exit_flags = true;
    m_condition->wakeAll();
}


