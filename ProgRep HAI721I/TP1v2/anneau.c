#define _XOPEN_SOURCE 500
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define MIN_PROC 2      // Nombre minimum de processus
#define MAX_PROC 1000     // Nombre maximum de processus

int main (int argc,char ** argv)
{
    int n;  // Nombre de processus dans l'anneau

    /* Lecture du paramètre */
    if (argc<2 || (n = (int)strtol(argv[1],NULL,0))<MIN_PROC || n>MAX_PROC)
    {
        fprintf (stderr,"Usage : %s <nombre>\n"
                        "Avec <nombre> compris entre %d et %d.\n",
                        argv[0],MIN_PROC,MAX_PROC);
        exit(1);
    }
    else
    {
        pid_t   pid;        // Réception du PID lors de fork()
        int     p[n][2];    // Place pour n paires de descripteurs (VLA)
        int     i;          // Indice de boucle

        /* Indication du nombre de processus à engendrer */
        printf ("Nombre de processus à engendrer : %d\n",n);

        /* Création des n tubes anonymes.             */
        /* On considère que l'appel réussit toujours. */
        for (i=0;i<n;++i) pipe(p[i]);

        /* Génération des n processus fils, qui vont communiquer */
        /* entre eux. Le processus père reste en superviseur.    */
        for (i=0;i<n;++i)
        {
            pid = fork();

            if (pid>0)
            {
                printf ("Création du processus fils #%d : PID %d\n",i,pid);
            }
            else if (!pid)
            {
                /*                          */
                /* ---- Processus fils ---- */
                /*                          */

                int     in;     /* Descripteur d'entrée     */
                int     out;    /* Descripteur de sortie    */
                int     data;   /* Donnée à émettre         */

                int     j;      /* Autre indice de boucle (puisque i reste */
                                /* de fait notre numéro de processus fils. */

                /* Temporisation pour que la boucle du processus père ait   */
                /* le temps de se terminer avant de commencer le traitement */
                sleep(1);

                /* Récupération des descripteurs adéquats */
                in  = p[ i       ][0];
                out = p[(i+1) % n][1];

                /* Fermeture des descripteurs inutiles */
                for (j=0;j<n;++j)
                {
                    if (p[j][0] != in)  close(p[j][0]);
                    if (p[j][1] != out) close(p[j][1]);
                }

                /* Récupération et émission de notre PID */
                data = (int)getpid();
                printf ("Processus #%d : émission de %d\n",i,data);
                write (out,&data,sizeof data);
                close (out);

                /* Réception de la donnée de l'autre processus */
                data = (int)getpid();
                read (in,&data,sizeof data);
                printf ("Processus #%d : réception de %d\n",i,data);
                close (in);

                /* En fin de traitement, un break pour quitter la boucle */
                /* démarrée par le processus père.                       */
                break;
            }
            else perror ("Erreur à l'appel de fork()");
        }

        /* Si PID est non nul à l'issue de la boucle, c'est qu'on est  */
        /* toujours dans le processus père. On en profite pour faire n */
        /* wait() successifs pour attendre tous nos fils.              */
        if (pid>0)
        for (i=0;i<n;++i) wait(NULL);
    }

    return 0;
}
