#ifndef NOTEHEADER_H
#define NOTEHEADER_H

#include <QWidget>
#include <QPoint>

class QLabel;
class QLineEdit;
class QPushButton;
class QMouseEvent;

class NoteHeader : public QWidget
{
    Q_OBJECT

public:
    explicit NoteHeader(const QString &title, QWidget *parent = nullptr);

    QString getTitle() const;
    void setTitle(const QString &title);

signals:
    void titleChanged(const QString &title);
    void newNoteRequested();
    // Ubuntu window manager ruining my dreams :(
    void alwaysOnTopRequested();

protected:
    // void mousePressEvent(QMouseEvent *event) override;
    // void mouseMoveEvent(QMouseEvent *event) override;
    // void mouseReleaseEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QLabel *titleLabel;
    QLineEdit *titleEdit;

    QPushButton *newNoteButton;


    // Some leftovers from trying to do a fully custom header.

    // QPushButton *minimizeButton;
    // QPushButton *closeButton;

    // QPoint dragOffset;
    // bool dragging = false;

    void beginTitleEdit();
    void finishTitleEdit();
};

#endif // NOTEHEADER_H