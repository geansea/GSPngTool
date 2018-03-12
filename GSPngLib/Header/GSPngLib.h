#ifndef GSPNGLIB_H
#define GSPNGLIB_H

#include "GSPngDef.h"
#include "IGSPng.h"

class GSPngLib
{
public:
    IGSPng * LoadPngFromFile(const QString &path);

private:
    GSPngLib();
};

#endif // GSPNGLIB_H
