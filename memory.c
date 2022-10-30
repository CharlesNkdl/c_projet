#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX 10

int table_build (bool lock_v [MAX][MAX],long (value)[][MAX],int taille, int a, int b, int c, int d);
int ask_user_taille(void);
int get_int(void);
int count_try = 0;
int get_coordo_l(int taille);
int get_coordo_c(int taille);

int main(void)
{
    // On demande la taille de la table
    int taille = ask_user_taille();
    // On calcule le nombre de valeur dans la table
    int nbrv = (taille * (taille - 1)/ 2);
    // On crée un array de taille égal au nombre de valeur unique
    long (*value)[nbrv] = malloc(sizeof(*value));
    // On crée un compteur
    int count = 0;
    // On initialise la seed pour randomiser
    srand(time(NULL));
    // On remplit l'array des valeurs uniques randomiser
    while (count != nbrv)
    {  
        *value[count] = ((rand()%127)+ 32);
        //sleep(0.1);
        count++;
        // On regarde si y a pas de valeur double dans le pur des hasard et on les incrémente de un si nécessaire
        if (count == nbrv)
        {
            for (int a = 0; a < nbrv; a++)
            {
                for (int r = 0; r < nbrv; r++)
                {
                    if ( a != r)
                    {
                        if (value[a] == value[r])
                        {
                            *value[a] += 1;
                            a = 0;
                            r = 0;
                        }
                
                    }
                }
            }
        }
    }
    /*
    // pour check que les valeurs sont bonne
    for (int p = 0; p < nbrv; p++)
    {
        printf("%i \n",*value[p]);
    }
    */
    // On initialise le double array qu'on va utiliser pour stocker les valeurs
    long value_r[taille][taille-1];
    // On initialise un double array de taille équivalente de type bool pour savoir quand une case est révélé ou pas
    bool (lock_v)[taille][taille-1];
    for (int j = 0; j < taille; j++)
    {
        for (int k = 0; k < taille-1; k++)
        {
            lock_v[j][k] = false;
        }
    }
    count = 0;
    // On place les valeurs de l'array value dans l'array double value_r pour simuler la grille
    for (int j = 0; j < taille; j++)
    {
        for (int k = (taille-1); k > 0; k--)
        {
            value_r[j][k] = *value[count];
            count++;
            if (count == nbrv)
            {
                count = 0;
            } 
            printf("valeur : %li",value_r[j][k]);
        } 
    }
    printf("\n");
    // La fonction pour construire la table, appelé 1 première fois pour que le joueur check
    for (int i = 0; i < taille; i++)
    {
        // Pour mettre les ptit numéros et les espaces au bon endroit pour que ce soit tout mims
        if (i == 0)
        {
            for (int q = 1; q < taille; q++)
            {
                if (q == 1)
                {
                    printf("  ");
                }
                printf("   %i",q);
            }
            printf("\n");   
        }
        // on rajoute un parce que les arrays débute de compter à 0 mais pas les humains lol
        int ib = i + 1;
        printf("  %i ",ib);
        for (int j = 0; j < taille-1; j++)
        {
            {
            printf("[  ]");
            }
        }
        printf("\n");
    }
    // on initialise la while loop pour le jeu, fini va devenir true quand toutes les valeurs de lock_v seront true, soit révélé
    bool fini = false;
    int a,b,c,d;
    while (fini != true)
    {
        a = get_coordo_l(taille);
        b = get_coordo_c(taille);
        c = get_coordo_l(taille);
        d = get_coordo_c(taille);
        // on appelle la fonction de la table avec tout les paramètres qu'il faut 
        table_build(lock_v,value_r,taille,a,b,c,d);
        int count_bool = 0;
        for (int j = 0; j < taille; j++)
        {
            for (int k = 0; k < taille-1; k++)
            {
                if (lock_v[j][k] == true)
                {
                    count_bool++;
                    if (count_bool == (nbrv*2))
                    {
                        fini = true;
                    }
                }
            }
        }
    }
    printf("Bien joué ! Tu as gagné mon pote !\n En seulement %i essai !", count_try);
    // on libère la mémoire
    free(*value);
    // finito
    return 0;
}
int get_int(void)
{
    // Cimer stack overflow, c'est très long pour avoir une valeur int safe de tout les mecs qui vont vouloir tester mon programme 
    char *p, s[100];
    int n;

    while (fgets(s, sizeof(s), stdin))
    {
        n = strtol(s, &p, 10);
        if (p == s || *p != '\n')
        {
            printf("Rentre un chiffre stp: ");
        } 
        else break;
    }
    return n;

}
int ask_user_taille(void)
{
    int taille = 0;
    // Les consignes
    printf("Bonjour , jeune joueur !\nBienvenue dans le memory de chalou, écrit en C pour entrainement suivant les pas de maxence-chan\nPour commencer tu vas devoir rentrer la taille voulu de ta grille ! Ecrit un chiffre entre 3 et 10 pour commencer !\n");

    // While loop qui va checker le joueur pour la taille de table
    while ((taille < 3) || (taille > 10))
    {
        taille = get_int();
        if ((taille < 3) || (taille > 10))
        {
            printf("Entre 3 et 10 stp frr\n");
        }
    }
    return taille;
}
int table_build (bool lock_v[MAX][MAX],long (value_r)[][MAX],int taille,int a, int b,int c, int d)
{
    // Construction de la table
    // on initialise 2 array temporaire pour stocker les valeurs aux index + les indexs
    int temp1[taille][taille];
    int temp2[taille][taille-1];
    int is;
    int js;
    
    for (int i = 0; i < taille; i++)
    {
        // Pour mettre les ptit numéros et les espaces au bon endroit pour que ce soit tout mims
        if (i == 0)
        {
            for (int q = 1; q < taille; q++)
            {
                if (q == 1)
                {
                    printf("  ");
                }
                printf("   %i",q);
            }
            printf("\n");
            
        }
        // on rajoute un parce que les arrays débute de compter à 0 mais pas les humains lol
        int ib = i + 1;
        printf("  %i ",ib);

        for (int j = 0; j < taille-1; j++)
        {
            // on commence par regarder si la valeur doit être révélé ou pas
            if (lock_v[i][j] == true)
            {
                printf("[%li]",value_r[i][j]);
            }
            // on révéle la première tentative du joueur, et on stocke la valeur pour pouvoir comparé avec la deuxième tentative
            if (a == i && b == j &&(lock_v[i][j]!=true))
            {
                temp1[0][0] = value_r[i][j];
                is = i;
                js = j;
                printf("[%li]",value_r[i][j]);
            }
            // idem mais avec la deuxième valeur
            if (c == i && d == j &&(lock_v[i][j]!=true))
            {
                temp2[0][0] = value_r[i][j];
                printf("[%li]",value_r[i][j]);
            }
            // le reste de la table qui s'imprime
            if (((a == i && b == j) != true) && ((c == i && d == j) != true) && (lock_v[i][j]!=true))
            {
            printf("[  ]");
            }
            // avec les valeurs stockés on regarde si elles sont équivalents , si oui, on change la valeur de lock_v en true
            if (temp1[0][0] == temp2[0][0])
            {
                lock_v[i][j] = true;
                lock_v[is][js] = true;
            }
        }
        printf("\n");
    }
    // on compte le nombre de tentative
    count_try++;
    printf("Nombre d'essai :%i\n",count_try);
}
int get_coordo_l(int taille)
{
    // fonction pour avoir les coordos de la ligne
    int numb = -1;
    while (numb < 0 || numb > taille)
    {
        printf("Ligne : ");
        numb = get_int();
        numb -= 1;
    }
    return numb;
}
int get_coordo_c(int taille)
{
    // fonction pour avoir les coordos de la colonne
    int numb = -1;
    while (numb < 0 || numb > taille-1)
    {
        printf("Colonne : ");
        numb = get_int();
        numb -= 1;
    }
    return numb;
}



