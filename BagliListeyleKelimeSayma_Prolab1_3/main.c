#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


struct dugum
{
    char *kelime;
    int sayac;
    struct dugum *sonraki;
};

struct dugum *liste=NULL;
struct dugum *iter=NULL;


//https://stackoverflow.com/questions/53842300/counting-the-number-of-occurences-of-string-in-a-linked-list
int adetHesapla(struct dugum* metin, char* aranan)
{
    int sayac=0;
    iter=metin;
    while (iter->sonraki != NULL)
    {

        if (strcmp(iter->kelime,aranan) == 0)
            sayac++;
        iter = iter->sonraki;
    }

    return sayac;
}

int adetHesapla2(struct dugum* metin, char* aranan)
{

    int sayac=0;
    iter=metin;
    while (iter->sonraki != NULL)
    {
        if (strcmp(iter->kelime,aranan) == 0)
            sayac++;
        iter = iter->sonraki;
        if(iter->kelime==aranan)
            break;
    }

    return sayac;
}



int kullanildiMi(struct dugum* metin, char* kelimee)
{
    if(adetHesapla2(metin,kelimee)>0)
        return 1;
    else
        return 0;
}


/*//https://sanalkurs.net/c-c-ile-programlama-tek-yonlu-bagli-liste-islemleri-linked-list-10053.html
struct dugum* basaEkle(char* kelimee)
{

    struct dugum* var=(struct dugum *)malloc(sizeof (struct dugum));
    //var->kelime=kelimee;

    if(liste==NULL)
    {
        var->kelime=kelimee;
       // var->sayac=adetHesapla(liste,kelimee);
        var->sonraki = NULL;
        liste = var;
        printf("ilk dugum olusturuldu");
    }
    else
    {
        var->kelime=kelimee;
//        var->sayac=adetHesapla(liste,kelimee);
        var->sonraki=liste;
        liste=var;
        printf("ikinci dugum olusturuldu");
    }
    // printf("%s ",var->kelime);
    return liste;
}*/

//https://www.youtube.com/watch?v=b2cyLP6uGqg&list=PLOsYO8J5EH_txthUirEEYlCEowJDm70Hw&index=6&ab_channel=MucitYaz%C4%B1l%C4%B1m
void basaEklee(char* kelimee, int adet)
{
    struct dugum* yeni;
    yeni=(struct dugum*)malloc(sizeof(struct dugum));
    yeni->kelime=kelimee;
    yeni->sayac=adet;
    //yeni->sayac=adetHesapla(liste,kelimee);
    yeni->sonraki=liste;
    liste=yeni;
}

//https://www.youtube.com/watch?v=b2cyLP6uGqg&list=PLOsYO8J5EH_txthUirEEYlCEowJDm70Hw&index=6&ab_channel=MucitYaz%C4%B1l%C4%B1m
void arayaEkle(char* kelime1, char* kelimee,int adet)
{
    struct dugum *yeni;
    yeni=(struct dugum*)malloc(sizeof(struct dugum));
    yeni->kelime=kelimee;
    yeni->sayac=adet;
    iter=liste;
    while(iter->sonraki->kelime != kelime1)
    {
        iter=iter->sonraki;
    }
    struct dugum* iter2=(struct dugum*)malloc(sizeof(struct dugum));
    iter2=iter->sonraki;
    iter->sonraki=yeni;
    yeni->sonraki=iter2;

}

//https://www.youtube.com/watch?v=YIWUcvQPDi8&ab_channel=MucitYaz%C4%B1l%C4%B1m
void sonaEkle( char *kelimee,int adet)
{

    struct dugum* yeni;
    yeni=(struct dugum*)malloc(sizeof(struct dugum));
    yeni->kelime=kelimee;
    yeni->sayac=adet;
    yeni->sonraki=NULL;

    if(liste==NULL)
    {
        liste=yeni;
    }
    else
    {
        iter=liste;
        while(iter->sonraki!=NULL)
        {
            iter=iter->sonraki;
        }
        iter->sonraki=yeni;
    }
}

