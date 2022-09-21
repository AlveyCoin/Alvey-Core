#ifndef ALVPUSHBUTTON_H
#define ALVPUSHBUTTON_H
#include <QPushButton>
#include <QStyleOptionButton>
#include <QIcon>

class AlveyPushButton : public QPushButton
{
public:
    explicit AlveyPushButton(QWidget * parent = Q_NULLPTR);
    explicit AlveyPushButton(const QString &text, QWidget *parent = Q_NULLPTR);

protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

private:
    void updateIcon(QStyleOptionButton &pushbutton);

private:
    bool m_iconCached;
    QIcon m_downIcon;
};

#endif // ALVPUSHBUTTON_H
