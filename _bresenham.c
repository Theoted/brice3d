/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bresenham.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theodeville <theodeville@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:17:55 by theodeville       #+#    #+#             */
/*   Updated: 2022/10/25 13:07:27 by theodeville      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/brice3d.h"

int _bresenham(t_data *data, int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        my_mlx_pixel_put(data, x0, y0, 0xFF0000);
        if ((x0 == x1) && (y0 == y1))
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
    return (0);
}