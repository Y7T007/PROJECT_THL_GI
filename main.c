#include <stdio.h>
#include "stdlib.h"

//     PARTIE 1 :

struct automates{
    int nombre_d_etat;
    int entree;
    int nombre_sorties;
    int sortie[50];
    char transitions[100][100];
    int etats[100];
};

struct automates remplissage_automate(){
    struct automates automate_1;

// INSERTIONS DE DONNEES DANS NOTRE STRUCTURE PAR LES INFOS SAISIS PAR L'UTILISATEUR
    printf("\nVeuillez saisir l'etat de depart :  ");
    scanf("%d",&automate_1.entree);

    printf("\nVeuillez le nombre de sortie[] :  ");
    scanf("%d",&automate_1.nombre_sorties);

    for (int i = 0; i < automate_1.nombre_sorties; ++i) {
        printf("\nVeuillez saisir l'etat de sortie[%d] :  ",i);
        scanf("%d",&automate_1.sortie[i]);
    }

    printf("\nVeuillez saisir le nombre des etats  :  ");
    scanf("%d",&(automate_1.nombre_d_etat));

    printf("\n\nVeuillez saisir l'ensemble des etats ordonnees de l'entree a la sortie[] ");

    for (int i = 0; i < automate_1.nombre_d_etat; ++i) {
        printf("\nSaissez le %d eme etat : ",i);
        scanf("%d",&automate_1.etats[i]);
    }

    printf("\nVeiillez saisissez les alphabets de transitions entre differents etats de votre automate  selon les transitions demandes. \n");

    for (int i = 0; i < automate_1.nombre_d_etat; ++i) {
        for (int j = 0; j < automate_1.nombre_d_etat; ++j) {
            printf("%d ---> %d : ",i,j);
            scanf("%s",&automate_1.transitions[i][j]);
        }
    }
    return automate_1;
}
void creer_dot_fichier(struct automates automates_1,FILE *ptr){

//    ON CONBINE LES DONNEES CONTENU DANS NOTRE STRUCTURE AVEC LA STRUCTURE DU FICHIERS .DOT

//LE POINTEUR *PTR POINTE SUR LE FICHIER .DOT SUR LE QUEL ON STOCKERA NOTRE GRAPH

    fprintf(ptr,"digraph test_graph{\ne[ label=\"ENTREE\" shape=none]\n"
                "s[ label=\"SORTIE\" shape=none]");
    for (int i = 0; i < (automates_1.nombre_d_etat ); ++i) {
        fprintf(ptr,"\n%d [label=\"%d\"]",automates_1.etats[i],automates_1.etats[i]);
    }
    fprintf(ptr,";");
        for (int i = 0; i < (automates_1.nombre_d_etat ); ++i) {
            if(automates_1.entree==automates_1.etats[i]){
                fprintf(ptr, "\ne -> %d  ;",automates_1.etats[i]);
            }
            for (int j = 0; j < automates_1.nombre_d_etat; ++j) {
                if((automates_1.sortie[j]==automates_1.etats[i])&&(automates_1.sortie[j]!=0)){
                    fprintf(ptr, "\n%d -> s ;",automates_1.etats[i]);

                }
                if((automates_1.transitions[i][j]!='-') && (automates_1.transitions[i][j]!='\0')){
                    fprintf(ptr, "\n%d -> %d [label=\"%c\" color=grey81 ] ",i,j,automates_1.transitions[i][j]);
                }
            }
        }
    fprintf(ptr,"}");
}
struct automates creer_fichier_texte(struct automates automate_1 ,FILE *ptr){


//    ON TRADUIT LES DONNEES RELATIVES AUX TRANSITIONS A UN FICHIER TEXTE SELON LA STRUCTURE SUIVANTE :
//ETAT_DEPART   ETAT_ARRIVEE  TRANSITION
    for (int i = 0; i < automate_1.nombre_d_etat; ++i) {
        for (int j = 0; j < automate_1.nombre_d_etat; ++j) {
            fprintf(ptr,"%d %d %c\n",i,j,automate_1.transitions[i][j]);
        }
    }

