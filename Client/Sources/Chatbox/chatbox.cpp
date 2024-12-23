#include "chatbox.h"
#include "./ui_chatbox.h"

Chatbox::Chatbox(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Chatbox)
{
    ui->setupUi(this);

    TcpClient = new QTcpSocket(this);
    handle_connection();
    TcpClient->connectToHost(QHostAddress::LocalHost, 8080);
    TcpClient->open(QIODevice::ReadWrite);
    if (TcpClient->waitForConnected(5000))
    {
        qDebug() << "TCP Socket connected successfully!";
    }
    else
    {
        qDebug() << "Failed to connect to TCP Socket: " + TcpClient->errorString();
    }
}

Chatbox::~Chatbox()
{
    delete ui;
}

void Chatbox::on_btnSend_clicked()
{
    if (TcpClient)
    {
        QString messageSent = ui->lnMessage->text();
        QByteArray messageToSend = messageSent.toUtf8();
        TcpClient->write(messageToSend);

        QListWidgetItem *item = new QListWidgetItem(messageSent);
        item->setTextAlignment(Qt::AlignRight);
        ui->lstMessages->addItem(item);
        ui->lstMessages->scrollToBottom();
        ui->lnMessage->clear();
    }
}

void Chatbox::read_data_from_socket()
{
    QByteArray dataFromServer = TcpClient->readAll();
    QString messageReceived = QString(dataFromServer);

    QListWidgetItem *item = new QListWidgetItem(messageReceived);
    item->setTextAlignment(Qt::AlignLeft);
    ui->lstMessages->addItem(item);
    ui->lstMessages->scrollToBottom();
}

void Chatbox::handle_connection()
{
    connect(TcpClient, SIGNAL(readyRead()), this, SLOT(read_data_from_socket()));
}
