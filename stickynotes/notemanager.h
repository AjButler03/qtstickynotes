#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include "notedata.h"

#include <QHash>
#include <QString>


// NoteManager is to handle saving / loading notes.
class NoteManager
{
public:
    NoteManager();

    // Loads all saved notes from file(s) into manager's hash
    // basically only ever runs on app startup
    bool loadNotes();

    // Creates an ID for new note
    // DOES NOT automatically save note to hash or file
    QString assignId();

    // Grabs note from manager's hash
    // Returns true/false for success, populates information into data
    bool getNoteInfo(const QString &id, NoteData &data);

    // Save note to manager's hash + file
    bool saveNote(const NoteData &data);

    // Delete from manager's hash + file
    bool deleteNote(const QString &id);

private:
    // Internal hashmap storage of the notes.
    QHash<QString, NoteData> m_notes;
};

#endif // NOTEMANAGER_H
