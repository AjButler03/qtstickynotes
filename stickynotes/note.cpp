#include "note.h"

#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

Note::Note(QWidget *parent)
    : QMainWindow{parent}
{
    setWindowTitle("My Sticky Note");
    resize(400, 200);

    // Create layouts & Central Widget to contain it
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *toolbarLayout = new QHBoxLayout;
    QWidget *centralWidget = new QWidget;

    // Create the primary textedit portion of the note
    QTextEdit *textEdit = new QTextEdit;

    // Add textEdit and toolbar to mainLayout
    mainLayout->addWidget(textEdit);
    mainLayout->addLayout(toolbarLayout);

    // Create a simple button for the toolbar (mostly a placeholder for now)
    QPushButton *clearButton = new QPushButton("Clear");
    toolbarLayout->addWidget(clearButton);

    // Connecting the button so that it clears text when clicked
    QObject::connect(
        clearButton,
        &QPushButton::clicked,
        textEdit,
        &QTextEdit::clear
        );

    // Set mainLayout for centralwidget, then put centralWidget in place
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void Note::setTitle(QString s){
    this->setWindowTitle(s);
}

QString Note::getTitle(){
    return this->windowTitle();
}
