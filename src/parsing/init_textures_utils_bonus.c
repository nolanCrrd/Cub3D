#include "map.h"
#include "parsing.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Return the texture in the struct based based on the given filepath
 *
 * @param path 
 * @param mlx 
 * @return texture with mlx_image / null if not found
 */
t_texture	*get_texture(char *path, mlx_context mlx)
{
	t_texture	*new_texture;

	new_texture = malloc(sizeof(t_texture));
	if (new_texture == NULL)
	{
		perror("cub3D");
		return (NULL);
	}
	new_texture->texture = mlx_new_image_from_file(mlx,
			path, &new_texture->width, &new_texture->height);
	return (new_texture);
}
