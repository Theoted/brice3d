/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeville <tdeville@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:45:20 by theodeville       #+#    #+#             */
/*   Updated: 2022/11/01 12:12:57 by tdeville         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/brice3d.h"

void    create_rays(t_data *data)
{
    t_vector2_d origin = {
        data->win_width / 2,
        data->win_height / 2
    };
    
    
}

t_vector2_f dda(t_data *data, t_ray *ray)
{
    t_vector2_d origin = {
        data->win_width / 2,
        data->win_height / 2};

    t_vector2_d map = {
        data->win_width / 2,
        data->win_height / 2};

    t_vector2_f dir = {ray->hit_point.x - origin.x, ray->hit_point.y - origin.y};
    t_vector2_f side_dist;  // Origin point offset to the nearest int positon
    t_vector2_f delta_dist; // Length of the hyptenuse

    delta_dist.x = (dir.x == 0) ? 1e30 : ft_abs_f(1.0f / dir.x); // 1e30 is a large value
    delta_dist.y = (dir.y == 0) ? 1e30 : ft_abs_f(1.0f / dir.y);

    t_vector2_d step;
    if (dir.x < 0)
    {
        step.x = -1;                                     // Calculating X step (depending on the direction)
        side_dist.x = (origin.x - map.x) * delta_dist.x; // Calculating X gap to the nearest integer coordinate
    }
    else
    {
        step.x = 1;
        side_dist.x = (map.x + 1.0f - origin.x) * delta_dist.x;
    }

    if (dir.y < 0)
    {
        step.y = -1;                                     // Calculating Y step (depending on the direction)
        side_dist.y = (origin.y - map.y) * delta_dist.y; // Calculating Y gap to the nearest integer coordinate
    }
    else
    {
        step.y = 1;
        side_dist.y = (map.y + 1.0f - origin.y) * delta_dist.y;
    }
    while (1)
    {
        if (side_dist.x < side_dist.y)
        {
            side_dist.x += delta_dist.x;
            map.x += step.x;
        }
        else
        {
            side_dist.y += delta_dist.y;
            map.y += step.y;
        }
        // Converting pixel coordinates to tab coordinates
        t_vector2_d cell = {
            map.x / 60,
            map.y / 60};
        if (data->tab[cell.y][cell.x] == 1) // Is a wall
        {
            _bresenham(data, origin.x, origin.y, map.x, map.y);
            mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->mlx_img, 0, 0);
            return (vector_d_to_f(map));
        }
    }
}

int ray_ro_mouse(int x, int y, t_data *data)
{
    t_ray ray;

    print_grid(data);
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    if (x > data->win_width)
        x = data->win_width;
    if (y > data->win_height)
        y = data->win_height;
    data->mouse_pos.x = x;
    data->mouse_pos.y = y;
    ray.hit_point.x = x;
    ray.hit_point.y = y;
    dda(data, &ray);
    return (0);
}

int mouse_hook(int keycode, int x, int y, t_data *data)
{
    data->mouse_pressed = 1;
    data->mouse_pos.x = x;
    data->mouse_pos.y = y;
    data->mouse_button = keycode;
    set_grid_cell(data, x, y);
    print_grid(data);
    return (0);
}

void set_grid_cell(t_data *data, int x, int y)
{
    // Converting pixel coordinates into tab coordinates
    t_vector2_d tab_pos = {
        x / data->cell_size, // x
        y / data->cell_size  // y
    };
    // Checking out of range coordinates
    if (x < 0 || tab_pos.x >= data->win_width || y < 0 || tab_pos.y >= data->win_height)
        return;

    // Changing cell value according to mouse button
    if (data->mouse_button == LMB)
    {
        data->tab[tab_pos.y][tab_pos.x] = 1;
    }
    else if (data->mouse_button == RMB)
    {
        data->tab[tab_pos.y][tab_pos.x] = 0;
    }
    print_grid(data);
}

void draw_rect_color(t_data *data, t_vector2_d top_left, t_vector2_d bottom_right, int color)
{
    for (int y = top_left.y; y < bottom_right.y; y++)
    {
        for (int x = top_left.x; x < bottom_right.x; x++)
        {
            my_mlx_pixel_put(data, x, y, color);
        }
    }
}

void print_grid(t_data *data)
{
    for (int y = 0; y < data->tab_height; y++)
    {
        for (int x = 0; x < data->tab_width; x++)
        {
            // Calculating square coordinates
            t_vector2_d top_left = {
                x * data->cell_size, // x
                y * data->cell_size  // y
            };
            t_vector2_d bottom_right = {
                top_left.x + data->cell_size,
                top_left.y + data->cell_size};

            // Drawing square
            if (data->tab[y][x] == 1) // If the cell is a wall
                draw_rect_color(data, top_left, bottom_right, 0xffc0cb);
            else
                draw_rect_color(data, top_left, bottom_right, 0x000000);
        }
    }
}

int init_tab(t_data *data)
{
    // Setting initial tab dimensions
    data->tab_height = 15;
    data->tab_width = 20;
    data->cell_size = 60;

    // Allocating tab
    data->tab = malloc(sizeof(int *) * data->tab_height);
    if (data->tab == NULL) // Checking allocation error
        return (1);

    for (int y = 0; y < data->tab_height; y++)
    {
        data->tab[y] = malloc(sizeof(int) * data->tab_width);
        if (data->tab[y] == NULL) // Checking allocation error
            return (1);

        // Putting values in tab
        for (int x = 0; x < data->tab_width; x++)
        {
            if (y == 0 || x == 0 || x == data->tab_width - 1 || y == data->tab_height - 1)
                data->tab[y][x] = 1;
            else
                data->tab[y][x] = 0;
        }
    }
    return (0);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->img_addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void init_mlx(t_data *data)
{
    data->mlx_ptr = mlx_init();
    data->mlx_win = mlx_new_window(data->mlx_ptr, 20 * 60, 15 * 60, "brice3D");
    data->mlx_img = mlx_new_image(data->mlx_ptr, 20 * 60, 15 * 60);
    data->img_addr = mlx_get_data_addr(data->mlx_img, &data->bits_per_pixel, &data->line_length, &data->endian);
    init_tab(data);
    data->win_height = data->tab_height * 60;
    data->win_width = data->tab_width * 60;
}

int main(int ac, char **av)
{
    t_data data;

    init_mlx(&data);
    print_grid(&data);
    mlx_mouse_hook(data.mlx_win, mouse_hook, &data);
    mlx_hook(data.mlx_win, 6, 1L << 6, ray_ro_mouse, &data);
    mlx_loop(data.mlx_ptr);
    return (0);
}
