#include "Arac.h"

// Constructor
Arac::Arac(std::string p, std::string t)
    : plaka(p), tur(t) {
    girisSaati = std::time(nullptr); // program çalıştığı an
    cikisSaati = 0;
}

// Setter
void Arac::setCikisSaati(std::time_t saat) {
    cikisSaati = saat;
}

// Getter'lar
std::string Arac::getPlaka() const {
    return plaka;
}

std::string Arac::getTur() const {
    return tur;
}

std::time_t Arac::getGirisSaati() const {
    return girisSaati;
}

// Bilgi yazdırma (polimorfik)
void Arac::bilgileriYazdir() const {
    std::cout << "Plaka: " << plaka
              << " | Tür: " << tur
              << " | Giriş Saati: " << std::ctime(&girisSaati);
}
