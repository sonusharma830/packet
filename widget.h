#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "QUdpSocket"
#include "packet.h"

#define HOST "127.0.0.1"
#define PORT 1000

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    QUdpSocket *socket;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    int constructPakcet(UINT8* sendBuffer, UINT16 cmdID, UINT8* dataBuffer, UINT32 sizeOfData);

private slots:
    void sendConnectCmd();
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
