/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaacosta <jaacosta@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:33:19 by jaacosta          #+#    #+#             */
/*   Updated: 2025/04/18 20:23:01 by jaacosta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_len_ll(long long n)
{
	int len;
       
	len = 1;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	ft_putn_save_ll(long long n, char *s, int *i)
{
	if (n > 9)
	{
		ft_putn_save_ll(n/10, s, i);
		ft_putn_save_ll(n%10, s, i);
	}
	else
		s[(*i)++] = n + '0';
}

char	*ft_lltoa(long long n)
{
	char		*s;
	int			i;
	int			len;

	len = ft_len_ll(n);
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		s[i++] = '-';
		n *= -1;
	}
	ft_putn_save_ll(n, s, &i);
	s[i] = '\0';
	return (s);
}
