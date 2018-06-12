#ifndef GSLOGGER_H
#define GSLOGGER_H

#include "GSDef.h"

class GSLogger
{
public:
    static GSLogger * GetInstance();

public:
    void Log(GSLogType type, QString msg);
    QString GetLog(int logType) const;

private:
    struct LogLine
    {
        GSLogType type;
        QString content;

        LogLine();
    };

    GSLogger();

private:
    QList<LogLine> m_lines;
};

#endif // GSLOGGER_H
