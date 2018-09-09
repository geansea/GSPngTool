#ifndef PNGCMDARGS_H
#define PNGCMDARGS_H

#include <QtCore>

class PngCmdArgs
{
public:
    PngCmdArgs(int argc, char *argv[]);
    ~PngCmdArgs();

    QString GetCommand() const;
    QString GetInputPath() const;
    QString GetOutputPath() const;

private:
    QVector<QString> m_args;
};

#endif // PNGCMDARGS_H
