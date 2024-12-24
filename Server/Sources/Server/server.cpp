#include "server.h"
#include "./ui_server.h"

const QString SERVER_STYLE_PATH = ":/Styles/Server.qss";

Server::Server(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Server)
{
    ui->setupUi(this);
    setupStyles();
    initializeSocket();
}

Server::~Server()
{
    delete ui;
}

/**
 * @brief Loads and applies the stylesheet for the server UI.
 */
void Server::setupStyles()
{
    QFile styleFile(SERVER_STYLE_PATH);
    if (styleFile.open(QFile::ReadOnly))
    {
        qDebug() << "Open style file successful!";
        setStyleSheet(QString::fromUtf8(styleFile.readAll()));
    }
    else
    {
        qDebug() << "Fail to open style file!";
    }

    ui->cbClients->addItem("All");
    ui->lnMessage->setPlaceholderText("Type your message here...");
    ui->btnSend->setText("Send");
}

/**
 * @brief Initializes the TCP server and starts listening for connections.
 */
void Server::initializeSocket()
{
    TcpServer = new QTcpServer(this);
    if (TcpServer->listen(QHostAddress::Any, 8080))
    {
        connect(TcpServer, &QTcpServer::newConnection, this, &Server::new_connection);
        qDebug() << "Server initialized successfully!";
    }
    else
    {
        qDebug() << "Failed to initialize server!";
    }
}

/**
 * @brief Adds a new client to the server.
 * @param client The QTcpSocket object representing the connected client.
 */
void Server::add_client(QTcpSocket *client)
{
    clients.append(client);

    connect(client, &QTcpSocket::readyRead, this, &Server::read_data_from_socket);
    connect(client, &QTcpSocket::disconnected, this, &Server::client_disconnected);

    QString clientName = QString::number(client->socketDescriptor());
    ui->cbClients->addItem(clientName);

    QString message = "Client " + clientName + " connected to the server.";
    qDebug() << message;
}

/**
 * @brief Reads data from the socket of a connected client.
 */
void Server::read_data_from_socket()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    if (!client)
        return;

    QByteArray data = client->readAll();
    QString message = QString("Client %1: %2")
                          .arg(client->socketDescriptor())
                          .arg(QString::fromUtf8(data));

    qDebug() << "Received:" << message;

    auto receivedMessage = new QListWidgetItem(message);
    receivedMessage->setTextAlignment(Qt::AlignLeft);
    ui->lstMessages->addItem(receivedMessage);
    ui->lstMessages->scrollToBottom();
}

/**
 * @brief Sends a message to a specific client.
 * @param client The QTcpSocket object of the client.
 * @param message The message to be sent.
 */
void Server::send_message_to_client(QTcpSocket *client, const QString &message)
{
    if (client)
    {
        client->write(message.toUtf8());
        qDebug() << "Message sent to Client" << client->socketDescriptor() << ":" << message;

        auto sentMessage = new QListWidgetItem(message);
        sentMessage->setTextAlignment(Qt::AlignRight);
        ui->lstMessages->addItem(sentMessage);
        ui->lstMessages->scrollToBottom();
    }
    else
    {
        qDebug() << "Invalid client socket!";
    }
}

/**
 * @brief Handles the disconnection of a client.
 */
void Server::client_disconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    if (!client)
        return;

    QString clientName = QString::number(client->socketDescriptor());
    qDebug() << "Client" << clientName << "disconnected";

    clients.removeAll(client);
    delete client;

    for (int i = 0; i < ui->cbClients->count(); ++i)
    {
        if (ui->cbClients->itemText(i) == clientName)
        {
            ui->cbClients->removeItem(i);
            break;
        }
    }

    QString message = "Client " + clientName + " disconnected.";
    ui->lstMessages->addItem(new QListWidgetItem(message));
}

/**
 * @brief Handles new client connections.
 */
void Server::new_connection()
{
    while (TcpServer->hasPendingConnections())
    {
        QTcpSocket *client = TcpServer->nextPendingConnection();
        add_client(client);
    }
}

/**
 * @brief Handles the "Send" button click to send a message to a client or all clients.
 */
void Server::on_btnSend_clicked()
{
    QString messageToSend = ui->lnMessage->text().trimmed();

    if (messageToSend.isEmpty())
    {
        qDebug() << "Cannot send an empty message!";
        return;
    }

    QString clientName = ui->cbClients->currentText();

    if (clientName == "All")
    {
        for (QTcpSocket *client : clients)
        {
            send_message_to_client(client, messageToSend);
        }
    }
    else
    {
        for (QTcpSocket *client : clients)
        {
            if (QString::number(client->socketDescriptor()) == clientName)
            {
                send_message_to_client(client, messageToSend);
                break;
            }
        }
    }
}
