#include "bridge.h"
#include "worker.h"
#include "units.h"
#include "device.h"

Bridge::Bridge()
{
    m_worker = nullptr;
}

void Bridge::export_package(const QString &dir, const QString &pkgname)
{
    qDebug() << dir << pkgname;
    if(m_worker != nullptr)
    {
        auto unit = Units::create(MSG_EXPORT);
        unit->setArg1(dir);
        unit->setArg2(pkgname);
        m_worker->add(unit);
    }
}

void Bridge::remove_package(const QString &pkgname)
{
    qDebug() << pkgname;
    if(m_worker != nullptr)
    {
        auto unit = Units::create(MSG_REMOVE);
        unit->setArg1(pkgname);
        m_worker->add(unit);
    }
}

void Bridge::refresh()
{
    if(m_worker != nullptr)
    {
        auto unit = Units::create(MSG_REFRESH);
        m_worker->add(unit);
    }
}

void Bridge::filter(const QString &filter)
{
    mFilterNames.clear();
    for(const QString& s:mNames)
    {
        if(s.contains(filter))
        {
            mFilterNames.append(s);
        }
    }
    emit namesChanged();
}

void Bridge::reset()
{
    qDebug() << __FUNCTION__;
    mFilterNames = mNames;
    emit namesChanged();
}

int Bridge::size() const
{
    auto size = mFilterNames.size();
    qDebug() << size;
    return size;
}

void Bridge::quit()
{
    if(m_worker != nullptr)
    {
        qDebug() << __FUNCTION__;
        m_worker->quit();
    }
}

QString Bridge::name(int idx)
{
    return mFilterNames[idx];
}

QStringList Bridge::names() const
{
    return mNames;
}

void Bridge::setNames(const QStringList &names)
{
    mNames = names;
}

Worker *Bridge::worker() const
{
    return m_worker;
}

void Bridge::setWorker(Worker *worker)
{
    if(m_worker != nullptr)
    {
        disconnect(m_worker,SIGNAL(unit_processed(qint64)),this,0);
        m_worker = nullptr;
    }
    if(worker != nullptr)
    {
        connect(worker,SIGNAL(connected()),SLOT(on_connected()));

        connect(worker,SIGNAL(unit_processed(qint64)),SLOT(on_units_processed(qint64)));
        m_worker = worker;
    }
}

void Bridge::on_units_processed(qint64 id)
{
    auto unit = Units::get(id);
    if(unit != nullptr)
    {
        switch (unit->type())
        {
        case MSG_EXPORT:
            emit packageSaved();
            break;
        case MSG_REMOVE:
        case MSG_REFRESH:
            mNames = m_worker->current()->list();
            reset();
            break;
        default:
            break;
        }
    }

}

void Bridge::on_connected()
{
    auto device = m_worker->current();
    auto names = device->list();
    qDebug() << names;
    mNames = names;
    reset();
}
