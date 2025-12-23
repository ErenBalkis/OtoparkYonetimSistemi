#include "ParkKaydi.h"
#include <cmath>

ParkKaydi::ParkKaydi(std::string plaka, int parkYeriId)
    : plaka(plaka),
      parkYeriId(parkYeriId),
      ucret(0.0)
{
    girisZamani = time(nullptr);
    cikisZamani = 0;
}

void ParkKaydi::cikisYap() {
    cikisZamani = time(nullptr);
}

void ParkKaydi::ucretHesapla(double saatlikUcret) {
    if (cikisZamani == 0) return;

    double farkSaniye = difftime(cikisZamani, girisZamani);
    double saat = ceil(farkSaniye / 3600.0);

    ucret = saat * saatlikUcret;
}

std::string ParkKaydi::getPlaka() const {
    return plaka;
}

int ParkKaydi::getParkYeriId() const {
    return parkYeriId;
}

time_t ParkKaydi::getGirisZamani() const {
    return girisZamani;
}

time_t ParkKaydi::getCikisZamani() const {
    return cikisZamani;
}

double ParkKaydi::getUcret() const {
    return ucret;
}
