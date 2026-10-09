#include "noteheader.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QWidget>
#include <QEvent>
#include<QDebug>

NoteHeader::NoteHeader(const QString &title, QWidget *parent)
    : QWidget(parent)
{
    // Create title widgets
    titleLabel = new QLabel(title, this);
    titleEdit = new QLineEdit(title, this);

    titleEdit->hide();

    // Create window control buttons
    minimizeButton = new QPushButton("-", this);
    closeButton = new QPushButton("x", this);

    minimizeButton->setFixedSize(25, 22);
    closeButton->setFixedSize(25, 22);

    // Create layout
    QHBoxLayout *layout = new QHBoxLayout(this);

    layout->setContentsMargins(5, 2, 5, 2);
    layout->setSpacing(5);

    // Add widgets, stretch to layout
    layout->addWidget(titleLabel);
    layout->addWidget(titleEdit);
    layout->addStretch();
    layout->addWidget(minimizeButton);
    layout->addWidget(closeButton);

    // Style the header
    // This is a placeholder; in theory, this should be done
    // later in QML.
    setStyleSheet(
        "NoteHeader {"
        "    background-color: #E6DFA5;"
        "}"
        "QPushButton {"
        "    border: none;"
        "    background-color: transparent;"
        "}"
        "QPushButton:hover {"
        "    background-color: #D5CD91;"
        "}"
        "QPushButton:hover {"
        "    border: none;"
        "}"
        );

    // Connect window controls
    connect(minimizeButton, &QPushButton::clicked,
            this, &NoteHeader::minimizeRequested);

    connect(closeButton, &QPushButton::clicked,
            this, &NoteHeader::closeRequested);

    // Begin editing when the title is double-clicked
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
        title = "Untitled Note";

    titleLabel->setText(title);
    titleEdit->setText(title);

    titleEdit->hide();
    titleLabel->show();

    emit titleChanged(title);
}

bool NoteHeader::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == titleLabel &&
        event->type() == QEvent::MouseButtonDblClick)
    {
        beginTitleEdit();
        return true;
    }

    return QWidget::eventFilter(watched, event);
}

void NoteHeader::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragging = true;

        // Note: dragOffset is to store the location of the mouse
        // Cursor within the window, not the change in position
        // of the mouse on the screen.
        dragOffset =
            event->globalPosition().toPoint()
            - window()->frameGeometry().topLeft();
        qDebug() << "MousePress";
        event->accept();
        return;
    }

    QWidget::mousePressEvent(event);
}

void NoteHeader::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging && (event->buttons() & Qt::LeftButton)) {
        // Move the top-level window to follow the cursor.
        qDebug() << "Offset Prev: " << dragOffset;
        window()->move(
            event->globalPosition().toPoint() - dragOffset
            );

        event->accept();
    }
}

void NoteHeader::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        qDebug() << "MouseRelease";
        dragging = false;
        event->accept();
    }
}