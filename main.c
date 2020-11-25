#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXSTRINGSIZE 10
#define LINESIZE 128
struct node
{
    int plaka;
    struct node *sonraki;
};

struct dugum
{
    int plaka;
    int komsuSayisi;
    char sehir[100];
    char bolge[100];
    struct dugum *next;
    struct dugum *prev;
    struct node *nextkomsu;
};
struct dugum* start = NULL;


struct dugum* dugumOlustur(int veri,int veri2,char *gecici1,char *gecici2)
{
    struct dugum* ciftDugum = (struct dugum*)malloc(sizeof(struct dugum));
    ciftDugum->plaka = veri;
    ciftDugum->komsuSayisi=veri2;
    strcpy(ciftDugum->sehir,gecici1);
    strcpy(ciftDugum->bolge,gecici2);
    ciftDugum->next = NULL;
    ciftDugum->prev = NULL;
    return ciftDugum;
}
void sonaEkle(int veri,int veri2,char *gecici1,char *gecici2)
{
    struct dugum* sonaEklenecek = dugumOlustur(veri,veri2,gecici1,gecici2);
    //Eðer listede hiç eleman yoksa yeni eleman ekliyoruz
    if (start == NULL)
    {
        start = sonaEklenecek;
        // printf("%d",start->plaka);

    }
    else
    {
        struct dugum* temp = start;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        sonaEklenecek->prev = temp;
        temp->next = sonaEklenecek;
    }

}
//Çift yönlü bağlı listede başa düğüm ekleyen fonksiyon
void basaEkle(int veri,int veri2,char *gecici1,char *gecici2)
{
    struct dugum* basaEklenecek = dugumOlustur(veri,veri2,gecici1,gecici2);

    if (start == NULL)
    {
        start = basaEklenecek;
        return;
    }

    start->prev = basaEklenecek;
    basaEklenecek->next = start;
    start = basaEklenecek;
}

