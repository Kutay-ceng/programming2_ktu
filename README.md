# NumTool - Sayı Teorisi Hesaplama Aracı 🧮

Bu proje, C programlama dili ile geliştirilmiş komut tabanlı bir sayı teorisi hesaplama aracıdır. Girdi olarak verilen bir metin dosyasındaki matematiksel komutları ayrıştırır (parsing), dinamik bellek üzerinde (Linked List) saklar ve optimize edilmiş algoritmalarla sonuçları bir çıktı dosyasına yazar.

## 🚀 Özellikler

* **Modüler Mimari:** Proje `main.c`, `parser.c`, `math_utils.c` modüllerine ayrılmış ve bir `Makefile` ile otomatik derlenecek şekilde tasarlanmıştır.
* **Dinamik Bellek Yönetimi:** Sabit boyutlu diziler (static arrays) kullanılmamış; komutlar ve argümanlar çalışma zamanında oluşturulan **Bağlı Liste (Linked List)** yapısında tutulmuştur. İşlem bitiminde `free()` ile bellek sızıntıları (memory leak) önlenmiştir.
* **Gelişmiş Metin Ayrıştırma:** Özel bir parser (ayrıştırıcı) ile dosya okuma (`fgets`), yorum satırlarını atlama, noktalı virgüllere göre komutları bölme (`strtok`) ve parametreleri ayıklama (`sscanf`) işlemleri gerçekleştirilmiştir.
* **Standart Kütüphane Bağımsızlığı:** Hiçbir matematiksel hesaplama için `<math.h>` kütüphanesi kullanılmamış, tüm algoritmalar sıfırdan implemente edilmiştir.

## 🧠 Desteklenen Algoritmalar ve Optimizasyonlar

Program, büyük veri setlerinde zaman aşımını (Time Limit) önlemek amacıyla aşağıdaki zaman karmaşıklıklarında (Time Complexity) çalışan algoritmalar içerir:

1. **GCD (En Büyük Ortak Bölen):** Öklid Algoritması kullanılarak $O(\log(\min(a,b)))$ sürede hesaplanır.
2. **POW (Modüler Üs Alma):** İkili Üs Alma (Binary Exponentiation) yöntemiyle, döngülü çarpım yerine $O(\log N)$ sürede hesaplanıp taşmalar (overflow) önlenir.
3. **PRIME (Asallık Testi):** Sayıların $6k-1$ ve $6k+1$ formunda olduğu gerçeğinden yola çıkılarak $O(\sqrt{N})$ zaman karmaşıklığında optimize edilmiştir.
4. **INV (Modüler Ters):** Genişletilmiş Öklid Algoritması (Extended Euclidean) ile modüler ters hesaplanır.
5. **PHI (Euler Totient):** Tam sayı bölmesi kullanılarak hassasiyet kaybı olmadan, asal çarpanlara ayırma yöntemiyle $O(\sqrt{N})$ sürede hesaplanır.
6. **CHECK:** Bulunan modüler tersin doğruluğunu $(A \times Ters) \pmod M == 1$ denklemi ile test eder.

## 🛠️ Kurulum ve Kullanım

Projeyi kendi bilgisayarınızda çalıştırmak için aşağıdaki adımları izleyin:

**1. Repoyu Klonlayın:**
```bash
git clone [https://github.com/KULLANICI_ADIN/NumTool-C-Project.git](https://github.com/KULLANICI_ADIN/NumTool-C-Project.git)
cd NumTool-C-Project

Proje dosyalarını manuel derlemenize gerek yoktur. Terminalde sadece make komutunu çalıştırarak numtool isimli programı üretebilirsiniz.
make
Program bir girdi ve bir çıktı dosyası parametresi ile çalışır. (Örnek input.txt repoda mevcuttur).
./numtool input.txt output.txt


# Yorum satırları atlanır
GCD 48 18; POW 2 10 1000
PRIME 29
INV 3 11; PHI 36
CHECK 1234567 1000000007
