#include "Otopark.h"
#include "AracTurleri.h"
#include <iostream>
#include <fstream>
#include "ParkYeri.h"
#include <stdexcept>  //exception için
#include <algorithm> // replace işlemi için gerekli

//Yapıcı metot (nesne ilk oluştuğunda çalışır)
Otopark::Otopark(std::string ad, int kapasite) : otoparkAdi(ad) {
    for (int i = 1; i<=kapasite; ++i) {
        //her 20 araçta bir kat artışı
        int kat = (i <=20) ? 1 : 2;
        parkYerleri.push_back(ParkYeri(i, kat));
    }
}

//Yıkıcı metot (belleği temizleyecek)

// Yıkıcı metot (DÜZELTME: Program kapanırken otomatik kaydet)
Otopark::~Otopark() {
    verileriKaydet(); // Program aniden bitse bile kaydetmeyi dener

    for (Arac* arac : aktifAraclar) {
        delete arac;
    }
    aktifAraclar.clear();
}


// --- ARAÇ KAYIT VE YÖNETİM İŞLEMLERİ ---

// Yardımcı Fonksiyon: Boş yerin indeksini döner
int Otopark::bosParkYeriBul() {
    for (int i = 0; i < (int)parkYerleri.size(); ++i) {
        if (!parkYerleri[i].isDolu()) {
            return i;
        }
    }
    return -1; // Yer yoksa
}

// ARAÇ GİRİŞİ: Aracı listeye ekler ve park yerini doldurur
void Otopark::aracGiris(Arac* yeniArac) {
    int index = bosParkYeriBul();

    if (index == -1) {
        std::cout << "HATA: Otopark dolu! " << yeniArac->getPlaka() << " iceri alinamaz.\n";
        return;
    }

    // Park yerini güncelle (Plaka ile birlikte)
    parkYerleri[index].setDurum(true, yeniArac->getPlaka());

    // Aracı aktif araçlar listesine ekle
    aktifAraclar.push_back(yeniArac);

    std::cout << "Giris Basarili: " << yeniArac->getPlaka()
              << " -> Yer: " << parkYerleri[index].getId()
              << " (Kat: " << parkYerleri[index].getKat() << ")\n";
}

// ARAÇ ÇIKIŞI: Plaka üzerinden aracı bulur, ücreti gösterir ve siler
void Otopark::aracCikis(std::string plaka) {
    bool bulundu = false;

    for (auto it = aktifAraclar.begin(); it != aktifAraclar.end(); ++it) {
        if ((*it)->getPlaka() == plaka) {
            // 1. Ücreti hesapla
            std::cout << "\n--- Arac Cikisi ---\n";
            std::cout << "Plaka: " << plaka << " | Ucret: " << (*it)->hesaplaUcret() << " TL\n";

            // 2. Park yerini fiziksel olarak boşalt
            for (auto& yer : parkYerleri) {
                if (yer.getPlaka() == plaka) {
                    yer.setDurum(false, ""); // Boşalt ve plakayı sil
                    break;
                }
            }

            // 3. Bellekten ve listeden sil (Senin en önemli görevin)
            delete *it;
            aktifAraclar.erase(it);

            bulundu = true;
            std::cout << "Islem tamamlandi. Gule gule!\n";
            break;
        }
    }

    if (!bulundu) {
        std::cout << "HATA: " << plaka << " plakali arac sistemde yok!\n";
    }
}

// --- DOSYA İŞLEMLERİ (YAZMA VE SİLME/GÜNCELLEME MANTIĞI) ---

void Otopark::verileriKaydet() {
    std::ofstream dosya("ParkYerleri.txt");

    try {
        if (!dosya.is_open()) {
            throw std::runtime_error("Dosya yazma hatasi: ParkYerleri.txt acilamadi!");
        }

        for (const ParkYeri& yer : parkYerleri) {
            std::string kaydedilecekPlaka = yer.isDolu() ? yer.getPlaka() : "BOS";

            // DÜZELTME: Plakadaki boşlukları alt çizgi yap (34 ABC 12 -> 34_ABC_12)
            // Böylece dosyadan okurken tek parça okunabilir.
            std::replace(kaydedilecekPlaka.begin(), kaydedilecekPlaka.end(), ' ', '_');

            dosya << yer.getKat() << " "
                  << yer.getId() << " "
                  << yer.isDolu() << " "
                  << kaydedilecekPlaka << "\n";
        }

        dosya.close();
        std::cout << "Veriler kaydedildi.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "KRITIK HATA: " << e.what() << "\n";
    }
}

void Otopark::verileriYukle() {
    std::ifstream dosya("ParkYerleri.txt");
    if (!dosya.is_open()) {
        std::cout << "Kayitli veri bulunamadi, yeni otopark baslatiliyor.\n";
        return;
    }

    int kat, id;
    bool dolu;
    std::string plaka;
    int index = 0;

    // Dosyadan okuma
    while (dosya >> kat >> id >> dolu >> plaka && index < (int)parkYerleri.size()) {

        // DÜZELTME: Okunan plakadaki alt çizgileri tekrar boşluğa çevir (34_ABC_12 -> 34 ABC 12)
        std::replace(plaka.begin(), plaka.end(), '_', ' ');

        if (dolu) {
            parkYerleri[index].setDurum(true, (plaka == "BOS" ? "" : plaka));

            // NOT: Dosyadan yüklenen araçları 'aktifAraclar' listesine de eklememiz lazım
            // Yoksa çıkış yaparken sistem aracı bulamaz!
            // Demo amaçlı hepsini varsayılan olarak Otomobil ekliyoruz (Çünkü dosya tür bilgisini tutmuyor)
            if (plaka != "BOS") {
                 aktifAraclar.push_back(new Otomobil(plaka));
            }

        } else {
            parkYerleri[index].setDurum(false, "");
        }
        index++;
    }

    dosya.close();
    std::cout << "Otopark durumu ve plakalar dosyadan yuklendi.\n";
}

void Otopark::bosYerleriListele() const {
    std::cout << "\n--- Bos Park Yerleri ---\n";
    for (const auto& yer : parkYerleri) {
        if (!yer.isDolu()) {
            std::cout << "[K" << yer.getKat() << "-No" << yer.getId() << "] ";
        }
    }
    std::cout << "\n";
}

void Otopark::durumRaporu() const {
    std::cout << "\n=== OTOPARK MEVCUT DURUM ===\n";
    for (const auto& yer : parkYerleri) {
        std::cout << "Yer " << yer.getId() << " (Kat " << yer.getKat() << "): "
                  << (yer.isDolu() ? "DOLU [" + yer.getPlaka() + "]" : "BOS") << "\n";
    }
}
