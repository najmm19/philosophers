/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiop <fdiop@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:07:43 by fdiop             #+#    #+#             */
/*   Updated: 2025/07/07 12:55:47 by fdiop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_atoi(const char *ss)
{
	int				i;
	long long		nb;
	char			*str;

	i = 0;
	nb = 0;
	str = (char *)ss;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		if (nb > INT_MAX)
			return (0);
		i++;
	}
	if (str[i] != '\0')
		nb = 0;
	return ((int)nb);
}

void	init_args(t_args *args)
{
	args->nb_philo = 0;
	args->t_die = 0;
	args->t_eat = 0;
	args->t_sleep = 0;
	args->nb_t_eat = 0;
	args->som_dead = 0;
	args->all_eat = 0;
	pthread_mutex_init(&args->mutex_dead, NULL);
	pthread_mutex_init(&args->mutex_meal, NULL);
	pthread_mutex_init(&args->mutex_print, NULL);
	pthread_mutex_init(&args->mutex_dead_meal, NULL);
}

t_args	*parse(int ac, char **av, long start_time, t_args *args)
{
	init_args(args);
	if (!(ac == 5 || ac == 6))
		return (args);
	args->start_time = start_time;
	args->nb_philo = philo_atoi(av[1]);
	args->t_die = philo_atoi(av[2]);
	args->t_eat = philo_atoi(av[3]);
	args->t_sleep = philo_atoi(av[4]);
	if (ac == 6)
		args->nb_t_eat = philo_atoi(av[5]);
	return (args);
}

int	check_args(t_args *args, int ac)
{
	int	res;

	res = 1;
	if (args->nb_philo == 0)
		res = 0;
	if (args->t_die == 0)
		res = 0;
	if (args->t_eat == 0)
		res = 0;
	if (args->t_sleep == 0)
		res = 0;
	if (ac == 6 && args->nb_t_eat == 0)
		res = 0;
	if (!res)
		printf("\033[1m\033[31mError:\033[0m\033[31m "
			"Arguments must be 4-5 positive numbers.\033[0m\n");
	return (res);
}

/*int main(void)
{
	printf("%d\n", philo_atoi("214748364732"));
	return (0);
}*/