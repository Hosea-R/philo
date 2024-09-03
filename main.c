#include "philo.h"

int main(int argc, char **argv) {
    t_table table;
    
    if (argc < 5 || argc > 6) {
        fprintf(stderr, "Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return (1);
    }

    init_data(&table, argc, argv);

    int i;

    i = 0;
    while (i < table.num_philosophers) {
        pthread_create(&table.philosophers[i].thread, NULL, philosopher_life, &table.philosophers[i]);
        i++;
    }
    check_death(&table);
        
    i = 0;
    while (i < table.num_philosophers) {
        pthread_join(table.philosophers[i].thread, NULL);
        i++;
    }
    destroy_data(&table);
    return (0);
}
