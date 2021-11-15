#include "Windows.h"
#include <QtWidgets/QApplication>
#include  "HWCPipe.hpp"
#include  "HWCPipeParser.hpp"
#include  "HWCPipeNodeRegister.hpp"
#include  "Log.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Windows w;
    w.show();
    return a.exec();
}
