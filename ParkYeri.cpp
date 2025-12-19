#include "ParkYeri.h"

//Yapıcı metot (nesne ilk oluştuğunda çalışır)
ParkYeri::ParkYeri(int id, int kat) : id(id), kat(kat), doluMu(false){}

//Park yeri dolu mu boş mu kontrolü
bool ParkYeri::isDolu() const {
    return doluMu;
}
//Park yernin durumunu günceller (araç girdiğinde true çıktığında false)
void ParkYeri::setDurum(bool durum) {
    doluMu = durum;
}

int ParkYeri::getId() const {
    return id;
}
int ParkYeri::getKat() const {
    return kat;
}
