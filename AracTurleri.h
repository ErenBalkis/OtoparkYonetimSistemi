#ifndef ARACTURLERI_H
#define ARACTURLERI_H

#include "Arac.h"
#include <string>

/**
 * ARAÇ TÜRLERİ SINIFLARI
 * --------------------------------
 * - Arac soyut sınıfından türeyen somut (concrete) sınıfları içerir
 * - Her araç türü kendi ücret tarifesini tanımlar
 * - Zaman bazlı dinamik ücretlendirme kullanır
 *
 * ÜCRET FORMÜLÜ:
 * Toplam = Baz Ücret + (Saat - 1) * Saatlik Ücret
 * (İlk saat baz ücrete dahildir)
 */

// ==================== OTOMOBİL ====================
class Otomobil : public Arac {
public:
  // Ücretlendirme Sabitleri
  static constexpr double BAZ_UCRET = 50.0;     // TL - İlk saat
  static constexpr double SAATLIK_UCRET = 10.0; // TL - Her ek saat

  explicit Otomobil(const std::string &p);
  double hesaplaUcret() const override;
};

// ==================== KAMYONET ====================
class Kamyonet : public Arac {
public:
  // Ücretlendirme Sabitleri (Daha büyük araç = Daha yüksek ücret)
  static constexpr double BAZ_UCRET = 80.0;     // TL - İlk saat
  static constexpr double SAATLIK_UCRET = 15.0; // TL - Her ek saat

  explicit Kamyonet(const std::string &p);
  double hesaplaUcret() const override;
};

// ==================== MOTOSİKLET ====================
class Motosiklet : public Arac {
public:
  // Ücretlendirme Sabitleri (Küçük araç = Düşük ücret)
  static constexpr double BAZ_UCRET = 30.0;    // TL - İlk saat
  static constexpr double SAATLIK_UCRET = 5.0; // TL - Her ek saat

  explicit Motosiklet(const std::string &p);
  double hesaplaUcret() const override;
};

#endif // ARACTURLERI_H
