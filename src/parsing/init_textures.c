#include "map.h"
#include "libft.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

t_texture	*get_image(char *path, mlx_context *mlx)
{
	t_texture	*new_texture;
	
	new_texture = malloc(sizeof(t_texture));
	if (new_texture == NULL)
	{
		perror("cub3D");
		return (NULL);
	}
	new_texture->texture = mlx_new_image_from_file(*mlx, path, &new_texture->width, &new_texture->height);
	return (new_texture);
}

int	init_textures(int fd)
{
	t_textures	*textures;
	char		*line;
	int			nb_texture_loaded;

	textures = ft_calloc(1, sizeof(t_textures));
	if (textures == NULL)
	{
		perror("cub3D");
		return (1);
	}
	nb_texture_loaded = 0;
	while (nb_texture_loaded < 6)
	{
		nb_texture_loaded++;
	}
	return (0);
}
