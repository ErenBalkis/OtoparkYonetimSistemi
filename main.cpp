#include <iostream>
#include <limits>
#include "Otopark.h"
#include "AracTurleri.h"

/*
    OTOPARK YÖNETİM SİSTEMİ
    - Menü tabanlı konsol uygulaması
    - Polimorfizm, kalıtım ve soyut sınıf kullanımı içerir
    - Hata yönetimi try-catch ile sağlanmıştır
*/

// Ekranı temizlemek için yardımcı fonksiyon (Linux/Windows uyumlu)
void ekraniTemizle() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {

    // Otopark nesnesini oluştur (Örn: "Merkez Otopark", 20 Kapasite)
    Otopark otopark("Istanbul Uni Otopark", 20);

    // Verileri dosyadan yükle 
     otopark.verileriYukle(); 

    int secim;          // Kullanıcı menü seçimi
    bool devam = true;  // Program döngü kontrolü

    // Ana menü döngüsü
    while (devam) {
        // ekraniTemizle(); 
        // Menü ekranı
        std::cout << "\n=== OTOPARK YONETIM SISTEMI ===\n";
        std::cout << "1. Arac Girisi Yap\n";
        std::cout << "2. Arac Cikisi Yap\n";
        std::cout << "3. Bos Park Yerlerini Listele\n";
        std::cout << "4. Durum Raporu\n";
        std::cout << "5. Test Verisi Yukle (Demo Modu)\n";
        std::cout << "0. Cikis\n";
        std::cout << "Seciminiz: ";

        try {
            // Menü seçimi sayısal mı kontrolü
            if (!(std::cin >> secim)) {
                throw std::runtime_error("Gecersiz giris! Sayi giriniz.");
            }

            // Giriş tamponunu temizle
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (secim) {

                // ---------------- ARAÇ GİRİŞİ ----------------
                case 1: {
                    int turSecim;

                    // Araç türü seçimi
                    std::cout << "\n--- Arac Turu Seciniz ---\n";
                    std::cout << "1. Otomobil\n2. Kamyonet\n3. Motosiklet\n";
                    std::cin >> turSecim;

                    // Tampon temizleme
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    // Geçersiz tür kontrolü
                    if (turSecim < 1 || turSecim > 3) {
                        std::cout << "Hatali arac turu secimi!\n";
                        break;
                    }

                    // Plaka bilgisi (boşluklu giriş desteklenir)
                    std::string plaka;
                    std::cout << "Plaka giriniz: ";
                    std::getline(std::cin, plaka);

                    // Polimorfik araç işaretçisi
                    Arac* yeniArac = nullptr;

                    // Seçilen türe göre nesne oluşturma
                    if (turSecim == 1)
                        yeniArac = new Otomobil(plaka);
                    else if (turSecim == 2)
                        yeniArac = new Kamyonet(plaka);
                    else if (turSecim == 3)
                        yeniArac = new Motosiklet(plaka);

                    // Otoparka araç ekleme (hata yakalama ile)
                    try {
                        otopark.aracGiris(yeniArac);
                        std::cout << "Arac girisi basarili.\n";
                    }
                    catch (...) {
                        // Hata durumunda bellek sızıntısını önle
                        delete yeniArac;
                        throw;
                    }
                    break;
                }

                // ---------------- ARAÇ ÇIKIŞI ----------------
                case 2: {
                    std::string plaka;
                    std::cout << "Cikis yapacak aracin plakasi: ";
                    std::getline(std::cin, plaka);

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

                // ---------------- TEST / DEMO MODU ----------------
                case 5:
                    // Farklı türlerde araçlar eklenerek polimorfizm gösterilir
                    otopark.aracGiris(new Otomobil("34 ABC 123"));
                    otopark.aracGiris(new Kamyonet("34 XYZ 789"));
                    otopark.aracGiris(new Motosiklet("35 KL 55"));
                    std::cout << "Test verileri eklendi.\n";
                    break;

                // ---------------- PROGRAMDAN ÇIKIŞ ----------------
                case 0:
                    std::cout << "Veriler kaydediliyor ve cikiliyor...\n";
                     otopark.verileriKaydet();
                    devam = false;
                    break;

                // ---------------- HATALI SEÇİM ----------------
                default:
                    std::cout << "Gecersiz menu secimi, tekrar deneyin!\n";
            }
        }
        catch (const std::exception& e) {
            // Genel hata yakalama
            std::cerr << "\nHATA: " << e.what() << "\n";
            std::cin.clear(); // Hata bayrağını temizle
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Tamponu temizle
        }
    }

    return 0;
}

