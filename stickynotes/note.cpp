#include "note.h"
#include "doubleclicklabel.h"

#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>

Note::Note(QWidget *parent)
    : QMainWindow{parent}
{
    setWindowTitle(baseTitle);
    resize(400, 200);

    // Create layouts & Central Widget to contain it
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *toolbarLayout = new QHBoxLayout;
    QWidget *centralWidget = new QWidget;

    // Create title label + label editor
    titleLabel = new DoubleClickLabel("poopcock");
    titleEdit = new QLineEdit(baseTitle);

    // Hide titleEdit; only want label until editing
    titleEdit->hide();

    // Create the primary textedit portion of the note
    QTextEdit *textEdit = new QTextEdit;

    // Add textEdit and toolbar to mainLayout
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(titleEdit);
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

    // Double-clicking the title label will start editing title
    QObject::connect(
        titleLabel,
        &DoubleClickLabel::doubleClicked,
        this,
        &Note::beginTitleEdit);

    // Pressing enter finishes title edit
    QObject::connect(
        titleEdit,
        &QLineEdit::returnPressed,
        this,
        &Note::finishTitleEdit);

    // Finish edit when title edit loses focus
    QObject::connect(
        titleEdit,
        &QLineEdit::editingFinished,
        this,
        &Note::finishTitleEdit);

    // Set mainLayout for centralwidget, then put centralWidget in place
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

// Sets the window title to the given string.
void Note::setTitle(QString s){
    setWindowTitle(s);
    titleLabel->setText(s);
}

QString Note::getTitle(){
    return titleLabel->text();
}

void Note::beginTitleEdit(){
    // Make sure the existing title is populated into the edit
    titleEdit->setText(titleLabel->text());

    // Hide the actual label, show the edit section
    titleLabel->hide();
    titleEdit->show();

    // Not immediately sure what these do
    titleEdit->setFocus();
    titleEdit->selectAll();
}

void Note::finishTitleEdit(){
    // Grab the new text
    QString title = titleEdit->text().trimmed();

    // If title is empty, populate with base title
    if (title.isEmpty())
    {
        title = baseTitle;
    }

    // Update fields that should have title text
    titleLabel->setText(title);
    setWindowTitle(title);

    // Hide textedit, show the title label
    titleEdit->hide();
    titleLabel->show();
}
