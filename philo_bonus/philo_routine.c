/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaacosta <jaacosta@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:12:10 by jaacosta          #+#    #+#             */
/*   Updated: 2025/04/26 18:12:13 by jaacosta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void    eat(t_philo *philo)
{
    if (philo->shared_data->must_eat_count != -1 && 
        philo->meals_eaten >= philo->shared_data->must_eat_count) {
        return;
    }
    print_status(philo, "is eating");
    pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	//return ;
    return (precise_usleep(philo->shared_data->time_to_eat, philo->shared_data));
}

void    sleep_philo(t_philo *philo)
{
    print_status(philo, "is sleeping");
		return (precise_usleep(philo->shared_data->time_to_sleep, philo->shared_data));
}

void    release_forks(t_philo *philo)
{
    if (philo->id == philo->shared_data->num_philos)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}