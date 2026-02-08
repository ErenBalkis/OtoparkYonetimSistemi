#include "AracTurleri.h"
#include "Otopark.h"
#include <iostream>
#include <limits>
#include <memory>
#include <string>

/**
 * OTOPARK YÖNETİM SİSTEMİ - ANA PROGRAM
 * --------------------------------
 * - Menü tabanlı konsol uygulaması
 * - C++17 standartlarına uygun
 * - Smart pointer ile bellek güvenliği
 * - Zaman bazlı ücretlendirme
 */

// ==================== GİRDİ DOĞRULAMA ====================

/**
 * Güvenli tamsayı girişi alır
 * @param mesaj Kullanıcıya gösterilecek mesaj
 * @param minVal Minimum kabul edilebilir değer
 * @param maxVal Maksimum kabul edilebilir değer
 * @return Doğrulanmış tamsayı değeri
 */
int inputValidator(const std::string &mesaj, int minVal, int maxVal) {
  int deger;

  while (true) {
    std::cout << mesaj;

    if (std::cin >> deger) {
      // Giriş tamponunu temizle
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      // Aralık kontrolü
      if (deger >= minVal && deger <= maxVal) {
        return deger;
      }
      std::cout << "\n[!] Geçersiz değer! " << minVal << " ile " << maxVal
                << " arasında bir değer giriniz.\n";
    } else {
      // Geçersiz giriş (harf vb.)
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "\n[!] Geçersiz giriş! Lütfen bir sayı giriniz.\n";
    }
  }
}

/**
 * Boşluklu metin girişi alır (örn: plaka)
 * @param mesaj Kullanıcıya gösterilecek mesaj
 * @return Girilen metin
 */
std::string getStringInput(const std::string &mesaj) {
  std::string deger;
  std::cout << mesaj;
  std::getline(std::cin, deger);
  return deger;
}

// ==================== MENÜ YAZDIRMA ====================

void menuYazdir() {
  std::cout << "\n";
  std::cout << "╔══════════════════════════════════════╗\n";
  std::cout << "║   OTOPARK YÖNETİM SİSTEMİ v2.0       ║\n";
  std::cout << "╠══════════════════════════════════════╣\n";
  std::cout << "║  1. Araç Girişi Yap                  ║\n";
  std::cout << "║  2. Araç Çıkışı Yap                  ║\n";
  std::cout << "║  3. Boş Park Yerlerini Listele       ║\n";
  std::cout << "║  4. Durum Raporu                     ║\n";
  std::cout << "║  5. Demo Verisi Yükle (Test)         ║\n";
  std::cout << "║  0. Çıkış                            ║\n";
  std::cout << "╚══════════════════════════════════════╝\n";
}

void aracTuruMenusu() {
  std::cout << "\n╔══════════════════════════════════════╗\n";
  std::cout << "║         ARAÇ TÜRÜ SEÇİNİZ            ║\n";
  std::cout << "╠══════════════════════════════════════╣\n";
  std::cout << "║  1. Otomobil  (Baz: 50 TL + 10 TL/s) ║\n";
  std::cout << "║  2. Kamyonet  (Baz: 80 TL + 15 TL/s) ║\n";
  std::cout << "║  3. Motosiklet(Baz: 30 TL +  5 TL/s) ║\n";
  std::cout << "╚══════════════════════════════════════╝\n";
}

// ==================== ANA FONKSİYON ====================

int main() {
  // Otopark nesnesini oluştur
  Otopark otopark("İstanbul Üniversitesi Otoparkı", 20);

  // Önceki oturumdan verileri yükle
  otopark.verileriYukle();

  bool devam = true;

  // Ana menü döngüsü
  while (devam) {
    menuYazdir();

    int secim = inputValidator("Seçiminiz (0-5): ", 0, 5);

    switch (secim) {
    // ---------------- ARAÇ GİRİŞİ ----------------
    case 1: {
      aracTuruMenusu();
      int turSecim = inputValidator("Tür seçimi (1-3): ", 1, 3);

      std::string plaka = getStringInput("Plaka giriniz: ");

      if (plaka.empty()) {
        std::cout << "\n[!] Plaka boş olamaz!\n";
        break;
      }

      // Seçilen türe göre araç oluştur (smart pointer ile)
      std::unique_ptr<Arac> yeniArac;

      switch (turSecim) {
      case 1:
        yeniArac = std::make_unique<Otomobil>(plaka);
        break;
      case 2:
        yeniArac = std::make_unique<Kamyonet>(plaka);
        break;
      case 3:
        yeniArac = std::make_unique<Motosiklet>(plaka);
        break;
      }

      // Otoparka araç ekle (ownership transfer)
      otopark.aracGiris(std::move(yeniArac));
      break;
    }

    // ---------------- ARAÇ ÇIKIŞI ----------------
    case 2: {
      std::string plaka = getStringInput("Çıkış yapacak aracın plakası: ");

      if (plaka.empty()) {
        std::cout << "\n[!] Plaka boş olamaz!\n";
        break;
      }

      otopark.aracCikis(plaka);
      break;
    }

    // ---------------- BOŞ YER LİSTELE ----------------
    case 3:
      otopark.bosYerleriListele();
      break;

    // ---------------- DURUM RAPORU ----------------
    case 4:
      otopark.durumRaporu();
      break;

    // ---------------- DEMO / TEST MODU ----------------
    case 5: {
      std::cout << "\n[i] Demo verileri yükleniyor...\n";

      // Farklı türlerde araçlar ekle (polimorfizm gösterimi)
      otopark.aracGiris(std::make_unique<Otomobil>("34 ABC 123"));
      otopark.aracGiris(std::make_unique<Kamyonet>("34 XYZ 789"));
      otopark.aracGiris(std::make_unique<Motosiklet>("35 KL 55"));

      std::cout << "\n[✓] 3 adet test aracı eklendi.\n";
      break;
    }

    // ---------------- PROGRAMDAN ÇIKIŞ ----------------
    case 0: {
      std::cout << "\n╔══════════════════════════════════════╗\n";
      std::cout << "║  Veriler kaydediliyor...             ║\n";
      std::cout << "║  Güle güle!                          ║\n";
      std::cout << "╚══════════════════════════════════════╝\n";
      devam = false;
      break;
    }
    }
  }

  return 0;
}
