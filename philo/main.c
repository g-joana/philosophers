#include "philosophers.h"

static int mise_en_place(t_table *table)
{
    int	count = 0;

    pthread_create(&table->monitor_thread, NULL, (void *)monitor, table);
    while (count < table->n_philos)
    {
	pthread_create(&table->philos[count].thread, NULL, (void *)dinner, &table->philos[count]);
	count++;
    }
    table->philos_ready = 1;
    count = 0;
    while (count < table->n_philos)
    {
	pthread_join(table->philos[count].thread, NULL);
	count++;
    }
    pthread_join(table->monitor_thread, NULL);
    printf("saiuu\n");
    return (0);
}

int main(int argc, char **argv)
{
    t_table table;

    if (argc < 5 || argc > 6)
    {
        printf("\ninsert a valid input(int):\n");
        printf("./philo number_of_philosophers time_to_die time_to_eat, time_to_sleep [number_of_times_each_philosopher_must_eat]\n\n");
        return (EXIT_FAILURE);
    }
    parse(argc, argv, &table);
    init(&table);
    if (table.n_philos == 1)
    {
	printf("%lu %i has taken a fork\n", (unsigned long)0, 1);
	printf("%lu %i is DEAD\n", (unsigned long)table.time_to_die, 1);
	free(table.philos);
	free(table.hashis);
	return (EXIT_SUCCESS);
    }
    mise_en_place(&table);
    free(table.philos);
    free(table.hashis);
    return (EXIT_SUCCESS);
}
