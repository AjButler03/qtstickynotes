#include "notemanager.h"

#include <QUuid>
#include <QString>

NoteManager::NoteManager() {
    // NoteManager should always be constructed on launch of app
    // always should load existing NoteData entries from file

}


QString NoteManager::createNote()
{
    QString id = QUuid::createUuid().toString(
        QUuid::WithoutBraces
        );

    NoteData data;
    data.id = id;
    // This should be overwritten once the user does something with created note.
    data.title = "INIT_PLACEHOLDER";

    m_notes.insert(id, data);

    save();

    return id;
}

void NoteManager::save(){
    // TOOD
}

void NoteManager::load(){
    //TODO
}
