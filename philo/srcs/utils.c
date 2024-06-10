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

//
//void	clear_data(t_data	*data)
//{
//	if (data->tid)
//		free(data->tid);
//	if (data->forks)
//		free(data->forks);
//	if (data->philos)
//		free(data->philos);
//}
//
//
//void	ft_exit(t_data *data)
//{
//	int	i;
//
//	i = -1;
//	while (++i < data->philo_num)
//	{
//		pthread_mutex_destroy(&data->forks[i]);
//		pthread_mutex_destroy(&data->philos[i].lock);
//	}
//	pthread_mutex_destroy(&data->write);
//	pthread_mutex_destroy(&data->lock);
//	clear_data(data);
//}
//
//
int	error(char *str, t_table *table)
{
	printf("%s\n", str);
	if (table)
		destroy_philo_table(table);
	return (1);
}
/*
 *
 * Pair prend fourchette droite
 * Impair prend fourchette gauche
 * */

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
		return (error("gettimeofday() FAILURE\n", NULL));
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;

	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < time)
		usleep(time / 10);
	return (0);
}
