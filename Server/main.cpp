#include <utility>
#include <iostream>

#include <QCoreApplication>

#include "Server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Vivoka::Server server(1234, std::make_pair<unsigned int, unsigned int>(1, 100), 10, true);
    return a.exec();
}
