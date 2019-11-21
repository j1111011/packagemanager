#ifndef UNITS_H
#define UNITS_H
#define MSG_REFRESH 0
#define MSG_EXPORT 1
#define MSG_REMOVE 2

#include <QMap>
#include <QString>
#include <QVariant>
class QMutex;
class Units
{
    Units();
public:
    static Units* create(int msg);
    static void release(Units* unit);
    static Units* get(qint64 id);

    int type() const;
    void setType(int type);

    qint64 id() const;

    QVariant getArg1() const;
    void setArg1(const QVariant &arg1);

    QVariant getArg2() const;
    void setArg2(const QVariant &arg2);

private:
    qint64 m_id;
    int m_type;
    int m_arg0;
    QVariant m_arg1;
    QVariant m_arg2;
    static QMap<qint64,Units*> m_units;
    static QMutex* m_mtx;
};

#endif // UNITS_H
