#include "parsing.h"

//soit la case suivant == 1 || == 0 OK
//soit la case vaut x => on a deja ete sur cette case il faut pas y retourner
//soit la case n'existe pas, soit il y a un espace => dans ce cas on a une erreur
//si y == 0 || y == height - 1 (on est aux deux extrem haut bas)
//si x == 0 || x == \0 on est aux deux extrem gauche et droite
int move_up(t_map *s_map, int start_y, int start_x, int *mvt_values)
{
    char next_pos;

    if ((int)ft_strlen(s_map->map[start_y - 1]) <= start_x)
        ft_error("Unvalid Map", 0);
    next_pos = s_map->map[start_y - 1][start_x];
    if (next_pos == 'x' || next_pos == '1')
        return (0);
    if (next_pos == '0')
    {
        mvt_values[0] = -1;
        mvt_values[1] = 0;
        return (1);
    }
    else
        return(ft_error("Unvalid Map", 3));
}

int move_right(t_map *s_map, int start_y, int start_x, int *mvt_values)
{
    char next_pos;

    next_pos = s_map->map[start_y][start_x + 1];
    if (next_pos == 'x' || next_pos == '1')
        return (0);
    if (next_pos == '0')
    {
        mvt_values[0] = 0;
        mvt_values[1] = 1;
        return (1);
    }
    else
        return(ft_error("Unvalid Map", 4));
}

int move_down(t_map *s_map, int start_y, int start_x, int *mvt_values)
{
    char next_pos;

    if ((int)ft_strlen(s_map->map[start_y + 1]) <= start_x)
        ft_error("Unvalid Map", 0);
    next_pos = s_map->map[start_y + 1][start_x];
    if (next_pos == 'x' || next_pos == '1')
        return (0);
    if (next_pos == '0')
    {
        mvt_values[0] = 1; 
        mvt_values[1] = 0;
        return (1);
    }
    else
        return(ft_error("Unvalid Map", 4));
}

int move_left(t_map *s_map, int start_y, int start_x, int *mvt_values)
{
    char next_pos;

    next_pos = s_map->map[start_y][start_x - 1];
    if (next_pos == 'x' || next_pos == '1')
        return (0);
    if (next_pos == '0')
    {
        mvt_values[0] = 0; 
        mvt_values[1] = -1;
        return (1);
    }
    else
        return(ft_error("Unvalid Map", 4));
}
