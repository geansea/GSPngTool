#ifndef GSDEF_H
#define GSDEF_H

#include <QtCore>

// Retuen Fail on Fail
#define GSRFF(x) do     \
{                       \
    if (!(x))           \
    {                   \
        return false;   \
    }                   \
} while (0)

// Retuen Null on Fail
#define GSRNF(x) do     \
{                       \
    if (!(x))           \
    {                   \
        return NULL;    \
    }                   \
} while (0)

// Retuen Fail on Fail with Log
#define GSRFFL(x, msg) do   \
{                           \
    if (!(x))               \
    {                       \
        GSError(msg);       \
        return false;       \
    }                       \
} while (0)

// Retuen Null on Fail with Log
#define GSRNFL(x, msg) do   \
{                           \
    if (!(x))               \
    {                       \
        GSError(msg);       \
        return NULL;        \
    }                       \
} while (0)

template<class T>
inline void SafeDelete(T *&p)
{
    if (p != NULL)
    {
        delete p;
        p = NULL;
    }
}

template<class T>
class GSPointerScope
{
public:
    GSPointerScope(T *p)
        : m_p(p)
        , m_cancelled(false)
    {
    }

    ~GSPointerScope()
    {
        if (m_p && !m_cancelled)
        {
            SafeDelete(m_p);
        }
    }

    void Cancel()
    {
        m_cancelled = true;
    }

private:
    T * m_p;
    bool m_cancelled;
};

void GSLog(QString msg);
void GSWarning(QString msg);
void GSError(QString msg);
QString GSGetLog();

#endif // GSDEF_H
