#ifndef PNGCMDUTILS_H
#define PNGCMDUTILS_H

#include <QtCore>

class PngCmdUtils
{
public:
    static bool ShowInfo(QString filePath);
    static bool OpiFile(QString inFilePath, QString outFilePath);

private:
    PngCmdUtils() {}
};

#endif // PNGCMDUTILS_H
