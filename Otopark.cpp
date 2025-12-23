#include "Otopark.h"
#include "AracTurleri.h"
#include <iostream>
#include <fstream>
#include "ParkYeri.h"
#include <stdexcept>
#include <algorithm>
#include <ctime>

Otopark::Otopark(std::string ad, int kapasite) : otoparkAdi(ad) {
    for (int i = 1; i <= kapasite; ++i) {
        int kat = (i <= 20) ? 1 : 2;
        parkYerleri.push_back(ParkYeri(i, kat));
    }
}

Otopark::~Otopark() {
    verileriKaydet(); 
    for (Arac* arac : aktifAraclar) {
        delete arac;
    }
    aktifAraclar.clear();
}

int Otopark::bosParkYeriBul() {
    for (int i = 0; i < (int)parkYerleri.size(); ++i) {
        if (!parkYerleri[i].isDolu()) return i;
    }
    return -1;
}

void Otopark::aracGiris(Arac* yeniArac) {
    int index = bosParkYeriBul();
    if (index == -1) {
        std::cout << "HATA: Otopark dolu!\n";
        delete yeniArac; // Bellek sızıntısını önlemek için nesneyi sil
        return;
    }
    parkYerleri[index].setDurum(true, yeniArac->getPlaka());
    aktifAraclar.push_back(yeniArac);
    std::cout << "Giris: " << yeniArac->getPlaka() << " [" << yeniArac->getTur() << "]\n";
}

void Otopark::aracCikis(std::string plaka) {
    bool bulundu = false;

    // 1. Aktif araçlar listesinde plakayı ara
    for (auto it = aktifAraclar.begin(); it != aktifAraclar.end(); ++it) {
        if ((*it)->getPlaka() == plaka) {
            
            // 2. Ücreti hesapla (Polimorfizm: Arac türüne göre (Otomobil/Kamyonet vb.) farklı hesaplar)
            double ucret = (*it)->hesaplaUcret();
            
            // 3. Zaman bilgisini al (Log için)
            time_t simdi = time(0);
            std::string tarih = ctime(&simdi); // Çıkış tarihini metne çevir

            // 4. Ekrana bilgi yazdır
            std::cout << "\n--- ARAC CIKIS FISI ---" << std::endl;
            std::cout << "Plaka       : " << plaka << std::endl;
            std::cout << "Arac Turu   : " << (*it)->getTur() << std::endl;
            std::cout << "Toplam Ucret: " << ucret << " TL" << std::endl;
            std::cout << "-----------------------" << std::endl;

            // 5. OtoparkLog.txt dosyasına ARŞİVLE (Kalıcı kayıt)
            std::ofstream logDosyasi("OtoparkLog.txt", std::ios::app); // 'app' modu sonuna ekleme yapar
            if (logDosyasi.is_open()) {
                logDosyasi << "--- ISLEM KAYDI ---" << std::endl;
                logDosyasi << "Plaka: " << plaka << " | Tur: " << (*it)->getTur() << std::endl;
                logDosyasi << "Ucret: " << ucret << " TL" << std::endl;
                logDosyasi << "Tarih: " << tarih; // ctime zaten \n içerir
                logDosyasi << "-------------------" << std::endl;
                logDosyasi.close();
            }

            // 6. Park Yerini Fiziksel Olarak Boşalt
            // Park yerleri listesinde bu plakaya ait olan yeri bul ve durumunu 'boş' yap
            for (auto& yer : parkYerleri) {
                if (yer.getPlaka() == plaka) {
                    yer.setDurum(false, ""); // Park yerini boşalt ve plakayı sil
                    break;
                }
            }

            // 7. BELLEK YÖNETİMİ (Kritik Adım)
            delete *it;              // main.cpp'de 'new' ile ayrılan heap belleğini serbest bırak
            aktifAraclar.erase(it);  // Vector içindeki pointer (adres) bilgisini sil
            
            bulundu = true;
            std::cout << "Cikis islemi tamamlandi. Iyi yolculuklar!\n";
            break;
        }
    }

    if (!bulundu) {
        std::cout << "HATA: " << plaka << " plakali arac otoparkta bulunamadi!\n";
    }
}


