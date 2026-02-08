# 🚗 Otopark Yönetim Sistemi

Bu proje, C++17 standartları kullanılarak geliştirilmiş, Nesne Yönelimli Programlama (OOP) prensiplerine dayalı bir otopark otomasyon sistemidir. Sistem; araç giriş-çıkışlarını yönetir, araç türüne göre dinamik ücret hesaplar ve verileri dosya sisteminde kalıcı olarak saklar.

## 📸 Ekran Görüntüleri

Aşağıda uygulamanın çalışma anına ait ekran görüntüleri yer almaktadır:

### 1. Ana Menü ve Durum Paneli
![Ana Menü Görünümü](https://github.com/ErenBalkis/OtoparkYonetimSistemi/blob/main/screenshots/terminal-1.png)

<br>

### 2. Araç Giriş/Çıkış İşlemleri
![İşlem Ekranı Görünümü](https://github.com/ErenBalkis/OtoparkYonetimSistemi/blob/main/screenshots/terminal-2.png)

---

## ✨ Özellikler

* **Nesne Yönelimli Mimari:** Kalıtım (Inheritance) ve Çok Biçimlilik (Polymorphism) yapıları (`Arac` -> `Otomobil`, `Kamyonet`, `Motosiklet`).
* **Modern Bellek Yönetimi:** Bellek sızıntılarını önlemek için `std::unique_ptr` (Smart Pointers) kullanımı.
* **Veri Kalıcılığı:**
    * Program kapandığında araçlar `otopark_data.csv` dosyasına kaydedilir.
    * Açılışta veriler otomatik olarak geri yüklenir.
* **Loglama Sistemi:** Çıkış yapan araçların geçmişi ve ücret bilgileri `otopark_log.txt` dosyasına kaydedilir.
* **Hata Yönetimi:** Kullanıcıdan alınan hatalı girişler (örn: sayı yerine harf girilmesi) `cin.clear()` mekanizmasıyla yönetilir.

## 💰 Ücret Tarifesi

Sistemde her araç türü için farklı bir fiyatlandırma politikası uygulanır:

| Araç Türü | Baz Ücret (İlk 1 Saat) | Saatlik Ek Ücret |
| :--- | :--- | :--- |
| **Otomobil** | 50.00 TL | +10.00 TL/saat |
| **Kamyonet** | 80.00 TL | +15.00 TL/saat |
| **Motosiklet** | 30.00 TL | +5.00 TL/saat |

## 🛠️ Kurulum ve Derleme

Bu projeyi bilgisayarınızda çalıştırmak için:

1.  **Projeyi Klonlayın:**
    ```bash
    git clone [https://github.com/ErenBalkis/OtoparkYonetimSistemi.git](https://github.com/ErenBalkis/OtoparkYonetimSistemi.git)
    cd OtoparkYonetimSistemi
    ```

2.  **Derleme (Terminal):**
    Proje birden fazla modülden oluştuğu için tüm `.cpp` dosyalarını birlikte derlemelisiniz:
    ```bash
    g++ main.cpp Otopark.cpp Arac.cpp AracTurleri.cpp ParkYeri.cpp -o otopark -std=c++17
    ```

3.  **Çalıştırma:**
    ```bash
    ./otopark
    ```
    *(Windows kullanıyorsanız `otopark.exe`)*

## 📂 Dosya Yapısı

* `main.cpp`: Uygulamanın giriş noktası ve menü döngüsü.
* `Otopark.cpp / .h`: Otopark mantığını (park etme, boş yer bulma, dosya okuma/yazma) yöneten sınıf.
* `Arac.cpp / .h`: Tüm araç türleri için temel (base) sınıf.
* `AracTurleri.cpp / .h`: Özelleştirilmiş araç sınıfları (Otomobil, Kamyonet vb.).
* `ParkYeri.cpp / .h`: Tekil park alanının durumunu yöneten sınıf.

## 🤝 Katkıda Bulunma

Hata bildirmek veya özellik eklemek isterseniz "Pull Request" göndermekten çekinmeyin!

---
*Geliştiriciler: Eren Balkış, Yusuf Diler, Nurcan Sungur, Özkan Tunç Özdamar*
