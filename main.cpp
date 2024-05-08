#include <iostream>
#include "Grib.h"

int main() {
    Grib grib("all.grib");
    grib.findGrib();
    grib.findEnd();
    grib.readSection1();
    grib.readDateFromSection1();

    return 0;
}
