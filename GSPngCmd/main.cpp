#include <QCoreApplication>
#include "IGSPng.h"
#include "GSDef.h"

int showInfo(QString filePath)
{
    IGSPng *png = IGSPng::CreateFromFile(filePath);
    if (png == NULL)
    {
        return 1;
    }
    printf("size: %d\n", png->GetSize());
    printf("width: %d\n", png->GetWidth());
    printf("height: %d\n", png->GetHeight());
    SafeDelete(png);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 3 && strncmp(argv[1], "-i", 2) == 0)
    {
        int ret = showInfo(argv[2]);
        if (ret != 0)
        {
            return ret;
        }
    }
    return 0;
}
