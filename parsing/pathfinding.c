#include"parsing.h"
#include<stdio.h>

int *move_up(t_map *s_map, int start_y, int start_x, int *mvt_values);
int *move_right(t_map *s_map, int start_y, int start_x, int *mvt_values);
int *move_down(t_map *s_map, int start_y, int start_x, int *mvt_values);
int *move_left(t_map *s_map, int start_y, int start_x, int *mvt_values);
int valid_position(t_map *s_map, int start_y, int start_x);

//une fois se trouve sur une case on doit la remplacer par un 'x' pour signifier
//qu'on peut pas retourner sur cette case;
int pathfinding(t_map *s_map, int start_y, int start_x)
{
    int i;
    int *(*move[4])(t_map *s_map, int start_y, int start_x, int *mvt_values);
    int mvt_values[2];

    valid_position(s_map, start_y, start_x);
	move[0] = &move_up;
	move[1] = &move_right;
	move[2] = &move_down;
	move[3] = &move_left;
    i = 0;
    while (i < 4)
    {
        if (move[i](s_map, start_y, start_x, mvt_values))
        {
            printf("mvt_values[0]= %d, mvt_values[1] = %d\n", mvt_values[0], mvt_values[1]);
            s_map->map[start_y][start_x] = 'x';
            pathfinding(s_map, start_y + mvt_values[0] , start_x + mvt_values[1]);
        }
        i++;
    }
    return (0);    
}

int valid_position(t_map *s_map, int start_y, int start_x)
{
    if (start_y == 0 || start_y == s_map->height - 1)
        return(ft_error("Unvalid Map", 1));
    else if (start_x == 0 || s_map->map[start_y][start_x + 1] == '\0')
        return(ft_error("Unvalid Map", 2));
    return (1);
}
