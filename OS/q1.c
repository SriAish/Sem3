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

pthread_t ply1, ply2, ref;
pthread_mutex_t lock1, lock2, lock3;
pthread_cond_t cond1, cond2, cond3;
// A normal C function that is executed as a thread
// when its name is specified in pthread_create()
void *player1(void *pnum){
    // Store the value argument passed to this thread
    ll *p_id = (ll *)pnum;
    pthread_mutex_lock(&lock1);
        ply1 = pthread_self();
        pthread_cond_wait(&cond1, &lock1);
    pthread_mutex_unlock(&lock1);
    sleep(1);
    printf("p1 returning\n");
    return NULL;
}

void *player2(void *pnum){
    // Store the value argument passed to this thread
    ll *p_id = (ll *)pnum;
    pthread_mutex_lock(&lock2);
        ply2 = pthread_self();
        pthread_cond_wait(&cond2, &lock2);
    pthread_mutex_unlock(&lock2);
    sleep(1);
    printf("p2 returning\n");
    return NULL;
}

void *refree(void *rnum){
    // Store the value argument passed to this thread
    ll *r_id = (ll *)rnum;
    pthread_mutex_lock(&lock3);
        ref = pthread_self();
        pthread_cond_wait(&cond3, &lock3);
    pthread_mutex_unlock(&lock3);
    sleep(0.5);
    printf("r returning\n");
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
            int ch;
            if(pin%2) ch = pthread_create(&player_id[pin], NULL, player1, (void *)&state[pin/2]);
            else ch = pthread_create(&player_id[pin], NULL, player2, (void *)&state[pin/2]);
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
            pthread_t p1, p2, r1;

            pthread_mutex_lock(&lock1);
                pthread_cond_signal(&cond1);
                p1 = ply1;
            pthread_mutex_unlock(&lock1);
            pthread_mutex_lock(&lock2);
                pthread_cond_signal(&cond2);
                p2 = ply2;
            pthread_mutex_unlock(&lock2);
            pthread_mutex_lock(&lock3);
                pthread_cond_signal(&cond3);
                r1 = ref;
            pthread_mutex_unlock(&lock3);
            printf("here p1=%ld p2:%ld r1:%ld\n",p1,p2,r1);
            for(i=0 ; i<=pin+pleft ; i++) printf("p:%ld\n", player_id[i]);
            for(i=0 ; i<=rin+rleft ; i++) printf("p:%ld\n", refree_id[i]);

            pthread_join(p1, NULL);
            pthread_join(p2, NULL);
            //pthread_join(r1, NULL);
            pdone+=2;
            rdone++;

        }
        printf("out\n");
        sleep(0.5);
    }
    return 0;
}
