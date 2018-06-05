#ifndef GSLOGGER_H
#define GSLOGGER_H

#include "GSDef.h"

class GSLogger
{
public:
    static GSLogger * GetInstance();

public:
    void LogInfo(QString msg);
    void LogWarning(QString msg);
    void LogError(QString msg);
    QString GetLog() const;

private:
    GSLogger();

private:
    QString m_log;
};

#endif // GSLOGGER_H