    fprintf(ptr,"%d\n ",automate_1.entree);
        for (int i = 0; i < automate_1.nombre_sorties; ++i) {
            fprintf(ptr,"%d ",automate_1.sortie[i]);

        }

    return automate_1;
}
struct automates lire_fichier_texte(FILE *ptr){
    struct automates automate_1;
//    LES DONNEES RELATIVES AUX TRANSITIONS SONT STOCKER DANS UN FICHIER TEXTE SELON LA STRUCTURE SUIVANTE :
//ETAT_DEPART   ETAT_ARRIVEE  TRANSITION

        if(!ptr){
            printf("\n L'ouverture du fichier a echoue   \n");

        }
//LE TABLEAU LINE FAIT REFERANCE A CHAQUE LIGNE ECRITE DANS LE FICHIER TXT
        char line[500];
//        DATA EST LE TABLEAU TEMPORAIRE DANS LEQUEL ON STOCKERA LES TRANSITIONS ET LES ETAT SIMULTANEMANT COMME SUIVANT:
//ETAT_DEPART   ETAT_ARRIVEE  TRANSITION

        char data[500][500];
//        LA VARIABLE J SIGNIFIE LA LIGNE ACTUEL ET A LA FIN IL VAIT ETRE AUTOMATIQUEMENT LA VALEUR DES NOMBRES DE LIGNES EXISTANTES
        int j=0;
        automate_1.nombre_d_etat=0;

//        CETTE BOUCLE WHILE NOUS PERMET DE SCANNER LES LIGNES A PARTIR DU FICHIER TEXTE JUSQU'ON A PLUS DE LIGNES QUI CONTIENNENT DES CHAR

        while (fgets(line, sizeof(line), ptr)) {
            for (int i = 0;line[i]!='\0' ; ++i) {
                data[j][i]=line[i];

                for (int k = 1; k <sizeof(line); ++k) {
                    if(automate_1.nombre_d_etat<(data[k][0]-48)){
                        automate_1.nombre_d_etat=(data[k][0]-48);
                        printf("%d",automate_1.nombre_d_etat);
                    }
                }
            }
//CETTE INCREMENTATION NOUS PERMET DE CONTER COMBIEN EN A SCANNER DE LIGNES AINSI QU'IL NOUS PERMET DE SAISIR LES DONNEES DANS LA TABLE DATA DONS CA BONNE LIGNE
            j++;
        }
//        LA COLONNE 0 CONTIENT LES ETATS DE DEPARTS
//        LA COLONNE 0 CONTIENT LES ETATS D'ARRIVEES
        for (int i = 0; i<j-2 ; ++i) {
            if(((data[i][4])>=97 && (data[i][4])<=122)|| (data[i][4])==45  ){
                automate_1.transitions[data[i][0]-48][data[i][2]-48]=(data[i][4]);
            }
        }
//        ON INCREMENTE LE NOMBRE D'ETATS A CHAQUE FOIS QU'ON TROUVE UN NOUVEAU ETAT
        automate_1.nombre_d_etat++;
        for (int i = 0; i < automate_1.nombre_d_etat; ++i) {
            automate_1.etats[i] = i ;
        }
//;     AVANT DERNIERE LIGNE CONTIENT L ETAT D'ENTREE
//      DANS NOTRE CAS C'EST J-2 EST NON PAS J-1 A CAUSE DE LA DERNIERE INCREMENTATION
        automate_1.entree=data[j-2][0]-48;
//ON INITIALISE L'ETAT DE SORTIE ET ON COMMENCE A SCANNER CES ETATS EN INCREMENTANT LE NOMBRE DES SORTIES SIMULTANEMENT
        automate_1.nombre_sorties=0;
        for (int i = 0; i < data[j-1][i]!='\0'; ++i) {
            automate_1.sortie[i]=((data[j-1][(i*2)])-48);
            automate_1.nombre_sorties++;
        }
//        LINCREMENTATION PRECEDENTE A INCREMENTER LES NOMBRES DE SORTIES AINSI QUE LES ESPACES QUI LES SEPARES
//        DONC ON DIVISE LE NOMBRE D'ELEMENT SCANNEE PAR DEUX ET EN AJOUTE 1 AU CAS OUR LA VALEUR ENTIERE N'EST PAS EFFECTIVEMENT LE NOMBRE EXACTE

