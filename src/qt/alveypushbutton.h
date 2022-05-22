#ifndef ALVPUSHBUTTON_H
#define ALVPUSHBUTTON_H
#include <QPushButton>
#include <QStyleOptionButton>
#include <QIcon>

class AlveyCoinPushButton : public QPushButton
{
public:
    explicit AlveyCoinPushButton(QWidget * parent = Q_NULLPTR);
    explicit AlveyCoinPushButton(const QString &text, QWidget *parent = Q_NULLPTR);

protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

private:
    void updateIcon(QStyleOptionButton &pushbutton);

private:
    bool m_iconCached;
    QIcon m_downIcon;
};

#endif // ALVPUSHBUTTON_H
