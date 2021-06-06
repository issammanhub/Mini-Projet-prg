#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>>

///------------------- structures ---/
typedef struct voiture
{
    int idvoiture;
    char marque[15];
    char nomvoiture[15];
    char couleur[7];
    int nbplaces;
    int prixjour;
    char enlocation[4];
} voiture;

typedef struct lv
{
    voiture car;
    struct lv *next;
} listev;

typedef struct date
{
    int ans;
    int mois;
    int jours;
} date;

typedef struct contratlocation
{
    float numcontrat;
    int idvoiture;
    int idclient;
    date debut;
    date fin;
    int cout;
} contrat;

typedef struct client
{
    int idclient;
    char nom[20];
    char prenom[20];
    int cin;
    char adresse[15];
    int telephone;
} client;

typedef struct elm  ///--liste de contrats
{
    contrat con;
    struct elm *next;
} listec;

typedef struct cli  ///--liste de clients
{
    client cl;
    struct cli *next;
} listecl;



///--- Les fonctions
void modifierc(listec **,float);
void retournerv(listev **,int ,listec **,float );
void affichev(void);
void ajoutervf(voiture *);
void ajouterv(listev **);
void modifierv(listev **,int);
void suprimerv(listev **,int);
void affc(listec *);
void affichec(listec *,float);
void remplircl(listecl *);
void testv(listev **,int);
void louerv(listecl **, listev **);
void suppcontrat(listec **,float);


///------------------- FONCTIONS -------/
///------------------- VOITURE ---------/
///------------------- afficher ---/
void affichev(void)
{
    FILE *car=fopen("voitures.txt","r");
    char ligne[200];
    if(car==NULL)
    {
        printf("erreur");
        exit(-1);
    }
    else
    {
        while(fgets(ligne,sizeof(ligne),car)!=NULL)
            printf("%s",ligne);
    }
    fclose(car);
}

///------------------- ajouter une structure de voiture a un fichier ---/
void ajoutervf(voiture *mv)
{
    FILE *car=fopen("voitures.txt","a+");
    if(car==NULL) printf("ERROR");
    else
    {
        fputs(mv->idvoiture,car);
        fputs(mv->marque,car);
        fputs(mv->nomvoiture,car);
        fputs(mv->couleur,car);
        fputs(mv->nbplaces,car);
        fputs(mv->prixjour,car);
        fputs(mv->enlocation,car);
        fclose(car);
    }
}

///------------------- ajouter une voiture a un fichier et liste ---/
void ajouterv(listev **tetev)
{
    listev *car1=(listev*)malloc(sizeof(listev));
    printf("saisir id de votre voiture: ");
    scanf("%d",car1->car.idvoiture);
    printf("saisir la marque de votre voiture: ");
    scanf("%s",car1->car.marque);
    printf("saisir le nom de votre voiture: ");
    scanf("%s",car1->car.nomvoiture);
    printf("saisir la couleur de votre voiture: ");
    scanf("%s",car1->car.couleur);
    printf("saisir le nombre de places: ");
    scanf("%d",car1->car.nbplaces);
    printf("saisir le prix par jour de votre voiture: ");
    scanf("%d",car1->car.prixjour);
    printf("la voiture est en location ?: ");
    scanf("%s",car1->car.enlocation);
    car1->next=NULL;

    if(*tetev==NULL)
    {
        *tetev=car1;
    }
    else
    {
        while((*tetev)->next!=NULL)
        {
            (*tetev)=(*tetev)->next;
        }
        (*tetev)->next=car1;
    }
    ajoutervf(car1);
}

///------------------- modification ---/
void modifierv(listev **k,int v)
{
    listev *n=*k;
    if(n==NULL)
    {
        printf( "la liste est vide!!");
        exit(-1);
    }

    while(n->car.idvoiture!=v)
    {
        n=n->next;
    }

    ///cas de v n'existe pas
    if(n==NULL)
    {
        n->car.idvoiture=v;
        printf("saisir la marque de votre voiture: ");
        scanf("%s",n->car.marque);
        printf("\n saisir  le nom de votre voiture: ");
        scanf("%s",n->car.nomvoiture);
        printf("\n saisir la couleur de votre voiture: ");
        scanf("%s",n->car.couleur);
        printf("\n saisir le nombre de places: ");
        scanf("%d",n->car.nbplaces);
        printf("\n saisir le prix par jour de votre voiture: ");
        scanf("%d",n->car.prixjour);
        printf("\n la voiture est en location ?: ");
        scanf("%s",n->car.enlocation);
        voiture car1;
        car1=(n->car);
        FILE *c=fopen("voitures.txt","w+");
        n=*k;
        while(n)
        {
            ajoutervf(&car1);
            n=n->next;
            car1=(n->car);
        }
    }
    else printf("ID de voiture invalide! \n");
}

