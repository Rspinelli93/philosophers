/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:06:40 by rick              #+#    #+#             */
/*   Updated: 2025/12/10 13:52:11 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_dead(t_data *data, int index);
static bool	all_finished(t_data *data, int finished);

/*
1. Infinite Loop (while 1):
- Iterate through all philosophers
* Dead check:
	If the philosopher time since last meal is bigger than
	The time of death, then we execute is_dead()
* Check if full:
	If the philosopher reached the needed amount of meals,
	we increment the counter finished_eating on each iteration
	for each philosopher.
- Unlock internal meal_mtx.
* All finished:
	If reached this point in the iteration, all the philosopers
	have reached the n_meals, we finish the iteration.
- Reset full_philos counter.
*/
void	*monitor_routine(void *table_data)
{
	t_data	*data;
	int		i;
	int		finished_eating;

	data = (t_data *)table_data;
	while (1)
	{
		i = 0;
		finished_eating = 0;
		while (i < data->num_philo)
		{
			pthread_mutex_lock(&data->philos[i].meal_mtx);
			if (is_dead(data, i))
				return (NULL);
			if (data->n_meals != -1
				&& data->philos[i].meals_cnt >= data->n_meals)
				finished_eating++;
			pthread_mutex_unlock(&data->philos[i].meal_mtx);
			i++;
		}
		if (all_finished(data, finished_eating))
			return (NULL);
		usleep(500);
	}
}

/*
* Function helper to handle the case where the time from last
* meal is bigger than time to die.
1. Unlocks meal_mtx
2. Locks end_mtx
3. Set end simulation to true
4. Unlock end mutex
5. Print message
*/
static bool	is_dead(t_data *data, int index)
{
	if (get_time() - data->philos[index].tm_last_meal > data->tm_die)
	{
		pthread_mutex_unlock(&data->philos[index].meal_mtx);
		pthread_mutex_lock(&data->end_mtx);
		data->end_sim = true;
		pthread_mutex_unlock(&data->end_mtx);
		print_msg(&data->philos[index], index + 1, 5);
		return (true);
	}
	return (false);
}

/*
* Function helper to handle the case where all philosophers
* have finished eating the amount of meals necessary
1. Locks end_mtx
2. Set end simulation to true
3. Unlock end mutex
*/
static bool	all_finished(t_data *data, int finished)
{
	if (data->n_meals != -1 && finished == data->num_philo)
	{
		pthread_mutex_lock(&data->end_mtx);
		data->end_sim = true;
		pthread_mutex_unlock(&data->end_mtx);
		return (true);
	}
	return (false);
}
