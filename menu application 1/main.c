/*
Datele de intrare sunt date citite din fiser (pe fiecare linie din fisier avem informatiile legate de un produs:id,nume,culoare,masa,
                oras,separate cu virgula) si datele introduse de utilizator de la tastatura,adica id-ul pentru cautare
Date de iesire sunt afisarea rezultatului cautarii dupa nume in tabel, afisarea dupa stergerea unui produs sau afisearea pur si simplu a datelor de intrare.
           La cautarea dupa id , fom folosi un mesaj corespunzator in caz ca nu avem un produs cu acel id , in acest caz vom afisa mesajul :"nu exista produsul in tabela",
           iar la stergere la fel un mesaj corespunzator , daca produsul pe care vrem sa il stergem nu exita.
Metoda de rezolvare : Am declarat o structura Date de care ne vom folosi pentru a insera datele,apoi am declarat un vector de
                    pointeri la structura noastra care va contine adresa de inceput a fiecarei liste.Vom folosi functia de dispersie.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 32
typedef struct
{
    int id;
    char *nume;
    char *culoare;
    int masa;
    char *oras;

} Date;


typedef struct tip_nod
{
    Date *date;
    struct tip_nod *urm;
} Tip_nod;
Tip_nod *HT[M];


int f_d(int k)
{

    return k % M;
}

Date *aloca_date( int id,char *nume, char *culoare,int masa,char *oras)
{
    Date *date=(Date*)malloc(sizeof(Date));
    date->culoare=(char*)malloc((strlen(culoare)+1)*sizeof(char));
    date->nume=(char*)malloc((strlen(nume)+1)*sizeof(char));
    date->oras=(char*)malloc((strlen(oras)+1)*sizeof(char));

    date->id=id;
    date->masa=masa;
    strcpy(date->culoare,culoare);
    strcpy(date->nume,nume);
    strcpy(date->oras,oras);
    return date;
}

Tip_nod* cautare(int id)
{

    int h=f_d(id);
    Tip_nod * p=HT[h];
    while(p)
    {
        if(id==p->date->id)
            return p;
        p=p->urm;
    }
    return 0;
}

void citire()
{
    FILE *f=fopen("Produs.txt","r");
    if(!f)
    {
        exit(1);
    }
    int i;
    for(i=0; i<M; i++)
        HT[i]=0;
    char sir[500];

    while(!feof(f))
    {
        if(fgets(sir,500,f)!=NULL)
        {

            int id=atoi(strtok(sir,","));
            char *nume=strtok(NULL,",");
                        char *culoare=strtok(NULL,",");
            int masa=atoi(strtok(NULL,","));
            char *oras=strtok(NULL,",");

            oras[strlen(oras)-1]='\0';
            Date *date=aloca_date(id,nume,culoare,masa,oras);

            Tip_nod *  p=(Tip_nod*)malloc(sizeof(Tip_nod));
            p->date=date;

            int h=f_d(id);
            if(HT[h]==0)
            {
                HT[h]=p;
                p->urm=0;
            }
            else
            {
                p->urm=HT[h];
                HT[h]=p;

            }

        }
    }

}

void Sterge()
{
    int id;
    printf("id: ");
    scanf("%d",&id);

    int h=f_d(id);
    Tip_nod * p=HT[h];

    while(p)
    {
        if(id==p->date->id)
        {

            free(p);
            HT[h]=0;
            break;
        }

        p=p->urm;
    }

    if(p==0)
    {
        printf("Nu se regaseste produs in tabel");
    }
}


void Afisare()
{
    int i;
    for(i=0; i<M; i++)
    {
        if(HT[i]!=0)
        {
            Tip_nod*  p=HT[i];
            while(p!=0)
            {
                printf("Id: %d; Nume: %s; Culoare: %s; Masa: %d; Oras: %s; \n",p->date->id,p->date->nume,p->date->culoare,p->date->masa,p->date->oras);
                p=p->urm;
            }

        }

    }

}


int main()
{
    int optiune;
    citire();
    while(1)
    {
        printf("Optiunii: \n 1 Afisare  \n 2 Sterge \n 3. Cautare \n 4. Exit\n");
        scanf("%d",&optiune);

        switch(optiune)
        {

        case 1:
        {
            Afisare();
            break;
        }
        case 2:
        {
            Sterge();
            break;
        }
        case 3:
        {
            int id;
            printf("Id: ");

            scanf("%d",&id);
            Tip_nod *p=cautare(id);
            printf("Id: %d; Nume: %s;Culoare: %s Masa: %d; Oras: %s; \n",p->date->id,p->date->nume,p->date->culoare,p->date->masa,p->date->oras);

            break;

        }
         case 4:
        {
            return 0;
            break;
        }
        default:
        {

            break;
        }
        }
    }
    return 0;
}
