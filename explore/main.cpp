#include "mainactivity.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainActivity demo;
    demo.show();
    return a.exec();
}
