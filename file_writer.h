#ifndef FILE_WRITER_H
#define FILE_WRITER_H

#include <QObject>

class File_writer : public QObject
{
    Q_OBJECT
public:
    explicit File_writer(QObject *parent = nullptr);

signals:

public slots:
};

#endif // FILE_WRITER_H