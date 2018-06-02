#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

struct dugum {
    int icerik;
    struct dugum *sol;
    struct dugum *sag;
};

struct ikili_arama_agaci{
    struct dugum *kok;
};

void ikili_arama_agaci_olustur(struct ikili_arama_agaci **agac){
    *agac=(struct ikili_arama_agaci*)malloc(sizeof(struct ikili_arama_agaci));
    if(*agac==NULL){
        printf("Heapte gerekli yer ayrilamadi... exit ...\n");
        exit(1);
    }
    (*agac)->kok=NULL;
}

struct dugum* dugum_olustur(int icerik){
    struct dugum *d = (struct dugum*)malloc(sizeof(struct dugum));
    if(d==NULL){
        printf("Heapte gerekli yer ayrilamadi... exit ...\n");
        exit(1);
    }
    d->icerik = icerik; (*d).icerik=icerik;
    d->sol=d->sag=NULL;
    return d;
}


void ekle(struct ikili_arama_agaci *agac,int icerik){
    struct dugum *dugum;
    struct dugum *d;
    struct dugum *geri;

    d=agac->kok;
    while(d!=NULL){
        geri=d;
        if(icerik < d->icerik) d=d->sol;
        else if(icerik > d->icerik) d= d->sag;
        else return;
    }
    dugum=dugum_olustur(icerik);
    if(agac->kok==NULL){
        agac->kok = dugum;
        return;
    }
    if(icerik < geri->icerik) geri->sol = dugum;
    else geri->sag = dugum;

}


void yazdir(struct dugum *kok){

    if(kok==NULL) return;
    printf("%4d ",kok->icerik);
    yazdir(kok->sol);
    yazdir(kok->sag);

}


int dugum_sayisi(struct dugum *kok){
    if(kok==NULL) return 0;
    return 1+dugum_sayisi(kok->sol)+dugum_sayisi(kok->sag);
}

int agac_derinlik(struct dugum *kok){
    if(kok == NULL) return 0;
    int solDerinlik = agac_derinlik(kok->sol);
    int sagDerinlik = agac_derinlik(kok->sag);
    if(solDerinlik > sagDerinlik){
        return (1 + solDerinlik);
    }
    else{
        return (1 + sagDerinlik);
    }
}

int toplam_derinlik(struct dugum *kok,int dugumDerinlik){
    if(kok == NULL) return 0;
    else{
        return (dugumDerinlik + toplam_derinlik(kok->sol,dugumDerinlik+1) + toplam_derinlik(kok->sag,dugumDerinlik+1));
    }
}



int main(int argc, char** argv) {
    srand(time(NULL));
    struct ikili_arama_agaci *agac;
    ikili_arama_agaci_olustur(&agac);
    int elemanSayisi;
    int i;
    printf("Agacin eleman sayisini giriniz = ");
    scanf("%d",&elemanSayisi);
    for(i=0;i<elemanSayisi;i++){
        ekle(agac,1+rand()%100);
    }

    yazdir(agac->kok);
    printf("\n");
    printf("Agacin Derinligi = %d\n",agac_derinlik(agac->kok));
    printf("Toplam Derinlik = %d\n",toplam_derinlik(agac->kok,0));
    printf("Sonuc(Toplam Derinlik / Eleman Sayisi) = %d",(toplam_derinlik(agac->kok,0)) / elemanSayisi);

    return 0;
}
