#include "home.h"
#include "note.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSaveFile>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

Home::Home(QWidget *parent)
    : QMainWindow{parent}
{}


QString Home::saveFilePath() const
{
    QString directory = QStandardPaths::writableLocation(
        QStandardPaths::AppDataLocation
        );

    return directory + "/notes.json";
}
