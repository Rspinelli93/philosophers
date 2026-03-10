/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:54:03 by rick              #+#    #+#             */
/*   Updated: 2025/12/10 14:14:42 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	one_philo(t_philo *philo);
static void	eating(t_philo *philo);

/*
* Philosophers Routine:
- Handle 1 Philosopher Case.
- Prevent all philos from grabbing forks at the same time:
	ft_usleep()
* Infinite loop:
    -Check if dead before starting new cycle
*EAT
	- eating();
*SLEEP
	- Print "is sleeping".
	- ft_usleep(time_to_sleep).
*THINK
	- Print "is thinking".
*/
void	*ph_rout(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (philo->data->num_philo == 1)
		return (one_philo(philo), NULL);
	if (philo->id % 2 == 0)
		ft_usleep(35, philo->data);
	while (1)
	{
		pthread_mutex_lock(&philo->data->end_mtx);
		if (philo->data->end_sim)
		{
			pthread_mutex_unlock(&philo->data->end_mtx);
			break ;
		}
		pthread_mutex_unlock(&philo->data->end_mtx);
		eating(philo);
		print_msg(philo, philo->id, 3);
		ft_usleep(philo->data->tm_sleep, philo->data);
		print_msg(philo, philo->id, 4);
	}
	return (NULL);
}

/*
/ Lock l_fork & Print "has taken a fork".
/ Lock r_fork & Print "has taken a fork".
/ Print "is eating".
/ Lock internal mutex (to protect last_meal update).
	* important, so there is no data race between the monitor and
	* the philo changing the data on "last meal and meal count"
/ Update last_meal = get_time().
/ Increment meals_cnt.
/ Unlock internal mutex.
/ ft_usleep(time_to_eat).
/ Unlock r_fork & Unlock l_fork. */
static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork->mtx);
	print_msg(philo, philo->id, 1);
	pthread_mutex_lock(&philo->r_fork->mtx);
	print_msg(philo, philo->id, 1);
	print_msg(philo, philo->id, 2);
	pthread_mutex_lock(&philo->meal_mtx);
	philo->tm_last_meal = get_time();
	philo->meals_cnt++;
	pthread_mutex_unlock(&philo->meal_mtx);
	ft_usleep(philo->data->tm_eat, philo->data);
	pthread_mutex_unlock(&philo->r_fork->mtx);
	pthread_mutex_unlock(&philo->l_fork->mtx);
}

/*  
	If num_philo == 1:
	Lock l_fork.
	Print "has taken a fork".
	ft_usleep(time_to_die).
	Unlock l_fork.
	Return NULL (He dies). */
static void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork->mtx);
	print_msg(philo, philo->id, 1);
	ft_usleep(philo->data->tm_die, philo->data);
	pthread_mutex_unlock(&philo->l_fork->mtx);
}
