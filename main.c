/* * Ad Soyad: Kutay Keleş, Ahmet Taha Dinç
 * Öğrenci No: 434318, 434343
 * Dosya: main.c
 * Görev: Komut satırı argümanlarının kontrolü, dosya okuma/yazma işlemleri ve ana program akışı.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "math_utils.h"
#include <ctype.h>

int main(int argc, char *argv[]) {
    
    // --- 1. ARGÜMAN KONTROLÜ ---
    // Programın doğru argüman sayısıyla çağrılıp çağrılmadığını kontrol et
    if (argc != 3) {
        printf("Hatali kullanim! Lutfen su formatta calistirin: ./numtool <giris_dosyasi> <cikis_dosyasi>\n");
        return 1; 
    }

    // --- 2. DOSYA OKUMA VE BAĞLI LİSTE OLUŞTURMA ---
    FILE *giris_dosyasi = fopen(argv[1], "r");
    if (giris_dosyasi == NULL) {
        printf("Hata: %s dosyasi bulunamadi veya acilamadi!\n", argv[1]);
        return 1;
    }

    CommandNode *ilk_dugum = NULL; // Bağlı listenin (Linked List) başlangıç düğümü
    char satir[256]; 
    
    // Dosyayı satır satır sonuna kadar oku
    while (fgets(satir, sizeof(satir), giris_dosyasi) != NULL) {
        
        // '#' karakteri ile başlayan yorum satırlarını atla
        char *p = satir;

        while (*p != '\0' && isspace((unsigned char)*p)) {
            p++;
        }

        if (*p == '#' || *p == '\0') {
            continue;
        }

        // Aynı satırdaki komutları noktalı virgül (;) ve alt satır (\n) karakterine göre böl
        char *parca = strtok(satir, ";\n"); 
        
        while (parca != NULL) {
            // Yeni bir düğüm için bellek tahsis et
            CommandNode *yeni_islem = yeni_dugum_uret();
            
            // Ayrıştırılan komutu ve argümanları düğümün veri yapısına kaydet
            komutu_ayristir(parca, &(yeni_islem->data));
            
            // Düğümü bağlı listenin sonuna ekle
            duguma_ekle(&ilk_dugum, yeni_islem);
            
            // Satırdaki bir sonraki komuta geç
            parca = strtok(NULL, ";\n");
        }
    }
    
    fclose(giris_dosyasi);
    printf("Dosya basariyla okundu ve listeye eklendi!\n");


    // --- 3. KOMUTLARI İŞLEME VE ÇIKTI DOSYASINA YAZMA ---
    FILE *cikis_dosyasi = fopen(argv[2], "w");
    if (cikis_dosyasi == NULL) {
        printf("Hata: Cikti dosyasi olusturulamadi!\n");
        return 1;
    }

    CommandNode *islem_dugumu = ilk_dugum;

    // Bağlı listeyi baştan sona dolaşarak her bir komutu işlet
    while (islem_dugumu != NULL) {
        if (islem_dugumu->data.is_error == 1) {
            fprintf(cikis_dosyasi, "%s -> %s\n",
                    islem_dugumu->data.command,
                    islem_dugumu->data.result);

            islem_dugumu = islem_dugumu->next;
            continue;
        }
        
        // --- PHI KOMUTU ---
        if (strcmp(islem_dugumu->data.command, "PHI") == 0) {
            long long sayi = islem_dugumu->data.args[0];
            long long sonuc = hesapla_phi(sayi); 
            
            if (sonuc == ERROR_INVALID_INPUT) { 
                islem_dugumu->data.is_error = 1;
                strcpy(islem_dugumu->data.result, "ERROR_INVALID_INPUT");
            } else {
                sprintf(islem_dugumu->data.result, "%lld", sonuc);
            }
            fprintf(cikis_dosyasi, "%s %lld -> %s\n", islem_dugumu->data.command, sayi, islem_dugumu->data.result);
        } 
        // --- GCD KOMUTU ---
        else if (strcmp(islem_dugumu->data.command, "GCD") == 0) {
            long long sayi1 = islem_dugumu->data.args[0];
            long long sayi2 = islem_dugumu->data.args[1];
            long long sonuc = hesapla_gcd(sayi1, sayi2);
            
            if (sonuc == ERROR_INVALID_INPUT) {
                islem_dugumu->data.is_error = 1;
                strcpy(islem_dugumu->data.result, "ERROR_INVALID_INPUT");
            } else {
                sprintf(islem_dugumu->data.result, "%lld", sonuc);
            }
            fprintf(cikis_dosyasi, "%s %lld %lld -> %s\n", islem_dugumu->data.command, sayi1, sayi2, islem_dugumu->data.result);
        } 
        // --- PRIME KOMUTU ---
        else if (strcmp(islem_dugumu->data.command, "PRIME") == 0) {
            long long sayi = islem_dugumu->data.args[0]; 
            int sonuc = asallık_testi(sayi);               
            
            if (sonuc == ERROR_INVALID_INPUT) {
                islem_dugumu->data.is_error = 1;
                strcpy(islem_dugumu->data.result, "ERROR_INVALID_INPUT");
            } else if (sonuc == 1) {
                strcpy(islem_dugumu->data.result, "YES"); 
            } else {
                strcpy(islem_dugumu->data.result, "NO");  
            }
            fprintf(cikis_dosyasi, "%s %lld -> %s\n", islem_dugumu->data.command, sayi, islem_dugumu->data.result);
        }
        // --- POW KOMUTU ---
        else if (strcmp(islem_dugumu->data.command, "POW") == 0) {
            long long t = islem_dugumu->data.args[0];
            long long u = islem_dugumu->data.args[1];
            long long m = islem_dugumu->data.args[2];
            long long sonuc = hesapla_pow(t, u, m);
            
            if (sonuc == ERROR_INVALID_INPUT) {
                islem_dugumu->data.is_error = 1;
                strcpy(islem_dugumu->data.result, "ERROR_INVALID_INPUT");
            } else {
                sprintf(islem_dugumu->data.result, "%lld", sonuc);
            }
            fprintf(cikis_dosyasi, "%s %lld %lld %lld -> %s\n", islem_dugumu->data.command, t, u, m, islem_dugumu->data.result);
        }
        // --- INV KOMUTU ---
        else if (strcmp(islem_dugumu->data.command, "INV") == 0) {
            long long a = islem_dugumu->data.args[0];
            long long m = islem_dugumu->data.args[1];
            long long sonuc = hesapla_inverse(a, m);

            if (sonuc == -2) {
                strcpy(islem_dugumu->data.result, "ERROR_NO_INVERSE");
            } else {
                sprintf(islem_dugumu->data.result, "%lld", sonuc);
            }
            fprintf(cikis_dosyasi, "INV %lld %lld -> %s\n", a, m, islem_dugumu->data.result);
        }
        // --- CHECK KOMUTU ---
        else if (strcmp(islem_dugumu->data.command, "CHECK") == 0) {
            long long a = islem_dugumu->data.args[0];
            long long m = islem_dugumu->data.args[1];
            long long ters = hesapla_inverse(a, m);

            if (ters == -2) {
                strcpy(islem_dugumu->data.result, "ERROR_NO_INVERSE");
            } else {
                if ((a * ters) % m == 1) {
                    strcpy(islem_dugumu->data.result, "CORRECT");
                } else {
                    strcpy(islem_dugumu->data.result, "FAILED");
                }
            }
            fprintf(cikis_dosyasi, "CHECK %lld %lld -> %s\n", a, m, islem_dugumu->data.result);
        }

        // Bir sonraki düğüme geç
        islem_dugumu = islem_dugumu->next;
    }

    fclose(cikis_dosyasi); 


    // --- 4. BELLEK YÖNETİMİ (MEMORY CLEANUP) ---
    // Dinamik olarak ayrılan bellek alanlarını sisteme iade et
    CommandNode *silinecek_dugum = ilk_dugum;
    
    while (silinecek_dugum != NULL) {
        // Mevcut düğümü silmeden önce sonrakinin adresini yedekle
        CommandNode *siradaki = silinecek_dugum->next; 
        free(silinecek_dugum); 
        silinecek_dugum = siradaki; 
    }

    printf("Islemler basariyla tamamlandi. %s dosyasini kontrol edebilirsiniz!\n", argv[2]);

    return 0; 
}
