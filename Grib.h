#ifndef GRIB_H
#define GRIB_H

#include <iostream>
#include <fstream>

class Grib {
private:
    std::fstream gribFile;
    uint32_t startSection0;

public:
    Grib(const std::string& filename);
    ~Grib();

    void findGrib();
    void findEnd();
    void readSection1();
    void readDateFromSection1();
};

#endif // GRIB_H
