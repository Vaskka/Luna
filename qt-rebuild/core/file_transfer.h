#ifndef FILETRANSFER_H
#define FILETRANSFER_H

#include <QObject>

class FileTransfer : public QObject {
  Q_OBJECT

 signals:

 public slots:

 public:
  explicit FileTransfer(QObject* parent = nullptr);
};

#endif  // FILETRANSFER_H
