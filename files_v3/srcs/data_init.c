/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 13:35:03 by acrespy           #+#    #+#             */
/*   Updated: 2023/03/25 13:35:06 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*philosopher(void *arg)
{
	int		id;
	t_data	*data;

	data = (t_data *)arg;
	id = data->id_tmp;
	printf("Philosopher %d is alive\n", id);
	return (NULL);
}

int	data_init(t_data **data)
{
	int	id;

	id = 1;
	(*data)->philo_alive = 0;
	while (id != (*data)->philo_nb + 1)
	{
		(*data)->philo_eat_nb = (int *)malloc(sizeof(int) * (*data)->philo_nb + 1);
		if (!(*data)->philo_eat_nb)
			return (1);
		(*data)->philo_eat_nb[id - 1] = 0;
		(*data)->id_tmp = id;
		(*data)->philo_thread = (pthread_t *)malloc(sizeof(pthread_t) * (*data)->philo_nb);
		if (!(*data)->philo_thread)
			return (1);
		pthread_create(&(*data)->philo_thread[id - 1], NULL, &philosopher, *data);
		usleep(10);
		id++;
	}
	usleep(1000);
	return (0);
}