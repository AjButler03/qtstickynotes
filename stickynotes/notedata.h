#ifndef NOTEDATA_H
#define NOTEDATA_H

#include <QString>

// Struct to contain note information; used for save/load of a Note
struct NoteData {
    // Unique identifier
    QString id;

    // Is the note currently open (on screen?)
    bool isOpen = false;

    // User-Created title and body text
    QString title;
    QString bodyText;

    // The note's on-screen location when last saved
    int winx = 256;
    int winy = 256;

    // The Note's window dimensions when last saved
    int winWidth = 400;
    int winHeight = 200;
};

#endif // NOTEDATA_H
