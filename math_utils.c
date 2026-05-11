/* * Ad Soyad: Kutay Keleş, Ahmet Taha Dinç
 * Öğrenci No: 434318, 434343
 * Dosya: math_utils.c
 * Görev: Matematiksel hesaplamalar için fonksiyonların implementasyonu.
 */

#include "math_utils.h"
 
// --- 1. PHI (Euler Totient) Fonksiyonu ---
// Bir sayıya kadar olan ve o sayıyla aralarında asal olan sayıların adedini bulur.
long long hesapla_phi(long long n) {
    if (n < 1) {
        return ERROR_INVALID_INPUT;
    }

    long long sonuc = n;

    // Sayıyı asal çarpanlarına ayırarak ilerliyoruz
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sonuc = sonuc - (sonuc / i); // Formül: sonuc *= (1 - 1/p)
            
            // Aynı asal çarpandan kalanları temizle
            while (n % i == 0) {
                n = n / i;
            }
        }
    }

    // Eğer n'nin kendisi de 1'den büyük bir asalsa, onu da işleme dahil et
    if (n > 1) {
        sonuc = sonuc - (sonuc / n);
    }

    return sonuc;
}

// --- 2. GCD (En Büyük Ortak Bölen) Fonksiyonu ---
// Öklid Algoritması kullanarak EBOB hesaplar.
long long hesapla_gcd(long long a, long long b) {
    // Sayılar negatif veya sıfır ise işlemi reddediyoruz
    if (a <= 0 || b <= 0) {
        return ERROR_INVALID_INPUT;
    }
    
    // b sıfır olana kadar bölümden kalanları alarak ilerle
    while (b != 0) {
        long long gecici = b; 
        b = a % b;            
        a = gecici;           
    }
    
    return a; // Kalan son sayı EBOB'dur
}

// --- 3. PRIME (Asallık Testi) Fonksiyonu ---
// O(sqrt(N)) zaman karmaşıklığı ile sayının asal olup olmadığını kontrol eder.
int asallık_testi(long long n) {
    if (n <= 1) {
        return ERROR_INVALID_INPUT;
    }
    if (n == 2 || n == 3) {
        return 1; // 2 ve 3 asaldır
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return 0; // Çift sayılar ve 3'ün katlarını baştan ele
    }
    
    // Optimizasyon: Sadece 6k-1 ve 6k+1 formundaki sayıları kontrol et
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0;
        }
    }
    
    return 1; // Hiçbir sayıya bölünmediyse asaldır
}

// --- 4. POW (İkili Üs Alma / Binary Exponentiation) Fonksiyonu ---
// Zaman aşımını (Time Limit) önlemek için logaritmik sürede modlu üs alır.
long long hesapla_pow(long long taban, long long us, long long mod) {
    if (taban < 0 || us < 0 || mod <= 0) {
        return ERROR_INVALID_INPUT;
    }
    
    long long sonuc = 1;
    taban = taban % mod; // Başlangıçta tabanın modunu alarak taşmayı önle

    // Üssü ikiye bölerek ilerliyoruz
    while (us > 0) {
        if (us % 2 == 1) { // Üs tek sayıysa tabanla çarp
            sonuc = (sonuc * taban) % mod;
        }
        us = us / 2; // Üssü yarıya indir
        taban = (taban * taban) % mod; // Tabanın karesini al
    }

    return sonuc;
}

// --- 5. INV (Modüler Ters) Fonksiyonu ---
// Genişletilmiş Öklid Algoritması (Extended Euclidean) ile modüler ters bulur.
long long hesapla_inverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

    if (m == 1) return 0;
    
    // Algoritma döngüsü
    while (a > 1) {
        if (m == 0) return -2; // Aralarında asal değilse tersi yoktur (Hata)
        
        q = a / m;
        t = m;
        
        m = a % m;
        a = t;
        t = x0;
        
        x0 = x1 - q * x0;
        x1 = t;
    }
    
    // Eğer GCD 1 çıkmadıysa, modüler tersi alınamaz
    if (a != 1) return -2;
    
    // Sonuç negatifse, pozitife çevirmek için mod değeri ekle
    if (x1 < 0) x1 += m0;

    return x1;
}