//Çift yönlü bağlı listede araya düğüm ekleyen fonksiyon
void arayaEkle(int kiminOnune,int veri2,int veri,char *gecici1,char *gecici2)
{
    struct dugum* temp = start;
    struct dugum* arayaEklenecek = dugumOlustur(veri,veri2,gecici1,gecici2);
    struct dugum* once = NULL;
    struct dugum* sonra = NULL;

    if (start == NULL)
    {
        start = arayaEklenecek;
    }
    /*else if(start->plaka == kiminOnune)
    {
        //basaEkle(eklenecek);
    }*/
    else
    {
        while (temp->next!= NULL)
        {
            if (veri< (temp->next->plaka))
            {
                once= temp;
                sonra=temp->next;
                break;
            }
            temp = temp->next;
        }
        temp->next = arayaEklenecek;
        arayaEklenecek->prev = once;
        arayaEklenecek->next = sonra;
        sonra->prev=arayaEklenecek;

    }


}
//Çift yönlü bağlı listede baştan düğüm silen fonksiyon
void bastanSil()
{
    if (start == NULL)
    {
        printf("\n Liste zaten bos ....");
        return;
    }

    if (start->next == NULL)
    {
        free(start);
        start = NULL;
        return;
    }

    struct dugum* ikinci = start->next;
    free(start);
    ikinci->prev = NULL;
    start = ikinci;
}
//Çift yönlü bağlı listede sondan düğüm silen fonksiyon
void sondanSil()
{
    if (start == NULL)
    {
        printf("\n Liste zaten bos ....");
        return;
    }

    if (start->next == NULL)
    {
        bastanSil();
        return;
    }

    struct dugum* temp = start;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    struct dugum* onceki = temp->prev;
    free(temp);
    onceki->next = NULL;
}
//Çift yönlü bağlı listede aradan düğüm silen fonksiyon
void aradanSil(char *silinecek)
{
    struct dugum* temp = start;
    while (temp->next != NULL)
    {
        if (strcmp(temp->sehir,silinecek)==0)
            break;
        temp = temp->next;
    }
    struct dugum* sonraki = temp->next;
    struct dugum* onceki = temp->prev;
    free(temp);
    onceki->next = sonraki;
    sonraki->prev = onceki;
}
int sehirara(char *gecici1)
{
    struct dugum*gecici;
    int kontrol=0;
    gecici=start;

    while(gecici!= NULL)
    {

        if(strcmp(gecici->sehir,gecici1)==0 )
        {
            kontrol=1;
        }

        gecici=gecici->next;
    }

    return kontrol;

}
int sehirara1(char *gecici1)
{
    struct dugum*gecici;
    int kontrol;
    gecici=start;

    while(gecici!= NULL)
    {

        if(strcmp(gecici->sehir,gecici1)==0 )
        {
            kontrol=gecici->plaka;
            return kontrol;
        }

        gecici=gecici->next;
    }



}
int plakaara(int gecici1)
{
    struct dugum*gecici;

    gecici=start;


    while(gecici != NULL)
    {

        if(gecici->plaka==gecici1)
        {

            return 1;
        }

        gecici=gecici->next;

    }

    return 0;

}
int plakaara1(int gecici1)
{
    struct dugum*gecici;
    char kontrol[100];
    gecici=start;

    while(gecici != NULL)
    {

        if(gecici->plaka==gecici1)
        {
            strcpy(kontrol,gecici->sehir);

        }

        gecici=gecici->next;

    }

    return kontrol;

}
//Düğüm yapısını ekrana yazdıran fonksiyon
void yazdir()
{
    struct dugum* temp = start;
    struct node* deneme;
    FILE *dosya = fopen ("cikan.txt", "a" );
    while (temp != NULL)
    {
        deneme=temp->nextkomsu;
        printf(" %d", temp->plaka);
        fprintf(dosya, "%d ",temp->plaka);
        printf(" %s", temp->sehir);
        fprintf(dosya, "%s ",temp->sehir);
        printf(" %s", temp->bolge);
        fprintf(dosya, "%s ",temp->bolge);
        printf(" %d ", temp->komsuSayisi);
        fprintf(dosya, "%d ",temp->komsuSayisi);
        while(deneme !=NULL)
        {
            printf(" %d ", deneme->plaka);
            fprintf(dosya,"%d ", deneme->plaka);
            //dosyayayazdir(deneme->plaka);
            deneme=deneme->sonraki;
        }
        temp = temp->next;
        printf("\n");
         fprintf(dosya,"\n");
    }
    fclose(dosya);
}

/*void dosyayayazdir(int plaka)
{
    FILE *dosya = fopen ("cikan.txt", "a" );
    printf(" %d", deneme->plaka);
    fclose(dosya);

}*/

struct node* baslangic = NULL;
struct node* geciciDegisken;

struct node* dugumOlustur1()
{
    struct node* yeniDugum = (struct node*)malloc(sizeof(struct node));
    return yeniDugum;
}
void sonaEkle1(int gecici,struct dugum *dugum)
{
    //plakayı veri olarak alıyorum
    struct node* element = dugumOlustur1();
    element->plaka=gecici;
    element->sonraki = NULL;

    if(dugum->nextkomsu == NULL)
    {
        baslangic=element;
        dugum->nextkomsu = element;

    }

    else
    {

        geciciDegisken = dugum->nextkomsu;

        while(geciciDegisken->sonraki != NULL)
        {
            geciciDegisken = geciciDegisken->sonraki;
        }
        geciciDegisken->sonraki = element;
    }

}
void arayaEklekomsu(int veri,char *gecici1)
{
    struct dugum* cift = start;
    struct node* tek ;
    struct node* arayaEklenecek=dugumOlustur1() ;
    struct node* son=(struct node*)malloc(sizeof(struct node));
    arayaEklenecek->plaka=veri;

    while (cift!= NULL)
    {
        if (strcmp(cift->sehir,gecici1)==0)
        {
            break;
        }
        cift=cift->next;
    }
    tek=cift->nextkomsu;

    while (tek!= NULL)
    {
        if (tek->sonraki->plaka > veri)
        {
            printf("%d",tek->sonraki->plaka);
            break;
        }
        tek= tek->sonraki;
    }
    son=tek->sonraki;
    tek->sonraki=arayaEklenecek;
    arayaEklenecek->sonraki=son;


}
void basaEklekomsu(int veri,struct dugum*gecici)
{
    struct node* basaEklenecek = dugumOlustur1();
    struct node *tek;
    tek=gecici->nextkomsu;
    basaEklenecek->plaka=veri;

    if (gecici->nextkomsu->sonraki == NULL)
    {
        gecici->nextkomsu = basaEklenecek;

    }
    gecici->nextkomsu=basaEklenecek;
    basaEklenecek->sonraki=tek;


}

