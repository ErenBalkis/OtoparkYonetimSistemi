#include "Otopark.h"
#include "AracTurleri.h"
#include <algorithm>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

/**
 * OTOPARK YÖNETİM SINIFI IMPLEMENTASYONU
 * --------------------------------
 * - std::unique_ptr ile bellek yönetimi
 * - CSV formatında veri kalıcılığı
 * - Zaman bazlı ücretlendirme desteği
 */

// ==================== CONSTRUCTOR & DESTRUCTOR ====================

Otopark::Otopark(const std::string &ad, int kapasite) : otoparkAdi(ad) {
  // Park yerlerini oluştur (2 kat varsayımı)
  for (int i = 1; i <= kapasite; ++i) {
    int kat = (i <= kapasite / 2) ? 1 : 2;
    parkYerleri.emplace_back(i, kat);
  }
}

Otopark::~Otopark() {
  // Çıkışta verileri kaydet
  verileriKaydet();
  // unique_ptr sayesinde araçlar otomatik temizlenir
}

// ==================== YARDIMCI METOTLAR ====================

int Otopark::bosParkYeriBul() const {
  for (size_t i = 0; i < parkYerleri.size(); ++i) {
    if (!parkYerleri[i].isDolu()) {
      return static_cast<int>(i);
    }
  }
  return -1;
}

int Otopark::bosYerSayisi() const {
  int sayac = 0;
  for (const auto &yer : parkYerleri) {
    if (!yer.isDolu()) {
      ++sayac;
    }
  }
  return sayac;
}

// ==================== ARAÇ GİRİŞ/ÇIKIŞ ====================

void Otopark::aracGiris(std::unique_ptr<Arac> yeniArac) {
  int index = bosParkYeriBul();

  if (index == -1) {
    std::cout << "\n╔══════════════════════════════════════╗\n";
    std::cout << "║  HATA: Otopark dolu!                 ║\n";
    std::cout << "╚══════════════════════════════════════╝\n";
    return; // unique_ptr otomatik olarak temizlenir
  }

  // Park yerini işaretle
  parkYerleri[index].setDurum(true, yeniArac->getPlaka());

  std::cout << "\n╔══════════════════════════════════════╗\n";
  std::cout << "║         ARAÇ GİRİŞ BİLGİSİ           ║\n";
  std::cout << "╠══════════════════════════════════════╣\n";
  std::cout << "║ Plaka    : " << std::left << std::setw(25)
            << yeniArac->getPlaka() << " ║\n";
  std::cout << "║ Tür      : " << std::left << std::setw(25)
            << yeniArac->getTur() << " ║\n";
  std::cout << "║ Park No  : " << std::left << std::setw(25) << (index + 1)
            << " ║\n";
  std::cout << "║ Kat      : " << std::left << std::setw(25)
            << parkYerleri[index].getKat() << " ║\n";
  std::cout << "╚══════════════════════════════════════╝\n";

  // Ownership transfer
  aktifAraclar.push_back(std::move(yeniArac));
}

