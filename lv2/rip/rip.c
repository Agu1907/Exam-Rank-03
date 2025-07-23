#include <stdio.h>
int paranthesis(char *s)
{
    int opened = 0; // Acilan parantezler icin tanimlanan degisken
    int closed = 0; // Kapanan parantezler icin tanimlanan degisken
    int i = 0; // Index uzerinden ilerlemek icin

    while (s[i]) // Tum string boyunca
    {
        if (s[i] == '(') // Eger acilan bir parantez gorursen
            opened++; // Acilan parantezlere +1 ekle
        else if (s[i] == ')') // Eger kapanan bir parantez gorduysen 
        {
            if (opened) // Acik olan hali hazirda bir parantez var ise
                opened--; // Parantezi kapa, mantiken acilmis bisey varsa onceden bu kapama operatoru geldikten sonra orasi kapanmistir
            else
                closed++; // Eger acik olan bir parantez yoksa kapanan sayisini arttir
        }
        i++;
    }
    return (opened + closed); // En son toplam handle edilecek parantez sayisini dondur
}
void    rip(char *s, int must_fix, int n_fix , int pos)  //  must_fix = handle edilmesi gereken parantez sayisi | n_fix = suana kadar handle edilen parantez sayisi | pos = anlik olarak durdugun pozisyon
{
    if (n_fix == must_fix && !paranthesis(s)) // Fixleyecegin tum parantezler hallolduysa ve stringde handle edicek parantez kalmadiysa
    {
        puts(s); // Stringi yazdir ve cik
        return;
    }
    int i = pos; // Oldugun en son pozisyonu i ye at ve i den isleme devam et
    while (s[i])
    {
        if (s[i] == '(' || s[i] == ')') // Eger acilan veya kapanan parantez gorursen
        {
            char temp = s[i]; // Bucket mantigi, suan oldugun degiskeni gecici bir degiskene at
            s[i] = ' '; // Oldugun indexe bosluk ata(Debug ederken "-" kullanman debugda anlamanda daha yardimci olur)
            rip(s , must_fix , n_fix + 1 , i + 1); // Fixlenen parantezi ve pozisyonunu bir arttirarak tekrardan recursive olarak stringini fonksiyona sok
            s[i] = temp; // Gecici olarak tuttugun degiskeni stringine geri koy
        }
        i++; // Pozisyonlara teker teker bak
    }
}
int main (int ac, char **av)
{
    if (ac != 2) // Arguman kontrolu
        return (1);
    int must_fix = paranthesis(av[1]); // Kac tane parantez handle edilmeli hesabini yapmak icin stringini fonksiyona gonder
    rip(av[1] , must_fix , 0 , 0); // Parantez islemi icin stringi ve gerekli degiskenleri fonksiyona gonder
}