#include "philo.h"

int main(int argc, char **argv) {
    t_table table;
    
    if (argc < 5 || argc > 6) {
        printf("%s Invalid number of arguments", argv[0]);
        return (1);
    }

    init_data(&table, argc, argv);
    table.start_time = current_time();

    int i = 0;
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
