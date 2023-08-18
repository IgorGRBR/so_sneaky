/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slscene.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:01:20 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/24 11:01:22 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLSCENE_H
# define SLSCENE_H
# include "ytypes.h"
# include "yvec2.h"
# include "slassets.h"
# include "slgame.h"
# include "slscene_types.h"
# include "slmlx.h"
# include "slviewport.h"

// Load a scene from the specified filepath
t_scene			*scene_new(char *path, t_game_data *game);

// Deallocate all the scene data
void			scene_delete(t_scene *scene);

// Perform a single tick of an update to the scene
t_update_status	scene_update(t_scene *scene, double dt, t_game_data *game);

// Set the tile of a scene at the specified coordinates.
void			scene_set_tile(t_scene *scene, t_uint x, t_uint y,
					t_tile tile);

// Assert the validity of a scene. A scene is valid if it is enclosed by the,
// walls, has a rectangular shape, a single player start position, a single
// exit and at least a single collectible. If a scene is not valid, the game
// will print an error message to the STDERR, followed by a crash.
void			verify_scene(t_scene *scene);

// Helper function that sets up keymap state for the scene.
void			scene_setup_keys(t_scene *scene, t_game_data *game);

// Helper function that loads scene assets.
void			setup_scene_assets(t_scene *scene, t_asset_col *assets,
					t_mlxc *mlxc);

// (internal function) Helper function that loads scene tileset
void			_setup_scene_tileset(t_scene *scene, t_asset_col *assets);

void			_scene_setup_door(t_scene *scene, t_ivec2 pos, t_uint tag);

// Helper function that sets up the player state
void			scene_setup_player_state(t_scene *scene);

// Helper function to automatically setup basic tlemap
void			scene_setup_tiles_auto(t_scene *scene);

// Helper data structure for ber.ext parsing
typedef struct s_ext_tag {
	char	type;
	t_uint	data;
}	t_ext_tag;

// Helper function to parse ber.ext file
void			scene_parse_ext(t_scene *scene, t_list *ext_lines);

// Draws the scene to the viewport
void			scene_draw(t_scene *scene, t_viewport *vp);

// Key pressed event
void			scene_key_pressed(t_scene *scene, t_game_data *game, int key);

// Key released event
void			scene_key_released(t_scene *scene, t_game_data *game, int key);

// Item pickup event
void			scene_on_item_pickup(t_scene *scene, t_item item);

// A helper utility that queries if the item is able to be picked up by
// the player
t_bool			is_pickup_item(t_item item);

// Helper utility that determines if the tile is solid
t_bool			is_tile_solid(t_tile tile);

void			scene_query_nearby(t_scene *scene, t_ivec2 pos,
					t_node *node[4]);

#endif
