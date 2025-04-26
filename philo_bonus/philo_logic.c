/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaacosta <jaacosta@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:33:17 by jaacosta          #+#    #+#             */
/*   Updated: 2025/04/18 20:19:24 by jaacosta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->shared_data->must_eat_count != -1) {
        pthread_mutex_lock(&philo->meal_mutex);
        if (philo->meals_eaten >= philo->shared_data->must_eat_count) {
            pthread_mutex_unlock(&philo->meal_mutex);
            return; // No toma tenedores si ya comió suficiente
        }
        pthread_mutex_unlock(&philo->meal_mutex);
    }
	if (philo->id == philo->shared_data->num_philos)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken: right fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken left fork");
	}
	else
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->right_fork);
			print_status(philo, "has taken: right fork");
			pthread_mutex_lock(philo->left_fork);
			print_status(philo, "has taken: left fork");
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			print_status(philo, "has taken left fork");
			pthread_mutex_lock(philo->right_fork);
			print_status(philo, "has taken: right fork");
		}
	}
}

void	*philosopher(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1500);
	while (!check_stop(philo->shared_data))
	{
		if (philo->shared_data->must_eat_count != -1 && philo->meals_eaten >= philo->shared_data->must_eat_count)
			break ;
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		sleep_philo(philo);
		print_status(philo, "is Thinking");		
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_data *data;
	int	i;

	data = (t_data *)arg;
	while (!check_stop(data))
	{
		usleep(1500);
		i = 0;
		while(i < data->num_philos)
		{
			//if ((get_time() - get_last_meal(&data->philos[i]) > data->time_to_die))
			//if (((get_time() - data->philos[i].last_meal) > data->time_to_die))
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
	}
	return (NULL);
}