/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaacosta <jaacosta@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:47:51 by jaacosta          #+#    #+#             */
/*   Updated: 2025/04/21 17:25:55 by jaacosta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

/*void	create_threads(t_data data, t_philo *philos, pthread_t *threads, pthread_t *monitor)
{
	int i;

	i = 0;
	while (i < data.num_philos)
	{
		pthread_create(&threads[i], NULL, philosopher, &philos[i]);
		i++;
	}
	pthread_create(monitor, NULL, monitor_routine, &data);
}

int	handle_threads(t_data data, pthread_t *threads, pthread_t monitor)
{
	int	i;

	pthread_join(monitor, NULL);
	i = 0;
	while (i < data.num_philos)
	{
		pthread_join(threads[i], NULL);	
		i++;
	}
	return (0);
}*/

int main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;
	pthread_t	*threads;
	pthread_t	monitor;
	int	i;

	if(validate_av(ac, av))
	{
		data = init_data(ac, av);
		philos = init_philos(&data);
		data.philos = philos;
		threads = malloc(data.num_philos * sizeof(pthread_t));
		if (!threads)
			return (0);
		//create_threads(data, philos, threads, &monitor);
		//handle_threads(data, threads, monitor);
		i = 0;
		while (i < data.num_philos)
		{
			pthread_create(&threads[i], NULL, philosopher, &philos[i]);
			i++;
		}
		pthread_create(&monitor, NULL, monitor_routine, &data);
		//handle_threads(data, threads, monitor);
		i = 0;
		while (i < data.num_philos)
		{
			pthread_join(threads[i], NULL);	
			i++;
		}
		pthread_join(monitor, NULL);
		ft_usleep(5);
		clean(&data, philos);
		free(threads);
	}
}

