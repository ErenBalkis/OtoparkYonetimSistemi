#include "ParkYeri.h"

ParkYeri::ParkYeri(int id, int kat) 
    : id(id), kat(kat), doluMu(false), parkEdenPlaka("") {}

bool ParkYeri::isDolu() const {
    return doluMu;
}

// Araç girdiğinde plaka atanır, çıktığında boşaltılır
void ParkYeri::setDurum(bool durum, std::string plaka) {
    doluMu = durum;
    parkEdenPlaka = durum ? plaka : "";
}

int ParkYeri::getId() const {
    return id;
}

int ParkYeri::getKat() const {
    return kat;
}

std::string ParkYeri::getPlaka() const {
    return parkEdenPlaka;
}