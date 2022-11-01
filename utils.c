/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theodeville <theodeville@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:44:47 by theodeville       #+#    #+#             */
/*   Updated: 2022/10/27 12:00:11 by theodeville      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/brice3d.h"

t_vector2_f	vector_d_to_f(t_vector2_d vector_d)
{
	t_vector2_f	vector_f;

	vector_f.x = vector_d.x;
	vector_f.y = vector_d.y;
	return (vector_f);
}

t_vector2_d	vector_f_to_d(t_vector2_f vector_f)
{
	t_vector2_d	vector_d;

	vector_d.x = vector_f.x;
	vector_d.y = vector_f.y;
	return (vector_d);
}

int	ft_abs_d(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	else
		return (nbr);
}

float	ft_abs_f(float nbr)
{
	if (nbr < 0.0f)
		return (-nbr);
	else
		return (nbr);
}

double	get_angle(t_vector2_d start, t_vector2_d end)
{
	double	dx;
	double	dy;

	dx = (double)(end.x - start.x);
	dy = (double)(end.y - start.y);
	if (dx >= 0 && dy < 0)
		return (atan(-dy / dx));
	else if (dx < 0 && dy < 0)
		return (atan(dx / dy) + 3.14f / 2.0f);
	else if (dx < 0 && dy > 0)
		return (atan(-dy / dx) + 3.14f);
	else
		return (atan(dx / dy) + 3.14 + 1.57f);
}

double	get_angle_f(t_vector2_f start, t_vector2_f end)
{
	double	dx;
	double	dy;

	dx = (double)(end.x - start.x);
	dy = (double)(end.y - start.y);
	if (dx >= 0 && dy < 0)
		return (atan(-dy / dx));
	else if (dx < 0 && dy < 0)
		return (atan(dx / dy) + 3.14f / 2.0f);
	else if (dx < 0 && dy > 0)
		return (atan(-dy / dx) + 3.14f);
	else
		return (atan(dx / dy) + 3.14 + 1.57f);
}


