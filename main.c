/*
BUT:Jeu du pendu
ENTREE:une chaine d'un ou plusieurs caracteres
SORTIE:la validite ou non du mot/ de la lettre entre(e)
PROGRAMME pendu

CONST
    ALPHA="abcdefghijklmnopqrstuvwxyz"  //repertorie l'alphabet

VAR
    motEtoile,motCache,motCherche:CHAINE
    essai,fin,gagne,perdu:ENTIER

---------------------------PROCEDURES ET FONCTIONS----------------------------

BUT: tester si tout les caracteres entrees sont bien une ou des lettres minuscules
ENTREE: une chaine de 1 a N caracteres
SORTIE: un entier servant de booleen vrai/faux
FONCTION testMotValid(mot:CHAINE):ENTIER
var
    i,j:ENTIER
DEBUT
    i<-0
    j<-0
    POUR i<-1 A LONGUEUR(mot) FAIRE
    DEBUT
        POUR j<-1 A LONGUEUR(ALPHA) FAIRE
        SI mot[i]=ALPHA[j] ALORS    // on teste si tout les caracteres de la chaine sont bien inclus dans (ALPHA)
            j<-j+1
        FINSI
    FINPOUR

    SI j= LONGUEUR(mot) ALORS
        testMotValid=1
    SINON
        testMotValid=0
    FINSI
FINFONCTION

------------------------------------------------------------------------------

BUT:initialiser le mot cache (motCache) correctement
ENTREE: une chaine (motCache)
SORTIE: la meme chaine validee
PROCEDURE initMotCache(motCache:CHAINE)
DEBUT
    REPETER
        ECRIRE"entrez le mot cache, pas de chiffre ou de caracteres speciaux SVP"
        LIRE motCache
        EFFACE ECRAN
    JUSQUA (LONGUEUR(motCache)>1) ET (testMotValid(motCache)=1)
FINPROCEDURE

------------------------------------------------------------------------------

BUT:Initialise (motEtoile) pour qu'il fasse la meme taille que (motCache)
ENTREE:une chaine
SORTIE:motEtoile initialise
PROCEDURE initMotEtoile(motEtoile:CHAINE,motCache:CHAINE)
var
    i:ENTIER
DEBUT
    POUR i<-1 A LONGUEUR(motCache) FAIRE
        motEtoile[i]<-"*"
    FINPOUR
FINPROCEDURE

------------------------------------------------------------------------------

BUT:tester si le joueur a trouve le mot complet
ENTREE:une chaine de 1 a N caracteres
SORTIE:un entier (gagne) servant de booleen recupere la reponse du test
PROCEDURE testOneShot(mot:CHAINE,var gagne:ENTIER)
DEBUT
    SI mot=motCache ALORS
        gagne<-1
    SINON
        gagne<-0
    FINSI
FINPROCEDURE

------------------------------------------------------------------------------

BUT:tester si la chaine de 1 caractere entree est bien dans le mot recherche
ENTREE: une chaine de 1 caractere
SORTIE: (motEtoile) est edite si la chaine de 1 caractere entree est bien dans le mot cherche
PROCEDURE testLettre(motCherche:CHAINE,motCache:CHAINE,var motEtoile:CHAINE)
var
    i:ENTIER
DEBUT
    i<-0
    POUR i<-1 A LONGUEUR(motCache) FAIRE
        SI motcherche[1]=motCache[i] ALORS  // si une lettre est bien au meme emplacement elle remplace une etoile de (motEtoile) par la bonne lettre
            motEtoile[i]<-motCache[i]
        FINSI
    FINPOUR

FINPROCEDURE

------------------------------------------------------------------------------

BUT:afficher la phrase de debut de tour de jeu
ENTREE:(motEtoile) pour pouvoir l'afficher
SORTIE: un texte s'affiche
PROCEDURE affichage(motEtoile:CHAINE)
DEBUT
    ECRIRE motEtoile
    ECRIRE"entrez un caractère pour chercher le mot cache ou tenter d'ecrire ce mot directement"
    ECRIRE"pas de caracteres speciaux ou de majuscules"
FINPROCEDURE


-------------------------FIN PROCEDURES ET FONCTIONS--------------------------

DEBUT

-------------------------INITIALISATION DES VARIABLES-------------------------

motEtoile<-''
motCache<-''
motCherche<-''
essai<-0
fin-<0
gagne<-0
perdu<-0

-----------------------FIN INITIALISATION DES VARIABLES-----------------------

REPETER

    perdu<-0
    initMotCache(motCache)
    essai<-LONGUEUR(motCache)
    initMotEtoile(motEtoile,motCache)

-------------------------------DEBUT TOUR DE JEU------------------------------

    REPETER
        REPETER
            gagne<-0
            affichage(motEtoile)
            LIRE motCherche
            EFFACER ECRAN
        JUSQUA testMotValid(motCherche)=1

        testOneShot(motCherche,gagne) // on teste si le joueur a entre le mot complet

        SI (gagne=0) ET (LONGUEUR(motCherche)=1) ALORS // si le joueur a entre une chaine avec un sul caractere on test s'il a trouve le mot
        DEBUT
            testLettre(motCherche,motCache,motEtoile)   //teste la lettre seule
            testOneShot(motEtoile,gagne)    //teste si apres avoir ajoute la lettre, le joueur a trouve toutes les lettres
        FIN
        FINSI

        SI gagne=0 ALORS //si le joueur n'a pas trouve le mot, il perd un essai et passe au tour suivant
            essai=essai-1
        FINSI

        SI essai=0 ALORS //si le joueur n'as plus d'essai il perd
        DEBUT
            ECRIRE "Vous avez perdu..."
            perdu<-1
        FIN
        FINSI

    JUSQUA (gagne=1) OU (perdu=1)

--------------------------------FIN TOUR DE JEU-------------------------------

    SI gagne=1 ALORS    //n'affiche la ligne du dessous que si le joueur a gagne
        ECRIRE"Vous avez trouve le mot " & motCache & " , BRAVO !"
    FINSI

    REPETER
        ECRIRE "voulez-vous quitter ? (oui=1/non=0)
        LIRE fin
    JUSQUA (fin=1 OU fin=0)


JUSQUA fin=1

FINGROGRAMME
*/

