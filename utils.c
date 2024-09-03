#include "philo.h"

void check_death(t_table *table) {
    int i;
    while (!table->stop) {
        i = 0;
        while (i < table->num_philosophers) {
            if (current_time() - table->philosophers[i].last_meal >= table->time_to_die) {
                print_action(table, i, "died");
                table->stop = 1;
                break;
            }
            i++;
        }
        usleep(1000);
    }
}

void print_action(t_table *table, int philosopher_id, const char *action) {
    pthread_mutex_lock(&table->print_lock);
    if (!table->stop)
        printf("%d %s\n", philosopher_id + 1, action);
    pthread_mutex_unlock(&table->print_lock);
}
