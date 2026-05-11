# * Ad Soyad: Kutay Keleş Ahmet Taha Dinç
# * Öğrenci No: 434318 434343
# * Dosya: Makefile
# * Görev: Derleme ve derleme süreçlerini yönetme.


# Derleyici olarak GCC kullanıyoruz
CC = gcc

# Derleme bayrakları (Uyarıları göster, standartları belirle)
CFLAGS = -Wall -Wextra -std=c99

# Üretilecek programın adı (Ödevde "numtool" olması istenmiş)
TARGET = numtool

# Birleştirilecek olan obje dosyaları (.c'lerin derlenmiş hali)
OBJS = main.o parser.o math_utils.o

# Terminale sadece "make" yazıldığında çalışacak ana hedef
all: $(TARGET)

# numtool programının nasıl üretileceğini tarif ediyoruz
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# main.c'nin derlenmesi
main.o: main.c parser.h math_utils.h
	$(CC) $(CFLAGS) -c main.c

# parser.c'nin derlenmesi
parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

# math_utils.c'nin derlenmesi
math_utils.o: math_utils.c math_utils.h
	$(CC) $(CFLAGS) -c math_utils.c

# "make clean" yazıldığında oluşan çöpleri (.o dosyalarını ve programı) siler
clean:
	rm -f $(OBJS) $(TARGET)