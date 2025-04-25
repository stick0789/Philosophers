/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaacosta <jaacosta@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:26:52 by jaacosta          #+#    #+#             */
/*   Updated: 2025/04/18 20:11:09 by jaacosta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	check_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->stop_mutex);
	stop = data->stop_flag;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stop);
}

void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
}

long long	get_last_meal(t_philo *philo)
{
	long long time;

	pthread_mutex_lock(&philo->meal_mutex);
	time = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (time);
}

int	check_meals(t_data *data)
{
	int	i;


	if (data->must_eat_count == -1)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if (data->philos[i].meals_eaten < data->must_eat_count)
		{
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		i++;
	}
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_data *data;
	int	i;

	data = (t_data *)arg;
	//while (!check_stop(data))
	//while (!data->stop_flag)
	while (!check_stop(data))
	{
		usleep(1500);
		i = 0;
		while(i < data->num_philos)
		{
			if ((get_time() - get_last_meal(&data->philos[i]) > data->time_to_die))
			{
				print_status(&data->philos[i], "has died");
				set_stop(data);
				return (NULL);
			}
			i++;
		}
		if (check_meals(data))
		{
			set_stop(data);
			return (NULL);
		}
		//return (NULL);
	}
	return (NULL);
}
