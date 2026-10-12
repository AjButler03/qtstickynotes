#ifndef NOTE_H
#define NOTE_H

#include "notemanager.h"

#include <QMainWindow>
#include <QTextEdit>


class DoubleClickLabel;
class QLineEdit;
class NoteHeader;

class Note : public QMainWindow
{
    Q_OBJECT
public:
    explicit Note(NoteManager *manager, const QString &noteid, QWidget *parent = nullptr);



    void setTitle(const QString &s);
    void setText(const QString &text);

    QString getTitle() const;
    QString getText() const;

private:
    const QString baseTitle = "Untitled Note";
    NoteHeader *header;
    QTextEdit *textEdit;
    NoteManager *noteManager;
    QString noteId;

signals:

};

#endif // NOTE_H
