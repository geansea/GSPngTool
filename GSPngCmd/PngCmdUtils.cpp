#include "PngCmdUtils.h"
#include "IGSPng.h"
#include "GSDef.h"

bool PngCmdUtils::ShowInfo(QString filePath)
{
    IGSPng *png = IGSPng::CreateFromFile(filePath);
    GSRFF(png != NULL);

    printf("path:   %s\n", filePath.toLocal8Bit().constData());
    printf("size:   %d\n", png->GetSize());
    printf("width:  %d\n", png->GetWidth());
    printf("height: %d\n", png->GetHeight());
    printf("%s", png->GetMetadata().toLocal8Bit().constData());

    SafeDelete(png);
    return true;
}
