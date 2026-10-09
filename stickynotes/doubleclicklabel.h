#ifndef DOUBLECLICKLABEL_H
#define DOUBLECLICKLABEL_H

#include <QLabel>
#include <QMouseEvent>

class DoubleClickLabel : public QLabel
{
    Q_OBJECT

public:
    explicit DoubleClickLabel(const QString &text, QWidget *parent = nullptr)
        : QLabel(text, parent)
    {
    }

signals:
    void doubleClicked();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override
    {
        emit doubleClicked();
        QLabel::mouseDoubleClickEvent(event);
    }
};

#endif // DOUBLECLICKLABEL_H
