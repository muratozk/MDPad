#include "mdpad.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
   // a.setWindowIcon(QIcon(":/res/icon.png"));
    MDPad w;
    w.show();

    return a.exec();
}
