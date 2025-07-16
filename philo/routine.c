/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiop <fdiop@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:36:16 by fdiop             #+#    #+#             */
/*   Updated: 2025/07/07 13:33:44 by fdiop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	safe_print(get_time_log(philo->args->start_time),
		philo->id, "is sleeping\n", philo);
	usleep(philo->args->t_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	safe_print(get_time_log(philo->args->start_time),
		philo->id, "is thinking\n", philo);
	usleep(200);
}

void	part_eat(t_philo *philo)
{
	if (check_nb_eat(philo->args) || check_death(philo->args))
	{
		pthread_mutex_unlock(&philo->r_fork->mid);
		pthread_mutex_unlock(&philo->l_fork->mid);
		return ;
	}
	safe_print(get_time_log(philo->args->start_time),
		philo->id, "has taken a fork\n", philo);
	safe_print(get_time_log(philo->args->start_time),
		philo->id, "has taken a fork\n", philo);
	safe_print(get_time_log(philo->args->start_time),
		philo->id, "is eating\n", philo);
	usleep(philo->args->t_eat * 1000);
	pthread_mutex_lock(&philo->mutex_nb_meal);
	philo->nb_meal += 1;
	pthread_mutex_unlock(&philo->mutex_nb_meal);
	pthread_mutex_lock(&philo->mutex_time_last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->mutex_time_last_meal);
	pthread_mutex_unlock(&philo->r_fork->mid);
	pthread_mutex_unlock(&philo->l_fork->mid);
}

void	*philo_eat(t_philo *philo)
{
	if (philo->args->nb_philo == 1)
	{
		pthread_mutex_lock(&philo->r_fork->mid);
		safe_print(get_time_log(philo->args->start_time),
			philo->id, "has taken a fork\n", philo);
		usleep(philo->args->t_die * 1000);
		pthread_mutex_unlock(&philo->r_fork->mid);
		return (NULL);
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->r_fork->mid);
		pthread_mutex_lock(&philo->l_fork->mid);
	}
	else
	{
		pthread_mutex_lock(&philo->l_fork->mid);
		pthread_mutex_lock(&philo->r_fork->mid);
	}
	part_eat(philo);
	return (NULL);
}

void	*routine_function(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		if (check_nb_eat(philo->args) || check_death(philo->args))
			break ;
		philo_eat(philo);
		if (check_nb_eat(philo->args) || check_death(philo->args))
			break ;
		philo_think(philo);
		if (check_nb_eat(philo->args) || check_death(philo->args))
			break ;
		philo_sleep(philo);
	}
	return (NULL);
}

// eat -> think -> sleep