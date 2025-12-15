#ifndef PARKYERI_H
#define PARKYERI_H

class ParkYeri {
private:
    int id;
    int kat;
    bool doluMu;
    // İstersen burada park eden aracın plakasını da tutabilirsin
    
public:
    ParkYeri(int id, int kat);

    bool isDolu() const;
    void setDurum(bool durum);
    int getId() const;
    int getKat() const;
};

#endif // PARKYERI_H