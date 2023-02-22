#include <stdio.h>
#include "math.h"


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
struct automates creer_dot_fichier(struct automates automates_1,FILE *ptr){

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
                if(automates_1.transitions[i][j]!='-'){
                    fprintf(ptr, "\n%d -> %d [label=\"%c\" color=grey81 ] ",i,j,automates_1.transitions[i][j]);
                }
            }
        }
    fprintf(ptr,"}");
}
struct automates struct_to_file(char rw,struct automates automate_1 ,FILE *ptr){

    if( rw == 'w' ){

    for (int i = 0; i < automate_1.nombre_d_etat; ++i) {
        for (int j = 0; j < automate_1.nombre_d_etat; ++j) {
            printf("\n%d %d %c",i,j,automate_1.transitions[i][j]);
            fprintf(ptr,"%d %d %c\n",i,j,automate_1.transitions[i][j]);
        }
    }

    fprintf(ptr,"%d\n%d ",automate_1.entree,automate_1.nombre_sorties);
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

}
struct automates read_only_function(char rw,FILE *ptr){
    struct automates automate_1;
    if(rw =='r'){


        if(!ptr){
            printf("\n Unable to open  \n");
        }

        char line[500];
        char data[500][500];
        int j=0;
        int line_max;
        while (fgets(line,line_max = sizeof(line), ptr)) {

            for (int i = 0;line[i]!='\0' ; ++i) {
                data[j][i]=line[i];
            }
            j++;
        }
        int temp;
        for (int i = 0; i<j-2 ; ++i) {
            if((data[i][4])>=97 && (data[i][4])<=122){
                automate_1.transitions[data[i][2]-48][data[i][0]-48]=(data[i][4]);

            }
        }
        automate_1.nombre_d_etat= (int)sqrt(j) ;
        for (int i = 0; i < automate_1.nombre_d_etat; ++i) {
            automate_1.etats[i] = (data[i][2]-48) ;
        }



        automate_1.entree=data[j-2][0]-48;
        automate_1.nombre_sorties=(data[j-1][0]-48);
        for (int i = 0; i < automate_1.nombre_sorties ; ++i) {
            automate_1.sortie[i]=((data[j-1][2+(i*2)])-48);
        }
        fclose(ptr);
        return automate_1;

    }
}

//  PARTIE 2222222222 :

struct automates test_mots(char mot[200], struct automates automates_1 ){
    char etat_actif=automates_1.entree;
    int lettre=0;
    for (int i = 0; i < automates_1.nombre_d_etat; ++i) {
        if(automates_1.transitions[etat_actif][i]==mot[lettre]){
            etat_actif=i;
            lettre++;
        }
        for (int j = 0; j < automates_1.nombre_sorties; ++j) {
            if(etat_actif==automates_1.sortie[j]){
                printf("\nVOTRE MOT A ETE VALIDE PAR CET AUTOMATE AVEC SUCCES. ");
                break;
            }
        }
    }
}


int main() {
//    ON COMMENCE PAR SALUTAION ET ON DEMANDE A L'UTILISATEUR POUR CHOISIR L'ACTION QU'IL SOUHAITE
    printf("BONJOUR,\nVOULEZ VOUS CREER UN NOUVEAU AUTOMATE (n) OU CHARGER UN EXISTANT (o) :\n\n (n/o) ? :");
    char reponse;
    scanf("%c",&reponse);

//       SI L'USER VEUT CREER UN NOUVEAU FICHIER DONC ON PROCEDE PAR LA CONDITION SUIVANTE
    if(reponse=='n'){

//        ON CREE NOTRE AUTOMATE EN CREANT UN OBJET QUI EST CONFORME A LA STRUCTURE QU'ON A DECLARE
        struct automates obj1;

//        LA VARIABLE QUI CONTIENT LE NOM DU FICHIER.TXT
        printf("VEUILLER SAISIR LE NOM DU NOUVEAU FICHIER TEXTE POUR STOCKER VOTRE AUTOMATE : ");
        char chemin_r[50];
        scanf("%s",&chemin_r);

//        VOICI UN POINTEUR QUI POINTE SUR LE FICHIER QUE L'USER VIENT D'ENTRER
        FILE *ptr2;
        ptr2 =fopen(chemin_r,"w");

//        PAR LA FONCTION DU REMPLISSAGE QU'ON A CREE ON PEUT REMPLIR LES VARIABLES DE NOTRE OBJECT
        obj1=remplissage_automate();

//        ENSUITE EN UTILISANT CETTE FONCTION QUI ECRIT NOTRE AUTOMATE SUR LE FICHIER.TXT
        struct_to_file('w',obj1,ptr2);
//         DE MEME ON PROCEDE POUR LA CREATION DU FICHIER .DOT
        printf("VEUILLER SAISIR LE NOM DU NOUVEAU FICHIER DOT POUR STOCKER VOTRE AUTOMATE : ");
        char fich_dot[50];
        scanf("%s",&fich_dot);

//         EN UTILISANT UN AUTRE POINTEUR
        FILE *ptr1;
        ptr1= fopen(fich_dot,"w");
//      en utilisant la fonction qui nous permet de cree un fichier.dot
        creer_dot_fichier(obj1,ptr1);
    }
    if(reponse=='o'){
        printf("VEUIILLEZ INSERER SVP LE CHEMIN DE VOTRE FICHIER CONTENANT L\'AUTOMATE : ");
        char chemin[70];
        scanf("%s",&chemin);
        struct automates obj2;

        FILE *ptr3;
        ptr3 = fopen( chemin,"r");
        obj2= read_only_function('r',ptr3);

        struct_to_file( 'r',obj2,ptr3);
        printf("\n\nCONGRATULAAAAATIIOOOOOOOONNNNNNN !!!!!!!!!!!!!!!!! OOOOH MYY GOOOOD U HAVE OPENED THE FIIIIILE SUCCESSSEEEEEFULLYYYYYYY \n YAAAAAAAAY!!!!!!!!\n");
        for (int i = 0; i < obj2.nombre_d_etat; ++i) {
            for (int j = 0; j < obj2.nombre_d_etat; ++j) {
                if(obj2.transitions[i][j]!='\0'){
                    printf("\n %d---%c-->%d",j,obj2.transitions[i][j],i);
                }
            }
        }
        printf("\nLes sortie sont :");
        for (int i = 0; i < obj2.nombre_sorties; ++i) {
            printf("%d ",obj2.sortie[i]);
        }
    }

//    PARTE 2 :

    printf("VEUILLEZ ENTREZ VOTRE MOT : ");
    char mot[100];
    scanf("%s",mot);
    printf("%s",mot);

    return 0;
}
