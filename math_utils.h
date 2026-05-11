/* * Ad Soyad: Kutay Keleş, Ahmet Taha Dinç
 * Öğrenci No: 434318, 434343
 * Dosya: math_utils.h
 * Görev: Matematiksel hesaplamalar için sabitlerin ve fonksiyon prototiplerinin tanımlanması.
 */

#ifndef MATH_UTILS_H
#define MATH_UTILS_H

// --- HATA KODLARI ---
// Genel geçersiz giriş (negatif sayı, sıfıra bölme vb.) durumunda döndürülen hata
#define ERROR_INVALID_INPUT -1

// --- FONKSİYON PROTOTİPLERİ ---

// Euler Totient (PHI) hesaplaması
long long hesapla_phi(long long n);

// Öklid Algoritması ile En Büyük Ortak Bölen (EBOB/GCD) hesaplaması
long long hesapla_gcd(long long a, long long b);

// O(sqrt(N)) karmaşıklığı ile asallık testi (Asal ise 1, değilse 0 döner)
int asallık_testi(long long n);

// İkili Üs Alma (Binary Exponentiation) ile (taban^us % mod) hesaplaması
long long hesapla_pow(long long taban, long long us, long long mod);

// Genişletilmiş Öklid Algoritması ile Modüler Ters (INV) hesaplaması (Ters yoksa -2 döner)
long long hesapla_inverse(long long a, long long m);

#endif // MATH_UTILS_H