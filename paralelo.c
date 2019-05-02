
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <crypt.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>

#define MAX_CHARS 4
#define THREADS 3
#define DEBUG_MODE false

// PROTOTIPOS
void TimeInit(void);
double TimeStart(void);
double TimeStop(double);

// VALOR DO OVERHEAD DA MEDICAO DE TEMPO
static double TimeOverhead = 0.0;

int num_valid_chars;
char *valid_chars = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
char *hash_to_search = "aaI8pRQwCn7N2"; //AAAA
//char *hash_to_search = "aaWEGpNpWCGPg"; //AB
int found_hash = false;
char salt[3];

// FUNCAO QUE CALCULA O OVERHEAD DA MEDICAO DE TEMPO
void TimeInit()
{
    double t;

    TimeOverhead = 0.0;
    t = TimeStart();
    TimeOverhead = TimeStop(t);
}

// FUNCAO QUE CAPTURA O TEMPO INICIAL DO TRECHO A SER MEDIDO
double TimeStart()
{
    struct timeval tv;
    struct timezone tz;

    if (gettimeofday(&tv, &tz) != 0)
        exit(1);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

// FUNCAO QUE CALCULA O TEMPO GASTO NO FINAL DO TRECHO A SER MEDIDO
double TimeStop(double TimeInitial)
{
    struct timeval tv;
    struct timezone tz;
    double Time;

    if (gettimeofday(&tv, &tz) != 0)
        exit(1);
    Time = tv.tv_sec + tv.tv_usec / 1000000.0;
    return Time - TimeInitial - TimeOverhead;
}

void CheckCrypt(char word[], char salt[])
{
    struct crypt_data data[1] = {0};
    char *response;

    response = crypt_r(word, salt, data);
    DEBUG_MODE ? printf("Returned Value: %s\n", response) : 0;
}

int CheckHash(char prefix[], struct crypt_data data)
{
    if (strcmp(hash_to_search, crypt_r(prefix, salt, &data)) == 0)
    {
        return true;
    }
    return false;
}

void nextCombination(int step, char init[], struct crypt_data *data)
{
    step += 1;
    bool inRange = step <= MAX_CHARS;
    int j;
    for (j = 0; j < num_valid_chars; j++)
    {
        if (inRange && !found_hash)
        {
            init[step - 1] = valid_chars[j];
            if (strcmp(hash_to_search, crypt_r(init, salt, data)) == 0)
            {
                fprintf(stderr, "\n\n### Decrypted: %s ###\n\n", init);
                found_hash = true;
            }
            DEBUG_MODE ? fprintf(stderr, "Checking: %s...\n", init) : 0;
            nextCombination(step, init, data);
        }
    }
}

int main()
{
    char indChars[MAX_CHARS];
    double inicio, total;

    num_valid_chars = strlen(valid_chars);
    omp_set_num_threads(THREADS);

    TimeInit();
    inicio = TimeStart();

    salt[0] = hash_to_search[0];
    salt[1] = hash_to_search[1];
    salt[2] = '\0';

    int i;
    #pragma omp parallel for
    for (i = 0; i < num_valid_chars; i++)
    {
        struct crypt_data data;
        data.initialized = 0;
        char init[MAX_CHARS];
        init[0] = valid_chars[i];
        strcmp(hash_to_search, crypt_r(init, salt, &data));
        nextCombination(1, init, &data);
    }

    // MOSTRA O TEMPO DE EXECUCAO
    total = TimeStop(inicio);
    printf("\n---%lf segundos---\n", total);
    printf("---%d threads---\n", THREADS);

    //CheckCrypt("AB","aa");

    return 0;
}