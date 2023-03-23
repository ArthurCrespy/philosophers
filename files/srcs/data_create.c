/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:01:26 by acrespy           #+#    #+#             */
/*   Updated: 2023/03/22 17:01:26 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void create_node(t_data **data, int id)
{
	t_philo *tmp;
	t_philo *new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return ;
	new->id = id;
	new->fork = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	if (!(*data)->philo)
	{
		new->next = new;
		(*data)->philo = new;
	}
	else
	{
		tmp = (*data)->philo;
		while (tmp->next != (*data)->philo)
			tmp = tmp->next;
		tmp->next = new;
		new->next = (*data)->philo;
	}
}

void create_table(t_data **data)
{
	int id;

	id = 0;
	(*data)->all_alive = 0;
	(*data)->philo = NULL;
	while (id != (*data)->nb_philo)
	{
		create_node(&(*data), id + 1);
		id++;
	}
	go_to_philo(&(*data), 0);
	id = 0;
	while (id != (*data)->nb_philo)
	{
		pthread_create(&(*data)->philo->thread, NULL, philosopher, (void*)(*data));
		(*data)->philo = (*data)->philo->next;
		usleep(10000);
		id++;
	}
	id = 0;
	(*data)->all_alive = 1;
	while (id != (*data)->nb_philo)
	{
		pthread_join((*data)->philo->thread, NULL);
		(*data)->philo = (*data)->philo->next;
		id++;
	}
}