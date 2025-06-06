#include <stdio.h>
#include <string.h>
#include <pthread.h>

/* Makro, um Verwendung von Mutexes ein- und auszuschalten.
 * Wenn USE_MUTEX den Wert Null hat, wird kein Mutex verwendet.
 * Ansonsten wird ein Mutex verwendet.
 */
#define USE_MUTEX 1

/* Vorwärtsdeklarationen von Funktionen */
void *thread_main(void*);

/* Zählervariable */
int counter = 0;

#if USE_MUTEX
pthread_mutex_t counter_mutex; /* Mutex für den Zähler */
#endif

int main(void)
{
    int ret;    /* Variable für Rückgabewerte von pthread_*-Funktionen */
    /* Thread-IDs für beide Threads */
    pthread_t thread_1;
    pthread_t thread_2;
    void *retval; /* Variable für Rückgabewerte von Threads */

#if USE_MUTEX
    /* Mutex initialisieren */
    ret = pthread_mutex_init(&counter_mutex, NULL);
    if (ret != 0) {
        /* Bei Fehler Fehlermeldung ausgeben */
        printf("Initialisierung von Mutex fehlgeschlagen: %s\n", strerror(ret));
        return 1;
    }
#endif

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

    printf("Zählerwert nach Beendigung beider Threads (soll 200000): %d\n", counter);

#if USE_MUTEX
    /* Mutex wieder freigeben */
    ret = pthread_mutex_destroy(&counter_mutex);
    if (ret != 0) {
        /* Bei Fehler Fehlermeldung ausgeben */
        printf("Freigabe von Mutex fehlgeschlagen: %s\n", strerror(ret));
        return 1;
    }
#endif

    return 0;
}

/* Thread-Hauptfunktion */
void *thread_main(void *param)
{
    printf("%s wurde gestarted\n", (char*)param);

    for (int i=0;i<100000;i++) {
#if USE_MUTEX
        /* Mutex sperren */
        pthread_mutex_lock(&counter_mutex);
#endif
        counter++;
#if USE_MUTEX
        /* Mutex freigeben */
        pthread_mutex_unlock(&counter_mutex);
#endif
    }

    printf("%s wird beendet\n", (char*)param);
    
    return param;
}