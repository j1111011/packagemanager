#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QMutex>
#include <QVector>


class Units;
class QMutex;
class QWaitCondition;
class Device;
class Worker : public QThread
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
    ~Worker();
    virtual void run();
    void add(Units* unit);
    Device* current()
    {
        return m_device;
    }

signals:
    void unit_processed(qint64 id);
    void connected();
    void disconnected();
public slots:
    void quit();
private:
    bool m_exit_flags;
    QVector<Units*> m_units;
    QMutex* m_mtx;
    QWaitCondition* m_condition;
    Device* m_device;
};

#endif // WORKER_H
