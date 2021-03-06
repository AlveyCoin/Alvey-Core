#ifndef RECEIVETOKENPAGE_H
#define RECEIVETOKENPAGE_H

#include <QDialog>

namespace Ui {
class ReceiveTokenPage;
}
class PlatformStyle;

class ReceiveTokenPage : public QDialog
{
    Q_OBJECT

public:
    explicit ReceiveTokenPage(const PlatformStyle *platformStyle, QWidget *parent = 0);
    ~ReceiveTokenPage();

    void setAddress(QString address);
    void setSymbol(QString symbol);

private Q_SLOTS:
    void on_copyAddressClicked();

private:
    Ui::ReceiveTokenPage *ui;
    QString m_address;

    void createLRCode();

    const PlatformStyle *platformStyle;
};

#endif // RECEIVETOKENPAGE_H