void Otopark::aracCikis(const std::string &plaka) {
  // Aracı bul
  auto it = std::find_if(aktifAraclar.begin(), aktifAraclar.end(),
                         [&plaka](const std::unique_ptr<Arac> &arac) {
                           return arac->getPlaka() == plaka;
                         });

  if (it == aktifAraclar.end()) {
    std::cout << "\n╔══════════════════════════════════════╗\n";
    std::cout << "║  HATA: Araç bulunamadı!              ║\n";
    std::cout << "║  Plaka: " << std::left << std::setw(28) << plaka << " ║\n";
    std::cout << "╚══════════════════════════════════════╝\n";
    return;
  }

  // Çıkış zamanını ayarla ve ücret hesapla
  (*it)->setCikisSaati(std::time(nullptr));
  double ucret = (*it)->hesaplaUcret();

  // Giriş ve çıkış zamanlarını formatla
  std::time_t giris = (*it)->getGirisSaati();
  std::time_t cikis = (*it)->getCikisSaati();

  char girisStr[26], cikisStr[26];
  std::strftime(girisStr, 26, "%d/%m/%Y %H:%M:%S", std::localtime(&giris));
  std::strftime(cikisStr, 26, "%d/%m/%Y %H:%M:%S", std::localtime(&cikis));

  // Süre hesapla
  double sureSaat = std::difftime(cikis, giris) / 3600.0;

  // Çıkış fişi yazdır
  std::cout << "\n╔══════════════════════════════════════╗\n";
  std::cout << "║         ARAÇ ÇIKIŞ FİŞİ              ║\n";
  std::cout << "╠══════════════════════════════════════╣\n";
  std::cout << "║ Plaka       : " << std::left << std::setw(22) << plaka
            << " ║\n";
  std::cout << "║ Tür         : " << std::left << std::setw(22)
            << (*it)->getTur() << " ║\n";
  std::cout << "╠══════════════════════════════════════╣\n";
  std::cout << "║ Giriş       : " << std::left << std::setw(22) << girisStr
            << " ║\n";
  std::cout << "║ Çıkış       : " << std::left << std::setw(22) << cikisStr
            << " ║\n";
  std::cout << "║ Süre        : " << std::fixed << std::setprecision(1)
            << std::setw(18) << sureSaat << " saat ║\n";
  std::cout << "╠══════════════════════════════════════╣\n";
  std::cout << "║ TOPLAM ÜCRET: " << std::fixed << std::setprecision(2)
            << std::setw(18) << ucret << " TL  ║\n";
  std::cout << "╚══════════════════════════════════════╝\n";
  std::cout << "       İyi yolculuklar dileriz!\n\n";

  // Log dosyasına kaydet
  std::ofstream logDosyasi(LOG_DOSYASI, std::ios::app);
  if (logDosyasi.is_open()) {
    logDosyasi << "=== İŞLEM KAYDI ===\n";
    logDosyasi << "Plaka: " << plaka << " | Tür: " << (*it)->getTur() << "\n";
    logDosyasi << "Giriş: " << girisStr << " | Çıkış: " << cikisStr << "\n";
    logDosyasi << "Süre: " << std::fixed << std::setprecision(1) << sureSaat
               << " saat\n";
    logDosyasi << "Ücret: " << std::fixed << std::setprecision(2) << ucret
               << " TL\n";
    logDosyasi << "==================\n\n";
    logDosyasi.close();
  }

  // Park yerini boşalt
  for (auto &yer : parkYerleri) {
    if (yer.getPlaka() == plaka) {
      yer.setDurum(false, "");
      break;
    }
  }

  // unique_ptr'ı listeden çıkar (otomatik delete)
  aktifAraclar.erase(it);
}

// ==================== LİSTELEME FONKSİYONLARI ====================

void Otopark::bosYerleriListele() const {
  std::cout << "\n╔══════════════════════════════════════╗\n";
  std::cout << "║         BOŞ PARK YERLERİ             ║\n";
  std::cout << "╠══════════════════════════════════════╣\n";

  int bosCount = 0;
  for (const auto &yer : parkYerleri) {
    if (!yer.isDolu()) {
      std::cout << "║  [K" << yer.getKat() << "-N" << std::setw(2)
                << yer.getId() << "] ";
      ++bosCount;
      if (bosCount % 4 == 0) {
        std::cout << "             ║\n";
      }
    }
  }

  if (bosCount % 4 != 0) {
    // Satırı tamamla
    int kalan = 4 - (bosCount % 4);
    for (int i = 0; i < kalan; ++i) {
      std::cout << "        ";
    }
    std::cout << "             ║\n";
  }

  std::cout << "╠══════════════════════════════════════╣\n";
  std::cout << "║ Toplam Boş Yer: " << std::left << std::setw(20) << bosCount
            << " ║\n";
  std::cout << "╚══════════════════════════════════════╝\n";
}

