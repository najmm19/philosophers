/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiop <fdiop@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:18:09 by fdiop             #+#    #+#             */
/*   Updated: 2025/07/07 14:28:40 by fdiop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_fork(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->args->nb_philo)
	{
		pthread_mutex_destroy(&philo[i].r_fork->mid);
		pthread_mutex_destroy(&philo[i].mutex_nb_meal);
		pthread_mutex_destroy(&philo[i].mutex_time_last_meal);
		i++;
	}
}

void	destroy_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->args->nb_philo)
	{
		pthread_join(philo[i].tid, NULL);
		i++;
	}
	pthread_join(philo->args->monitor, NULL);
}

void	destroy_mutex(t_args *args)
{
	pthread_mutex_destroy(&args->mutex_dead);
	pthread_mutex_destroy(&args->mutex_meal);
	pthread_mutex_destroy(&args->mutex_dead_meal);
	pthread_mutex_destroy(&args->mutex_print);
}

void	exit_philo(t_philo *philo, t_args *args)
{
	destroy_threads(philo);
	destroy_fork(philo);
	destroy_mutex(args);
	free(philo[0].r_fork);
	free(&philo[0]);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_args	*args;
	t_args	args_struct;

	args = &args_struct;
	args->start_time = get_time();
	args = parse(ac, av, args->start_time, args);
	if (!check_args(args, ac))
		return (1);
	philo = init_philo(args);
	exit_philo(philo, args);
	return (0);
}

// void	print_philo(t_args *args, t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	printf("\n");
// 	while (i < args->nb_philo)
// 	{
// 		printf("\033[90m[PHILO %d]  [TID :%lu]  [R_FORK : id = %d - mid = %p]  "
// 			"[L_FORK : id = %d - mid = %p]\033[0m\n",
// 			philo[i].id, philo[i].tid,
// 			philo[i].r_fork->id, (void *)&philo[i].r_fork->mid,
// 			philo[i].l_fork->id, (void *)&philo[i].l_fork->mid);
// 		i++;
// 	}
// 	printf("\n");
// }