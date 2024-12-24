#include "chatbox.h"
#include "./ui_chatbox.h"

const QString CHATBOX_STYLE_PATH = ":/Styles/Chatbox.qss";

Chatbox::Chatbox(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Chatbox)
{
    ui->setupUi(this);
    setupStyles();
    initializeSocket();
    setupConnections();
}

Chatbox::~Chatbox()
{
    delete ui;
}

/**
 * @brief Initializes the TCP socket connection.
 *
 * Sets up a TCP socket, connects it to the host, and opens the socket
 * for reading and writing. It also checks if the connection was successful.
 */
void Chatbox::initializeSocket()
{
    TcpClient = new QTcpSocket(this);
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

/**
 * @brief Loads the QSS file and applies it to the UI.
 *
 * This function loads a QSS (Qt Style Sheet) file to customize the
 * appearance of the UI. It also sets initial properties for various widgets.
 */
void Chatbox::setupStyles()
{
    QFile styleFile(CHATBOX_STYLE_PATH);
    if (styleFile.open(QFile::ReadOnly))
    {
        qDebug() << "Style file loaded successfully.";
        setStyleSheet(QString::fromUtf8(styleFile.readAll()));
    }
    else
    {
        qDebug() << "Failed to load style file.";
    }

    ui->lbName->setText("Name");
    ui->cbStatus->addItems({"Online", "Offline", "Away", "Busy"});
    ui->lnMessage->setPlaceholderText("Type your message here...");
    ui->btnSend->setText("Send");
}

/**
 * @brief Handles the send button click event.
 *
 * This function sends the user's input message via the TCP socket
 * and displays it in the chat list. The message is right-aligned to
 * indicate it was sent by the user.
 */
void Chatbox::on_btnSend_clicked()
{
    if (TcpClient)
    {
        // Send the message via TCP
        QByteArray messageToSend = ui->lnMessage->text().toUtf8();
        TcpClient->write(messageToSend);

        // Display the sent message in the chat list
        auto *sentItem = new QListWidgetItem(QString::fromUtf8(messageToSend));
        sentItem->setTextAlignment(Qt::AlignRight);
        ui->lstMessages->addItem(sentItem);

        // Scroll to the bottom and clear the input field
        ui->lstMessages->scrollToBottom();
        ui->lnMessage->clear();
    }
}

/**
 * @brief Reads data from the TCP socket and displays it.
 *
 * This function is triggered whenever the socket emits the `readyRead` signal.
 * It reads incoming messages from the server, converts them to a QString,
 * and displays them in the chat list. The messages are left-aligned to indicate
 * they were received from the server.
 */
void Chatbox::read_data_from_socket()
{
    QString messageReceived = QString(TcpClient->readAll());
    auto *receivedItem = new QListWidgetItem(messageReceived);
    receivedItem->setTextAlignment(Qt::AlignLeft);
    ui->lstMessages->addItem(receivedItem);

    // Scroll to the bottom
    ui->lstMessages->scrollToBottom();
}

/**
 * @brief Sets up connections between signals and slots.
 *
 * This function connects the TCP socket's `readyRead` signal to the
 * `readSocketData` slot, enabling the chatbox to handle incoming messages.
 */
void Chatbox::setupConnections()
{
    connect(TcpClient, &QTcpSocket::readyRead, this, &Chatbox::read_data_from_socket);
}
