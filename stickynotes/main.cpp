#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    // Initialize the application with passed arguements
    QApplication app(argc, argv);

    // Initialize a new window
    // Note specified title and size
    QMainWindow window;
    window.setWindowTitle("My Sticky Note");
    window.resize(400, 300);
    window.setMinimumSize(200, 100);

    // Create a textedit object
    QTextEdit textEdit;

    // Creating a button to clear written text
    QPushButton clearButton("Clear");
    QPushButton saveButton("Save (N/A)");

    // Create layout, add widgets to it
    QVBoxLayout mainLayout;
    QHBoxLayout toolBarLayout;


    // Create Widget to act as container for main, toolbar layouts
    QWidget centralWidget;

    // add buttons to toolbar layout
    toolBarLayout.addWidget(&clearButton);
    toolBarLayout.addWidget(&saveButton);
    toolBarLayout.addStretch();

    // add textedit, toolbar to main layout
    // and then that layout to main widget
    mainLayout.addWidget(&textEdit);
    mainLayout.addLayout(&toolBarLayout);
    centralWidget.setLayout(&mainLayout);

    // Set the main widget as the window's central widget
    window.setCentralWidget(&centralWidget);

    // Signal & Slot;
    // When button is clicked, clear the text
    QObject::connect(
        &clearButton,
        &QPushButton::clicked,
        &textEdit,
        &QTextEdit::clear
        );


    window.show();

    // run application; this is the event loop
    return app.exec();
}