///------------------- supression ---/
void suprimerv(listev **k,int v)
{
    listev *n=*k;
    listev *p;
    if(n==NULL)
    {
        printf( "la liste est vide!");
        exit(-1);
    }
    /// cas du 1 er element
    if(n->car.idvoiture==v)
    {
        p=n;
        n=n->next;
        free(p);
        exit(3);
    }
    /// autre cas
    while(n->next->car.idvoiture!=v || n==NULL)
    {
        n=n->next;
    }
    /// ID n'existe pas
    if(n==NULL)
    {
        printf("ID n'existe pas!");
        exit(8);
    }
    p=n->next;
    n->next=p->next;
    free(p);
    FILE *c=fopen("voitures.txt","w+");
    n=*k;
    voiture ca;
    ca=n->car;
    while(n->next)
    {
        ajoutervf(&ca);
        n=n->next;

    }
    fclose(c);
}

///------------------- LOCATION ---/
///------------------- affich contrat ---/
void affc(listec *ctr)
{
    printf("Numero du contrat: %f\n",ctr->con.numcontrat);
    printf("\nID de la voiture: %d\n",ctr->con.idvoiture);
    printf("\nID du client: %d\n",ctr->con.idclient);
    printf("\nla date du debut:%d-%d-%d\n",ctr->con.debut.jours,ctr->con.debut.mois,ctr->con.debut.ans);
    printf("\nla date du fin:%d-%d-%d\n",ctr->con.fin.jours,ctr->con.fin.mois,ctr->con.fin.ans);
    printf("\nCout: %d\n",ctr->con.cout);
    printf("\t-----------------------------------------------------------\n");
}

///------------------- VISUALISER CONTRAT ---/
void affichec(listec *ctr,float numc)
{
    listec *rech=ctr;
    if(rech==NULL)
    {
        printf("ERREUR!");
        exit(-2);
    }
    else
    {
        while(((rech)->con).numcontrat != numc && rech == NULL)
        {
            rech = rech->next;
        }

        if(rech == NULL) printf("ERREUR! n'existe pas");
        else affc(rech);

    }

}

///------------------- ajouter une structure de contrat a un fichier ---/
///------------------- remplir les info du client ---/

