#ifndef CHATBOX_H
#define CHATBOX_H

#include <QMainWindow>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QDebug>
#include <QString>
#include <QListWidgetItem>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Chatbox;
}
QT_END_NAMESPACE

class Chatbox : public QMainWindow
{
    Q_OBJECT

public:
    Chatbox(QWidget *parent = nullptr);
    ~Chatbox();
    void handle_connection();

private: 
    Ui::Chatbox *ui;
    QTcpSocket *TcpClient;

private slots:
    void on_btnSend_clicked();
    void read_data_from_socket();
};
#endif // CHATBOX_H
