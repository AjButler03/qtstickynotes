#ifndef NOTE_H
#define NOTE_H

#include <QMainWindow>

class Note : public QMainWindow
{
    Q_OBJECT
public:
    explicit Note(QWidget *parent = nullptr);

    void setTitle(QString s);
    QString getTitle();

signals:

};

#endif // NOTE_H
