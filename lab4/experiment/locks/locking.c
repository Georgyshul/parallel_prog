#include "locking.h"

int main() {
    int num_threads = 4;
    int shared_counter = 0;
    int num_iterations = 10000;

    #ifdef WITH_LOCKS
        printf("Started program with locks...\n");
    #else
        printf("Started program without locks...\n");
    #endif

    omp_lock_t counter_lock;
    omp_init_lock(&counter_lock);

    #pragma omp parallel num_threads(num_threads)
    {
        int tid = omp_get_thread_num();
        printf("Thread %d starting...\n", tid);

        for (int i = 0; i < num_iterations; ++i) {
            #ifdef WITH_LOCK
                omp_set_lock(&counter_lock);
            #endif
            shared_counter++;
            #ifdef WITH_LOCK
                omp_unset_lock(&counter_lock);
            #endif
        }

        printf("Thread %d finished.\n", tid);
    }

    #ifdef WITH_LOCKS
        printf("Final value of the shared counter with lock: %d\n", shared_counter);
    #else
        printf("Final value of the shared counter without lock: %d\n", shared_counter);
    #endif

    printf("Expected value: %d\n", num_threads * num_iterations);

    omp_destroy_lock(&counter_lock);

    return 0;
}