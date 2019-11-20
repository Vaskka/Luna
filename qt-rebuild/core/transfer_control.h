#ifndef TRANSFERCONTROL_H
#define TRANSFERCONTROL_H

#include <QObject>

class TransferControl : public QObject
{
    Q_OBJECT
public:
    explicit TransferControl(QObject *parent = nullptr);

signals:

public slots:
};

#endif // TRANSFERCONTROL_H
