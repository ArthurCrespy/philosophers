/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:02:37 by acrespy           #+#    #+#             */
/*   Updated: 2023/03/16 13:02:37 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	https://we.tl/t-UokNw4TMe4;

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_data		*data;

	if (args_check(argc, argv))
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data_parse(data, argc, argv);
	gettimeofday(&data->time_start, NULL);
	create_table(&data);
	table_print(data);
	gettimeofday(&data->time_stop, NULL);
	printf("%d >Machine      : Program took %d.%d seconds to run\n", ft_timecode(data), (int)(data->time_stop.tv_sec - data->time_start.tv_sec), (int)(data->time_stop.tv_usec - data->time_start.tv_usec));
	usleep(10000);
	table_free(data);
	return (0);
}
