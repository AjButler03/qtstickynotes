#include "noteheader.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QWidget>
#include <QEvent>
#include <QTimer>
#include <QDebug>

// This is a separate class to handle the header of a sticky note.
// I originally wanted to remove the existing OS header, making
// this fully custom. I Wasn't able to get the window dragging
// to work, so we're just goint to use the existing OS header
// and work around that.
NoteHeader::NoteHeader(const QString &title, QWidget *parent)
    : QWidget(parent)
{
    // Create title widgets
    titleLabel = new QLabel(title, this);
    titleEdit = new QLineEdit(title, this);

    titleEdit->hide();

    // Create window control buttons
    newNoteButton = new QPushButton("+", this);

    // Create layout
    QHBoxLayout *layout = new QHBoxLayout(this);

    layout->setContentsMargins(5, 2, 5, 2);
    layout->setSpacing(5);

    // Add widgets, stretch to layout
    layout->addWidget(titleLabel);
    layout->addWidget(titleEdit);
    layout->addStretch();
    layout->addWidget(newNoteButton);

    // Event filter for the title label
    titleLabel->installEventFilter(this);

    // Finish editing when Enter is pressed or editing ends
    connect(titleEdit, &QLineEdit::editingFinished,
            this, &NoteHeader::finishTitleEdit);
}

QString NoteHeader::getTitle() const
{
    return titleLabel->text();
}

void NoteHeader::setTitle(const QString &title)
{
    window()->setWindowTitle("Note: " + title);
    titleLabel->setText(title);
    titleEdit->setText(title);
}

void NoteHeader::beginTitleEdit()
{
    titleEdit->setText(titleLabel->text());

    titleLabel->hide();
    titleEdit->show();

    titleEdit->setFocus();
    titleEdit->selectAll();
}

void NoteHeader::finishTitleEdit()
{
    QString title = titleEdit->text().trimmed();

    if (title.isEmpty())
        title = "Untitled";

    window()->setWindowTitle("Note: " + title);
    titleLabel->setText(title);
    titleEdit->setText(title);

    titleEdit->hide();
    titleLabel->show();

    emit titleChanged(title);
}

// Event filter to detect double click on title
bool NoteHeader::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == titleLabel) {
        // Double click on title -> edit title
        if (event->type() == QEvent::MouseButtonDblClick) {
            beginTitleEdit();
            return true;
        }
    }

    return QWidget::eventFilter(watched, event);
}