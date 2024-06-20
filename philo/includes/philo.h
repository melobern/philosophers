/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:56:09 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/14 13:04:28 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

# ifndef WRONG_NUMBER_OF_ARGUMENTS
#  define WRONG_NUMBER_OF_ARGUMENTS \
	"\e[1;31mError: wrong number of arguments\e[0m\n\
\e[0;32mCorrect format should contains 5 or 6 arguments :\e[0m\n\
number_of_philosophers\tdie_time\teat_time\tsleep_time\t\
[number_of_times_each_philosopher_must_eat]\n"
# endif

# ifndef PHILO_200_ERROR
#  define PHILO_200_ERROR \
	"\e[1;31mError: number of philosophers should be inferior to 200\e[0m\n"
# endif

# ifndef PHILO_0_ERROR
#  define PHILO_0_ERROR \
	"\e[1;31mError: number of philosophers should be superior to 0\e[0m\n"
# endif

# ifndef TIME_TO_DIE_ERROR
#  define TIME_TO_DIE_ERROR \
	"\e[1;31mError: time to die should be superior to 59\e[0m\n"
# endif

# ifndef TIME_TO_EAT_ERROR
#  define TIME_TO_EAT_ERROR \
	"\e[1;31mError: time to eat should be superior to 59\e[0m\n"
# endif

# ifndef TIME_TO_SLEEP_ERROR
#  define TIME_TO_SLEEP_ERROR \
	"\e[1;31mError: time to sleep should be superior to 59\e[0m\n"
# endif

# ifndef NUMBER_OF_MEALS_ERROR
#  define NUMBER_OF_MEALS_ERROR \
	"\e[1;31mError: number of meals should be superior to 0\e[0m\n"
# endif

# ifndef FORK
#  define FORK "\e[0;35m has taken a fork\e[0m\n"
# endif

# ifndef EAT
#  define EAT "\e[0;32m is eating\e[0m\n"
# endif

# ifndef THINK
#  define THINK "\e[0;33m is thinking\e[0m\n"
# endif

# ifndef SLEEP
#  define SLEEP "\e[0;36m is sleeping\e[0m\n"
# endif

# ifndef DIED
#  define DIED "\e[0;31m died\e[0m\n"
# endif

typedef struct s_table	t_table;

typedef struct s_philo_thread
{
	pthread_t		thread;
	int				id;
	bool			thread_created;
	bool			mutex_created;
	int				meals_eaten;
	u_int64_t		last_meal;
	int				num_forks;
	bool			l_fork_taken;
	bool			*r_fork_taken;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*write_mutex;
	pthread_mutex_t	*meals_mutex;
	pthread_mutex_t	*errors_mutex;
	bool			*dead_detected;
	bool			*error_detected;
	bool			*dinner_started;
	bool			meals_defined;
	int				num_of_philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				meals_num;
	u_int64_t		start_time;
	t_table			*table;
}					t_philo_thread;

typedef struct s_table
{
	bool			meals_defined;
	bool			dead_detected;
	bool			dinner_started;
	bool			error_detected;
	bool			mutex_created;
	int				num_of_philos;
	int				finished_meals;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				meals_num;
	u_int64_t		start_time;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	errors_mutex;
	t_philo_thread	*philos;
}					t_table;

//////////////////////		CHECK AND ASSIGN 		////////////////////////////
bool				check_arguments_and_assign(char **av, t_table *t);
//////////////////////		UTILS						////////////////////////
void				*ft_calloc(size_t nmemb, size_t size);
int					ft_usleep(useconds_t time, t_philo_thread *p);
u_int64_t			get_time_in_ms(void);
//////////////////////		ROUTINE 				////////////////////////////
void				*routine(void *arg);
//////////////////////		MESSAGES 				////////////////////////////
void				print_msg(t_philo_thread *p, char *msg,
						bool is_dead, bool is_eat);
bool				everyone_has_eaten(t_philo_thread *p);
//////////////////////		INIT	 				////////////////////////////
bool				init_table(t_table *table);
//////////////////////		MUTEX	 				////////////////////////////
bool				no_death_detected(t_philo_thread *p);
bool				init_mutex(t_table *t);
bool				assign_bool_mutex(bool *var, pthread_mutex_t *m, bool val);

//////////////////////		DESTROY	 				////////////////////////////
void				destroy_philo_table(t_table *table);
#endif // PHILO_H