        automate_1.nombre_sorties=(int)((automate_1.nombre_sorties+1)/2);

        fclose(ptr);
        return automate_1;
}

//   PARTIE 2 :

void test_mots(char mot[200], struct automates automates_1 ){
//    INITIALISATION DES VARIABLES A PARTIR DE NOTRE AUTOMATE CREE PAR NOTRE STRUCTURE
    int etat_actif = automates_1.entree;
//    "LETTRE" SIGNIFIE LA LETTRE DU MOT A TESTER DANS L ETAT ACTIF
    int lettre=0;
//    "COMPLETE" NOUS PERMET DE SE SITUER ENTRE LORSQUE LE MOT EST (VALIDE 2) OU (REFUSE 0)  OU (EN COURS DE TRAITEMENT 1)
    int complete=1;

    while (complete==1 && ((mot[lettre]>=97) && (mot[lettre]<= 122)) ){
        complete=0;
        for (int i = 0; i < automates_1.nombre_d_etat; ++i) {
            if (automates_1.transitions[etat_actif][i] == mot[lettre]) {
//                L ETAT ACTIF PREND L ETAT QUI SUIT LA TRANSITION EQUIVALENTE A NOTRE LETTRE
                etat_actif = i;
                complete=1;
                lettre++;
                break;
            }
            else{
                complete=0;
            }
        }
        if(complete==0){
            break;
        }

        for (int j = 0; j < automates_1.nombre_sorties; ++j) {
//                        SI ON A LES DEUX CONDITIONS SUIVANTES ON ARRETE LA BOUCLE :
//                                -ON A SCANNER TOUS LES LETTRES DU MOTS;
//                                -TOUTES LES LETTRES SONT ACCEPTEES PAR NOTRE AUTOMATE;
            if ((etat_actif == automates_1.sortie[j]) && (mot[lettre]=='\0')) {
                printf("\nCE MOT A ETE VALIDE PAR CET AUTOMATE AVEC SUCCES. ");
                complete=2;
                break;
            }
        }
    }
//    SI L AUTOMATE N'A PAS VALIDE LE MOTS , DONC IL SERA REJETEE
    if(complete!=2){
        printf("\nCE MOT N'EST PAS VALIDE :( ");
    }
}
char** importer_liste_mots(FILE *ptr){

    char** data=(char ** ) malloc(2000*sizeof(char*));

    if(!ptr){
        printf("\n L'OUVERTURE DU FICHIER A ECHOUE \n");
        return 1;
    }
//LE TABLEAU LINE FAIT REFERANCE A CHAQUE LIGNE ECRITE DANS LE FICHIER TXT

    char line[500];
//    ET J FAIT REFERENCE A LA LIGNE ACTIVE
    int j=0;

    while (fgets(line,sizeof(line), ptr)) {
        data[j]=(char*) malloc(500* sizeof(char));
        for (int i = 0; line[i]!='\0' ; ++i) {
            if((line[i])>=97 && (line[i])<=122){
                data[j][i]=line[i];
            } else{
                data[j][i]='\0';
            }
        }
        j++;
    }
    return data;
}


