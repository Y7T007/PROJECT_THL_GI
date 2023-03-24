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
                if((automates_1.transitions[i][j]!='-') && (automates_1.transitions[i][j]!='\0')&&(automates_1.transitions[i][j]!='e')){
                    fprintf(ptr, "\n%d -> %d [label=\"%c\" color=grey81 ] ",i,j,automates_1.transitions[i][j]);
                } else if(automates_1.transitions[i][j]=='e'){
                    fprintf(ptr, "\n%d -> %d [label=\"%c\" color=red ] ",i,j,automates_1.transitions[i][j]);
                }
            }
            for (int j = 0; j < automates_1.nombre_sorties; ++j) {
                if(automates_1.sortie[j]==automates_1.etats[i]){
                    fprintf(ptr, "\n%d -> s ;",automates_1.etats[i]);
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
            if (automate_1.transitions[i][j]!='\0') {
            fprintf(ptr,"%d %d %c\n",i,j,automate_1.transitions[i][j]);
            }
        }
    }

    fprintf(ptr,"%d\n",automate_1.entree);
        for (int i = 0; i < automate_1.nombre_sorties; ++i) {
            fprintf(ptr,"%d ",automate_1.sortie[i]);

        }

    return automate_1;
}
struct automates lire_fichier_texte(FILE *ptr){
    struct automates automate_1;
    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < 50; ++j) {
            automate_1.transitions[i][j]='\0';
        }
    }

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

//   PARTIE 3 :
struct automates etoile_automate(struct automates automates01){
    struct automates etoile;
    for (int i = 0; i < 50 ; ++i) {
        for (int j = 0; j < 50; ++j) {
        etoile.transitions[i][j]='\0';
        }
    }
    etoile.nombre_d_etat=automates01.nombre_d_etat+4;
    for (int i = 0; i <= etoile.nombre_d_etat; ++i) {
        etoile.etats[i]=i;
    }

    etoile.entree=0;

    etoile.transitions[0][1]='e';
    etoile.transitions[1][2]='e';
    etoile.transitions[0][etoile.nombre_d_etat-1]='e';
    etoile.transitions[etoile.nombre_d_etat-2][etoile.nombre_d_etat-1]='e';

    for (int i = 0; i <= automates01.nombre_d_etat; ++i) {
        for (int j = 0; j <= automates01.nombre_d_etat; ++j) {
            etoile.transitions[i+2][j+2]=automates01.transitions[i][j];
        }
    }

    for (int i = 0; i <= automates01.nombre_d_etat; ++i) {
        for (int j = 0; j < automates01.nombre_sorties; ++j) {
            if(automates01.etats[i]==automates01.sortie[j]){
                etoile.transitions[i+2][etoile.nombre_d_etat-2]= 'e';
            }
        }
    }
    etoile.transitions[etoile.nombre_d_etat-2][1]='e';

    etoile.nombre_sorties=1;
    etoile.sortie[0]=etoile.nombre_d_etat-1;

    return etoile;
}
struct automates union_deux_automates(struct automates a1,struct automates a2){
    struct automates uni;
    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < 50; ++j) {
            uni.transitions[i][j]='\0';
        }
    }
    uni.entree=0;
    uni.nombre_d_etat=a1.nombre_d_etat+a2.nombre_d_etat+6;

    for (int i = 0; i <= uni.nombre_d_etat; ++i) {
        uni.etats[i]=i;
    }

    uni.transitions[0][1]='e';
    uni.transitions[0][2]='e';
    uni.transitions[1][3]='e';
    uni.transitions[2][a1.nombre_d_etat+3]='e';

    for (int i = 0; i < a1.nombre_d_etat; ++i) {
        for (int j = 0; j < a1.nombre_d_etat; ++j) {
            uni.transitions[i+3][j+3]=a1.transitions[i][j];
        }
    }
    for (int i = 0; i < a2.nombre_d_etat; ++i) {
        for (int j = 0; j < a2.nombre_d_etat; ++j) {
            uni.transitions[a1.nombre_d_etat+i+3][a1.nombre_d_etat+j+3]=a2.transitions[i][j];
        }
    }

    for (int i = 0; i < a1.nombre_d_etat; ++i) {
        for (int j = 0; j < a1.nombre_sorties; ++j) {
            if(a1.etats[i]==a1.sortie[j]){
                uni.transitions[i+3][uni.nombre_d_etat-3]= 'e';
            }
        }
    }

    for (int i =0; i < a2.nombre_d_etat; i++) {
        for (int j = 0; j < a2.nombre_sorties; j++) {
            if(a2.etats[i]==a2.sortie[j] &&a2.sortie[j]!=0 ){
                uni.transitions[a1.nombre_d_etat+i+3][uni.nombre_d_etat-2]= 'e';
            }
        }
    }
    uni.transitions[uni.nombre_d_etat-3][uni.nombre_d_etat-1]='e';
    uni.transitions[uni.nombre_d_etat-2][uni.nombre_d_etat-1]='e';

    uni.nombre_sorties=1;
    uni.sortie[0]=uni.nombre_d_etat-1;
    return uni;

}
struct automates produit_deux_automates(struct automates a1,struct automates a2){
    struct automates pr;
    pr.entree=0;
    pr.nombre_sorties=0;
    for (int i = 0; i < a1.nombre_sorties; ++i) {
        for (int j = 0; j < a2.nombre_sorties; ++j) {
            if(a1.sortie[i]==a2.sortie[j] && a1.sortie[i]!='\0'){
                pr.sortie[pr.nombre_sorties]=a1.sortie[i];
                pr.nombre_sorties++;
            }
        }
    }
    if(a1.nombre_d_etat<a2.nombre_d_etat){
        pr.nombre_d_etat=a1.nombre_d_etat;
    }
    if(a1.nombre_d_etat>=a2.nombre_d_etat){
        pr.nombre_d_etat=a2.nombre_d_etat;
    }
    for (int i = 0; i <= pr.nombre_d_etat; ++i) {
        pr.etats[i]=i;
    }
    for (int m = 0; m <= pr.nombre_d_etat; ++m) {
        for (int k = 0; k <= pr.nombre_d_etat; ++k) {
            if((a1.transitions[k][m] == a2.transitions[k][m])&& (a2.transitions[k][m]>=97 && a2.transitions[k][m]<=122)){
                pr.transitions[k][m]=a1.transitions[k][m];
            }
        }
    }

