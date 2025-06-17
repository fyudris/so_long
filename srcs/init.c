/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:09:10 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/17 02:53:35 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * @brief Initializes the entire data struct to zeros (0, NULL, false).
 * 
 */
void	init_game_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
}
