#include "note.h"
#include "noteheader.h"

#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTimer>

Note::Note(QWidget *parent)
    : QMainWindow{parent}
{
    // Removing the native window border
    // setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    setWindowTitle(baseTitle);
    resize(400, 200);

    /*
     * === MAIN DESIGN ===
     */
    // Create layouts & Central Widget to contain it
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *toolbarLayout = new QHBoxLayout;
    QWidget *centralWidget = new QWidget;

    // Create the note's header
    header = new NoteHeader(baseTitle, this);

    // Create the primary textedit portion of the note
    QTextEdit *textEdit = new QTextEdit;

    // Add header, textedit, and toolbar to main layout
    mainLayout->addWidget(header);
    mainLayout->addWidget(textEdit);
    mainLayout->addLayout(toolbarLayout);

    /*
     * === TOOLBAR WIDGETS ===
     */
    // Create a simple button for the toolbar (mostly a placeholder for now)
    QPushButton *clearButton = new QPushButton("Clear");
    toolbarLayout->addWidget(clearButton);

    /*
     * === SIGNAL / SLOT CONNECTIONS ===
     */
    // Connecting the button so that it clears text when clicked
    QObject::connect(
        clearButton,
        &QPushButton::clicked,
        textEdit,
        &QTextEdit::clear
        );

    // Connecting header signals to the window
    connect(header, &NoteHeader::closeRequested,
            this, &QWidget::close);

    connect(header, &NoteHeader::minimizeRequested,
            this, &QWidget::showMinimized);

    connect(header, &NoteHeader::titleChanged,
            this, &Note::setTitle);

    // Set mainLayout for centralwidget, then put centralWidget in place
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

// Sets the window title to the given string.
void Note::setTitle(QString s){
    header->setTitle(s);
}

QString Note::getTitle(){
    return header->getTitle();
}
