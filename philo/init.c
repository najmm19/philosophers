/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiop <fdiop@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:45:21 by fdiop             #+#    #+#             */
/*   Updated: 2025/07/07 10:54:41 by fdiop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*init_fork(t_args *args)
{
	t_fork	*struct_fork;
	int		i;

	struct_fork = malloc(args->nb_philo * sizeof(t_fork));
	i = 0;
	while (i < (args->nb_philo))
	{
		struct_fork[i].id = i + 1;
		pthread_mutex_init(&struct_fork[i].mid, NULL);
		i++;
	}
	return (struct_fork);
}

t_philo	*init_fork_for_philo(t_philo *struct_philo,
	t_fork *struct_fork, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		struct_philo[i].nb_meal = 0;
		struct_philo[i].r_fork = &struct_fork[i];
		if (i != (args->nb_philo - 1))
			struct_philo[i].l_fork = &struct_fork[i + 1];
		if (i == (args->nb_philo - 1))
			struct_philo[i].l_fork = &struct_fork[0];
		i++;
	}
	return (struct_philo);
}

t_philo	*create_philo(t_args *args, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		philo[i].last_meal = get_time();
		pthread_create(&philo[i].tid, NULL, &routine_function, &philo[i]);
		i++;
	}
	pthread_create(&args->monitor, NULL, &monitoring_function, philo);
	i = 0;
	return (philo);
}

t_philo	*init_philo(t_args *args)
{
	t_philo	*struct_philo;
	t_fork	*struct_fork;
	int		i;

	struct_philo = malloc(args->nb_philo * sizeof(t_philo));
	i = 0;
	while (i < args->nb_philo)
	{
		pthread_mutex_init(&struct_philo[i].mutex_nb_meal, NULL);
		pthread_mutex_init(&struct_philo[i].mutex_time_last_meal, NULL);
		struct_philo[i].id = i + 1;
		struct_philo[i].nb_t_eat = args->nb_t_eat;
		struct_philo[i].args = args;
		i++;
	}
	struct_fork = init_fork(args);
	struct_philo = init_fork_for_philo(struct_philo, struct_fork, args);
	struct_philo = create_philo(args, struct_philo);
	return (struct_philo);
}
