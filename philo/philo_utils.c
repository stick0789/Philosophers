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

long	ft_atoi(const char *nptr)
{
	long	y;
	long	z;

	y = 1;
	z = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == 45)
		y *= -1;
	if (*nptr == 43 || *nptr == 45)
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		z = (*nptr - '0') + (z * 10);
		nptr++;
	}
	return (z * y);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ((void) NULL);
	while (*s)
		write(fd, s++, 1);
}

void	clean(t_data *data, t_philo *philos)
{
	int	i;

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

void	precise_usleep(long long miliseconds)
{
	long long start;

	start = get_time();
	while (get_time() - start < miliseconds)
		usleep(miliseconds/10);
}
