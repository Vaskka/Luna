#ifndef LUNACORE_H
#define LUNACORE_H

#include <QObject>

class LunaCore : public QObject
{
    Q_OBJECT
public:
    explicit LunaCore(QObject *parent = nullptr);

signals:

public slots:
};

#endif // LUNACORE_H
