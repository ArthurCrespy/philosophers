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

int	data_init(t_data **data)
{
	int	id;

	id = 1;
	while (id != (*data)->philo_nb + 1)
	{
		(*data)->philo = malloc(sizeof(t_philo *) * (*data)->philo_nb);
		if (!(*data)->philo)
			return (1);
		(*data)->philo[id].id = id;
		(*data)->philo[id].eat_count = 0;
		(*data)->philo[id].data = *data;
		pthread_create(&(*data)->philo[id].thread, NULL, &philosopher, &(*data)->philo[id]);
		id++;
	}
	return (0);
}