void enBuyukVeyaEsitMi(struct dugum* metin, struct dugum* siradaki){

    struct dugum* iter5 = liste;

    while(iter5 != siradaki)
    {
        if(siradaki->sayac > iter5->sayac && kullanildiMi(liste,siradaki->kelime)==0 )
        {
            iter5=iter5->sonraki;
        }
        else if(siradaki->sayac == iter5->sayac && kullanildiMi(liste,siradaki->kelime)==0)
        {
            iter5=iter5->sonraki;
        }
        else
            break;
        basaEklee(siradaki->kelime,siradaki->sayac);

        break;
    }

}

void aradaMi(struct dugum* metin, struct dugum* siradaki){
 struct dugum* iter5=liste;

    while(iter5 != siradaki)
    {

        if(siradaki->sayac < iter5->sayac && siradaki->sayac > iter5->sonraki->sayac)
        {
            iter5=iter5->sonraki;
        }
        else
            break;
//if(kullanildiMi(liste,siradaki)==0)
        arayaEkle(iter5->kelime,siradaki->kelime,siradaki->sayac);

        break;

    }
}

void enKucukMu(struct dugum* metin, struct dugum* siradaki){
     struct dugum* iter5=liste;


    while(iter5->sonraki != siradaki)
    {

        if(siradaki->sayac < iter5->sayac )
        {
           iter5=iter5->sonraki;
        }
        else
            break;
//if(kullanildiMi(liste,siradaki)==0)
                sonaEkle(siradaki->kelime,siradaki->sayac);

        break;

    }

}

// 3. ve sonraki kelimeleri ekleme fonksiyonu
void karsilastir(struct dugum* metin, struct dugum* siradaki)
{

enBuyukVeyaEsitMi(metin,siradaki);
aradaMi(metin,siradaki);
enKucukMu(metin,siradaki);

}






void listeyiYazdir()
{
    iter=liste;
    int iterr=1;
    while(iter != NULL)
    {
        printf("%d.%s: %d\n",iterr, iter->kelime,iter->sayac);

        iter=iter->sonraki;
        iterr++;

    }
}

int main()
{
    setlocale(LC_ALL, "Turkish");
    FILE *dosya;
    dosya= fopen ("metin.txt", "r");
    if (dosya == NULL)
    {
        printf ("dosya acilamadi\n");
        return 1;
    }


    struct dugum* metin=(struct dugum*)malloc(sizeof(struct dugum));
    struct dugum* iterMetin=metin;

//http://bilgisayarkavramlari.com/2007/05/03/linked-list-linkli-liste-veya-bagli-liste/
    while(!feof(dosya))
    {
        iterMetin->kelime = malloc(12 * sizeof(char));
        fscanf(dosya,"%s",iterMetin->kelime);
        iterMetin->sonraki=(struct dugum*)malloc(sizeof(struct dugum));
        iterMetin=iterMetin->sonraki;
    }
    iterMetin->sonraki=NULL;
    printf("\n");


    struct dugum *iter2=metin;
    struct dugum *iter3=metin;
    struct dugum *iter4=metin;


    //kelimelerin adet sayilari
    while(iter2->sonraki != NULL)
    {
        // iter->sayac=adetHesapla(metin,iter2->kelime);
        iter2->sayac=adetHesapla(metin,iter2->kelime);
        // printf("%s %d defa gecmistir\n",iter2->kelime,iter2->sayac);
        iter2=iter2->sonraki;
    }

    basaEklee(iter3->kelime,iter3->sayac);
    iter4=iter4->sonraki;





    while(iter4->sonraki != NULL)
    {
        if(kullanildiMi(metin,iter4->kelime)==0)
              karsilastir(metin, iter4);
          iter4=iter4->sonraki;

    }



    listeyiYazdir();



    fclose(dosya);
    return 0;
}







