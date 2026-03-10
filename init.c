/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:51:06 by rick              #+#    #+#             */
/*   Updated: 2025/12/10 13:43:03 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_philo(t_data *data);

/*
*Function to initialize the data or "table"
- Gets all values from argument vector.
- Runs init_tab()*/
t_data	*init_philo(int ac, char **av)
{
	t_data	*data;

	data = safe_malloc(sizeof(t_data), NULL);
	data->num_philo = ft_atol(av[1]);
	data->tm_die = ft_atol(av[2]);
	data->tm_eat = ft_atol(av[3]);
	data->tm_sleep = ft_atol(av[4]);
	if (ac == 6)
		data->n_meals = ft_atol(av[5]);
	else
		data->n_meals = -1;
	init_tab(data);
	return (data);
}

/*
*Function to initialize forks and philos.
- Initialize the mutex for printing and end simulation
- Allocate philos and forks
	With that, their respective data.
	For forks the mutexes.
	For philos all philo data.*/
void	init_tab(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->print_mtx, NULL);
	pthread_mutex_init(&data->end_mtx, NULL);
	data->end_sim = false;
	data->philos = safe_malloc(sizeof(t_philo) * data->num_philo, data);
	data->forks = safe_malloc(sizeof(t_fork) * data->num_philo, data);
	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_init(&(data->forks[i].mtx), NULL);
		data->forks[i].ix = i;
		i++;
	}
	i = 0;
	set_philo(data);
}

/*
* Helper function to init data on each philosopher. */
static void	set_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % data->num_philo];
		data->philos[i].meals_cnt = 0;
		data->philos[i].tm_last_meal = 0;
		data->philos[i].full = false;
		pthread_mutex_init(&data->philos[i].meal_mtx, NULL);
		i++;
	}
}

void	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->num_philo)
	{
		data->philos[i].tm_last_meal = data->start_time;
		pthread_create(&data->philos[i].trd, NULL, ph_rout, &data->philos[i]);
		i++;
	}
	pthread_create(&data->monitor, NULL, monitor_routine, data);
	i = 0;
	while (i < data->num_philo)
	{
		pthread_join(data->philos[i].trd, NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
}
