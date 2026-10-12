#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <QHash>
#include <QString>

#include "notedata.h"


// NoteManager is to handle saving / loading notes.
class NoteManager
{
public:
    NoteManager();

    QString createNote();

    // difference between these?
    NoteData *getNote(const QString &id);
    const NoteData *getNote(const QString &id) const;

    bool updateNote(const NoteData &data);
    bool deleteNote(const QString &id);

private:
    // Internal hashmap storage of the notes.
    QHash<QString, NoteData> m_notes;

    void save();
    void load();
};

#endif // NOTEMANAGER_H
