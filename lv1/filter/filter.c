#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define BUFFER_SIZE 4

void    search_and_replace(char *line , char *str)
{
    if (!line || !str || strlen(line) < strlen(str)) // Olmama ve sansurleyecegin kelime stringden buyuk ise hic bakma bile direkt return at
        return ;
    int i;
    int j;
    int match; // Eslesme durumu (Eslesmisse 1, degilse 0 olacak)

    i = 0;
    while (line[i]) // Line'im null olana kadar donguye gir
    {
        j = 0; // Index baslatma klasik
        match = 1; // Ilk basta eslesmis olarak kabul ediyoruz
        while (str[j]) // Sansurleyecegimiz kelime olana kadar gir donguye
        {
            if (line[i + j] != str[j]) // Eger sansurleyecegimiz kelime line de yoksa
            {
                match = 0; // Eslesmeyi 0'la ve donguyu kir
                break;
            }
            j++;
        }
        if (match) // Eger eslesen bir durum var ise
        {
            j = 0;
            while (str[j]) // Sansurleyecegim string bitene kadar
            {
                line[i + j] = '*'; // Line'in indexlerine * at
                j++;
            }
            i += j; // Yukaridaki dongude kac tane yildiz attiysam o kadar ilerle, yani yildiz attiklarimdan sonrakileri kontrol et artik
        }
        else
            i++; // Eger eslesen bir sey yoksa bir sonraki indexe gec
    }
}
int main (int ac , char **av)
{
    if (ac != 2) // Arguman kontrolu (Spesifik olarak 1 dondurmemizi pdf istiyor)
        return (1);
    char    buffer[BUFFER_SIZE]; // Okudugumuz veriyi attigimiz string
    char    line[90000]; // Okudugumuz verinin line'ini aldigimiz degisken
    int byte_read; // Readden donen degeri tuttugumuz degisken
    int i; // Klasik index degiskeni
    int line_index = 0; // Sadece line icin kullandigimiz degisken

    while (1) // Stdinden input alacagimizdan sonsuz dongu aciyoruz
    {
        byte_read = read(0 , buffer , BUFFER_SIZE); // Okuma islemi
        if (byte_read == 1) // Okuyamama durumu
        {
            perror("Error ");
            return (1);
        }
        if (byte_read == 0) // Okunucak bir sey kalmadiysa donguyu kir
            break;
        i = 0; // Her okunucak durumda buffer'in da indexi 0 lanmasi gerektiginden i = 0 tanimi burada olmak zorunda
        while (i < byte_read) // Okunan byte degeri kadar i yi donguye sok
        {
            if (buffer[i] == '\n') // i'incisi newline ise
            {
                line[line_index] = '\0'; // Line'in sonuna NULL at
                search_and_replace(line , av[1]); // Line'in icinde av[1]'i arayacagindan dolayi 2 sinide fonksiyona gonder 
                printf("%s\n" , line); // Fonksiyon isleminden sonra line'i bastir 
                i++;
                line_index = 0; // Yeni line'a gececeginden dolayi line_index'ini 0'la
            }
            else // Newline degil ise 
            {
                line[line_index] = buffer[i]; // Direkt buffer'i line'a at
                i++;
                line_index++;
            }
        }
    }
}