void remplircl(listecl *cln)
{
    client cp;
    printf("saisir id du client: ");
    scanf("%d",cp.idclient);
    printf("saisir le nom du client: ");
    gets(cp.nom);
    printf("saisir le prenom du client: ");
    gets(cp.prenom);
    printf("saisir la CIN du client: ");
    scanf("%d",cp.cin);
    printf("saisir l'adresse du client: ");
    gets(cp.adresse);
    printf("saisir le numero de telephone du client: ");
    scanf("%d",cp.telephone);

    listecl *lcp=(listecl*)malloc(sizeof(listecl));
    lcp->cl=cp;
    lcp->next=NULL;

    while(cln->next!=NULL)
        cln=cln->next;
    cln->next=lcp;
    free(lcp);

    FILE *clt=("clients.txt","a+");
    if(clt==NULL) printf("ERREUR!");
    else
    {
        fprintf(clt,"ID client: %d.\n",cp.idclient);
        fprintf(clt,"Le nom du client: %s.\n",cp.nom);
        fprintf(clt,"Le prenom du client: %s.\n",cp.prenom);
        fprintf(clt,"La cin du client: %d.\n",cp.cin);
        fprintf(clt,"L'adresse du client: %s.\n",cp.adresse);
        fprintf(clt,"Tele du client: %d.\n",cp.telephone);
        fprintf(clt,"\t-----------------------------------------------------------\n");
    }
    fclose(clt);
}
///------------------- tests de voiture ---/
void testv(listev **l,int v)
{
    listev *p=*l;
    while(p!=NULL)
    {
        if(p->car.idvoiture==v)
        {
            if(p->car.enlocation=="oui") printf("la voiture est deja louer .\n");
            else if(p->car.enlocation=="non")
            {
                printf("elle est disponible ,vous voulez louez la voiture :(oui ou non)\n");
                scanf("%s",p->car.enlocation);

                FILE *vtr=fopen("voitures.txt","w+");
                if(vtr==NULL) printf("ERREUR!");
                else
                {
                    while(p)
                    {
                        fprintf(vtr,"ID du voiture: %d.\n",p->car.idvoiture);
                        fprintf(vtr,"La marque du voiture: %s.\n",p->car.marque);
                        fprintf(vtr,"Le nom du voiture: %s.\n",p->car.nomvoiture);
                        fprintf(vtr,"La couleur du voiture: %s.\n",p->car.couleur);
                        fprintf(vtr,"Le nbr de places du voiture: %d.\n",p->car.nbplaces);
                        fprintf(vtr,"Le prix par jour: %d.\n ",p->car.prixjour);
                        fprintf(vtr,"Location: %s.\n",p->car.enlocation);
                        fprintf(vtr,"\t-----------------------------------------------------------\n");
                    }
                }
                fclose(vtr);
            }
        }
        else p=p->next;
    }
}
///------------------- louer une voiture ---/
void louerv(listecl **lcl, listev **vo)
{
    char nm[20],pnm[20],ph[200];
    int n,m;

    printf("\n saisir le nom du client: ");
    gets(nm);
    printf("\n saisir le prenom du client: ");
    gets(pnm);
    printf("saisir ID de la voiture: ");
    scanf("%d",&n);

    FILE *test=fopen("clients.txt","r");
    if(test!=NULL)
    {
        fgets(ph,sizeof(ph),test);
        while(fgets(ph,sizeof(ph),test)!=NULL)
        {
            if(strcmp(ph,nm) == 0) m=1;
            else m=0;

            if(m==0)
            {
                remplircl(&lcl);
                testv(&vo,n);
            }
            else
            {
                printf("Ce client deja louer une voiture!\n");
            }
        }

    }
}
///------------------- supprimer une contrat  et  enregistrer nv liste de contrat dans le fichier ---/
void suppcontrat(listec **b,float f)
{
    listec *t=*b;
    listec *tmp=NULL;
    while(t!=NULL)
    {
        if(t->next->con.numcontrat==f)
        {
            tmp=t->next;
            t=tmp->next;
            free(tmp);
        }
        else t=t->next;
    }
    t=*b;
    FILE *ct=fopen("contratslocations.txt","w+");
    if(t==NULL) printf("ERREUR!");
    else
    {
        while(t)
        {
            fputs(t->con.idvoiture,ct);
            fputs(t->con.idclient,ct);
            fputs(t->con.debut.ans,ct);
            fputs(t->con.debut.mois,ct);
            fputs(t->con.debut.jours,ct);
            fputs(t->con.fin.ans,ct);
            fputs(t->con.fin.mois,ct);
            fputs(t->con.fin.jours,ct);
            fputs(t->con.cout,ct);
            fprintf(ct,"%f",t->con.numcontrat);
        }
        fclose(ct);

    }
}
///------------------- retourner une voiture ---/
void retournerv(listev **j,int v,listec **h,float c)
{
    listev *p=*j;
    while(p!=NULL)
    {
        if(p->car.idvoiture==v)
        {
            printf("la voiture est encore en locatioon ? :(oui ou non)\n\t");
            scanf("%s",p->car.enlocation);

            FILE *vtr=fopen("voitures.txt","w+");
            if(vtr==NULL) printf("ERREUR!");
            else
            {
                while(p)
                {
                    fputs(p->car.idvoiture,vtr);
                    fputs(p->car.marque,vtr);
                    fputs(p->car.nomvoiture,vtr);
                    fputs(p->car.couleur,vtr);
                    fputs(p->car.nbplaces,vtr);
                    fputs(p->car.prixjour,vtr);
                    fputs(p->car.enlocation,vtr);
                }
            }
            fclose(vtr);
        }
        else p=p->next;
    }
    suppcontrat(&h,c);
}

