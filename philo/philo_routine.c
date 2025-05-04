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

/*void    eat(t_philo *philo)
{
        //pthread_mutex_lock(&philo->shared_data->print_mutex);
        
        //if (philo->shared_data->stop_flag == 0)
        //    print_status(philo, "is eating");
        //else
        //    print_status_live(philo, "is eating");
        pthread_mutex_lock(&philo->meal_mutex);
	    philo->last_meal = get_time();
	    philo->meals_eaten++;
	    pthread_mutex_unlock(&philo->meal_mutex);
        print_status(philo, "is eating");
        //pthread_mutex_unlock(&philo->shared_data->print_mutex);
	    //return ;
        return (precise_usleep(philo->shared_data->time_to_eat, philo->shared_data));
}*/
/*
void    sleep_philo(t_philo *philo)
{
	    pthread_mutex_lock(&philo->meal_mutex);
        print_status(philo, "is sleeping");
        //pthread_mutex_lock(&philo->shared_data->print_mutex);
        //if (philo->shared_data->stop_flag == 0)
        //    print_status(philo, "is sleeping");
        //else
        //    print_status_live(philo, "is sleeping");
        //pthread_mutex_unlock(&philo->shared_data->print_mutex);
	    pthread_mutex_unlock(&philo->meal_mutex);
	    return (precise_usleep(philo->shared_data->time_to_sleep, philo->shared_data));
}

void    think_philo(t_philo *philo)
{
        pthread_mutex_lock(&philo->meal_mutex);
        print_status(philo, "is thinking");
        //pthread_mutex_lock(&philo->shared_data->print_mutex);
        //if (philo->shared_data->stop_flag == 0)
        //    print_status(philo, "is Thinking");
        //else	
        //    print_status_live(philo, "is Thinking");
        //pthread_mutex_unlock(&philo->shared_data->print_mutex);
        pthread_mutex_unlock(&philo->meal_mutex);
        long long time_since_last_meal = get_time() - philo->last_meal;
    
        if (time_since_last_meal > philo->shared_data->time_to_die * 0.7) {
            precise_usleep(philo->shared_data->time_to_eat, philo->shared_data);  // Espera larga
        } else {
            precise_usleep(philo->shared_data->time_to_eat / 3, philo->shared_data);  // Espera normal
        }
        //precise_usleep(1, philo->shared_data);
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
}*/