#include "Arac.h"

/**
 * Arac SINIFI IMPLEMENTASYONU
 * - Tüm araç türleri için temel (base) sınıftır
 * - Zaman bazlı ücretlendirme altyapısı sağlar
 * - std::unique_ptr ile uyumlu tasarlanmıştır
 */

// ---------------- CONSTRUCTOR ----------------
Arac::Arac(const std::string &p, const std::string &t, double baz,
           double saatlik)
    : plaka(p), tur(t), bazUcret(baz), saatlikUcret(saatlik) {

  girisSaati = std::time(nullptr); // Şu anki zaman
  cikisSaati = 0;                  // Henüz çıkış yapılmadı
}

// ---------------- SAAT HESAPLAMA ----------------
double Arac::hesaplaSure() const {
  std::time_t bitisSaati = (cikisSaati != 0) ? cikisSaati : std::time(nullptr);
  double farkSaniye = std::difftime(bitisSaati, girisSaati);

  // Saat cinsine çevir ve yukarı yuvarla (minimum 1 saat)
  double saat = std::ceil(farkSaniye / 3600.0);
  return (saat < 1.0) ? 1.0 : saat;
}

// ---------------- SETTER METOTLARI ----------------
void Arac::setGirisSaati(std::time_t saat) { girisSaati = saat; }

void Arac::setCikisSaati(std::time_t saat) { cikisSaati = saat; }

// ---------------- GETTER METOTLARI ----------------
std::string Arac::getPlaka() const { return plaka; }

std::string Arac::getTur() const { return tur; }

std::time_t Arac::getGirisSaati() const { return girisSaati; }

std::time_t Arac::getCikisSaati() const { return cikisSaati; }

// ---------------- BİLGİ YAZDIRMA ----------------
void Arac::bilgileriYazdir() const {
  std::cout << "Plaka: " << plaka << " | Tür: " << tur
            << " | Giriş Saati: " << std::ctime(&girisSaati);
}
