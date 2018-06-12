#ifndef PNGCHUNK_H
#define PNGCHUNK_H

#include "Core/PngDef.h"

class PngChunk
{
public:
    enum Type
    {
        IHDR = 'IHDR', // Shall be first
        PLTE = 'PLTE', // Before first IDAT
        IDAT = 'IDAT', // Multiple IDAT chunks shall be consecutive
        IEND = 'IEND', // Shall be last
        cHRM = 'cHRM', // Before PLTE and IDAT
        gAMA = 'gAMA', // Before PLTE and IDAT
        iCCP = 'iCCP', // Before PLTE and IDAT, If the iCCP chunk is present, the sRGB chunk should not be present
        sBIT = 'sBIT', // Before PLTE and IDAT
        sRGB = 'sRGB', // Before PLTE and IDAT, If the sRGB chunk is present, the iCCP chunk should not be present
        bKGD = 'bKGD', // After PLTE; before IDAT
        hIST = 'hIST', // After PLTE; before IDAT
        tRNS = 'tRNS', // After PLTE; before IDAT
        pHYs = 'pHYs', // Before IDAT
        sPLT = 'sPLT', // Before IDAT
        tIME = 'tIME',
        iTXt = 'iTXt',
        tEXt = 'tEXt',
        zTXt = 'zTXt',
        UNSUPPORTED = 0
    };

    static PngChunk * Create(QDataStream &src);
    static bool AllowsMultiple(Type type);

public:
    PngChunk(Type type);
    virtual ~PngChunk();

    Type GetType() const;
    int GetSize() const;

    bool Read(QDataStream &src, quint32 length);
    bool Write(QDataStream &dst);

protected:
    virtual bool LoadData();
    virtual bool UpdateData();

private:
    quint32 GetCRC() const;

protected:
    Type       m_type;
    QByteArray m_data;
};

#endif // PNGCHUNK_H
