#include "units.h"

#include <QDateTime>
#include <QMutex>

QMutex* Units::m_mtx = new QMutex();
QMap<qint64,Units*> Units::m_units;

Units::Units()
{
    m_id = QDateTime::currentMSecsSinceEpoch();
}

Units *Units::create(int msg)
{
    QMutexLocker locker(m_mtx);
    auto unit = new Units();
    unit->setType(msg);
    m_units[unit->id()] = unit;
    return unit;
}

void Units::release(Units *unit)
{
    QMutexLocker locker(m_mtx);
    if(unit != nullptr)
    {
        m_units.remove(unit->id());
        delete unit;
    }
}

Units *Units::get(qint64 id)
{
    QMutexLocker locker(m_mtx);
    Units* unit = nullptr;
    if(m_units.contains(id))
    {
        unit = m_units[id];
    }
    return unit;
}

int Units::type() const
{
    return m_type;
}

void Units::setType(int type)
{
    m_type = type;
}


qint64 Units::id() const
{
    return m_id;
}

QVariant Units::getArg1() const
{
    return m_arg1;
}

void Units::setArg1(const QVariant &arg1)
{
    m_arg1 = arg1;
}

QVariant Units::getArg2() const
{
    return m_arg2;
}

void Units::setArg2(const QVariant &arg2)
{
    m_arg2 = arg2;
}
