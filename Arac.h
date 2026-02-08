#ifndef ARAC_H
#define ARAC_H

#include <cmath>
#include <ctime>
#include <iostream>
#include <string>

/**
 * ARAC SINIFI (SOYUT SINIF)
 * --------------------------------
 * - Otopark sistemindeki tüm araç türleri için temel sınıftır
 * - Doğrudan nesnesi oluşturulamaz (abstract class)
 * - Polimorfizm ve std::unique_ptr ile uyumlu tasarlanmıştır
 * - Zaman bazlı ücretlendirme altyapısı içerir
 */

class Arac {
protected:
  std::string plaka;      // Araca ait plaka bilgisi
  std::string tur;        // Aracın türü (Otomobil, Kamyonet, Motosiklet)
  std::time_t girisSaati; // Aracın otoparka giriş zamanı
  std::time_t cikisSaati; // Aracın otoparktan çıkış zamanı

  // Ücretlendirme parametreleri (türetilmiş sınıflar tarafından ayarlanır)
  double bazUcret;     // İlk saat sabit ücret (TL)
  double saatlikUcret; // Her ek saat için ücret (TL)

  /**
   * Park süresini hesaplar (saat cinsinden, yukarı yuvarlanır)
   * @return Toplam park süresi (minimum 1 saat)
   */
  double hesaplaSure() const;

public:
  /**
   * CONSTRUCTOR
   * @param p Plaka bilgisi
   * @param t Araç türü
   * @param baz Baz ücret (TL)
   * @param saatlik Saatlik ek ücret (TL)
   */
  Arac(const std::string &p, const std::string &t, double baz = 0.0,
       double saatlik = 0.0);

  /**
   * VIRTUAL DESTRUCTOR
   * - Polimorfik kullanımda bellek sızıntısını önler
   * - unique_ptr ile uyumlu çalışır
   */
  virtual ~Arac() = default;

  /**
   * SAF SANAL FONKSİYON (PURE VIRTUAL)
   * - Her araç türü kendi ücret hesaplama mantığını yazmalıdır
   * - Formül: bazUcret + (saat - 1) * saatlikUcret
   */
  virtual double hesaplaUcret() const = 0;

  // ---------------- SETTER METOTLARI ----------------
  void setGirisSaati(std::time_t saat);
  void setCikisSaati(std::time_t saat);

  // ---------------- GETTER METOTLARI ----------------
  std::string getPlaka() const;
  std::string getTur() const;
  std::time_t getGirisSaati() const;
  std::time_t getCikisSaati() const;

  /**
   * Bilgi Yazdırma Fonksiyonu
   * - Sanal (virtual) olarak tanımlanmıştır
   * - Türetilmiş sınıflar tarafından override edilebilir
   */
  virtual void bilgileriYazdir() const;
};

#endif // ARAC_H
