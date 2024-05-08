#include "Grib.h"

Grib::Grib(const std::string& filename) {
    gribFile.open(filename, std::ios::binary | std::ios::in);
    if (!gribFile.is_open()) {
        std::cout << "Nie udalo sie otworzyc pliku!\n";
    }
}

Grib::~Grib() {
    if (gribFile.is_open()) {
        gribFile.close();
    }
}

void Grib::findGrib() {
    char byte1, byte2, byte3, byte4;

    while (!gribFile.eof()) {
        gribFile.read(&byte1, 1);
        if (byte1 == 'G') {
            gribFile.read(&byte2, 1);
            gribFile.read(&byte3, 1);
            gribFile.read(&byte4, 1);
            if (byte2 == 'R' && byte3 == 'I' && byte4 == 'B') {
                std::cout << "Znalazlem Grib na pozycji: " << static_cast<uint32_t>(gribFile.tellg()) - 4 << "\n";
                startSection0 = static_cast<uint32_t>(gribFile.tellg()) - 4;
                break;
            }
        }
    }
}

void Grib::findEnd() {
    char byte1, byte2, byte3, byte4;

    while (!gribFile.eof()) {
        gribFile.read(&byte1, 1);
        if (byte1 == '7') {
            gribFile.read(&byte2, 1);
            gribFile.read(&byte3, 1);
            gribFile.read(&byte4, 1);
            if (byte2 == '7' && byte3 == '7' && byte4 == '7') {
                std::cout << "Znalazlem 7777 na pozycji: " << static_cast<uint32_t>(gribFile.tellg()) - 4 << "\n";
                break;
            }
        }
    }
}

void Grib::readSection1() {
    char byte1, byte2, byte3;
    int32_t section1Length;

    gribFile.seekg(startSection0 + 4);

    gribFile.read(&byte1, 1);
    gribFile.read(&byte2, 1);
    gribFile.read(&byte3, 1);
    section1Length = (int)byte1 << 16 | (int)byte2 << 8 | (int)byte3 & 0xff;

    std::cout << "Dlugosc sekcji 1: " << section1Length << "\n";
}

void Grib::readDateFromSection1() {
    char byte;
    int32_t year, month, day, hour, minute;

    gribFile.seekg(startSection0 + 12);
    gribFile.read(&byte, 1);
    year = (int)byte;

    gribFile.seekg(startSection0 + 13);
    gribFile.read(&byte, 1);
    month = (int)byte;

    gribFile.seekg(startSection0 + 14);
    gribFile.read(&byte, 1);
    day = (int)byte;

    gribFile.seekg(startSection0 + 15);
    gribFile.read(&byte, 1);
    hour = (int)byte;

    gribFile.seekg(startSection0 + 16);
    gribFile.read(&byte, 1);
    minute = (int)byte;

    std::cout << "Data z sekcji 1: " << year << "-" << month << "-" << day << " " << hour << ":" << minute << std::endl;
}
