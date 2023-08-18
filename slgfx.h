/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slgfx.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:11:04 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/09 14:11:26 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLGFX_H
# define SLGFX_H
# include "ytypes.h"
# include "slassets.h"
# include "slcolor.h"
# include "slmlx.h"
# include "slviewport.h"

// solong graphics context
typedef struct s_gfx_context {
	t_ivec2	translation;
	t_ivec2	scale;
	t_image	*display_surface;
	t_image	*drawing_surface;
	t_list	*views;
}	t_gfx_context;

// Creates new graphics context
t_gfx_context	*gfx_new_context(t_mlx_context *mlx, t_ivec2 ssize);

// Destroys graphics context
void			gfx_destroy_context(t_gfx_context *gfx, t_mlx_context *mlx);

// Draws viewport to the drawing surface
void			gfx_draw_view(t_viewport *vp, t_gfx_context *gfx);

// Applies global scale to graphics context
void			gfx_scale(t_gfx_context *gfx, t_ivec2 sc);

// Draws viewports and blits graphics to screen
void			gfx_blit_to_screen(t_gfx_context *gfx, t_mlx_context *mlx);

// Clear context surface and viewports with color
void			gfx_clear_surface(t_gfx_context *gfx, t_argb color);

// Swap active and drawn surfaces
void			gfx_swap_surface(t_gfx_context *gfx);

// Creates a new viewport
t_viewport		*gfx_new_viewport(t_gfx_context *gfx, t_mlxc *c, t_ivec2 s);

#endif
