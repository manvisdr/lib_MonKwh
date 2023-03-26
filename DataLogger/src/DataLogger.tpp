#include "DataLogger.h"

template <typename T, size_t S>
DataLogger<T, S>::DataLogger(const char *fileName, void (*saveFunc)(void *, File &), bool clearFile)
{
    XFS.begin();
    setFileName(fileName);
    if (clearFile)
        this->clearFile();
    if (saveFunc != NULL)
        this->saveFunc = saveFunc;
}

template <typename T, size_t S>
void DataLogger<T, S>::forEach(void (*f)(void *))
{
    for (int i = 0; i < size(); i++)
    {
        T obj = buf[i];
        f(&obj);
    }
}

template <typename T, size_t S>
void DataLogger<T, S>::saveToFile(bool clearBuffer)
{
    File fp = XFS.open(fileName, "a");
    for (int i = 0; i < size(); i++)
    {
        T obj = buf[i];
        saveFunc(&obj, fp);
    }
    if (clearBuffer)
        buf.clear();
    fp.close();
}

template <typename T, size_t S>
void DataLogger<T, S>::addSave(T el, bool clearBuffer)
{
    add(el);
    saveToFile(saveFunc, clearBuffer);
}

template <typename T, size_t S>
void DataLogger<T, S>::addSaveDelayed(T el, int ms)
{
    add(el);
    msSave = millis() + ms;
}

template <typename T, size_t S>
void DataLogger<T, S>::refresh(ulong ms)
{
    if (ms > msSave)
    {
        saveToFile(true);
        msSave = UINT32_MAX;
    }
}

template <typename T, size_t S>
void DataLogger<T, S>::clearFile()
{
    File fp = XFS.open(fileName, "w");
    if (fp)
        fp.close();
}

template <typename T, size_t S>
String DataLogger<T, S>::readFromFile()
{
    String s;
    File f = XFS.open(getFileName(), "r");
    if (f)
    {
        s = f.readString();
        f.close();
    }
    return s;
}
