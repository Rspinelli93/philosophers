/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:11:55 by rick              #+#    #+#             */
/*   Updated: 2025/12/09 23:17:12 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// ------------- DEFINES ----------------

# define RED     "\033[1;31m"
# define GREEN   "\033[1;32m"
# define YELLOW  "\033[1;33m"
# define BLUE    "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define RESET   "\033[0m"

// ------------- INCLUDES ----------------

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>

// ------------- STRUCTS ----------------

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;
typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_trd;

struct s_data
{
	long	num_philo;
	long	tm_die;
	long	tm_eat;
	long	tm_sleep;
	long	n_meals;
	long	start_time;
	bool	end_sim;
	t_mutex	end_mtx;
	t_mutex	print_mtx;
	t_fork	*forks;
	t_philo	*philos;
	t_trd	monitor;
};

struct s_philo
{
	t_data	*data;
	int		id;
	long	meals_cnt;
	bool	full;
	long	tm_last_meal;
	t_fork	*l_fork;
	t_fork	*r_fork;
	t_trd	trd;
	t_mutex	meal_mtx;
};

struct s_fork
{
	t_mutex	mtx;
	int		ix;
};

// ------------- PROTOTYPES ----------------
//* ------ exit.c ------ //

void	exit_msg(char *msg);
void	usage_err_msg(void);
void	cleanup(t_data *data);
void	free_philo(t_data *data);

//* ------ init.c ------ //

void	init_tab(t_data *data);
void	start_simulation(t_data *data);
t_data	*init_philo(int ac, char **av);

//* ------ routines ------ //

void	*ph_rout(void *philosopher);
void	*monitor_routine(void *table_data);

//* ------ parse.c ------ //

int		input_parser(int ac, char **av);
long	ft_atol(char *str);

//* ------ utils.c ------ //

void	*safe_malloc(size_t bytes, t_data *data);
void	print_msg(t_philo *philo, int philo_id, int type);
long	get_time(void);
void	ft_usleep(long time_in_ms, t_data *data);

#endif