///------------------- MODIFIER CONTRAT ---/
void modifierc(listec **a,float z)
{
    listec *q=*a;
    while(q!=NULL)
    {
        if(q->con.numcontrat==z)
        {
            printf("nouveau date du fin de contrat: ");
            scanf("%d","%d","%d",q->con.fin.jours,q->con.fin.mois,q->con.fin.ans);

        }
        else q=q->next;

    }
    q=*a;
    FILE *cr=fopen("contratslocations.txt","w+");
    if(q==NULL) printf("ERREUR!");
    else
    {
        while(q)
        {
            fputs(q->con.idvoiture,cr);
            fputs(q->con.idclient,cr);
            fputs(q->con.debut.ans,cr);
            fputs(q->con.debut.mois,cr);
            fputs(q->con.debut.jours,cr);
            fputs(q->con.fin.ans,cr);
            fputs(q->con.fin.mois,cr);
            fputs(q->con.fin.jours,cr);
            fputs(q->con.cout,cr);
            fprintf(cr,"%f",q->con.numcontrat);
        }
        fclose(cr);

    }
}
///------------------- afficher la liste des clients ---/
void affichecl(void)
{
    FILE *cl=fopen("clients.txt","r");
    char ligne[200];
    if(cl==NULL)
    {
        printf("ERREUR!");
        exit(-1);
    }
    else
    {
        while(fgets(ligne,sizeof(ligne),cl)!=NULL)
            printf("%s",ligne);
    }
    fclose(cl);
}

///------------------- modifer la liste des clients ---/
void modifiercl(listecl **cl, int idc)
{
    listecl *n=*cl;
    client cp;
    if(n==NULL)
    {
        printf( "la liste est vide!");
        exit(-1);
    }

    while(n->cl.idclient!=idc)
    {
        n=n->next;
    }

    if(n==NULL)
    {
        printf("ERREUR!");
    }
    else
    {
        cp.idclient=idc;
        printf("saisir le nom du client: ");
        gets(cp.nom);
        printf("saisir le prenom du client: ");
        gets(cp.prenom);
        printf("saisir la cin du client: ");
        scanf("%d",cp.cin);
        printf("saisir l'adresse du client: ");
        gets(cp.adresse);
        printf("saisir le numero de telephone du client: ");
        scanf("%d",cp.telephone);
        n->cl=cp;
    }
    FILE *fcl=fopen("clients.txt","w+");

    if(fcl==NULL) printf("ERREUR!");
    else
    {
        fputs(cp.idclient,fcl);
        fputs(cp.nom,fcl);
        fputs(cp.prenom,fcl);
        fputs(cp.cin,fcl);
        fputs(cp.adresse,fcl);
        fputs(cp.telephone,fcl);
    }
    fclose(fcl);
}

///------------------- suprimer la liste des clients ---/
void suprimercl(listecl **cl, int idc)
{
    listecl *t=*cl;
    listecl *tmp=NULL;

    while(t!=NULL)
    {
        if(t->next->cl.idclient==idc)
        {
            tmp=t->next;
            t=tmp->next;
            free(tmp);
        }
        else t=t->next;
    }

    if(t==NULL) printf("ERREUR");
    else
    {
        FILE *fcl=fopen("clients.txt","w+");
        while(t)
        {
            if(fcl==NULL) printf("ERREUR!");
            else
            {
                fputs(t->cl.idclient,fcl);
                fputs(t->cl.nom,fcl);
                fputs(t->cl.prenom,fcl);
                fputs(t->cl.cin,fcl);
                fputs(t->cl.adresse,fcl);
                fputs(t->cl.telephone,fcl);
                t=t->next;
            }
        }
        fclose(fcl);
    }
}

///------------------- Menu Principal -------------------/
int menuep(void)
{
    system("cls");
    int choix;
    printf("         **** Menu Principal ****\n");
    printf("\nLocation ............................. 1\n");
    printf("\nGestion voitures ..................... 2\n");
    printf("\nGestion clients ...................... 3\n");
    printf("\nQuitter .............................. 4\n");

    do
    {
        printf("\n\t\t\tVotre choix : ");
        scanf("%d",&choix);
    }
    while(choix < 1 || choix > 4);
    printf("\n");

    return choix;
}

