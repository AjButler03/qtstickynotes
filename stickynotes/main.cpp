#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "note.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Initialize the main window
    QMainWindow window;
    window.setWindowTitle("Sticky Notes");
    window.resize(400, 150);

    // Create a button for creating new Note windows
    QPushButton newNoteButton("New Note");

    // Create central layout, and a widget to contain it
    QWidget centralWidget;
    QVBoxLayout layout;

    // Adds button to layout
    layout.addWidget(&newNoteButton);

    // Sets central widget to contain layout
    centralWidget.setLayout(&layout);
    // sets central widget as the central widget
    window.setCentralWidget(&centralWidget);

    // Connects the button press to create a new Note
    // calling Note Constructor
    QObject::connect(
        &newNoteButton,
        &QPushButton::clicked,
        []()
        {
            Note *note = new Note;
            note->setAttribute(Qt::WA_DeleteOnClose);
            note->show();
        }
        );

    window.show();

    return app.exec();
}