#include "chatbox.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Chatbox chatbox;
    chatbox.show();
    return a.exec();
}
