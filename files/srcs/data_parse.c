/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:58:50 by acrespy           #+#    #+#             */
/*   Updated: 2023/03/20 11:58:50 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int data_parse(t_data *data, int argc, char **argv)
{
	int i;

	i = 1;
	if (argc < 5)
		return (1);
	data->nb_philo = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		data->nb_eat = atoi(argv[5]);
	else
		data->nb_eat = 0;
	return (0);
}