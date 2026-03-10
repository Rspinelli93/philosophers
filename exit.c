/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:29:17 by rick              #+#    #+#             */
/*   Updated: 2025/12/10 13:42:46 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
*Function to print the parsing messages
- it has colors! :)
*/
void	exit_msg(char *msg)
{
	printf("%sERR: %s", RED, RESET);
	printf("%s%s%s", MAGENTA, msg, RESET);
	exit(EXIT_FAILURE);
}

/*
* Prints usage guide for the user in case of wrong arguments. */
void	usage_err_msg(void)
{
	printf("%sError: Wrong number of params%s\n", RED, RESET);
	printf("Usage: %s./philo %snumber_of_philosophers ", GREEN, BLUE);
	printf("%stime_to_die %stime_to_eat ", GREEN, BLUE);
	printf("%stime_to_sleep ", GREEN);
	printf("%s[number_of_times_each_philosopher_must_eat]%s\n", BLUE, RESET);
}

/*
* Frees allocated data/philos/forks*/
void	free_philo(t_data *data)
{
	if (!data)
		return ;
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	free(data);
}

/*
* Function to destroy all mutexes.*/
void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i].mtx);
		pthread_mutex_destroy(&data->philos[i].meal_mtx);
		i++;
	}
	pthread_mutex_destroy(&data->print_mtx);
	pthread_mutex_destroy(&data->end_mtx);
	free_philo(data);
}
