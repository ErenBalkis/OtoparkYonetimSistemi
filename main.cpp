#include <iostream>
#include <limits> // cin.ignore için gerekli
#include "Otopark.h"
#include "AracTurleri.h"

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
    // otopark.verileriYukle(); 

    int secim;
    bool devam = true;

    while (devam) {
        ekraniTemizle(); 
        std::cout << "\n=== OTOPARK YONETIM SISTEMI ===\n";
        std::cout << "1. Arac Girisi Yap\n";
        std::cout << "2. Arac Cikisi Yap\n";
        std::cout << "3. Bos Park Yerlerini Listele\n";
        std::cout << "4. Durum Raporu (Bonus)\n";
        std::cout << "0. Cikis ve Kaydet\n";
        std::cout << "Seciminiz: ";

        // Hata yakalama bloğu 
        try {
            if (!(std::cin >> secim)) {
                throw std::runtime_error("Gecersiz giris! Lutfen sayi giriniz.");
            }

            switch (secim) {
                case 1: {
                    std::cout << "\n--- Arac Turu Seciniz ---\n";
                    std::cout << "1. Otomobil\n2. Kamyonet\n3. Motosiklet\n";
                    int turSecim;
                    std::cin >> turSecim;
                    
                    std::string plaka;
                    std::cout << "Plaka giriniz: ";
                    std::cin >> plaka;

                    Arac* yeniArac = nullptr;

                    if (turSecim == 1) yeniArac = new Otomobil(plaka);
                    else if (turSecim == 2) yeniArac = new Kamyonet(plaka);
                    else if (turSecim == 3) yeniArac = new Motosiklet(plaka);
                    else std::cout << "Hatali tur secimi!\n";

                    if (yeniArac) {
                        otopark.aracGiris(yeniArac);
                        std::cout << "Arac girisi basarili.\n";
                    }
                    break;
                }
                case 2: {
                    std::string plaka;
                    std::cout << "Cikis yapacak plaka: ";
                    std::cin >> plaka;
                    otopark.aracCikis(plaka);
                    break;
                }
                case 3:
                    otopark.bosYerleriListele();
                    break;
                case 4:
                    otopark.durumRaporu();
                    break;
                case 0:
                    std::cout << "Veriler kaydediliyor ve cikiliyor...\n";
                    otopark.verileriKaydet();
                    devam = false;
                    break;
                default:
                    std::cout << "Gecersiz secim, tekrar deneyin.\n";
            }
        }
        catch (const std::exception& e) {
            std::cerr << "\nHATA: " << e.what() << "\n";
            std::cin.clear(); // Hata bayrağını temizle
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Tamponu temizle
        }
    }

    return 0;
}
