#include "mybutton.h"


MyButton::MyButton(const QString& text, QWidget *parent) :
    QToolButton(parent)
{
    setText(text);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

QSize MyButton::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 30;
    size.rwidth() = qMax(size.width(), size.height());
    return size;
}
