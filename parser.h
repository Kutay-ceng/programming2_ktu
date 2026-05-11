/* * Ad Soyad: Kutay Keleş, Ahmet Taha Dinç
 * Öğrenci No: 434318, 434343
 * Dosya: parser.h
 * Görev: Metin ayrıştırma (parsing) ve dinamik bellek (bağlı liste) yönetimi için gerekli yapıların ve fonksiyon prototiplerinin tanımlanması.
 */

#ifndef PARSER_H
#define PARSER_H

// --- VERİ YAPILARI (STRUCTS) ---

// Ödevde istenen ve her bir komutun tüm detaylarını taşıyan ana veri yapısı (Kargo Kutusu)
typedef struct {
    char command[20];   // Komutun adı (Örn: "GCD", "PHI", "POW")
    long long args[4];  // Komutun işleyeceği sayılar (Argümanlar)
    int arg_count;      // Okunan argüman adedi (Örn: GCD için 2, POW için 3)
    char result[100];   // İşlem sonucunun veya hata mesajının yazılacağı metin alanı
    int is_error;       // Hata durumunu tutan bayrak (0: İşlem başarılı, 1: Hata var)
} CommandRecord;

// Dinamik Bellek (Bağlı Liste) için Düğüm (Node / Vagon) yapısı
typedef struct CommandNode {
    CommandRecord data;           // Düğümün içinde taşınan asıl veri (Kargo)
    struct CommandNode *next;     // Trenin bir sonraki vagonunu gösteren kanca (Pointer)
} CommandNode;


// --- FONKSİYON PROTOTİPLERİ ---

// Hafızada (RAM) içi boş, yepyeni bir düğüm oluşturur ve adresini döndürür.
CommandNode* yeni_dugum_uret();

// İçi doldurulan düğümü, bağlı listenin (trenin) en sonuna güvenli bir şekilde ekler.
void duguma_ekle(CommandNode** ilk_dugum, CommandNode* eklenecek_dugum);

// strtok ile makaslanmış metni cımbızlayıp (sscanf) CommandRecord kutusuna yerleştirir.
void komutu_ayristir(char* okunan_metin, CommandRecord* kargo_kutusu);

#endif // PARSER_H