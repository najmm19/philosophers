/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiop <fdiop@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:22:10 by fdiop             #+#    #+#             */
/*   Updated: 2025/07/07 12:35:22 by fdiop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}

long	get_time_log(long start_time)
{
	return (get_time() - start_time);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (s1[i] - s2[i]);
	}
	return (s1[i] - s2[i]);
}

void	safe_print(long time, int id_philo, char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->args->mutex_print);
	if (ft_strcmp(str, "is eating\n") == 0)
		printf(COLOR_GREEN "[%ld] %d %s" COLOR_RESET, time, id_philo, str);
	else if (ft_strcmp(str, "has taken a fork\n") == 0)
		printf(COLOR_PURPLE "[%ld] %d %s" COLOR_RESET, time, id_philo, str);
	else if (ft_strcmp(str, "died\n") == 0)
		printf(COLOR_RED "[%ld] %d %s" COLOR_RESET, time, id_philo, str);
	else
		printf("[%ld] %d %s", time, id_philo, str);
	pthread_mutex_unlock(&philo->args->mutex_print);
}

/*void safe_print(long time, int id_philo, char *str, t_philo *philo)
{
    pthread_mutex_lock(&philo->args->mutex_print);
    printf("[%ld] %d %s", time, id_philo, str);
    pthread_mutex_unlock(&philo->args->mutex_print);
}*/

/*void safe_print_test(char *str, t_philo *philo)
{
    pthread_mutex_lock(&philo->args->mutex_print);
    printf("\033[0;32m[%ld] %d %s %d fois\n\033[0m",
    get_time_log(philo->args->start_time), philo->id, str, philo->nb_meal);
    pthread_mutex_unlock(&philo->args->mutex_print);
}*/

/*void safe_print_test2(t_philo *philo, int res)
{
    pthread_mutex_lock(&philo->args->mutex_print);
    printf("\033[0;35mNB DE PHILO QUI ONT ASSEZ MANGE = %d\n\033[0m", res);
    pthread_mutex_unlock(&philo->args->mutex_print);
}*/