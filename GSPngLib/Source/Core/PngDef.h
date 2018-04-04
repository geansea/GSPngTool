#ifndef PNGDEF_H
#define PNGDEF_H

#include <QtCore>

#define CheckForReturnFail(x) do    \
{                                   \
    if (!(x))                       \
    {                               \
        return false;               \
    }                               \
} while (0)

#define CheckForReturnNull(x) do    \
{                                   \
    if (!(x))                       \
    {                               \
        return NULL;                \
    }                               \
} while (0)

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
            delete m_p;
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

#endif // PNGDEF_H
