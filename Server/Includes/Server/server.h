#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QDebug>
#include <QString>
#include <QByteArray>
#include <QFile>
#include <QList>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Server;
}
QT_END_NAMESPACE

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

private:
    Ui::Server *ui;
    QTcpServer *TcpServer;
    QList<QTcpSocket *> clients;

    void setupStyles();
    void initializeSocket();
    void add_client(QTcpSocket *client);
    void read_data_from_socket();
    void send_message_to_client(QTcpSocket *client, const QString &message);
    void client_disconnected();

private slots:
    void on_btnSend_clicked();
    void new_connection();
};

#endif /* SERVER_H */