int main() {
//    ON COMMENCE PAR SALUTAION ET ON DEMANDE A L'UTILISATEUR POUR CHOISIR L'ACTION QU'IL SOUHAITE
    char reponse;
    do {
    printf("BONJOUR,\nVOULEZ VOUS CREER UN NOUVEAU AUTOMATE (n) OU CHARGER UN EXISTANT (o) :\n\n (n/o) ? :");
    scanf("%c",&reponse);
    } while (reponse!='n' && reponse!='N'&& reponse!='o' && reponse!='O');

//       SI L'USER VEUT CREER UN NOUVEAU FICHIER DONC ON PROCEDE PAR LA CONDITION SUIVANTE
    if(reponse=='n' ||reponse=='N'){

//        ON CREE NOTRE AUTOMATE EN CREANT UN OBJET QUI EST CONFORME A LA STRUCTURE QU'ON A DECLARE
        struct automates obj1;

//        LA VARIABLE QUI CONTIENT LE NOM DU FICHIER.TXT
        printf("\nVEUILLER SAISIR LE NOM DU NOUVEAU FICHIER TEXTE POUR STOCKER VOTRE AUTOMATE : ");
        char chemin_r[50];
        scanf("%s",&chemin_r);

//        VOICI UN POINTEUR QUI POINTE SUR LE FICHIER QUE L'USER VIENT D'ENTRER
        FILE *ptr2;
        ptr2 =fopen(chemin_r,"w");

//        PAR LA FONCTION DU REMPLISSAGE QU'ON A CREE ON PEUT REMPLIR LES VARIABLES DE NOTRE OBJECT
        obj1=remplissage_automate();

//        ENSUITE EN UTILISANT CETTE FONCTION QUI ECRIT NOTRE AUTOMATE SUR LE FICHIER.TXT
        creer_fichier_texte(obj1,ptr2);
//         DE MEME ON PROCEDE POUR LA CREATION DU FICHIER .DOT
        printf("\n\nVEUILLER SAISIR LE NOM DU NOUVEAU FICHIER DOT POUR STOCKER VOTRE AUTOMATE : ");
        char fich_dot[50];
        scanf("%s",&fich_dot);

//         EN UTILISANT UN AUTRE POINTEUR
        FILE *ptr1;
        ptr1= fopen(fich_dot,"w");
//      en utilisant la fonction qui nous permet de cree un fichier.dot
        creer_dot_fichier(obj1,ptr1);
    }
    if(reponse=='o' || reponse=='O'){
        printf("\nVEUIILLEZ INSERER SVP LE CHEMIN DE VOTRE FICHIER CONTENANT L\'AUTOMATE : ");
        char chemin[70];
        scanf("%s",&chemin);
        struct automates obj1;

        FILE *ptr3;
        ptr3 = fopen( chemin,"r");
        obj1= lire_fichier_texte(ptr3);

        creer_fichier_texte( obj1,ptr3);
        printf("\n\nL'OUVERTURE DU FICHIER A REUSSI AVEC SUCCES\n");
        for (int i = 0; i < obj1.nombre_d_etat; ++i) {
            for (int j = 0; j < obj1.nombre_d_etat; ++j) {
                if(obj1.transitions[i][j]!='\0'){
                    printf("\n %d---%c-->%d",j,obj1.transitions[i][j],i);
                }
            }
        }
        printf("\n L'entree est : %d ",obj1.entree);

        printf("\nLes etats sont :");
        for (int i = 0; i < obj1.nombre_d_etat; ++i) {
            printf("\nL'etat %d est %d",i,obj1.etats[i]);
        }

        printf("\nLes sortie sont :");
        for (int i = 0; i < obj1.nombre_sorties; ++i) {
            printf("%d ",obj1.sortie[i]);
        }

    printf("\n\nVEUILLER SAISIR LE NOM DU NOUVEAU FICHIER DOT POUR STOCKER VOTRE AUTOMATE : ");
    char fich_dot[50];
    scanf("%s",&fich_dot);

//         EN UTILISANT UN AUTRE POINTEUR

    ptr3= fopen(fich_dot,"w");
//      en utilisant la fonction qui nous permet de cree un fichier.dot
    creer_dot_fichier(obj1,ptr3);

//    PARTE 2 :

//    IMPORTER LISTE DES MOTS

    printf("\nVEUIILLEZ INSERER SVP LE CHEMIN DE VOTRE FICHIER CONTENANT LA LISTE DES MOTS (CHAQUE MOT DANS UNE LIGNE) : ");
    char chemin_mots[70];
    scanf("%s",&chemin_mots);

//    POINTEUR POINT SUR LE FICHIER
    FILE *ptr4;
    ptr4 = fopen( chemin_mots,"r");
    char **list_mots= importer_liste_mots(ptr4);

//    TESTER TOUS LES MOTS DU FICHIER
    for (int i = 0; list_mots[i]; ++i) {
        printf("\n\nLe mot a tester est : %s ",list_mots[i]);
        test_mots(list_mots[i],obj1);

    }
    }
    char quit;
    printf(" \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPour quitter entre clicquer sur entrer ");
    scanf("%s",&quit);

    return 0;
}
