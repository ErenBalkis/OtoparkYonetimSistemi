#include "Otopark.h"
#include "AracTurleri.h"
#include <iostream>
#include <fstream>
#include "ParkYeri.h"
#include <stdexcept>  //exception için

//Yapıcı metot (nesne ilk oluştuğunda çalışır)
Otopark::Otopark(std::string ad, int kapasite) : otoparkAdi(ad) {
    for (int i = 1; i<=kapasite; ++i) {
        //her 20 araçta bir kat artışı
        int kat = (i <=20) ? 1 : 2;
        parkYerleri.push_back(ParkYeri(i, kat));
    }
}

//Yıkıcı metot (belleği temizleyecek)








//Dosya yazma işlemi
void Otopark::verileriKaydet() {
    // fstream kullanarak dosya akışı açıyoruz
    std::ofstream dosya("ParkYerleri.txt");
    
    try {
        if (!dosya.is_open()) {
            // Hata fırlatma (Exception Handling)
            throw std::runtime_error("Dosya yazma hatasi: ParkYerleri.txt acilamadi!");
        }

        // Park yerlerini tek tek dönüp dosyaya yazıyoruz
        for (const ParkYeri& yer : parkYerleri) {
            dosya << yer.getKat() << " " 
                  << yer.getId() << " " 
                  << yer.isDolu() << "\n";
        }

        dosya.close();
        std::cout << "Otopark yer bilgileri basariyla kaydedildi.\n";
    }
    catch (const std::exception& e) {
        
        std::cerr << "KRITIK HATA: " << e.what() << "\n";
    }
}

// Verileri Yükleme (ParkYerleri.txt)
void Otopark::verileriYukle() {
    std::ifstream dosya("ParkYerleri.txt");
    
    // Eğer dosya henüz yoksa döngüye girme
    if (!dosya.is_open()) return;

    int kat, id;
    bool dolu;
    int index = 0;

    // Dosyadan satır satır verileri oku
    while (dosya >> kat >> id >> dolu && index < (int)parkYerleri.size()) {
        parkYerleri[index].setDurum(dolu);
        index++;
    }

    dosya.close();
    std::cout << "Veriler dosyadan geri yuklendi.\n";
}