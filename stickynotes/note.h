#ifndef NOTE_H
#define NOTE_H

#include "doubleclicklabel.h"

#include <QMainWindow>


class DoubleClickLabel;
class QLineEdit;
class NoteHeader;

class Note : public QMainWindow
{
    Q_OBJECT
public:
    explicit Note(QWidget *parent = nullptr);

    void setTitle(QString s);
    QString getTitle();

private:
    const QString baseTitle = "Untitled Note";
    NoteHeader *header;

signals:

};

#endif // NOTE_H
