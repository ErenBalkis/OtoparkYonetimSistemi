#ifndef OTOPARK_H
#define OTOPARK_H

#include "Arac.h"
#include "ParkYeri.h"
#include <memory>
#include <string>
#include <vector>

/**
 * OTOPARK YÖNETİM SINIFI
 * --------------------------------
 * - Park yerleri ve aktif araçları yönetir
 * - std::unique_ptr ile bellek güvenliği sağlar
 * - CSV formatında veri kalıcılığı destekler
 */

class Otopark {
private:
  std::string otoparkAdi;
  std::vector<ParkYeri> parkYerleri;
  std::vector<std::unique_ptr<Arac>> aktifAraclar; // Smart pointer ile yönetim

  // CSV dosya adları
  static constexpr const char *VERI_DOSYASI = "OtoparkVeri.csv";
  static constexpr const char *LOG_DOSYASI = "OtoparkLog.txt";

public:
  /**
   * Constructor
   * @param ad Otopark adı
   * @param kapasite Toplam park yeri sayısı
   */
  Otopark(const std::string &ad, int kapasite);

  // Destructor: Smart pointer sayesinde otomatik temizleme
  ~Otopark();

  // ---------------- TEMEL İŞLEVLER ----------------

  /**
   * Otoparka araç girişi yapar
   * @param yeniArac Giriş yapacak aracın unique_ptr'ı (ownership transfer)
   */
  void aracGiris(std::unique_ptr<Arac> yeniArac);

  /**
   * Otoparktan araç çıkışı yapar ve ücret hesaplar
   * @param plaka Çıkış yapacak aracın plakası
   */
  void aracCikis(const std::string &plaka);

  /**
   * Boş park yerlerini listeler
   */
  void bosYerleriListele() const;

  /**
   * Otopark durum raporu yazdırır
   */
  void durumRaporu() const;

  // ---------------- DOSYA İŞLEMLERİ ----------------

  /**
   * Mevcut durumu CSV formatında dosyaya kaydeder
   * Format: PLAKA,TUR,GIRIS_ZAMANI
   */
  void verileriKaydet() const;

  /**
   * CSV dosyasından verileri yükler
   */
  void verileriYukle();

  // ---------------- YARDIMCI METOTLAR ----------------

  /**
   * İlk boş park yerinin index'ini döndürür
   * @return Boş yer index'i veya -1 (dolu)
   */
  int bosParkYeriBul() const;

  /**
   * Toplam boş park yeri sayısını döndürür
   */
  int bosYerSayisi() const;
};

#endif // OTOPARK_H