/*
BUT:Jeu du pendu
ENTREE:une chaine d'un ou plusieurs caracteres
SORTIE:la validite ou non du mot/ de la lettre entre(e)*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHA "abcdefghijklmnopqrstuvwxyz"
#define LGCHAINE 26

int testMotValid(char mot[LGCHAINE],int *lgmot);
void initMotCache(char motCache[LGCHAINE],int *lgmot);
void initMotEtoile(char motEtoile[LGCHAINE],char motCache[LGCHAINE],int *lgmot);
void testOneShot(char mot[LGCHAINE],int *gagne,char motCache[LGCHAINE]);
void testLettre(char motCherche[LGCHAINE],char motCache[LGCHAINE],char motEtoile[LGCHAINE],int *lgmot);
void affichage(char motEtoile[LGCHAINE]);
void tailleEssai(char motCherche[LGCHAINE],int *lgmotEssai);

int main()
{
//--------------------------DECLARATION DES VARIABLES--------------------------
    char motEtoile[LGCHAINE];
    char motCache[LGCHAINE];
    char motCherche[LGCHAINE];
    int essai=0;
    int fin=0;
    int gagne=0;
    int perdu=0;
    int lgmot=0;
    int lgmotEssai=0;
//------------------------FIN DECLARATION DES VARIABLES------------------------
    do
    {
//-------------------------INITIALISATION DES VARIABLES-------------------------
        puts("manche suivante");
        motEtoile[0]='\0';
        motCache[0]='\0';
        motCherche[0]='\0';
        fin=0;
        gagne=0;
        perdu=0;
        lgmot=-1;
        initMotCache(motCache,&lgmot);
        initMotEtoile(motEtoile,motCache,&lgmot);
        essai=lgmot;

//-----------------------FIN INITIALISATION DES VARIABLES-----------------------

//-------------------------------DEBUT TOUR DE JEU------------------------------

        do
        {
            puts("tour suivant");
            do
            {
                gagne=0;
                lgmotEssai=0;
                affichage(motEtoile);
                printf("il vous reste %d essais\n",essai);
                gets(motCherche);
                tailleEssai(motCherche,&lgmotEssai);
                system("cls");
            }
            while (testMotValid(motCherche,&lgmot)==1);
            //printf("%d %s %s %s",lgmot,motCherche,motEtoile,motCache);
            testOneShot(motCherche,&gagne,motCache); // on teste si le joueur a entre le mot complet

            if((gagne==0) && (lgmotEssai==1)){ // si le joueur a entre une chaine avec un sul caractere on test s'il a trouve le mot
                testLettre(motCherche,motCache,motEtoile,&lgmot);   //teste la lettre seule
                testOneShot(motEtoile,&gagne,motCache);    //teste si apres avoir ajoute la lettre, le joueur a trouve toutes les lettres
            }

            if(gagne==0){ //si le joueur n'a pas trouve le mot, il perd un essai et passe au tour suivant
                essai--;
            }

            if(essai==0){  //si le joueur n'as plus d'essai il perd
                puts("Vous avez perdu...");
                perdu=1;
            }
        }
        while ((gagne==0)&&(perdu==0));

//--------------------------------FIN TOUR DE JEU-------------------------------

        if(gagne==1){    //n'affiche la ligne du dessous que si le joueur a gagne
            printf("Vous avez trouve le mot %s , BRAVO !",motCache);
        }
        do
        {
            puts("voulez-vous quitter ? (oui=1/non=0)");
            scanf("%d",&fin);
        }
        while((fin>1)||(fin<0));

    }
    while(fin==0);

    return EXIT_SUCCESS;
}
/*---------------------------PROCEDURES ET FONCTIONS----------------------------

BUT: tester si tout les caracteres entrees sont bien une ou des lettres minuscules
ENTREE: une chaine de 1 a N caracteres
SORTIE: un entier servant de booleen vrai/faux*/
int testMotValid(char mot[LGCHAINE],int *lgmot){
    int i=0;
    int j=0;
    int test=0;
    for (i=0;i<=*lgmot-1;i++){
        for (j=0;j<=strlen(ALPHA);j++){    // on teste si tout les caracteres de la chaine sont bien inclus dans (ALPHA)
            if (mot[i]==ALPHA[j]) {
            }
                test++;
        }
    }

    if(test==*lgmot-1){
        return 1;
    }
    else{
        return 0;
    }
}

