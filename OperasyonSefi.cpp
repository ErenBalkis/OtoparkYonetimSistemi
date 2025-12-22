#include "Otopark.h"
#include <iostream>
#include <ctime>

using namespace std;

/* constructor */
Otopark::Otopark(string ad, int kapasite)
    : otoparkAdi(ad)
{
    // Kapasite kadar park yeri oluştur
    for (int i = 0; i < kapasite; i++) {
        parkYerleri.emplace_back(i + 1, 1); // kat = 1 (istersen artırılabilir)
    }
}

/* desturctor kismi */
Otopark::~Otopark() {
    // İçeride kalan araçları bellekten temizle
    for (Arac* arac : aktifAraclar) {
        delete arac;
    }
    aktifAraclar.clear();
}

/* boş park yeri */
int Otopark::bosParkYeriBul() {
    for (int i = 0; i < parkYerleri.size(); i++) {
        if (!parkYerleri[i].isDolu())
            return i;
    }
    return -1; // boş yer yok
}

/* araç girişi */
void Otopark::aracGiris(Arac* yeniArac) {
    int index = bosParkYeriBul();

    if (index == -1) {
        cout << "Otopark dolu! Arac alinamadi.\n";
        delete yeniArac; // bellek sızıntısı önleme
        return;
    }

    parkYerleri[index].setDurum(true);
    aktifAraclar.push_back(yeniArac);

    cout << "Arac girisi yapildi.\n";
    cout << "Plaka: " << yeniArac->getPlaka() << endl;
    cout << "Tur: " << yeniArac->getTur() << endl;
    cout << "Park Yeri ID: " << parkYerleri[index].getId() << endl;
}

/* araç çıkışı */
void Otopark::aracCikis(string plaka) {
    for (int i = 0; i < aktifAraclar.size(); i++) {
        if (aktifAraclar[i]->getPlaka() == plaka) {

            // Çıkış saatini ayarla
            aktifAraclar[i]->setCikisSaati(time(nullptr));

            // Ücret POLİMORFİK olarak hesaplanır
            double ucret = aktifAraclar[i]->hesaplaUcret();

            cout << "Arac cikisi yapildi.\n";
            aktifAraclar[i]->bilgileriYazdir();
            cout << "Odenecek Ucret: " << ucret << " TL\n";

            // Park yerini boşalt
            parkYerleri[i].setDurum(false);

            // Bellekten sil
            delete aktifAraclar[i];
            aktifAraclar.erase(aktifAraclar.begin() + i);

            return;
        }
    }

    cout << "Bu plakaya ait arac bulunamadi.\n";
}

/* boş yerler */
void Otopark::bosYerleriListele() const {
    cout << "--- Bos Park Yerleri ---\n";
    for (const auto& p : parkYerleri) {
        if (!p.isDolu()) {
            cout << "Park Yeri ID: " << p.getId()
                 << " | Kat: " << p.getKat() << endl;
        }
    }
}

/* otopark durumunu sorgulama */
void Otopark::durumRaporu() const {
    cout << "\n--- OTOPARK DURUM RAPORU ---\n";
    cout << "Otopark Adi: " << otoparkAdi << endl;
    cout << "Toplam Park Yeri: " << parkYerleri.size() << endl;
    cout << "Dolu Park Yeri: " << aktifAraclar.size() << endl;
    cout << "Bos Park Yeri: "
         << parkYerleri.size() - aktifAraclar.size() << endl;
}

-