/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:13:57 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/04 13:13:57 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*copy;

	if (nmemb && size && ((nmemb * size) / nmemb != size))
		return (NULL);
	copy = malloc(nmemb * size);
	if (!(copy))
		return (NULL);
	memset(copy, 0, size);
	return (copy);
}

u_int64_t	get_time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		write(2, "gettimeofday() FAILURE\n", 23);
		return (1);
	}
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(useconds_t time, t_philo_thread *p)
{
	u_int64_t	start;

	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < time)
	{
		if (p == NULL || no_death_detected(p))
			usleep(1500);
		else
			break ;
	}
	return (0);
}
