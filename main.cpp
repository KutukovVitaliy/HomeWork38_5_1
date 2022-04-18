
#include "imagebutton.h"
#include <QVBoxLayout>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ImageButton redButton(nullptr);
    redButton.setFixedSize(320, 320);

    redButton.show();
    return a.exec();
}
