#include <stdio.h>
void    swap(char *a, char *b)
{
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void    sort(char *s)
{
    int x = 0;
    int y;

    while (s[x]) // x degiskenini ilk indexinden alarak basliyoruz
    {
        y = x + 1; // s stringinin ilk degiskeni harici geri kalan degiskenlerini alfabetik siralamak icin y yi x + 1 olarak tanimliyoruz, +1 in olma sebebi ilk indexin kombinasyonlarina bakiyoruz
        while (s[y]) // Tum kombinasyonlarini almak icin stringin geri kalanini donguye sokuyoruz
        {
            if (s[x] > s[y]) // Eger alfabetik sirali degil ise
                swap(&s[x] , &s[y]); // Yerlerini degistir
            y++; // Tum olasiliklari teker teker kontrol et
        }
        x++; // Ilk indexin tum kombinasyonlarina baktiktan sonra bir sonraki indexin kombinasyonlarina bakmak icin x'i arttir
    }
}
int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return (i);
}
void    prmt(char *s, int l , int r) // l = left, stringin soldan kontrolu icin gerekli degisken | r = right, sag taraf kontrolu icin gerekli degisken
{
    if (l == r) // Tum string islendiyse bu kosula girer
    {
        puts(s); // Stringi yazdirma islemi
        return ;
    }
    else
    {
        int i = l; // Baslangicimizi tutmak icin bir i degiskeni olusturuyoruz
        while (i <= r) // Baslangicimizdan stringimizin sonuna kadar tum karakterleri kontrol etmek icin i yi donguye sokuyoruz
        {
            swap(s + l , s + i); // Tum olasiklilari ele almak icin ilk basta stringin elemanlarini yer degistiriyoruz
            sort(s + l + 1); // Pdf yazdirma sirasinin alfabetik olmasini istediginden dolayi ilk karakterlerin yerini degistirdikten sonra elde edilen stringi alfabetik olarak siralamaya gonderiyoruz
            prmt(s , l + 1 , r); // Bir soldan permutasyon almaya devam etmek icin l yi 1 arttirip tekrardan recursive donguye sokuyoruz
            swap(s + l, s + i); // Ardindan islem bittikten sonra stringimizin ilk haline donmesi icin yerini degistirdigimiz karakterlerin yerlerini eski hallerine donduruyoruz
            i++; // Tum ihtimallere bakmak icin i yi teker teker arttiriyoruz
        }
    }
}
int main (int ac, char **av)
{
    if (ac != 2) // Arguman kontrolu
        return (1);
    int n = ft_strlen(av[1]); // Permutasyonunu alacagimiz stringin uzunlugu
    sort(av[1]); // Her durumda ne gelirse gelsin ilk gelen herşeyi alfabetik sirala
    prmt(av[1] , 0 , n - 1); // Permutasyon islemini yapacagimiz fonksiyona gonderiyoruz, n - 1 durumu ise index olarak kontrol edecegimizden dolayi n - 1 olarak gonderiyoruz
}