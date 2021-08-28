#include "mainwindow.h"
#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

/*int main()
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    try
    {
        Tenzor *T1 = new Tenzor;
        Tenzor* T2 = new Tenzor;
        T1->createTenzor("1ii +2jj +3kk");
        T2->createTenzor("1ii +2ji +3ik");
       equation e("(TenA xx TenB + TenA) ** TenA");
        e.createTenzorMap("TenA", T1);
        e.createTenzorMap("TenB", T2);
        e.solveEquation();
    }
    catch (const char* msg)
    {
        qDebug() << msg;
        return -1;
    }
    return a.exec();
}*/
