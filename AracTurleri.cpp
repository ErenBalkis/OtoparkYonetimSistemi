#include "AracTurleri.h"

/**
 * ARAÇ TÜRLERİ IMPLEMENTASYONU
 * --------------------------------
 * - Her araç türü zaman bazlı ücret hesaplar
 * - İlk saat baz ücrete dahildir
 * - Sonraki her saat için saatlik ücret eklenir
 */

// ==================== OTOMOBİL ====================

Otomobil::Otomobil(const std::string &p)
    : Arac(p, "Otomobil", BAZ_UCRET, SAATLIK_UCRET) {}

double Otomobil::hesaplaUcret() const {
  double saat = hesaplaSure();

  // İlk saat baz ücrete dahil, sonraki saatler ek ücret
  if (saat <= 1.0) {
    return BAZ_UCRET;
  }
  return BAZ_UCRET + (saat - 1.0) * SAATLIK_UCRET;
}

// ==================== KAMYONET ====================

Kamyonet::Kamyonet(const std::string &p)
    : Arac(p, "Kamyonet", BAZ_UCRET, SAATLIK_UCRET) {}

double Kamyonet::hesaplaUcret() const {
  double saat = hesaplaSure();

  if (saat <= 1.0) {
    return BAZ_UCRET;
  }
  return BAZ_UCRET + (saat - 1.0) * SAATLIK_UCRET;
}

// ==================== MOTOSİKLET ====================

Motosiklet::Motosiklet(const std::string &p)
    : Arac(p, "Motosiklet", BAZ_UCRET, SAATLIK_UCRET) {}

double Motosiklet::hesaplaUcret() const {
  double saat = hesaplaSure();

  if (saat <= 1.0) {
    return BAZ_UCRET;
  }
  return BAZ_UCRET + (saat - 1.0) * SAATLIK_UCRET;
}
