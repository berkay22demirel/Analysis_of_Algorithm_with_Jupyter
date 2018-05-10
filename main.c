#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int veri;
    struct list *sonraki;
} liste;

liste *yeni, *ilk = NULL, *gecici, *silGecici;

void ekle(int sayi) {

    if (ilk == NULL) {
        ilk = (liste*) malloc(sizeof (liste));
        ilk->veri = sayi;
        ilk->sonraki = NULL;
    }

    else {
        if ((ilk->veri) > (sayi)) {
            yeni = (liste*) malloc(sizeof (liste));
            yeni->veri = sayi;
            yeni->sonraki = ilk;
            ilk = yeni;
        } else {
            gecici = ilk;
            yeni = (liste*) malloc(sizeof (liste));
            yeni->veri = sayi;
            while (gecici != NULL) {
                if (gecici->sonraki == NULL && (gecici->veri) <= (sayi)) {
                    yeni->sonraki = NULL;
                    gecici->sonraki = yeni;
                    break;
                }
                if ((gecici->sonraki->veri) > (sayi)) {
                    yeni->sonraki = gecici->sonraki;
                    gecici->sonraki = yeni;
                    break;
                }
                gecici = gecici->sonraki;
            }
        }
    }
}

void listele() {
    if (ilk == NULL) {
        printf("Liste Bos\n");
    }
    else {
        gecici = ilk;
        while (gecici != NULL) {
            printf("%d\n", gecici->veri);
            gecici = gecici->sonraki;
        }
    }
    bekle();
}

int ara(int sayi) {
    int sayac = 0;
    gecici = ilk;
    while (gecici != NULL) {
        sayac++;
        if (gecici->veri == sayi)
            return sayac;
        gecici = gecici->sonraki;
    }
    return -1;
}

int sil(int sayi) {
    if (ilk == NULL)
        return -1;
    else if (ilk->veri == sayi) {
        silGecici = ilk;
        ilk = ilk->sonraki;
        free(silGecici);
        return 1;
    } else {
        gecici = ilk;
        while (gecici->sonraki != NULL) {
            if (gecici->sonraki->veri == sayi) {
                silGecici = gecici->sonraki;
                gecici->sonraki = silGecici->sonraki;
                free(silGecici);
                return 1;
            }
            gecici = gecici->sonraki;
        }

    }
    return 0;
}

void bekle() {
    char temp;
    printf("DEVAM ICIN ENTER'A BAS!\n");
    temp = getchar();
    temp = getchar();
    ekranTemizle();

}

void ekranTemizle() {
    system("cls");
}

void menu() {

    int secim, sayi, sira, kontrol;

    printf("\n1-ELEMAN EKLE\n\n");
    printf("\n2-LISTELE\n\n");
    printf("\n3-ARAMA YAP\n\n");
    printf("\n4-ELEMAN SIL\n\n");
    printf("\n5-CIKIS YAP\n\n");

    scanf("%d", &secim);

    switch (secim) {
        case 1:
            ekranTemizle();
            printf("SAYI GIRINIZ: ");
            scanf("%d", &sayi);
            ekle(sayi);
            bekle();
            break;
        case 2:
            ekranTemizle();
            listele();
            break;
        case 3:
            ekranTemizle();
            if (ilk == NULL) {
                printf("Liste Bos!\n");
                bekle();
                break;
            }
            printf("SAYI GIRINIZ: ");
            scanf("%d", &sayi);
            sira = ara(sayi);
            if (sira == -1)
                printf("Girilen sayi bulunamadý!\n");
            else
                printf("%d sayisi listenin %d. sirasinda\n", sayi, sira);
            bekle();
            break;
        case 4:
            ekranTemizle();
            if(ilk == NULL){
                printf("Liste Bos!\n");
                bekle();
                break;
            }
            printf("SAYI GIRINIZ: ");
            scanf("%d", &sayi);
            kontrol = sil(sayi);
            if (kontrol == -1)
                printf("Liste Bos!\n");
            else if (kontrol == 0)
                printf("%d listede bulunamadi!\n", sayi);
            else
                printf("%d silindi\n", sayi);
            bekle();

            break;
        case 5:
            ekranTemizle();
            printf("BiTTi !\n");
            exit(0);
            break;
        default:
            ekranTemizle();
            printf("Hatali Secim\n");
            bekle();
    }
}


int main() {

    while (1) {
        ekranTemizle();
        menu();
    }
    return 0;
}