void komsuSil(int silinecek,char *gecici)
{
    struct dugum* temp = start;
    struct dugum* temp1 = start;
    struct node* tek;
    struct node* onceki;
    while (temp!=NULL)
    {

        if(strcmp(temp->sehir,gecici)==0 )
        {
            break;
        }
        temp= temp->next;
    }
    tek=temp->nextkomsu;


    while(tek!=NULL)
    {
        if(silinecek==tek->plaka)
        {

            break;
        }
        onceki = tek;
        tek=tek->sonraki;

    }

    if(tek==temp->nextkomsu)
    {
        temp->nextkomsu=tek->sonraki;
        free(tek);

    }
    else
    {
        struct node* sonraki = tek->sonraki;
        free(tek);
        onceki->sonraki = sonraki;

    }
}
int virgulSayisiBul(char *chpt)
{
    int i=0;
    int virgulSayisi=0;
    while (chpt[i]!='\n')
    {
        if(chpt[i]==',')
            virgulSayisi++;
        i++;
    }
    return virgulSayisi;
}
//komsuluk sıralama
void bubbleSort(struct node *start)
{
    int swapped, i;
    struct node *ptr1;
    struct node *lptr = NULL;

    if (start == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->sonraki != lptr)
        {
            if (ptr1->plaka > ptr1->sonraki->plaka)
            {
                swap(ptr1, ptr1->sonraki);
                swapped = 1;
            }
            ptr1 = ptr1->sonraki;
        }
        lptr = ptr1;
    }
    while (swapped);
}

