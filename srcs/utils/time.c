/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:21:13 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/25 19:28:05 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS_PART
# include "../../include/so_long_bonus.h"
#else
# include "../../include/so_long.h"
#endif

/**
 * @brief Gets the current time as a single value in microseconds.
 * @details This function uses gettimeofday to get the current time in seconds
 * and microseconds, then combines them into a single long integer
 * representing the total number of microseconds. This is useful for
 * calculating elapsed time with high precision.
 *
 * @return The current time in microseconds as a long.
 */
long	get_time_in_usec(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000000) + tv.tv_usec);
}
