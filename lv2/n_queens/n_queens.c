#include <stdlib.h>
#include <stdio.h>

void    print_sol(int *board , int n)
{
    int i = 0; // Klasik sayac parametresi
    while (i < n) // Sayi dizisinin sonuna gelene kadar donguye sok
    {
        fprintf(stdout , "%d" , board[i]); // Int sayi dizesinde tuttugun her elemani sirayla bastir
        if (i < n - 1) // Eger son elemana gelmediysen 2 bastirdigin sayi arasinda bosluk bastir
            fprintf(stdout , "%s" , " ");
        else // Eger son elemana geldiysen son sayindan sonra newline bastir
            fprintf(stdout , "%s" , "\n");
        i++;
    }
}
int is_safe(int *board, int col , int row)
{
    int i = 0; // Klasik sayac parametresi
    while (i < col) // Yine o sutundaki tum durumlari kontrol etmek icin donguye sok
    {
        if (board[i] == row || (board[i] - row == col - i) || (row - board[i] == col - i)) // Sirasiyla:Ayni satirda , caprazda olma ve ters caprazda olma durumlari kontrol et
            return (0); // Eger bu kosula girerse mantiken vezir diger vezirlerin onu yigebilecegi bir noktada olacagindan, bu noktanin guvenli olmadigini gosterir
        i++;
    }
    return (1); // Bu durum, verdigimiz noktanin guvenli oldugunu ve veziri buraya koyabilcegimizi belirtir
}
void    solve(int *board , int col , int n)
{
    if (col == n) // Eger tum sutunlarini islediysen isledigin ihtimaller zincirini bastir
    {
        print_sol(board , n); // Durumlari bastirdigin fonksiyon
        return ;
    }
    int row = 0; // Ele aldigin sutunun her satirini kontrol etmek icin ilk satirdan baslat
    while (row < n) // n x n kadar tahta olusturucagin icin mantiken n kadarda satirin olabilir o yuzden tum satirlarini kontrol etmek icin donguye sok
    {
        if (is_safe(board , col , row)) // Aldigin sutun ve satir noktasini guvenli mi degil mi diye kontrol etmek icin kontrol etmeye gonder
        {
            board[col] = row; // Eger guvenliyse col sutununun kacinci satiri guvenliyse stringe o degeri yerlestir
            solve(board , col + 1, n); // En son oldugun sutunu islediginden dolayi bir sonraki sutuna gecmek icin col'un + 1 ini recursive olarak tekrardan fonksiyona yolla
        }
        row++; // Klasik bir sonraki satira gecme
    }
}
int main (int ac, char **av)
{
    if (ac != 2) // Arguman kontrolu
        return (0);
    int n = atoi(av[1]); // Isleyecegin tahta boyutunu ve vezir sayisini stringden int degere cevir
    if (n <= 0) // 0 dan esit veya kucuk herhangi bir tahta ve vezir sayisi olamayacagi icin hata durumu dondur
        return (0);
    int board[n]; // Olusturucagin ve islem yapacagin tahtaya yer ac
    solve(board , 0 , n); // Islem icin recursive'ye sokacagin fonksiyona gonder
}