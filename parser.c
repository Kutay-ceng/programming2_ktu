/*
 * Ad Soyad : Kutay Keleş, Ahmet Taha Dinç
 * Öğrenci No : 434318, 434343
 * Dosya : parser.c
 * Görev: Metin ayrıştırma (parsing) ve dinamik bellek (bağlı liste) yönetimi.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

// --- 1. HAFIZA ŞUBESI ---

// Yeni bir hafıza düğümü oluşturan fonksiyon
CommandNode* yeni_dugum_uret() {
    // malloc ile sistemden 1 düğümlük bellek istiyoruz
    CommandNode* yeni_kayit = (CommandNode*)malloc(sizeof(CommandNode));
    
    // Eğer bilgisayar bize başarıyla yer ayırdıysa:
    if (yeni_kayit != NULL) {
        yeni_kayit->data.arg_count = 0;   // İçindeki sayacı sıfırla
        yeni_kayit->data.is_error = 0;    // Başlangıçta hata yok (0)
        yeni_kayit->next = NULL;          // Arkasına henüz başka düğüm takılmadı.
    }
    
    return yeni_kayit; // Üretilen düğümü teslim et
}

// Üretilen düğümü listenin en sonuna ekleyen fonksiyon
void duguma_ekle(CommandNode** ilk_dugum, CommandNode* eklenecek_dugum) {
    // Eğer ortada hiç liste yoksa, bu düğüm listenin ilk düğümü olur
    if (*ilk_dugum == NULL) {
        *ilk_dugum = eklenecek_dugum;
        return;
    }

    // Önceden bir düğüm varsa, en son düğümü bulana kadar ilerle
    CommandNode* gecici_dugum = *ilk_dugum;
    while (gecici_dugum->next != NULL) {
        gecici_dugum = gecici_dugum->next;
    }
    
    // Son düğümü bulduk, yeni düğümü onun kancasına takıyoruz
    gecici_dugum->next = eklenecek_dugum;
}


// --- 2.METİN AYRIŞTIRMA ---

// strtok ile kesilmiş tek bir metin parçasını (örn: "GCD 48 18") ayıklar
void komutu_ayristir(char* okunan_metin, CommandRecord* kargo_kutusu) {
    char gecici_komut[20];
    long long sayi1, sayi2, sayi3;

    // sscanf: Metnin içindeki ilk kelimeyi çeker.
    int eslesme = sscanf(okunan_metin, "%s", gecici_komut);
    if (eslesme <= 0) return; // Eğer okuyamazsa işlemi iptal et

    // Yakaladığımız kelimeyi, kutumuzun komut etiketine kopyalıyoruz
    strcpy(kargo_kutusu->command, gecici_komut);

    // Hangi komut olduğuna bakıp, sayıları ona göre cımbızlıyoruz
    if (strcmp(gecici_komut, "PHI") == 0 || strcmp(gecici_komut, "PRIME") == 0) {
        // %*s komut adını atlar, %lld ilk sayıyı çeker
        sscanf(okunan_metin, "%*s %lld", &sayi1); 
        kargo_kutusu->args[0] = sayi1;
        kargo_kutusu->arg_count = 1; // Çantaya 1 sayı koyduk
    } 
    else if (strcmp(gecici_komut, "GCD") == 0 || strcmp(gecici_komut, "INV") == 0 || strcmp(gecici_komut, "CHECK") == 0) {
        // İki sayı bekleyen komutlar
        sscanf(okunan_metin, "%*s %lld %lld", &sayi1, &sayi2);
        kargo_kutusu->args[0] = sayi1;
        kargo_kutusu->args[1] = sayi2;
        kargo_kutusu->arg_count = 2; // Çantaya 2 sayı koyduk
    } 
    else if (strcmp(gecici_komut, "POW") == 0) {
        // Üç sayı bekleyen komut 
        sscanf(okunan_metin, "%*s %lld %lld %lld", &sayi1, &sayi2, &sayi3);
        kargo_kutusu->args[0] = sayi1;
        kargo_kutusu->args[1] = sayi2;
        kargo_kutusu->args[2] = sayi3;
        kargo_kutusu->arg_count = 3; // Çantaya 3 sayı koyduk
    }
}