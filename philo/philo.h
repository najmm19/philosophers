/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiop <fdiop@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:40:27 by fdiop             #+#    #+#             */
/*   Updated: 2025/07/07 12:40:42 by fdiop            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

// ANSI color codes
# define COLOR_GREEN  "\033[0;32m"
# define COLOR_PURPLE "\033[0;35m"
# define COLOR_RED    "\033[0;31m"
# define COLOR_RESET  "\033[0m"

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mid;
}	t_fork;

typedef struct s_args
{
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_t_eat;
	long			start_time;
	int				som_dead;
	int				all_eat;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_dead_meal;
	pthread_mutex_t	mutex_meal;
	pthread_t		monitor;
	t_fork			*struct_fork;
}	t_args;

typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	int				nb_t_eat;
	long			last_meal;
	int				nb_meal;
	pthread_mutex_t	mutex_time_last_meal;
	pthread_mutex_t	mutex_nb_meal;
	t_fork			*r_fork;
	t_fork			*l_fork;
	t_args			*args;
}	t_philo;

// parsing
int			check_args(t_args *args, int ac);
void		init_args(t_args *args);
t_args		*parse(int ac, char **av, long start_time, t_args *args);

// init
t_philo		*create_philo(t_args *args, t_philo *philo);
t_philo		*init_philo(t_args *args);
t_fork		*init_fork(t_args *args);

// time and print
long		get_time(void);
long		get_time_log(long start_time);
void		safe_print(long time, int id_philo, char *str, t_philo *philo);

// routine
void		*routine_function(void *data);
void		*monitoring_function(void *data);

// monitoring
int			check_death(t_args *args);
int			check_nb_eat(t_args *args);

// cleanup
void		destroy_fork(t_philo *philo);
void		destroy_mutex(t_args *args);
void		exit_philo(t_philo *philo, t_args *args);

#endif