#include "philosophers.h"

int	ft_atol(char *ascii)
{
	int	i;
	int	sig;
	int	count;
	long	nb;

	i = 0;
	sig = 1;
	count = 1;
	nb = 0;
	while ((ascii[i] >= 8 && ascii[i] <= 13) || (ascii[i] == ' '))
		i++;
	while ((ascii[i] == '-' || ascii[i] == '+') && count--)
	{
		if (ascii[i] == '-')
			sig = -1;
		i++;
	}
	while (ascii[i] >= '0' && ascii[i] <= '9')
		nb = nb * 10 + (ascii[i++] - '0');
    return (nb * sig);
}

int atoi_wrapper(char *ascii);

void	is_nbr(char **argv)
{
    int	n = 1;
    int	i;

    while (argv && argv[n])
    {
	i = 0;
	while (argv[n][i] && argv[n][i] >= '0' && argv[n][i] <= '9')
	    i++;
	if (argv[n][i] != '\0')
	{
	    printf("\ninput must be a positive int\n");
	    exit (1);
	}
	n++;
    }
}

void parse(int argc, char **argv, t_table *table)
{
    int ret = 0;

    is_nbr(argv);
    table->n_philos = ft_atol(argv[1]);
    if (table->n_philos > 200 || table->n_philos < 1)
	    ret = printf("number of philosophers must be from 1 to 200\n");
    table->time_to_die = ft_atol(argv[2]);
    if (table->time_to_die > INT_MAX || table->time_to_die < 1)
	    ret = printf("time to die must be from 1 to %i\n", INT_MAX);
    table->time_to_eat = ft_atol(argv[3]);
    if (table->time_to_eat > INT_MAX || table->time_to_eat < 1)
	    ret = printf("time to die must be from 1 to %i\n", INT_MAX);
    table->time_to_sleep = ft_atol(argv[4]);
    if (table->time_to_sleep > INT_MAX || table->time_to_sleep < 1)
	    ret = printf("time to die must be from 1 to %i\n", INT_MAX);
    if (argc == 6)
    {
	table->n_meals = ft_atol(argv[5]);
	    if (table->n_meals > INT_MAX || table->n_meals < 0)
		ret = printf("time to die must be from 0 to %i\n", INT_MAX);
    }
    else
	table->n_meals = -1;
    if (ret)
	exit (1);
}
