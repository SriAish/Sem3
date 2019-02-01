#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef long long int ll;
// state
ll st = -1;
// players and refrees in academy
ll pin, rin;
// players and refrees in academy and also in court
ll pdone, rdone;
// players and refrees left to come
ll pleft, rleft;

// A normal C function that is executed as a thread
// when its name is specified in pthread_create()
void *player(void *pnum){
    // Store the value argument passed to this thread
    ll *p_id = (ll *)pnum;

    while(*p_id!=st);

    sleep(1);
    return NULL;
}

void *refree(void *rnum){
    // Store the value argument passed to this thread
    ll *r_id = (ll *)rnum;

    while(*r_id!=st);
    sleep(0.5);
    return NULL;
}

int main()
{
    ll n;
    scanf("%lld", &n);
    pleft = 2*n;
    rleft = n;
    ll state[n];
    ll i;
    for (i = 0; i < n; ++i) {
        state[i]=i;
    }
    // thread ids
    pthread_t player_id[200005];
    pthread_t refree_id[100005];
    float prob = 0;
    int ply = 1;
    while (pleft || rleft) {
        if (!pleft){
            ply = 0;
        }
        else if (!rleft){
            ply = 1;
        }
        else{
            prob = ((float)rleft / (pleft + rleft));
            printf("%f\n", prob);
            if (prob > 0.5) ply = 0;
            else ply = 1;
        }

        if(ply){
            int ch = pthread_create(&player_id[pin], NULL, player, (void *)&state[pin/2]);
            if (ch) {
                // Failed to create thread.
                    printf("Failed to create thread");
                    exit(-1);
            }
            ++pin;
            --pleft;
        }
        else{
            int ch = pthread_create(&refree_id[rin], NULL, refree, (void *)&state[rin]);
            if (ch) {
                // Failed to create thread.
                    printf("Failed to create thread");
                    exit(-1);
            }
            ++rin;
            --rleft;
        }
        printf("players:%lld refrees:%lld\n",pin-pdone ,rin-rdone);

        if(pdone + 1 < pin && rdone < rin){
            st = state[rdone];

            ++rdone;
            ++pdone;
            ++pdone;

            pthread_join(player_id[pdone - 2], NULL);
            pthread_join(player_id[pdone - 1], NULL);
            pthread_join(refree_id[rdone], NULL);

        }
        sleep(3);
    }
    return 0;
}
