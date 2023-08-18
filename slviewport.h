/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slviewport.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:01:40 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/15 15:02:02 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLVIEWPORT_H
# define SLVIEWPORT_H
# include "ytypes.h"
# include "slassets.h"

typedef struct s_viewport {
	t_ivec2	s_pos;
	t_dvec2	s_sca;
	t_image	*surface;
	t_ivec2	t_pos;
	t_dvec2	t_sca;
}	t_viewport;

// Creates new viewport
t_viewport	*viewport_new(t_mlx_context *mlx, t_ivec2 ssize);

// Destroys viewport
void		viewport_destroy(t_viewport *vp, t_mlx_context *mlx);

// Applies worldspace translation to viewport content
void		viewport_translate(t_viewport *vp, t_ivec2 ts);

// Applies worldspace scale to viewport content
void		viewport_clear(t_viewport *vp, t_argb color);

// Applies screenspace translation to viewport
void		viewport_screen_translate(t_viewport *vp, t_ivec2 ts);

// Applies screenspace scale to viewport
void		viewport_screen_scale(t_viewport *vp, t_dvec2 sc);

// Draw image to the viewport
void		viewport_draw_image(t_viewport *vp,
				t_image *img, t_ivec2 pos, t_dvec2 sca);

#endif
