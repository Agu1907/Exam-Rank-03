#include <stdio.h>

char    valid_string[100000][256];
int     valid_counter = 0;

int ft_strcmp(char *s1, char *s2)
{
    int i = 0;
    while (s1 && s2 && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}
char    *ft_strcpy(char *dst, char *src)
{
    int i = 0;
    while (src[i])
    {
        dst[i] = src[i];
        i++;
    }
    return (dst);
}
int is_valid(char *s)
{
    int i = 0;
    while (i < valid_counter)
    {
        if (ft_strcmp(valid_string[i], s) == 0)
            return (1);
        i++;
    }
    return (0);
}
void    set_valid(char *s)
{
    if (valid_counter >= 100000)
        return;
    ft_strcpy(valid_string[valid_counter] , s);
    valid_counter++;
}
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
    if (n_fix > must_fix)
        return;
    if (paranthesis(s) > must_fix - n_fix)
        return;
    if (n_fix == must_fix && !paranthesis(s)) // Fixleyecegin tum parantezler hallolduysa ve stringde handle edicek parantez kalmadiysa
    {
        puts(s); // Stringi yazdir ve cik
        return;
    }
    if (is_valid(s))
        return;
    set_valid(s);
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