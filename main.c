/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:21:02 by rick              #+#    #+#             */
/*   Updated: 2025/12/09 23:10:01 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (input_parser(ac, av))
	{
		data = init_philo(ac, av);
		start_simulation(data);
		cleanup(data);
	}
	else
		return (usage_err_msg(), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
- pthread_create(thread_ptr, attr, routine, arg)
* Spawns a new thread that immediately runs the 'routine' 
	*function.
* Connection: Used to birth a philosopher who runs their 
	*lifecycle loop.

- pthread_join(thread, retval_ptr)
* Blocks the current thread until the specific 'thread' finishes.
* Connection: Main thread uses this to wait for all philosophers 
	*before exiting.

- pthread_detach(thread)
* Tells OS to reclaim thread resources automatically on finish; 
	*prevents joining.
* Connection: sometimes used for the death-monitoring thread 
	*to run independently.


- pthread_mutex_init(mutex_ptr, attr)
* Initializes a mutex object so it can be locked/unlocked.
* Connection: Turns a variable into a usable 'fork' 
	*before simulation starts.

- pthread_mutex_lock(mutex_ptr)
* Tries to take the lock; if taken, the thread waits/blocks until available.
* Connection: A philosopher taking a fork or protecting the print function.

- pthread_mutex_unlock(mutex_ptr)
* Releases the lock so other waiting threads can acquire it.
* Connection: A philosopher putting down a fork after eating.

- pthread_mutex_destroy(mutex_ptr)
* Invalidates the mutex and frees its resources (must be unlocked).
* Connection: Cleaning up forks/locks at the very end to prevent leaks.
*/
