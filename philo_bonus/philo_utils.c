/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaacosta <jaacosta@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:33:19 by jaacosta          #+#    #+#             */
/*   Updated: 2025/04/18 20:28:07 by jaacosta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	print_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->shared_data->print_mutex);
	if (!check_stop(philo->shared_data))
	{
		printf("%lld %d %s\n", get_time() - philo->shared_data->start_time,
			philo->id, str);
	}
	pthread_mutex_unlock(&philo->shared_data->print_mutex);
}

void	clean(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while(i < data->num_philos)
	{
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		i++;
	}
	i = 0;
	while(i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	free(data->forks);
	free(philos);
}

long long	get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_usleep(long long miliseconds, t_data *data)
{
	long long start;

	start = get_time();
	while (get_time() - start < miliseconds)
	{
		if (check_stop(data))
			break ;
		usleep(1000);
	}
}
