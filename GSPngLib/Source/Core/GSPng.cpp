#include "GSPng.h"

IGSPng::Chunk::Chunk()
    : length(0)
    , type(0)
    , data()
    , crc(0)
{
}

bool IGSPng::Chunk::Read(QDataStream &src)
{
    src >> length;
    src >> type;
    data.resize(length);
    src.readRawData(data.data(), data.size());
    src >> crc;
    return QDataStream::Status::Ok == src.status();
}

bool IGSPng::Chunk::Write(QDataStream &dst)
{
    dst << length;
    dst << type;
    dst.writeRawData(data.data(), data.size());
    dst << crc;
    return QDataStream::Status::Ok == dst.status();
}

GSPng::GSPng()
{
}

GSPng::~GSPng()
{
}