///------------------- Menu de Location -------------------/
int menuelo(void)
{
    system("cls");
    int choix;
    printf("       **** Location d'une voiture ****\n");
    printf("\nVisualiser contrat ..................... 1\n");
    printf("\nLouer voiture .......................... 2\n");
    printf("\nRetourner voiture ...................... 3\n");
    printf("\nModifier contrat ....................... 4\n");
    printf("\nSupprimer contrat ...................... 5\n");
    printf("\nRetour ................................. 6\n");

    do
    {
        printf("\n\t\t\tVotre choix : ");
        scanf("%d",&choix);
    }
    while(choix < 1 || choix > 6);
    printf("\n");

    return choix;
}

///------------------- Menu de Gestion voitures -------------------/
int menuev(void)
{
    system("cls");
    int choix;
    printf("      **** Gestion des voitures ****\n");
    printf("\nListe des voitures ..................... 1\n");
    printf("\nAjouter voiture ........................ 2\n");
    printf("\nModifier voiture ....................... 3\n");
    printf("\nSupprimer voiture ...................... 4\n");
    printf("\nRetour ................................. 5\n");

    do{
    printf("\n\t\t\tVotre choix : ");
    scanf("%d",&choix);
    }while(choix < 1 || choix > 5);
    printf("\n");

    return choix;
}

///------------------- Menu de Gestion clients -------------------/
int menuec(void)
{
    system("cls");
    int choix;
    printf("       **** Gestion des clients ****\n");
    printf("\nListe des clients ..................... 1\n");
    printf("\nAjouter client ........................ 2\n");
    printf("\nModifier client ....................... 3\n");
    printf("\nSupprimer client ...................... 4\n");
    printf("\nRetour ................................ 5\n");

    do
    {
        printf("\n\t\t\tVotre choix : ");
        scanf("%d",&choix);
    }
    while(choix < 1 || choix > 5);
    printf("\n");

    return choix;
}

///-------------------  /

int main(){
    int choimp=menuep();
    int choilo=0,choiv=0,choic=0;

    listev **tetev;
    int idvm,idvs;
    float numc;

    listec **ctr;
    listecl **lcl;

    int idvr;
    float numcr,numcm,numcs;

    int idcm,idcs;

        /****** Menu principal *****/
        switch (choimp){
            case 1:
                choilo=menuelo();
                break;
            case 2:
                choiv=menuev();
                break;
            case 3:
                choic=menuec();
                break;
            case 4:
                exit(5);
                //break;
        }
        /****** Menu de Location *****/
        switch (choilo){
            case 1:
                printf("Saisir lenumero de conrta: ");
                scanf("%f",&numc);
                affichec(ctr,numc);
                break;
            case 2:
                louerv(lcl,tetev);
                break;
            case 3:
                printf("Saisir id de voirture à retourner: ");
                scanf("%d",&idvr);
                printf("Saisir le numero de conrtat à retourner: ");
                scanf("%f",&numcr);
                retournerv(tetev,idvr,ctr,numcr);
                break;
            case 4:
                printf("Saisir le numero de conrtat à modifier: ");
                scanf("%f",&numcm);
                modifierc(ctr,numcm);
                break;
            case 5:
                printf("Saisir le numero de conrtat à supprimer: ");
                scanf("%f",&numcs);
                suppcontrat(ctr,numcs);
                break;
            case 6:
                choimp=menuep();
                break;
        }
        /****** Menu de Gestion voitures *****/
        switch (choiv){
            case 1:
                affichev();
                break;
            case 2:
                ajouterv(tetev);
                break;
            case 3:
                printf("Saisir id de voirture à modifier");
                scanf("%d",&idvm);
                modifierv(tetev,idvm);
                break;
            case 4:
                printf("Saisir id de voirture à suprimer");
                scanf("%d",&idvs);
                suprimerv(tetev,idvs);
                break;
            case 5:
                choimp=menuep();
                break;
        }
        /****** Menu de Gestion clients *****/
        switch (choic){
            case 1:
                affichecl();
                break;
            case 2:
                remplircl(lcl);
                break;
            case 3:
                printf("Saisir id client à modifier");
                scanf("%d",&idcm);
                modifiercl(lcl,idcm);
                break;
            case 4:
                printf("Saisir id client à suprimer");
                scanf("%d",&idcs);
                suprimercl(lcl,idcs);
                break;
            case 5:
                choimp=menuep();
                break;
        }
}
