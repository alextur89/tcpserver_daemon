#include <QCoreApplication>
#include "server.h"
#if defined(WIN32) || defined(_WIN32)
    #include <windows.h>
#endif

int main(int argc, char *argv[])
{
#if defined(WIN32) || defined(_WIN32)
    ShowWindow(FindWindowA("ConsoleWindowClass", NULL), false);
#endif
    QCoreApplication a(argc, argv);
    Server server;
    server.start();
    return a.exec();
}
