#include <stdio.h>
#include <string.h>
#include <pthread.h>

/* Anzahl von Philosophen */
#define PHILOSOPHER_COUNT 4

/* Vorwärtsdeklarationen von Funktionen */
void *philosopher_main(void*);

/* Essbesteck - repräsentiert durch Mutexes */
pthread_mutex_t mutex[PHILOSOPHER_COUNT];

int main(void)
{
    int ret;    /* Variable für Rückgabewerte von pthread_*-Funktionen */
    pthread_t thread_id[PHILOSOPHER_COUNT]; /* Philosophen-Thread-IDs */
    int thread_number[PHILOSOPHER_COUNT]; /* Philosophen-Nummern */

    /* Alle Mutexe initialisieren */
    for (int i=0; i<PHILOSOPHER_COUNT; i++) {
        ret = pthread_mutex_init(&mutex[i], NULL);
        if (ret != 0) {
            /* Bei Fehler Fehlermeldung ausgeben */
            printf("Initialisierung von Mutex %d fehlgeschlagen: %s\n", i, strerror(ret));
            return 1;
        }
    }

    /* Alle Philosophen-Threads starten */
    for (int i=0; i<PHILOSOPHER_COUNT; i++) {
        /* Initialisiere Thread-Nummer */
        thread_number[i] = i;
        ret = pthread_create(&thread_id[i], NULL, philosopher_main, &thread_number[i]);
        if (ret != 0) {
            /* Bei Fehler Fehlermeldung ausgeben */
            printf("Erstellung von Thread %d fehlgeschlagen: %s\n", i, strerror(ret));
            return 1;
        }
    }

    /* Auf Beedingung aller Threads warten */
    for (int i=0; i<PHILOSOPHER_COUNT; i++) {
        ret = pthread_join(thread_id[i], NULL);
        if (ret != 0) {
            /* Bei Fehler Fehlermeldung ausgeben */
            printf("Warten auf Thread %d fehlgeschlagen: %s\n", i, strerror(ret));
            return 1;
        }
        printf("Thread %d wurde beendet\n", i);
    }

    return 0;
}

void *philosopher_main(void *param) {
    int philosopher_id = *(int*)param;
    int left_chopstick = philosopher_id;
    int right_chopstick = (philosopher_id + 1) % PHILOSOPHER_COUNT;
    while (1) {
        /* Denken */
        printf("Philosoph %d denkt\n", philosopher_id);

        /* Gabeln nehmen */
        printf("Philosoph %d hat Hunger\n", philosopher_id);

        while (1) {
            printf("Philosoph %d greift linkes Stäbchen (Nummer %d)\n", philosopher_id, left_chopstick);
            pthread_mutex_lock(&mutex[left_chopstick]);
            printf("Philosoph %d hat linkes Stäbchen (Nummer %d)\n", philosopher_id, left_chopstick);

            // Versuche, rechtes Stäbchen zu greifen
            printf("Philosoph %d versucht rechtes Stäbchen (Nummer %d)\n", philosopher_id, right_chopstick);
            if (pthread_mutex_trylock(&mutex[right_chopstick]) == 0) {
                // Erfolgreich beide Stäbchen erhalten
                printf("Philosoph %d hat rechtes Stäbchen (Nummer %d)\n", philosopher_id, right_chopstick);
                break;
            } else {
                // Rechtes Stäbchen nicht verfügbar, linkes freigeben und warten
                printf("Philosoph %d kann rechtes Stäbchen nicht bekommen, gibt linkes zurück\n", philosopher_id);
                pthread_mutex_unlock(&mutex[left_chopstick]);
            }
        }

        /* Essen */
        printf("Philosoph %d isst\n", philosopher_id);

        /* Gabeln zurücklegen */
        printf("Philosoph %d ist satt\n", philosopher_id);
        printf("Philosoph %d gibt rechtes Stäbchen zurück (Nummer %d)\n", philosopher_id, right_chopstick);
        pthread_mutex_unlock(&mutex[right_chopstick]);
        printf("Philosoph %d gibt linkes Stäbchen zurück (Nummer %d)\n", philosopher_id, left_chopstick);
        pthread_mutex_unlock(&mutex[left_chopstick]);
    }
}