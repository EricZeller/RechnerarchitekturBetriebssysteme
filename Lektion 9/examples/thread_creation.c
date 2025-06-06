#include <stdio.h>
#include <string.h>
#include <pthread.h>

/* Vorwärtsdeklarationen von Funktionen */
void *thread_main(void*);

int main(void)
{
    int ret;    /* Variable für Rückgabewerte von pthread_*-Funktionen */
    /* Thread-IDs für beide Threads */
    pthread_t thread_1;
    pthread_t thread_2;
    void *retval; /* Variable für Rückgabewerte von Threads */

    /* Erstelle ersten Thread */
    ret = pthread_create(&thread_1, NULL, thread_main, "Thread 1");
    if (ret != 0) {
        /* Bei Fehler Fehlermeldung ausgeben */
        printf("Erstellung von Thread 1 fehlgeschlagen: %s\n", strerror(ret));
        return 1;
    }

    /* Erstelle zweiten Thread */
    ret = pthread_create(&thread_2, NULL, thread_main, "Thread 2");
    if (ret != 0) {
        /* Bei Fehler Fehlermeldung ausgeben */
        printf("Erstellung von Thread 2 fehlgeschlagen: %s\n", strerror(ret));
        return 1;
    }

    /* Auf Beedingung des ersten Threads warten */
    ret = pthread_join(thread_1, &retval);
    if (ret != 0) {
        /* Bei Fehler Fehlermeldung ausgeben */
        printf("Warten auf Thread 1 fehlgeschlagen: %s\n", strerror(ret));
        return 1;
    }
    printf("Thread 1 hat %s zurückgegeben\n", (char*)retval);

    /* Auf Beedingung des zweiten Threads warten */
    ret = pthread_join(thread_2, &retval);
    if (ret != 0) {
        /* Bei Fehler Fehlermeldung ausgeben */
        printf("Warten auf Thread 2 fehlgeschlagen: %s\n", strerror(ret));
        return 1;
    }
    printf("Thread 2 hat %s zurückgegeben\n", (char*)retval);

    return 0;
}

/* Thread-Hauptfunktion */
void *thread_main(void *param)
{
    printf("%s wurde gestarted\n", (char*)param);

    for (int i=0;i<200;i++) {
        printf("%s\n", (char*)param);
    }

    printf("%s wird beendet\n", (char*)param);
    
    return param;
}