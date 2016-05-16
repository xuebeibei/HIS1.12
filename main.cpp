#include "hismainwindow.h"
#include <QApplication>
#include "connectDB.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    myDB::connectDB();
    HISMainWindow w;
    w.show();
    return a.exec();
}
