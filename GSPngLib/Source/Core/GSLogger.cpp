#include "GSLogger.h"

void GSLog(QString msg)
{
    GSLogger::GetInstance()->LogInfo(msg);
}

void GSWarning(QString msg)
{
    GSLogger::GetInstance()->LogWarning(msg);
}

void GSError(QString msg)
{
    GSLogger::GetInstance()->LogError(msg);
}

QString GSGetLog()
{
    return GSLogger::GetInstance()->GetLog();
}

GSLogger * GSLogger::GetInstance()
{
    static GSLogger *pLogger = NULL;
    if (pLogger == NULL)
    {
        pLogger = new GSLogger();
    }
    return pLogger;
}

void GSLogger::LogInfo(QString msg)
{
    if (!msg.isEmpty())
    {
        m_log += "Info: " + msg + "\n";
    }
}

void GSLogger::LogWarning(QString msg)
{
    if (!msg.isEmpty())
    {
        m_log += "Warning: " + msg + "\n";
    }
}

void GSLogger::LogError(QString msg)
{
    if (!msg.isEmpty())
    {
        m_log += "Error: " + msg + "\n";
    }
}

QString GSLogger::GetLog() const
{
    return m_log;
}

GSLogger::GSLogger()
{
}
