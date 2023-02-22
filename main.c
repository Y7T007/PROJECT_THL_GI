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

    for (int i = 0; i < automate_1.nombre_d_etat; ++i) {
        for (int j = 0; j < automate_1.nombre_d_etat; ++j) {
            printf("\n%d %d %c",i,j,automate_1.transitions[i][j]);
            fprintf(ptr,"%d %d %c\n",i,j,automate_1.transitions[i][j]);
        }
    }

    fprintf(ptr,"%d\n ",automate_1.entree);
        for (int i = 0; i < automate_1.nombre_sorties; ++i) {
            fprintf(ptr,"%d ",automate_1.sortie[i]);

        }

    for (int i = 0; i < automate_1.nombre_d_etat; ++i) {
        printf("\n");
        for (int j = 0; j < automate_1.nombre_d_etat; ++j) {
            printf("%c",automate_1.transitions[j][i]);
        }
    }
    return automate_1;
}
struct automates lire_fichier_texte(FILE *ptr){
    struct automates automate_1;


        if(!ptr){
            printf("\n Unable to open  \n");
        }

        char line[500];
        char data[500][500];
        int j=0;
        int line_max;
        automate_1.nombre_d_etat=0;

        while (fgets(line,line_max = sizeof(line), ptr)) {
            for (int i = 0;line[i]!='\0' ; ++i) {
                data[j][i]=line[i];

                for (int j = 1; j <line_max ; ++j) {
                    if(automate_1.nombre_d_etat<(data[j][0]-48)){
                        automate_1.nombre_d_etat=(data[j][0]-48);
                        printf("%d",automate_1.nombre_d_etat);
                    }
                }
            }
            j++;
        }
        for (int i = 0; i<j-2 ; ++i) {
            if(((data[i][4])>=97 && (data[i][4])<=122)|| (data[i][4])==45  ){
                automate_1.transitions[data[i][0]-48][data[i][2]-48]=(data[i][4]);
            }
        }
        automate_1.nombre_d_etat++;


        for (int i = 0; i < automate_1.nombre_d_etat; ++i) {
            automate_1.etats[i] = i ;
        }

        automate_1.entree=data[j-2][0]-48;

        automate_1.nombre_sorties=0;
        for (int i = 0; i < data[j-1][i]!='\0'; ++i) {
            automate_1.sortie[i]=((data[j-1][(i*2)])-48);
            automate_1.nombre_sorties++;
        }
        automate_1.nombre_sorties=(int)((automate_1.nombre_sorties+1)/2);

        fclose(ptr);
        return automate_1;
}

//   PARTIE 2 :

void test_mots(char mot[200], struct automates automates_1 ){
    int etat_actif = automates_1.entree;
    int lettre=0;
    int complete=1;
    while (complete==1 && ((mot[lettre]>=97) && (mot[lettre]<= 122)) ){
        complete=0;
        for (int i = 0; i < automates_1.nombre_d_etat; ++i) {
            if (automates_1.transitions[etat_actif][i] == mot[lettre]) {
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
//            printf("\nsortie %d : %d , etat actif %d, lettre a tester : %c",j,automates_1.sortie[j],etat_actif,mot[lettre-1]);
            if ((etat_actif == automates_1.sortie[j]) && (mot[lettre]=='\0')) {
                printf("\nCE MOT A ETE VALIDE PAR CET AUTOMATE AVEC SUCCES. ");
                complete=2;
                break;
            }
        }
    }
    if(complete!=2){
        printf("\nCE MOT N'EST PAS VALIDE :( ");
    }
}
char** importer_liste_mots(FILE *ptr){
    char** data=(char ** ) malloc(2000*sizeof(char*));

    if(!ptr){
        printf("\n Unable to open  \n");
    }

    char line[500];
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
        printf("\nVEUILLER SAISIR LE NOM DU NOUVEAU FICHIER DOT POUR STOCKER VOTRE AUTOMATE : ");
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

    printf("\nVEUILLER SAISIR LE NOM DU NOUVEAU FICHIER DOT POUR STOCKER VOTRE AUTOMATE : ");
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

//    char **list= importer_liste_mots(ptr4);
//
//        for (int i = 0; i < 3; ++i) {
//            printf("\n%s",((*list)+i) );
//        }
//    verifier_mots_du_fichiers(importer_liste_mots(ptr4),obj1);






    }
    return 0;
}
