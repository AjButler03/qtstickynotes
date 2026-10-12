#ifndef NOTEDATA_H
#define NOTEDATA_H

#include <QString>

// Struct to contain note information; used for save/load of a Note
struct NoteData {
    // Unique identifier
    QString id;

    // Is the note currently open (on screen?)
    bool open = false;

    // User-Created title and body text
    QString title;
    QString bodytext;

    // The note's on-screen location when last saved
    int winx;
    int winy;

    // The Note's window dimensions when last saved
    int winWidth;
    int winHeight;
};

#endif // NOTEDATA_H