/*------------------------------------------------------------------------------

BUT:initialiser le mot cache (motCache) correctement
ENTREE: une chaine (motCache)
SORTIE: la meme chaine validee*/
void initMotCache(char motCache[LGCHAINE],int *lgmot){
    fflush(stdin);
    do
    {
        printf("entrez le mot secret, pas de chiffre ou de caracteres speciaux SVP \n");
        gets(motCache);
        do
        {
            *lgmot=*lgmot+1;
        }
        while (motCache[*lgmot]!='\0');
        system("cls");
    }
    while((strlen(motCache)>1) && (testMotValid(motCache,lgmot)==1));
}

/*------------------------------------------------------------------------------

BUT:Initialise (motEtoile) pour qu'il fasse la meme taille que (motCache)
ENTREE:une chaine
SORTIE:motEtoile initialise*/
void initMotEtoile(char motEtoile[LGCHAINE],char motCache[LGCHAINE],int *lgmot){
    int i=0;
    for (i=0;i<=*lgmot-1;i++){
        motEtoile[i]='*';
    }
    motEtoile[*lgmot]='\0';
}

/*------------------------------------------------------------------------------

BUT:tester si le joueur a trouve le mot complet
ENTREE:une chaine de 1 a N caracteres
SORTIE:un entier (gagne) servant de booleen recupere la reponse du test*/
void testOneShot(char mot[LGCHAINE],int *gagne,char motCache[LGCHAINE]){
    if(strcmp(mot,motCache)==0){
        *gagne=1;
    }
    else{
        *gagne=0;
    }
}

/*------------------------------------------------------------------------------

BUT:tester si la chaine de 1 caractere entree est bien dans le mot recherche
ENTREE: une chaine de 1 caractere
SORTIE: (motEtoile) est edite si la chaine de 1 caractere entree est bien dans le mot cherche*/
void testLettre(char motCherche[LGCHAINE],char motCache[LGCHAINE],char motEtoile[LGCHAINE],int *lgmot){
    int i=0;

    for(i=0;i<=*lgmot;i++){
        if(motCherche[0]==motCache[i]){  // si une lettre est bien au meme emplacement elle remplace une etoile de (motEtoile) par la bonne lettre
            motEtoile[i]=motCache[i];
        }
    }

}

/*------------------------------------------------------------------------------

BUT:afficher la phrase de debut de tour de jeu
ENTREE:(motEtoile) pour pouvoir l'afficher
SORTIE: un texte s'affiche*/
void affichage(char motEtoile[LGCHAINE]){
    puts(motEtoile);
    puts("entrez un caractere pour chercher le mot cache ou tenter d'ecrire ce mot directement");
    puts("pas de caracteres speciaux ou de majuscules");
}

/*------------------------------------------------------------------------------

BUT:recuperer la taille de la chaine entree par le joueur
ENTREE:la chaine du joueur
SORTIE:la taille de ladite chaine*/
void tailleEssai(char motCherche[LGCHAINE],int *lgmotEssai){
    do
    {
        *lgmotEssai=*lgmotEssai+1;
    }
    while (motCherche[*lgmotEssai]!='\0');
}

/*-------------------------FIN PROCEDURES ET FONCTIONS------------------------*/
