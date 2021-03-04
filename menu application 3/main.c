/* Datele de intrare vor fi intr-un fisier text denumit: "proiect.txt". Acestea vor fi inregistrari de forma: id(%d), nume(%s), produs(%s),cantitate(%d), oras(%s).
Datele vor fi citite din fisier si se va afisa lista ordonata descrescator dupa nume proiect, iar pt acelasi nume ordinea va fi crescatoare dupa cantitate.
Se va creea tipul de data proiect, ce va avea ca ele,mente date despre proiect, tipul de data Nod ce va contine si va face legatura catre proiect curent, predecesoredent si urmator,
 fiind astfel o lista dublu inlantuita si tipul de data lista ce va contine Nod.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *nume;
    int cantitate;
    int id;
    char *oras;
    char *produs;
} Proiect;

typedef struct nod
{
    Proiect *p;
    struct nod* predecesor,*urmator;

} Nod;

typedef struct
{
    Nod *primul, *ultimul,*curent;
    int dimensiune;

} Lista;

Proiect *Alocare_Proiect(int id,char *nume,char *produs,int cantitate,char *oras)
{
    Proiect *p=(Proiect*)malloc(sizeof(Proiect));
    p->nume=(char*)malloc((strlen(nume)+1)*sizeof(char));
    p->oras=(char*)malloc((strlen(oras)+1)*sizeof(char));
    p->produs=(char*)malloc((strlen(produs)+1)*sizeof(char));
    strcpy(p->nume,nume);
    strcpy(p->oras,oras);
    strcpy(p->produs,produs);
    p->id=id;
    p->cantitate=cantitate;

    return p;
}
Lista* Aloca_Lista()
{
    Lista *l=(Lista*)malloc(sizeof(Lista));
    l->primul=l->ultimul=NULL;
    return l;
}

Nod *Aloca_nod(Proiect *p)
{
    Nod *nod=(Nod*)malloc(sizeof(Nod));
    nod->predecesor=nod->urmator=NULL;
    nod->p=p;
    return nod;

}
void Cauta(Lista *l,Nod *nod)
{
    int fan;
    l->curent=l->primul;
    while(l->curent)
    {
        fan=strcmp(nod->p->nume,l->curent->p->nume);
        if(fan==0)
        {
            if(nod->p->cantitate<l->curent->p->cantitate)
            {
                return;
            }
            else
            {
                l->curent=l->curent->urmator;
            }
        }else
        if(fan>0)
        {
            return;
        }
        else
        {
            l->curent=l->curent->urmator;

        }
    }

}

void Add_ultimul(Lista *l,Nod *nod)
{


    l->dimensiune++;
    if(l->primul==NULL)
    {

        l->primul=l->ultimul=nod;

    }
    else
    {
        nod->predecesor=l->ultimul;
        l->ultimul->urmator=nod;
        l->ultimul=nod;
    }

}

void Add_primul(Lista *l,Nod *nod)
{
    l->dimensiune++;
    nod->urmator=l->primul;
    if(l->primul==NULL)
    {
        l->primul=l->ultimul=nod;

    }
    else
    {
        l->primul->predecesor=nod;

        l->primul=nod;

    }


}

void Afisare(Lista *l1)
{
    if(l1->primul!=NULL)
    {

        l1->curent=l1->primul;
        while(l1->curent)
        {
            printf(" Id= %d Nume= %s produs= %s  cantitate=%d oras=%s ",l1->curent->p->id,l1->curent->p->nume,l1->curent->p->produs,l1->curent->p->cantitate,l1->curent->p->oras);

            l1->curent=l1->curent->urmator;

        }
    }
    else
    {
        printf("Lista este goala\n");
    }
}
void Insert_nod(Lista *l1,Nod *nod)
{
    l1->dimensiune++;
    nod->predecesor=l1->curent->predecesor;
    nod->urmator=l1->curent;
    if(l1->curent->predecesor!=0)
    {
        l1->curent->predecesor->urmator=nod;

    }
    l1->curent->predecesor=nod;

    if(l1->curent==l1->primul)
    {
        l1->primul=nod;
    }

}

void stocare(Lista *l1)
{
    l1->curent=l1->primul;
    FILE *f=fopen("proiect.out","w");
    if(f==NULL)
    {
        printf("Fisierul nu se deschide!!\n");
        exit(1);
    }

    while(l1->curent!=NULL)
    {

         if(l1->curent->urmator!=NULL)
         {
             fprintf(f,"%d,%s,%s,%d,%s\n",l1->curent->p->id,l1->curent->p->nume,l1->curent->p->produs,l1->curent->p->cantitate,l1->curent->p->oras);
          }else
          {

                 fprintf(f,"%d,%s,%s,%d,%s ",l1->curent->p->id,l1->curent->p->nume,l1->curent->p->produs,l1->curent->p->cantitate,l1->curent->p->oras);
          }
         l1->curent=l1->curent->urmator;
    }
    fclose(f);
}

void Populare(Lista **l1)
{
    FILE *f=fopen("proiect.txt","r");

    if(f==NULL)
    {
        printf("Nu se poate deschide fisierul!!!\n");
        return;
    }
    char sir[500];
    while(!feof(f))
    {
        if(fgets(sir,500,f)!=NULL)
        {

            Proiect *p=NULL;
            char *id=strtok(sir,",");
            char *nume=strtok(NULL,",");  //Am pus NULL intentionat acolo
            char *produs=strtok(NULL,",");
            char *cantitate=strtok(NULL,",");
            char *oras=strtok(NULL,",");

            oras[strlen(oras)-1]='\0';
            p=Alocare_Proiect(atoi(id),nume,produs,atoi(cantitate),oras);
            Nod *nod=Aloca_nod(p);
               if((*l1)->primul==NULL)
    {
        Add_ultimul((*l1),nod);
    }
    else
    {
        Cauta((*l1),nod);
        if((*l1)->curent!=NULL)
        {
            Insert_nod((*l1),nod);
        }
        else
        {
            Add_ultimul((*l1),nod);

        }
    }
        }
    }

}

int main()
{
    Lista *l1=NULL;
    l1=Aloca_Lista();
    Populare(&l1);
    int optiune;
    while(1)
    {
        printf("optiune 1afisare 2iesire\n");
        printf("introduce optiunea: ");
        scanf("%d",&optiune);
        switch(optiune)
        {

        case 1:
        {
            Afisare(l1);
            break;

        }

        case 2:
        {
            stocare(l1);
            printf("La revedere!!\n");
            return 0;
            break;
        }

        default:
        {
            printf("Introduce optiunea din nou este gresita!!\n");
            break;
        }

        }
    }

    return 0;
}