void Otopark::verileriKaydet() {
    std::ofstream dosya("ParkYerleri.txt");
    try {
        if (!dosya.is_open()) throw std::runtime_error("ParkYerleri.txt acilamadi!");

        dosya << "Kat ID Dolu Plaka Tur Giris_Saniyesi Mevcut_Ucret Giris_Tarihi\n"; 
        dosya << "------------------------------------------------------------------\n";

        for (const ParkYeri& yer : parkYerleri) {
            std::string plaka = yer.isDolu() ? yer.getPlaka() : "BOS";
            std::string tur = "YOK";
            long int girisSaniye = 0;
            double ucret = 0.0;
            std::string okunabilirZaman = "---";

            if (yer.isDolu()) {
                // Aktif araçlar listesinde bu plakayı bul
                for (Arac* a : aktifAraclar) {
                    if (a->getPlaka() == yer.getPlaka()) {
                        tur = a->getTur();
                        girisSaniye = (long int)a->getGirisSaati();
                        ucret = a->hesaplaUcret();
                        
                        // --- DÜZELTME BAŞLANGIÇ (Standart C++ Tarih Formatı) ---
                        time_t t = a->getGirisSaati();
                        char* dt = std::ctime(&t); // Standart ctime kullanımı
                        okunabilirZaman = dt ? dt : "Hata";
                        // ctime sonuna \n koyar, onu silelim:
                        if (!okunabilirZaman.empty() && okunabilirZaman.back() == '\n') {
                            okunabilirZaman.pop_back();
                        }
                        // --- DÜZELTME BİTİŞ ---
                        break;
                    }
                }
            }

            // Plakadaki boşlukları _ yap
            std::string dosyaPlaka = plaka; // Orijinal plakayı bozmamak için kopya aldık
            std::replace(dosyaPlaka.begin(), dosyaPlaka.end(), ' ', '_');
            
            dosya << yer.getKat() << " " 
                  << yer.getId() << " " 
                  << yer.isDolu() << " " 
                  << dosyaPlaka << " "   // Düzeltilmiş plakayı yaz
                  << tur << " " 
                  << girisSaniye << " " 
                  << ucret << " TL " 
                  << okunabilirZaman << "\n";
        }
        dosya.close();
        // std::cout << "Kaydedildi...\n"; // Konsolu kirletmemek için kapatabilirsin
    } catch (const std::exception& e) { std::cerr << e.what() << "\n"; }
}

void Otopark::verileriYukle() {
    std::ifstream dosya("ParkYerleri.txt");
    if (!dosya.is_open()) return;

    // Dosyanın ilk iki satırı başlık olduğu için onları boşa okuyup geçmeliyiz
    std::string baslikSatiri;
    std::getline(dosya, baslikSatiri); // "Kat ID..." satirini oku ve geç
    std::getline(dosya, baslikSatiri); // "----..." satirini oku ve geç

    int kat, id; 
    bool dolu;
    std::string plaka, tur;
    long int girisZamani;
    
    // index sayacını kullanmak yerine dosyadan okunan ID'ye göre işlem yapmak daha güvenlidir
    // ama senin kod yapını bozmadan index ile devam edelim.
    int index = 0; 

    // Dikkat: index kontrolünü while içine ekledim
    while (index < (int)parkYerleri.size() && dosya >> kat >> id >> dolu >> plaka >> tur >> girisZamani) {
        
        // KRİTİK DÜZELTME: Satırın geri kalanını (Ücret, TL, Tarih vs.) oku ve yut.
        // Böylece imleç bir sonraki satırın başına geçer.
        std::string kalanSatir;
        std::getline(dosya, kalanSatir); 

        std::replace(plaka.begin(), plaka.end(), '_', ' ');

        if (dolu && plaka != "BOS") {
            parkYerleri[index].setDurum(true, plaka);
            
            Arac* yeniArac = nullptr;
            if (tur == "Otomobil") yeniArac = new Otomobil(plaka);
            else if (tur == "Kamyonet") yeniArac = new Kamyonet(plaka);
            else if (tur == "Motosiklet") yeniArac = new Motosiklet(plaka);

            if (yeniArac) {
                yeniArac->setGirisSaati((time_t)girisZamani); 
                aktifAraclar.push_back(yeniArac);
            }
        } else {
            // Eğer dosyadaki o satır boşsa, park yerini de boş olarak ayarla/garantiye al
             parkYerleri[index].setDurum(false, "");
        }
        index++;
    }
    dosya.close();
    std::cout << "Sistem basariyla geri yuklendi.\n";
}

// --- LINKER HATASINI ÇÖZEN EKSİK FONKSİYONLAR ---

void Otopark::bosYerleriListele() const {
    std::cout << "\n--- BOS PARK YERLERI ---\n";
    for (const auto& yer : parkYerleri) {
        if (!yer.isDolu()) {
            std::cout << "[K" << yer.getKat() << "-N" << yer.getId() << "] ";
        }
    }
    std::cout << "\n";
}

void Otopark::durumRaporu() const {
    std::cout << "\n=== OTOPARK MEVCUT DURUM ===\n";
    for (const auto& yer : parkYerleri) {
        std::cout << "Park No: " << yer.getId() 
                  << " | Kat: " << yer.getKat() 
                  << " | Durum: " << (yer.isDolu() ? "DOLU [" + yer.getPlaka() + "]" : "BOS") << "\n";
    }
}
