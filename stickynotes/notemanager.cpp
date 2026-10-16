#include "notemanager.h"
#include "notedata.h"

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QSaveFile>
#include <QStandardPaths>
#include <QUuid>
#include <QDebug>

// Returns the directory where note files are stored.
static QString getNotesDirectory()
{
    return QStandardPaths::writableLocation(
               QStandardPaths::AppDataLocation
               ) + "/notes";
}

// Returns the file path for a particular note.
static QString getNoteFilePath(const QString &id)
{
    return getNotesDirectory() + "/" + id + ".json";
}

NoteManager::NoteManager() {
    // Constructor is just concerned with initialization
    // Caller will be responsible for utilizing loadNotes() to populate hash
    // QHash<QString, NoteData> m_notes;
}

QString NoteManager::assignId(){
    QString id;

    // this will avoid id collisions.
    // It's apparently very unlikely, but I guess might as well.
    do {
        id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    } while (m_notes.contains(id));

    return id;
}

// Loads all saved notes from disk into the manager's hash.
bool NoteManager::loadNotes()
{
    QString directoryPath = getNotesDirectory();

    QDir directory(directoryPath);

    // If the directory doesn't exist yet, create it.
    if (!directory.exists()) {
        if (!QDir().mkpath(directoryPath)) {
            qWarning() << "Could not create notes directory:"
                       << directoryPath;
            return false;
        }

        // No saved notes exist yet.
        return true;
    }

    // Find all JSON files in the notes directory.
    QStringList files = directory.entryList(
        QStringList() << "*.json",
        QDir::Files
        );

    // Start with an empty hash.
    m_notes.clear();

    bool success = true;

    for (const QString &fileName : files) {
        QString filePath = directory.filePath(fileName);

        QFile file(filePath);

        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << "Could not open note file:"
                       << filePath
                       << file.errorString();

            success = false;
            continue;
        }

        QByteArray fileData = file.readAll();
        file.close();

        // Parse the JSON data.
        QJsonParseError parseError;

        QJsonDocument document =
            QJsonDocument::fromJson(fileData, &parseError);

        if (parseError.error != QJsonParseError::NoError ||
            !document.isObject()) {

            qWarning() << "Invalid JSON in note file:"
                       << filePath
                       << parseError.errorString();

            success = false;
            continue;
        }

        QJsonObject object = document.object();

        // Reconstruct the NoteData struct.
        NoteData data;

        data.id = object["id"].toString();
        data.title = object["title"].toString();
        data.bodyText = object["bodyText"].toString();

        data.winx = object["winx"].toInt(100);
        data.winy = object["winy"].toInt(100);

        data.winWidth = object["winWidth"].toInt(300);
        data.winHeight = object["winHeight"].toInt(350);

        // isOpen is runtime state, so it remains false.

        // Reject records without an ID.
        if (data.id.isEmpty()) {
            qWarning() << "Note has no ID:" << filePath;
            success = false;
            continue;
        }

        // Insert the note into the hash, using its ID as the key.
        m_notes.insert(data.id, data);
    }

    return success;
}

// Retrieves a note from the manager's hash.
bool NoteManager::getNoteInfo(
    const QString &id,
    NoteData &data)
{
    auto it = m_notes.constFind(id);

    if (it == m_notes.cend()) {
        return false;
    }

    data = it.value();

    return true;
}


// Saves a note to the manager's hash and its JSON file.
bool NoteManager::saveNote(const NoteData &data)
{
    // A note must have an ID.
    if (data.id.isEmpty()) {
        qWarning() << "Cannot save a note with an empty ID.";
        return false;
    }

    // Convert the note into a JSON object.
    QJsonObject object;

    object["id"] = data.id;
    object["title"] = data.title;
    object["bodyText"] = data.bodyText;

    object["winx"] = data.winx;
    object["winy"] = data.winy;

    object["winWidth"] = data.winWidth;
    object["winHeight"] = data.winHeight;

    // Create a JSON document from the object.
    QJsonDocument document(object);

    // Ensure the notes directory exists.
    QString directoryPath = getNotesDirectory();

    if (!QDir().mkpath(directoryPath)) {
        qWarning() << "Could not create notes directory:"
                   << directoryPath;
        return false;
    }

    // Determine the file path for this note.
    QString filePath = getNoteFilePath(data.id);

    // Write safely using QSaveFile.
    QSaveFile file(filePath);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Could not open note file for writing:"
                   << filePath
                   << file.errorString();
        return false;
    }

    QByteArray jsonData =
        document.toJson(QJsonDocument::Indented);

    if (file.write(jsonData) == -1) {
        qWarning() << "Could not write note file:"
                   << filePath
                   << file.errorString();

        file.cancelWriting();
        return false;
    }

    if (!file.commit()) {
        qWarning() << "Could not save note file:"
                   << filePath
                   << file.errorString();
        return false;
    }

    // Update the in-memory record only after the file is saved.
    m_notes.insert(data.id, data);

    return true;
}