    return pr;
}


//  features

//struct automates menu(){
//    struct automates obj;
//    int c=0;
//    while (c==0){
//        printf("Veuillez choisir votre prochaine fonction :\n\t1) Creer un automate;\n\t2) Lire un automate a partir d'un fichier\n\t3) Creer un fichier dot a partir d'un automate\n\t4) Tester un mot a partir de votre automate.\n\t5) Importer un liste de mot a tester.\n\t6) Fournir l'etoile d'un automate \n\t7) Fournir le produit de deux automates \n\t7) Fournir l'union de deux automates.\n(1\2\3\4\5\6\7)");
//        scanf("%d",&c);
//        switch (c) {
//            case 1:
//                obj=remplissage_automate();
//                return obj;
//                break;
//            case 2:
//                printf("\nVeuillez saisir le nom de fichier texte : ");
//                char chemin[50];
//                scanf("%s",chemin);
//                FILE *ch= fopen(chemin,"r");
//                lire_fichier_texte(ch);
//                break;
//            case 3:
//                printf("\n\nVEUILLER SAISIR LE NOM DU NOUVEAU FICHIER DOT POUR STOCKER VOTRE AUTOMATE : ");
//                char fich_dot[50];
//                scanf("%s",&fich_dot);
//                FILE *ch_dot= fopen(fich_dot,"r");
//                ch= fopen("ff2.dot","w");
//                creer_dot_fichier(obj,ch_dot);
//                break;
//            case 4:
//                break;
//            case 5:
//                break;
//            case 6:
//                break;
//            case 7:
//                break;
//        }
//    }


//}

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
//        scanf("%s",&chemin);
        struct automates obj1;

        FILE *ptr3;
        ptr3 = fopen( "ff2.txt","r");
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
//    scanf("%s",&fich_dot);

//         EN UTILISANT UN AUTRE POINTEUR

    ptr3= fopen("ff2.dot","w");
//      en utilisant la fonction qui nous permet de cree un fichier.dot
    creer_dot_fichier(obj1,ptr3);

//    PARTE 2 :

//    IMPORTER LISTE DES MOTS

    printf("\nVEUIILLEZ INSERER SVP LE CHEMIN DE VOTRE FICHIER CONTENANT LA LISTE DES MOTS (CHAQUE MOT DANS UNE LIGNE) : ");
    char chemin_mots[70];
//    scanf("%s",&chemin_mots);

//    POINTEUR POINT SUR LE FICHIER
    FILE *ptr4;
    ptr4 = fopen( "mots.txt","r");
    char **list_mots= importer_liste_mots(ptr4);

//    TESTER TOUS LES MOTS DU FICHIER
    for (int i = 0; list_mots[i]; ++i) {
        printf("\n\nLe mot a tester est : %s ",list_mots[i]);
        test_mots(list_mots[i],obj1);

    }

//      PARTIE 3 :

//      FONCTION ETOILE :
    struct automates etoile= etoile_automate(obj1);
    FILE *ptr5= fopen("etoile.dot","w+");
    creer_dot_fichier(etoile,ptr5);

//      FUNCTION UNION :
    FILE *A1= fopen("ff2.txt","r+");
    FILE *A2= fopen("ff3.txt","r+");

    struct automates unio= union_deux_automates(lire_fichier_texte(A1), lire_fichier_texte(A2));
    FILE *un= fopen("union.dot","w+");
    creer_dot_fichier(unio,un);


//      FONCTION PRODUIT
        FILE *a1= fopen("ff2.txt","a+");
        FILE *a2= fopen("ff3.txt","a+");
        struct automates a12= lire_fichier_texte(a1);
        struct automates a32= lire_fichier_texte(a1);
        struct automates a22= lire_fichier_texte(a2);
    struct automates produit= produit_deux_automates(a12,a22);
    FILE *pr= fopen("produit.dot","w+");
    creer_dot_fichier(produit,pr);


        //    CREER FICHIER TEXTE ETOILE:
        FILE *F_ETOILE= fopen("etoile.txt","w+");
        creer_fichier_texte(etoile,F_ETOILE);
        //    CREER FICHIER TEXTE UNION:
        FILE *F_UNION= fopen("union.txt","w+");
        creer_fichier_texte(unio,F_UNION);
        //    CREER FICHIER TEXTE PRODUIT:
        FILE *F_PROD= fopen("PRODUIT.txt","w+");
        creer_fichier_texte(produit,F_PROD);
    }

    char quit;
    printf(" \n\n\nPour quitter entre clicquer sur entrer ");
    scanf("%s",&quit);



    return 0;
}
