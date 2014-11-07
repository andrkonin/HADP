#include <QApplication>
#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setWindowFlags(Qt::Window);
w.setWindowTitle("Hyperion: Time-Of-Flight sensor family. Powerful sensors for industry, health, surveillance, image and object recognition, mobile platforms and robotics.");
    w.show();
    return a.exec();
}
