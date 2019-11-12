#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h> 

//od do kwota


typedef struct Dane {
    int autor;
    int odbiorca;
    int dolary;        
} dane;
dane *str;


int konta[]={100, 200, 40};


void *przelew(void *arg1) 
{
    int i = (int)arg1;
    int autor = (int)str[i].autor;
    int odbiorca = (int)str[i].odbiorca;
    int pieniadze = (int)str[i].dolary;

    printf("przelew %d --->%d na kwote %d\n",autor, odbiorca, pieniadze); 
    printf("stan konta przed: %d   %d\n", konta[autor], konta[odbiorca]);

    if(konta[autor] - pieniadze <0) printf("cant %d %d\n", autor, odbiorca);
    else
    {     
        konta[odbiorca]+=pieniadze;
        konta[autor]-=pieniadze;
    }

    printf("stan konta po: %d   %d\n", konta[autor], konta[odbiorca]);    

    return NULL; 
} 
 
int main(int argc, char **argv) 
{
    int ile_operacji = (argc-1) / 3;

    str = (dane*)malloc(ile_operacji*sizeof(dane));
    
    int licznik=1;
    for(int i=0; i<ile_operacji; i++)
    {
        str[i].autor = atoi(argv[licznik]); licznik++;
        str[i].odbiorca = atoi(argv[licznik]); licznik++;
        str[i].dolary = atoi(argv[licznik]); licznik++;
    }
    pthread_t thread_id[ile_operacji];

    printf("hello main\n");

    printf("stan konta przed przelewami: %d, %d, %d\n", konta[0], konta[1], konta[2]);

    for(int i=0; i<ile_operacji; i++)
    {
        pthread_create(&thread_id[i], NULL, przelew,(void *)i); 
    }    
    
    for(int i=0; i<ile_operacji; i++)
    {
        pthread_join(thread_id[i], NULL); 
    }
    

    printf("stan konta po przelewami: %d, %d, %d\n", konta[0], konta[1], konta[2]);

    return 0;
}


