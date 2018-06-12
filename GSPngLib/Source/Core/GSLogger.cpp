#include "GSLogger.h"

void GSLog(GSLogType type, QString msg)
{
    GSLogger::GetInstance()->Log(type, msg);
}

QString GSGetLog(int logType)
{
    return GSLogger::GetInstance()->GetLog(logType);
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

void GSLogger::Log(GSLogType type, QString msg)
{
    if (msg.isEmpty())
    {
        return;
    }
    LogLine line;
    line.type = type;
    line.content = msg;
    m_lines.push_back(line);
}

QString GSLogger::GetLog(int logType) const
{
    QString log;
    foreach (LogLine line, m_lines)
    {
        if (line.type & logType)
        {
            switch (line.type)
            {
            case GSLogInfo:
                log += "INFO: ";
                break;
            case GSLogWarning:
                log += "WARN: ";
                break;
            case GSLogError:
                log += "ERRO: ";
                break;
            default:
                log += "XXXX: ";
                break;
            }
            log += line.content;
            log += "\n";
        }
    }
    return log;
}

GSLogger::LogLine::LogLine()
    : type(GSLogInfo)
    , content()
{
}

GSLogger::GSLogger()
{
}
