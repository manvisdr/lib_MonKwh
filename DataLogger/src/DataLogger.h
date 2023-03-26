#pragma once

#include "CircularBuffer.h"

#if FS_LITTLEFS
#include <LittleFS.h>
#define XFS LittleFS
#endif
#if FS_SPIFFS
#include <SPIFFS.h>
#define XFS SPIFFS
#endif

template <typename T, size_t S>
class DataLogger
{
private:
    CircularBuffer<T, S> buf;
    const char *fileName;
    void (*saveFunc)(void *, File &);
    ulong msSave = UINT32_MAX;

    void setFileName(const char *fileName) { this->fileName = fileName; }

public:
    DataLogger(const char *, void (*saveFunc)(void *, File &) = NULL, bool clearFile = false);

    // Broj stavki u baferu.
    int size() { return buf.size(); }
    // Dohvatanje stavke iz bafera.
    T get(int idx) { return buf[idx]; }
    // Dohvatanje stavke iz bafera.
    const T &operator[](int i)
    {
        const T &obj = buf[i];
        return obj;
    }
    // Dodavanje stavke u bafer (kruznu listu).
    void add(T el) { buf.push(el); }
    // Prosledjena funkcija se izvrsava za sve stavke u baferu.
    void forEach(void (*f)(void *));
    // Vraca ime fajla koje je prosledjeno konstruktoru.
    const char *getFileName() { return fileName; }
    // Pisanje podataka iz bafera u fajl.
    void saveToFile(bool clearBuffer = true);
    // Dodavanje stavke u bafer (kruznu listu) uz upisivanje svih stavki u fajl.
    void addSave(T el, bool clearBuffer = true);
    // Dodavanje stavke u bafer (kruznu listu) uz odlozeno upisivanje svih stavki u fajl.
    void addSaveDelayed(T el, int ms = 1000);
    //
    void refresh(ulong ms);
    // Brisanje podataka u fajlu.
    void clearFile();
    //
    String readFromFile();
};

#include "DataLogger.tpp"