/* yer değiştirme sıralama için*/
void swap(struct node *a, struct node *b)
{
    int temp = a->plaka;
    a->plaka = b->plaka;
    b->plaka = temp;
}
int dugumara(int gecici1)
{
    struct dugum*gecici;
    char kontrol[100];
    gecici=start;

    while(gecici != NULL)
    {

        if(gecici->plaka==gecici1)
        {
            break;

        }

        gecici=gecici->next;

    }

    return gecici;

}
int main (void)
{
    FILE *myfile = fopen ( "Sehirler.txt", "r" );
    int i=0;
    char line[LINESIZE];
    char *value;
    int plaka;
    char *x;
    char sehir[50];
    char bolge[50];
    char komsu[50];
    int vSayi;
    int komsusayisi=0;

    while(fgets(line, sizeof(line), myfile))
    {
        vSayi=virgulSayisiBul(line);
        x= strtok(line, ", ");
        plaka=atoi(x);
        //printf("plaka: %d\n", plaka);

        value = strtok(NULL, ", ");
        // printf("sehirismi: %s\n", value);
        strcpy(sehir,value);

        value = strtok(NULL, ", ");
        // printf("bolge: %s\n", value);
        strcpy(bolge,value);

        for(int i=0; i<vSayi-2; i++)
        {

            value = strtok(NULL, ", ");
            //printf("komsular: %s\n", value);
            strcpy(komsu,value);
            komsusayisi++;

        }
        sonaEkle(plaka,komsusayisi,sehir,bolge);
        komsusayisi=0;

    }
    rewind(myfile);
    struct dugum* ciftdugum=start;
    int son;
    while(fgets(line, sizeof(line), myfile))
    {
        vSayi=virgulSayisiBul(line);
        x= strtok(line, ", ");

        value = strtok(NULL, ", ");

        value = strtok(NULL, ", ");

        for(int i=0; i<vSayi-2; i++)
        {

            value = strtok(NULL, ", ");
            strcpy(komsu,value);
            son=sehirara1(komsu);
            sonaEkle1(son,ciftdugum);
            komsusayisi++;

        }
        ciftdugum=ciftdugum->next;

        komsusayisi=0;

    }
    struct dugum *ciftdeneme=start;
    struct node *tekdeneme;
    while(ciftdeneme!=NULL)
    {
        tekdeneme=ciftdeneme->nextkomsu;
        bubbleSort(tekdeneme);
        ciftdeneme=ciftdeneme->next;

    }
    yazdir();

    printf("-------------------------\n");

    rewind(myfile);

    i++;
    int secim;
    char eklesehir[50];
    char eklebolge[50];
    int ekleplaka,eklekomsuSayisi;
    int eksecim;
    while (1)
    {
        printf("\n 1- Sehir ekleme");
        printf("\n 2- Komsuluk ekleme");
        printf("\n 3- Sehir ismi arama");
        printf("\n 4- Plaka kodu arama");
        printf("\n 5- Sehir kaydi silme");
        printf("\n 6- Komsuluk kaydi silme");
        printf("\n 7- Bolgede bulunan sehirleri listeleme");
        printf("\n 8- Belirli komsu sayisina uygun sehir arama");
        printf("\n 9- Bonus ");
        printf("\n Seciminizi yapin ... ");
        scanf("%d", &secim);

        switch (secim)
        {
        case 1:
            printf("\n Eklemek istediginiz sehri girin ... ");
            scanf("%s", eklesehir);
            if(sehirara(eklesehir)==1)
            {
                printf("Sehir listede var.\n");
            }
            else
            {
                printf("Sehir listede yok.");
                printf("\n Eklemek istediginiz plaka girin ... ");
                scanf("%d", &ekleplaka);
                printf("\n Eklemek istediginiz bolgeyi girin ... ");
                scanf("%s", eklebolge);
                printf("\n Eklemek istediginiz komsuluk sayisini girin ... ");
                scanf("%d", &eklekomsuSayisi);
                //listede  nereye ekleneceği ???
                struct dugum* p1 = start;

                while (1)
                {

                    if(p1->next==NULL)
                    {

                        sonaEkle(ekleplaka,eklekomsuSayisi,eklesehir,eklebolge);

                        break;

                    }
                    else if (p1->plaka > ekleplaka)
                    {

                        basaEkle(ekleplaka,eklekomsuSayisi,eklesehir,eklebolge);
                        break;

                    }
                    else if (p1->next->plaka > ekleplaka )
                    {

                        arayaEkle(p1->plaka,eklekomsuSayisi,ekleplaka,eklesehir,eklebolge);
                        break;

                    }


                    p1 = p1->next;

                }

                yazdir();
            }

            break;
        case 2:
            printf("\n Hangi sehre ekleme yapilsin... ");
            scanf("%s", eklesehir);

            printf("\n Komsuluk eklemek istediginiz sehrin plakasini girin... ");
            scanf("%d", &ekleplaka);

            struct dugum* p2 = start;
            struct node* tek ;
            struct node* tek1 ;
            struct node* tek2 ;
            int kontrol=0;

            while(p2!=NULL)
            {
                if(strcmp(p2->sehir,eklesehir)==0 )
                {
                    break;
                }
                p2 = p2->next;
            }
            tek=p2->nextkomsu;
            tek1=p2->nextkomsu;
            tek2=p2->nextkomsu;

            while(tek!=NULL)
            {
                if(ekleplaka==tek->plaka)
                {
                    kontrol=1;
                    break;
                }

                tek=tek->sonraki;

            }


            if(kontrol==1)
            {
                printf("Bu komsuluk zaten var\n");
            }
            else
            {
                printf("Komsuluk eklendi\n");

            }

            while(1)
            {
                if(tek1->sonraki==NULL)
                {
                    sonaEkle1(ekleplaka,p2);
                    break;

                }
                else if(tek2->plaka > ekleplaka)
                {
                    basaEklekomsu(ekleplaka,p2);
                    break;

                }
                else if(tek1->sonraki!=NULL && tek1->sonraki->plaka > ekleplaka)
                {
                    arayaEklekomsu(ekleplaka,eklesehir);
                    break;
                }
                tek1=tek1->sonraki;
            }

            yazdir();

            break;

        case 3:
            printf("\n Aramak istediginiz sehri girin...");
            scanf("%s", eklesehir);
            struct node* p3komsu ;

            if(sehirara(eklesehir)==1)
            {
                printf("Sehir listede var.\n");

                struct dugum* p3 = start;
                struct dugum* yenidugum = start;
                while (p3!= NULL)
                {
                    if (strcmp(p3->sehir,eklesehir)==0)
                    {
                        printf("\nPlakasi:%d Sehir Adi: %s Bolgesi:%s Komsu Sayisi:%d\n",p3->plaka,p3->sehir,p3->bolge,p3->komsuSayisi);
                        p3komsu=p3->nextkomsu;
                        while(p3komsu!=NULL)
                        {


                            yenidugum=dugumara(p3komsu->plaka);
                            printf("Komsu Plakasi:%d  ",yenidugum->plaka);
                            printf("Komsu Adi:%s  ",yenidugum->sehir);
                            printf("Komsu Bolge:%s\n",yenidugum->bolge);
                            p3komsu=p3komsu->sonraki;
                        }

                        break;
                    }
                    p3 = p3->next;
                }
            }
            else
            {
                printf("Sehir listede yok. Eklemek ister misin?\n");
                printf("Eklemek icin 1'i, seciniz\n");
                scanf("%d",&eksecim);
                int veri2=0;
                if(eksecim==1)
                {
                    printf("\n Eklemek istediginiz plaka girin ... ");
                    scanf("%d", &ekleplaka);
                    printf("\n Eklemek istediginiz bolgeyi girin ... ");
                    scanf("%s", eklebolge);
                    sonaEkle(ekleplaka,veri2,eklesehir,eklebolge);
                }
                yazdir();
            }

            break;

        case 4:
            printf("\n Aramak istediginiz sehrin plakasini girin...");
            scanf("%d", &ekleplaka);
            struct dugum* yenidugum = start;
            struct node* p4komsu;
            if(plakaara(ekleplaka)==1)
            {
                printf("Plaka listede var.\n");
                struct dugum* p4 = start;

                while (p4!= NULL)
                {
                    if (p4->plaka == ekleplaka)
                    {
                        printf("\nPlakasi:%d Sehir Adi: %s Bolgesi:%s Komsu Sayisi:%d\n",p4->plaka,p4->sehir,p4->bolge,p4->komsuSayisi);
                         p4komsu=p4->nextkomsu;
                        while(p4komsu!=NULL)
                        {


                            yenidugum=dugumara(p4komsu->plaka);
                            printf("Komsu Plakasi:%d  ",yenidugum->plaka);
                            printf("Komsu Adi:%s  ",yenidugum->sehir);
                            printf("Komsu Bolge:%s\n",yenidugum->bolge);
                            p4komsu=p4komsu->sonraki;
                        }

                        break;
                    }
                    p4 = p4->next;

                }
            }
            else
            {
                printf("Sehir listede yok. Eklemek ister misin?\n");
                printf("Eklemek icin 1'i, seciniz\n");
                scanf("%d",&eksecim);
                int veri2=0;
                if(eksecim==1)
                {
                    printf("\n Eklemek istediginiz sehri girin ... ");
                    scanf("%s", eklesehir);
                    printf("\n Eklemek istediginiz bolgeyi girin ... ");
                    scanf("%s", eklebolge);
                    sonaEkle(ekleplaka,veri2,eklesehir,eklebolge);
                }
                yazdir();
            }
            break;

        case 5:
            printf("\n Silinmesini istediginiz sehri girin ... ");
            scanf("%s", eklesehir);
            if(sehirara(eklesehir)==0)
            {
                printf("Sehir listede yok. Silinemez.");
            }
            else
            {
                struct dugum* p5 = start;
                while (1)
                {

                    if(strcmp(p5->sehir,eklesehir)==0)
                    {
                        if(p5->next!=NULL && p5->prev!=NULL)
                        {

                            aradanSil(eklesehir);

                            break;
                        }

                        if(p5->next==NULL && p5->prev!=NULL)
                        {

                            sondanSil();

                            break;
                        }

                        else
                        {

                            bastanSil();

                            break;
                        }

                    }
                    p5 = p5->next;

                }

            }
            yazdir();
            break;

        case 6:
            printf("\n Hangi sehirden komsuluk silinsin? \n ");
            scanf("%s", eklesehir);

            printf("\n Silinmesini istediginiz komsulugun plakasini girin:\n");
            scanf("%d", &ekleplaka);
            komsuSil(ekleplaka,eklesehir);
            yazdir();
            break;

        case 7:
            printf("\n Listelenmesini istediginiz bolgeyi girin ... ");
            scanf("%s", eklebolge);

            struct dugum* p7 = start;

            while (p7!=NULL)
            {
                if (strcmp(p7->bolge,eklebolge)==0)
                {
                    printf("\nPlakasi:%d Sehir Adi: %s Bolgesi:%s Komsu Sayisi:%d\n",p7->plaka,p7->sehir,p7->bolge,p7->komsuSayisi);

                }
                p7 = p7->next;
            }

            break;

        case 8:
            printf("\n Kac tane komsu sayisina uyan sehirler listelensin... ");
            int sayi;
            scanf("%d", &sayi);
            struct dugum* p8 = start;
            //struct dugum* p= (struct dugum*)malloc(sizeof(struct dugum));

            while (p8!=NULL)
            {
                if (p8->komsuSayisi==sayi)
                {
                    printf("\nPlakasi:%d Sehir Adi: %s Bolgesi:%s Komsu Sayisi:%d\n",p8->plaka,p8->sehir,p8->bolge,p8->komsuSayisi);

                }
                p8 = p8->next;
            }
            break;

        case 9:
            printf("\n Kac tane komsu sayisina uyan sehirler listelensin...(Orn: 3 ile7 ) ");
            int kucuk,buyuk;
            scanf("%d", &kucuk);
            scanf("%d", &buyuk);
            int *dizi,j=0,sayac=0;
            dizi=(int *)malloc(2*sizeof(int));
            struct dugum* p9 = start;
            char komsuismi1[50],komsuismi2[50];
            struct dugum* ciftdgm = start;
            struct node* tekdgm1;
            struct node* tekdgm2;
            int plaka1,plaka2,komsuplaka1=0,komsuplaka2=0,kontrol2=0;
            while (p9!=NULL)
            {
                if (p9->komsuSayisi>kucuk && p9->komsuSayisi<buyuk)
                {
                    printf("\nPlakasi:%d Sehir Adi: %s Bolgesi:%s Komsu Sayisi:%d\n",p9->plaka,p9->sehir,p9->bolge,p9->komsuSayisi);
                    dizi[j]=p9->plaka;
                    j++;
                    sayac++;
                    dizi=(int *)realloc(dizi,(j+2)*sizeof(int));


                }

                p9 = p9->next;
            }

            /*for(int i=0; i<j+1; i++)
            {
                printf("%d\n",dizi[i]);
            }*/

            printf("Komsulugu olmasini istediginiz sehir ismini giriniz:(Orn: Ankara ve Konya)\n");
            scanf("%s", komsuismi1);
            scanf("%s", komsuismi2);
            plaka1=sehirara1(komsuismi1);
            plaka2=sehirara1(komsuismi2);
            //printf("%d ",plaka1);
            // printf("%d ",plaka2);

            for(int a=0; a<sayac; a++)
            {

                ciftdgm=dugumara(dizi[a]);
                tekdgm1=ciftdgm->nextkomsu;
                tekdgm2=ciftdgm->nextkomsu;
                //printf("%d ",ciftdgm->plaka);


                while(tekdgm2!=NULL)
                {
                    if(tekdgm2->plaka==plaka2)
                    {
                        while(tekdgm1!=NULL)
                        {

                            if(tekdgm1->plaka==plaka1)
                            {

                                printf("%d ",ciftdgm->plaka);
                                printf("%s ",ciftdgm->sehir);
                                printf("%s \n",ciftdgm->bolge);
                                kontrol2=1;
                                break;
                            }
                            tekdgm1=tekdgm1->sonraki;
                        }
                    }
                    tekdgm2=tekdgm2->sonraki;
                }


            }
            if(kontrol2==0)
            {
                printf("YOK\n");
            }
            break;

            //yazdir();
        }

    }
    fclose(myfile);
    return 0;
}
