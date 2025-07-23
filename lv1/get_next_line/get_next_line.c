#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return (i);
}
char    *ft_strjoin(char *s1, char *s2)
{
    if (!s1) // ft_strchr'deki bahsettigim durumun aynisi, fonksiyon ilk calistiginda buffer NULL olarak geleceginden ve NULL bir degere atama yaparsan segfault yigeceginden dolayi
    {
        s1 = malloc(1); // Burada s1'e 1 bytelik yer ac
        if (!s1) // Malloc hata kontrolu
            return (NULL);
        s1[0] = '\0'; // Ve s1'in icine malloc ile NULL at ki artik bu stringin uzerine atama yapabilirsin
    }
    if (!s2)
        return (NULL);
    char    *temp = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!temp)
        return (NULL);
    int i = 0;
    int j = 0;
    while (s1[i])
    {
        temp[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        temp[i + j] = s2[j];
        j++;
    }
    temp[i + j] = '\0';
    free(s1);
    return (temp);
}
int ft_strchr(char *s, char a)
{
    int i = 0;
    if (!s) // Bu kosul ozellikle sen fonksiyonu ilk baslattiginda buffer'in read'e ilk defa geldiginde NULL olarak gelecek, ft_read'deki while dongusune girmesi icin bu kosul sart
        return (0);
    while (s[i])
    {
        if (s[i] == a)
            return (1);
        i++;
    }
    return (0);
}
char    *after_newline(char *str)
{
    int i = 0;
    if (!str) // Bu direkt stringin olmadigi durum klasik programlardaki null kontrolu
        return (NULL);
    if (!str[i]) // Bu durum normal degiskenin var ama degiskenin sadece '\0'ise stringini freele ve cik durumu
        return (free(str) , NULL);
    while (str[i] != '\n' && str[i]) // Newline veya null olana kadar ilerle
        i++;
    if (str[i] == '\n') // Newline varsa +1 ekle
        i++;
    char    *temp = malloc(ft_strlen(str) - i + 1); // Buradaki hesap newline'a kadar zaten hesapladin, stringden bu kismi cikartirsan newlineden sonrasi yani senin bu fonksiyonda istedigin kismin uzunlugunu elde edersin, +1 klasik zaten
    if (!temp) // Klasik malloc hata kontrolu
        return (NULL);
    int j = 0; // Temp'yi bastan teker teker kaydetmek icin j diye bir index gezmek icin degisken olustur
    while (str[i]) // Stringin geri kalan kisminin sonuna kadar
        temp[j++] = str[i++]; // Stringin her elemanini temp degiskenine at
    temp[j] = '\0'; // Temp degiskeninin sonuna NULL at
    free(str); // Artik buraya gonderdigin buffer degiskeniyle isin kalmadigi icin onceden buffer icin actigin yeri freele
    return (temp); // Bufferini yani line den sonra, fonksiyondan sonra kalmasini istedigin kismi dondur
}
char    *before_newline(char *str)
{
    int i = 0; // Index icin olusturulan degisken
    if (!str || !str[i]) // Eger stringin yoksa veya stringinin ilk elemani yoksa
        return (NULL);
    while (str[i] != '\n' && str[i]) // Stringinde '\n' ve stringinin i'inci indexi null olmayana kadar ilerle
        i++;
    if (str[i] == '\n') // Eger ulastigin index '\n' ise 1 daha arttir
        i++;
    char    *temp = malloc(i + 1); // Uzunlugunu hesapladigin string zaten almak istedigin string oldugu icin gecici bir degiskene hesapladigin degiskeninin boyutu kadar yer ac
    if (!temp) // Malloc hata durumu kontrolu
        return (NULL);
    i = 0; // Stringini bastan almak icin indexini 0'la
    while (str[i] != '\n' && str[i]) // Yukardaki kosulla ayni newline veya null olana kadar
    {
        temp[i] = str[i]; // Gordugun stringin her elemanini gecici degiskenine at
        i++; // Ve arttir
    }
    if (str[i] == '\n') // Eger stringinin sonu newline ise
        temp[i++] = '\n'; // Stringinin sonuna newline ekle ardindan NULL ekle
    temp[i] = '\0'; // Stringinin sonuna NULL ekle
    return (temp);
}
char    *ft_read(char *buffer, int fd)
{
    int size = 1; // Asagidaki while dongusune girmesi icin size'i ilk durumda 1 den baslatiyoruz
    char    *temp; // Okudugumuzu gecici olarak bir degiskende tutmamiz gerektiginden temp degiskenini tanimliyoruz
    temp = malloc(BUFFER_SIZE + 1); // Readden her zaman BUFFER_SIZE kadar okuyacagi icin BUFFER_SIZE kadar yer aciyoruz +1'i klasik NULL icin gerekli olan byte
    if (!temp) // Malloc yer acamama hata durumu
        return (NULL);
    while (!ft_strchr(buffer , '\n') && size != 0) // Stringimin icinde '\n' yok ise ve dosyamda okunacak bir veri var ise donguye gir
    {
        size = read(fd , temp , BUFFER_SIZE); // Read ile dosyadan okudugun veriyi temp'de kaydet, okudugun verinin uzunlugunu size'da tut
        if (size == -1) // Dosyada veri var fakat bu veriyi okuyamazsa, yani hata durumunda
        {
            free(temp); // Malloc ile actigin yeri freele ve cik
            return (NULL);
        }
        temp[size] = '\0'; // Okudugun verinin sonuna NULL koy, boylece olusturdugun veri tam olarak bir string olsun
        buffer = ft_strjoin(buffer , temp); // Okudugun veriyi onceki verinin sonuna ekle ki artik bu sekilde elde etmek istedigin veriyi elde et
    }
    free(temp); // Malloc ile actigin yeri freele cunku zaten olusturmak istedigin veriyi buffer'da olusturdun, bu yuzden bu veriyi daha kullanmayacaksin
    return (buffer); // Okuyup birlestirdigin veriyi dondur
}
char    *get_next_line(int fd)
{
    static  char    *buffer = NULL; // Static olarak bir buffer degiskeni tanimla, bu degisken fonksiyonla lineden sonraki kismi tutacak
    char    *line; // Elde edecegin line'i tutacak
    buffer = ft_read(buffer , fd); // Dosyadan okunacak veriyi handle etmek icin dosyani ve stringini bu fonksiyona gonder 
    if (!buffer) // ft_read fonksiyonunda NULL donme durumlarinda buradaki hata durumuna girecek
        return (free(buffer) , NULL);
    line = before_newline(buffer); // Okudugun veriyi line line dondurecegin icin stringin '\n'a gelene kadarki kismini alacagin fonksiyon  
    buffer = after_newline(buffer); // Okudugun verinin '\n'dan sonra alacagin fonksiyon
    return (line);
}