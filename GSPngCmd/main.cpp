#include <QCoreApplication>
#include "IGSPng.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    IGSPng *png = IGSPng::CreateFromFile("");
    if (png)
    {
        delete png;
    }

    return app.exec();
}
