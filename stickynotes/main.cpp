#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "note.h"
#include "notemanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create the NoteManager for handling file operations
    NoteManager noteManager = NoteManager();

    // Initialize the main window
    QMainWindow *window = new QMainWindow;
    window->setWindowTitle("Sticky Notes");
    window->resize(400, 150);

    // Create a button for creating new Note windows
    QPushButton *newNoteButton = new QPushButton("New Note");

    // Create central layout, and a widget to contain it
    QWidget *centralWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();

    // Adds button to layout
    layout->addWidget(newNoteButton);

    // Sets central widget to contain layout
    centralWidget->setLayout(layout);
    // sets central widget as the central widget
    window->setCentralWidget(centralWidget);

    // Connects the button press to create a new Note
    // calling Note Constructor
    QObject::connect(
        newNoteButton,
        &QPushButton::clicked,
        []()
        {
            Note *note = new Note;
            note->setAttribute(Qt::WA_DeleteOnClose);
            note->show();
        }
        );

    // Delete window when closed
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();

    return app.exec();
}