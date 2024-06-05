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
//int	error(char *str, t_data *data)
//{
//	printf("%s\n", str);
//	if (data)
//		ft_exit(data);
//	return (1);
//}
//
//u_int64_t	get_time(void)
//{
//	struct timeval	tv;
//
//	if (gettimeofday(&tv, NULL))
//		return (error("gettimeofday() FAILURE\n", NULL));
//	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
//}
//
//
//int	ft_usleep(useconds_t time)
//{
//	u_int64_t	start;
//
//	start = get_time();
//	while ((get_time() - start) < time)
//		usleep(time / 10);
//	return(0);
//}
