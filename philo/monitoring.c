/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiop <fdiop@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:04:02 by fdiop             #+#    #+#             */
/*   Updated: 2025/07/07 13:34:09 by fdiop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_args *args)
{
	int	som_dead;

	pthread_mutex_lock(&args->mutex_dead);
	som_dead = args->som_dead;
	pthread_mutex_unlock(&args->mutex_dead);
	return (som_dead);
}

int	check_nb_eat(t_args *args)
{
	int	all_done;

	pthread_mutex_lock(&args->mutex_dead_meal);
	all_done = args->all_eat;
	pthread_mutex_unlock(&args->mutex_dead_meal);
	return (all_done);
}

int	monitoring_death(t_philo *philo, int i)
{
	if ((get_time() - philo[i].last_meal) >= philo->args->t_die)
	{
		pthread_mutex_unlock(&philo[i].mutex_time_last_meal);
		pthread_mutex_lock(&philo->args->mutex_dead);
		philo->args->som_dead = 1;
		pthread_mutex_unlock(&philo->args->mutex_dead);
		pthread_mutex_lock(&philo->args->mutex_dead);
		safe_print(get_time_log(philo->args->start_time),
			philo[i].id, "died\n", &philo[i]);
		pthread_mutex_unlock(&philo->args->mutex_dead);
		return (1);
	}
	return (0);
}

int	monitoring_add_meal(t_philo *philo, int i, int res)
{
	int	nb;

	pthread_mutex_lock(&philo[i].mutex_nb_meal);
	nb = philo[i].nb_meal;
	pthread_mutex_unlock(&philo[i].mutex_nb_meal);
	if (nb >= philo[i].args->nb_t_eat)
		res++;
	if (res == philo[0].args->nb_philo && philo[0].args->nb_t_eat != 0)
	{
		philo->args->all_eat = 1;
		res = -1;
	}
	return (res);
}

void	*monitoring_function(void *data)
{
	t_philo	*philo;
	t_args	*args;
	int		i;
	int		res;

	philo = (t_philo *)data;
	args = philo->args;
	res = 0;
	while (!(check_death(args) || check_nb_eat(args)))
	{
		i = 0;
		res = 0;
		while (i < args->nb_philo)
		{
			pthread_mutex_lock(&philo[i].mutex_time_last_meal);
			if (monitoring_death(philo, i))
				return (NULL);
			pthread_mutex_unlock(&philo[i].mutex_time_last_meal);
			res = monitoring_add_meal(philo, i, res);
			if (res == -1)
				return (NULL);
			i++;
		}
	}
	return (NULL);
}