void Otopark::durumRaporu() const {
  std::cout << "\n╔══════════════════════════════════════════════════════╗\n";
  std::cout << "║              " << std::left << std::setw(38) << otoparkAdi
            << " ║\n";
  std::cout << "║                   DURUM RAPORU                       ║\n";
  std::cout << "╠══════════════════════════════════════════════════════╣\n";
  std::cout << "║ Toplam Kapasite : " << std::left << std::setw(33)
            << parkYerleri.size() << " ║\n";
  std::cout << "║ Dolu Park Yeri  : " << std::left << std::setw(33)
            << aktifAraclar.size() << " ║\n";
  std::cout << "║ Boş Park Yeri   : " << std::left << std::setw(33)
            << bosYerSayisi() << " ║\n";
  std::cout << "╠══════════════════════════════════════════════════════╣\n";

  if (!aktifAraclar.empty()) {
    std::cout << "║ MEVCUT ARAÇLAR:                                      ║\n";
    std::cout << "╠══════════════════════════════════════════════════════╣\n";

    for (const auto &arac : aktifAraclar) {
      std::time_t giris = arac->getGirisSaati();
      char girisStr[20];
      std::strftime(girisStr, 20, "%H:%M", std::localtime(&giris));

      std::cout << "║  " << std::left << std::setw(14) << arac->getPlaka()
                << " | " << std::setw(12) << arac->getTur()
                << " | Giriş: " << std::setw(8) << girisStr << "     ║\n";
    }
  } else {
    std::cout << "║ Otoparkta araç bulunmamaktadır.                      ║\n";
  }

  std::cout << "╚══════════════════════════════════════════════════════╝\n";
}

// ==================== DOSYA İŞLEMLERİ ====================

void Otopark::verileriKaydet() const {
  std::ofstream dosya(VERI_DOSYASI);

  if (!dosya.is_open()) {
    std::cerr << "HATA: " << VERI_DOSYASI << " dosyası açılamadı!\n";
    return;
  }

  // CSV header
  dosya << "PLAKA,TUR,GIRIS_ZAMANI\n";

  // Her aktif aracı kaydet
  for (const auto &arac : aktifAraclar) {
    // Plakadaki boşlukları _ ile değiştir
    std::string plaka = arac->getPlaka();
    std::replace(plaka.begin(), plaka.end(), ' ', '_');

    dosya << plaka << "," << arac->getTur() << ","
          << static_cast<long>(arac->getGirisSaati()) << "\n";
  }

  dosya.close();
}

void Otopark::verileriYukle() {
  std::ifstream dosya(VERI_DOSYASI);

  if (!dosya.is_open()) {
    // Dosya yoksa, ilk çalıştırma - hata değil
    return;
  }

  std::string satir;

  // Header satırını atla
  std::getline(dosya, satir);

  while (std::getline(dosya, satir)) {
    if (satir.empty())
      continue;

    std::stringstream ss(satir);
    std::string plaka, tur, zamanStr;

    // CSV parse
    std::getline(ss, plaka, ',');
    std::getline(ss, tur, ',');
    std::getline(ss, zamanStr, ',');

    // Plakadaki _ karakterini boşluğa çevir
    std::replace(plaka.begin(), plaka.end(), '_', ' ');

    // Giriş zamanını parse et
    long girisZamani = std::stol(zamanStr);

    // Araç nesnesini oluştur
    std::unique_ptr<Arac> arac;
    if (tur == "Otomobil") {
      arac = std::make_unique<Otomobil>(plaka);
    } else if (tur == "Kamyonet") {
      arac = std::make_unique<Kamyonet>(plaka);
    } else if (tur == "Motosiklet") {
      arac = std::make_unique<Motosiklet>(plaka);
    } else {
      continue; // Bilinmeyen tür, atla
    }

    // Giriş zamanını geri yükle
    arac->setGirisSaati(static_cast<std::time_t>(girisZamani));

    // Boş park yeri bul ve işaretle
    int index = bosParkYeriBul();
    if (index != -1) {
      parkYerleri[index].setDurum(true, plaka);
      aktifAraclar.push_back(std::move(arac));
    }
  }

  dosya.close();

  if (!aktifAraclar.empty()) {
    std::cout << "\n╔══════════════════════════════════════╗\n";
    std::cout << "║  Sistem başarıyla geri yüklendi.     ║\n";
    std::cout << "║  Yüklenen araç sayısı: " << std::left << std::setw(14)
              << aktifAraclar.size() << " ║\n";
    std::cout << "╚══════════════════════════════════════╝\n";
  }
}
