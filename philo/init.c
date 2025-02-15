#include "philosophers.h"

static void	init_hashis(t_table *table)
{
	int	count;

	table->hashis = malloc(sizeof(pthread_mutex_t) * (table->n_philos + 1));
	count = 0;
	while (count < table->n_philos)
	{
		pthread_mutex_init(&table->hashis[count], NULL);
		count++;
	}
}

static void	init_philos(t_table *table)
{
	int	count;

	count = 0;
	table->philos = malloc(sizeof(t_philo) * table->n_philos + 1);
	while (count < table->n_philos)
	{
		table->philos[count].left_hashi = &table->hashis[count];
		if (count == table->n_philos - 1)
			table->philos[count].right_hashi = &table->hashis[0];
		else
			table->philos[count].right_hashi = &table->hashis[count + 1];
		table->philos[count].table = table;
		table->philos[count].meals = 0;
		// table->philos[count].dead = 0;
		table->philos[count].last_meal = current_ms();
		table->philos[count].seat = count + 1;
		// pthread_mutex_init(&table->philos[count].dead_mtx, NULL);
		count++;
	}
}

void	init(t_table *table)
{
	if (table->n_philos == 1)
	{
		printf("%lu %i has taken a fork\n", (unsigned long)0, 1);
		printf("%lu %i is DEAD\n", (unsigned long)table->time_to_die, 1);
		free(table->philos);
		free(table->hashis);
		exit(1);
	}
	init_hashis(table);
	init_philos(table);
	table->start_time = current_ms();
	table->death = 0;
	table->philos_ready = 0;
	pthread_mutex_init(&table->dead_mtx, NULL);
	pthread_mutex_init(&table->write_mtx, NULL);
}
