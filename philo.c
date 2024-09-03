#include "philo.h"

void *philosopher_life(void *arg) {
    t_philosopher *philosopher = (t_philosopher *)arg;
    t_table *table = philosopher->table;

    while (!table->stop) {
        take_forks(philosopher);
        eating(philosopher);
        release_forks(philosopher);
        sleeping(philosopher);
        thinking(philosopher);
    }
    return NULL;
}
