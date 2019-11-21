#ifndef BRIDGE_H
#define BRIDGE_H

#include <QObject>
#include <QDebug>
class Worker;
class Bridge : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList names READ names WRITE setNames NOTIFY namesChanged)

public:
    Bridge();
    Q_INVOKABLE
    void export_package(const QString& dir,const QString& pkgname);
    Q_INVOKABLE
    void remove_package(const QString& pkgname);
    Q_INVOKABLE
    void refresh();
    Q_INVOKABLE
    void filter(const QString& filter);
    Q_INVOKABLE
    void reset();
    Q_INVOKABLE
    int size() const;
    Q_INVOKABLE
    void quit();
    Q_INVOKABLE
    QString name(int idx);
    QStringList names() const;
    void setNames(const QStringList& names);

    Worker *worker() const;
    void setWorker(Worker *worker);

signals:
    Q_SIGNAL
    void namesChanged();
    Q_SIGNAL
    void packageRemoved();
    Q_SIGNAL
    void packageSaved();
private slots:
    void on_units_processed(qint64 id);
    void on_connected();
private:

    QStringList mNames;
    QStringList mFilterNames;
    Worker* m_worker;
};
#endif // BRIDGE_H
