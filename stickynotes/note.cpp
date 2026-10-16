#include "note.h"
#include "noteheader.h"
#include "notedata.h"
#include "notemanager.h"

#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTimer>
#include <QDebug>

Note::Note(NoteManager *manager, const QString &noteId, QWidget *parent)
    : QMainWindow{parent}
{
    // Initialize given fields
    noteManager = manager;
    this->noteId = noteId;

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
    textEdit = new QTextEdit;

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

    // Connecting header request for new window to creating a new Note window
    connect(header, &NoteHeader::newNoteRequested,
            this,
            [this]()
            {
                QString id = noteManager->assignId();
                qDebug() << "NoteId: " << id;
                Note *note = new Note(noteManager, id);
                note->setAttribute(Qt::WA_DeleteOnClose);
                note->show();
            }
            );

    // Set mainLayout for centralwidget, then put centralWidget in place
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

}

// Sets the window title to the given string.
void Note::setTitle(const QString &s){
    header->setTitle(s);
}

// Manually sets the body text of the sticky note.
void Note::setText(const QString &text){
    textEdit->setPlainText(text);
}

// Retreives the sticky note's title.
QString Note::getTitle() const {
    return header->getTitle();
}

// Retreives the sticky note's body text.
QString Note::getText() const{
    return textEdit->toPlainText();
}

// Create a NoteData object and pass to noteManager to save note
void Note::saveNote(){
    NoteData data = NoteData();

    data.isOpen = true;

    // Populate data fields
    data.id = noteId;
    data.title = header->getTitle();
    data.bodyText = textEdit->toPlainText();
};
