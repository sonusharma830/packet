#include "widget.h"
#include "ui_widget.h"
#include "QByteArray"
#include "cstdlib"

#define MAX_SIZE 1024

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    socket=new QUdpSocket(this);
    connect(ui->connect,SIGNAL(clicked()),this,SLOT(sendConnectCmd()));
}

Widget::~Widget()
{
    delete ui;
}
void Widget::sendConnectCmd(){
    int offset=0;

    UINT8 sendBuffer[MAX_SIZE];
    UINT8 dataBuffer[MAX_SIZE];

    UINT16 cmdID= CONNECT_COMMAND;

    bool connect= 1;
    memcpy(&dataBuffer[offset], &connect, 1);
    offset+=1;

    int pktSize=constructPakcet(sendBuffer, cmdID, dataBuffer, offset);

    quint16 sendPort= CMD_PORT;
    int writtenBytes= socket->writeDatagram((char*)sendBuffer,
                                            pktSize,
                                            QHostAddress("127.0.0.1"),
                                            sendPort);

    if(writtenBytes == -1){
        qDebug()<<"Failed To Write";
    }else{
        qDebug()<<"Written Successfully";
    }
}

int  Widget::constructPakcet(UINT8 *sendBuffer, UINT16 cmdID, UINT8 *dataBuffer, UINT32 sizeOfData){
    int offset= 0;
    UINT16 header;
    UINT16 footer;
    UINT16 pktID;

    header= PACKET_HEADER;
    pktID= cmdID;
    footer= PACKET_FOOTER;

    memcpy(&sendBuffer[offset], &header, 2);
    offset+=2;

    memcpy(&sendBuffer[offset], &pktID, 2);
    offset+=2;

    memcpy(&sendBuffer[offset], dataBuffer, sizeOfData);
    offset+=sizeOfData;

    memcpy(&sendBuffer[offset], &footer, 2);
    offset+= 2;

    return offset;
}


