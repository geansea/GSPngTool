#include "PngCmdArgs.h"

PngCmdArgs::PngCmdArgs(int argc, char *argv[])
    : m_args(argc, QString())
{
    for (int i = 0; i < argc; ++i)
    {
        m_args[i] = QString::fromLocal8Bit(argv[i]);
    }
}

PngCmdArgs::~PngCmdArgs()
{
}

QString PngCmdArgs::GetCommand() const
{
    return (m_args.size() > 1) ? m_args[1] : QString();
}

QString PngCmdArgs::GetInputPath() const
{
    return (m_args.size() > 2) ? m_args[2] : QString();
}

QString PngCmdArgs::GetOutputPath() const
{
    return (m_args.size() > 3) ? m_args[3] : QString();
}
