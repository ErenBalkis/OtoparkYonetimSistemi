#ifndef OTOPARK_H
#define OTOPARK_H

#include <vector>
#include <string>
#include "Arac.h"
#include "ParkYeri.h"

class Otopark {
private:
    std::string otoparkAdi;
    std::vector<ParkYeri> parkYerleri; // Otopark "has-a" ParkYeri (Bileşim)
    std::vector<Arac*> aktifAraclar;   // Şu an içerideki araçlar (Polimorfizm için pointer şart)
    
    // Geçmiş kayıtları tutmak istersen (Bonus puan için raporlama):
    // std::vector<std::string> gecmisIslemler; 

public:
    Otopark(std::string ad, int kapasite);
    ~Otopark(); // Destructor'da new ile oluşturulan araçları silmeliyiz!

    // Temel İşlevler
    void aracGiris(Arac* yeniArac);
    void aracCikis(std::string plaka);
    void bosYerleriListele() const;
    void durumRaporu() const; // Bonus puan için rapor [cite: 96]
    
    // Dosya İşlemleri [cite: 61]
    void verileriKaydet();
    void verileriYukle();

    // Yardımcılar
    int bosParkYeriBul(); // İlk boş yerin indexini döner
};

#endif // OTOPARK_H