#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "note.h"
#include "notemanager.h"

int main(int argc, char *argv[])
{
    // Init application
    QApplication app(argc, argv);

    // Create the NoteManager for handling file operations
    QCoreApplication::setOrganizationName("AjButler03");
    QCoreApplication::setApplicationName("StickyNotes");

    NoteManager manager;

    if (!manager.loadNotes()) {
        qWarning() << "Failed to load notes.";
        return 1;
    }

    // Create a test note.
    NoteData data;
    data.id = manager.assignId();
    data.title = "Test Note";
    data.bodyText = "This is a test.";
    data.winx = 100;
    data.winy = 150;
    data.winWidth = 300;
    data.winHeight = 350;

    // Save the note.
    if (!manager.saveNote(data)) {
        qWarning() << "Failed to save note.";
        return 1;
    }

    qDebug() << "Saved note with ID:" << data.id;

    // Retrieve the note from the manager.
    NoteData loadedData;

    if (manager.getNoteInfo(data.id, loadedData)) {
        qDebug() << "Successfully retrieved note:";
        qDebug() << "ID:" << loadedData.id;
        qDebug() << "Title:" << loadedData.title;
        qDebug() << "Body:" << loadedData.bodyText;
        qDebug() << "Position:" << loadedData.winx << loadedData.winy;
        qDebug() << "Size:" << loadedData.winWidth << loadedData.winHeight;
    } else {
        qWarning() << "Failed to retrieve note.";
        return 1;
    }

    return 0;

    // // Initialize the main window
    // QMainWindow *window = new QMainWindow;
    // window->setWindowTitle("Sticky Notes");
    // window->resize(400, 150);

    // // Create a button for creating new Note windows
    // QPushButton *newNoteButton = new QPushButton("New Note");

    // // Create central layout, and a widget to contain it
    // QWidget *centralWidget = new QWidget();
    // QVBoxLayout *layout = new QVBoxLayout();

    // // Adds button to layout
    // layout->addWidget(newNoteButton);

    // // Sets central widget to contain layout
    // centralWidget->setLayout(layout);
    // // sets central widget as the central widget
    // window->setCentralWidget(centralWidget);

    // // Connects the button press to create a new Note
    // // calling Note Constructor
    // QObject::connect(
    //     newNoteButton,
    //     &QPushButton::clicked,
    //     [&noteManager]()
    //     {
    //         QString id = noteManager.assignId();
    //         qDebug() << "NoteId: " << id;
    //         Note *note = new Note(&noteManager, id);
    //         note->setAttribute(Qt::WA_DeleteOnClose);
    //         note->show();
    //     }
    //     );

    // // Delete window when closed
    // window->setAttribute(Qt::WA_DeleteOnClose);
    // window->show();

    // return app.exec();
}