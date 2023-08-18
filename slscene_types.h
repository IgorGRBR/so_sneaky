/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slscene_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:08:38 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/24 12:08:39 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLSCENE_TYPES_H
# define SLSCENE_TYPES_H
# include "yvec2.h"
# include "slassets.h"
# include "ytypes.h"

# define TILE_WIDTH 32
# define TILE_HEIGHT 32

typedef enum e_item {
	NO_ITEM,
	PURPLE_KEYCARD,
	GREEN_KEYCARD,
	ORANGE_KEYCARD,
	ITEM_TYPE_COUNT,
}	t_item;

typedef enum e_direction {
	UP,
	RIGHT,
	DOWN,
	LEFT,
}	t_direction;

typedef enum e_actor_state {
	IDLE,
	WALKING,
	ACTION,
	NEUTRALIZED,
	HIDDEN,
	ACTOR_STATE_COUNT,
}	t_actor_state;

typedef enum e_actor_type {
	PLAYER,
	ENEMY,
	RAT,
	ACTOR_TYPE_COUNT,
}	t_actor_type;

typedef enum e_walk_strategy {
	RANDOM_WALK,
	HUG_WALL_WALK,
	LAZY_TURNING_WALK,
}	t_walk_strategy;

// Position of an actor is in tile units
typedef struct s_actor {
	t_direction		direction;
	t_image			*image;
	t_ivec2			draw_offset;
	double			draw_frame;
	t_actor_state	state;
	t_actor_type	type;
	double			timer;
	t_ivec2			position;
	t_walk_strategy	walk_strategy;
	t_direction		turn_preference;
}	t_actor;

typedef enum e_tile {
	EMPTY,
	FLOOR,
	TOP_WALL,
	EXIT,
	EXIT_CLOSED,
	PURPLE_DOOR_OPEN,
	PURPLE_DOOR_CLOSED,
	PURPLE_DOOR_OPEN_H1,
	PURPLE_DOOR_OPEN_H2,
	PURPLE_DOOR_CLOSED_H1,
	PURPLE_DOOR_CLOSED_H2,
	GREEN_DOOR_OPEN,
	GREEN_DOOR_CLOSED,
	GREEN_DOOR_OPEN_H1,
	GREEN_DOOR_OPEN_H2,
	GREEN_DOOR_CLOSED_H1,
	GREEN_DOOR_CLOSED_H2,
	ORANGE_DOOR_OPEN,
	ORANGE_DOOR_CLOSED,
	ORANGE_DOOR_OPEN_H1,
	ORANGE_DOOR_OPEN_H2,
	ORANGE_DOOR_CLOSED_H1,
	ORANGE_DOOR_CLOSED_H2,
	TILE_TYPE_COUNT,
}	t_tile;

typedef struct s_node {
	t_tile	tile;
	t_actor	*actor;
	t_item	item;
	t_tile	front_tile;
}	t_node;

typedef enum e_key {
	KEY_UP,
	KEY_RIGHT,
	KEY_DOWN,
	KEY_LEFT,
	KEY_ACTION,
	KEY_CANCEL,
	KEYCOUNT,
}	t_key;

typedef enum e_update_status {
	CONTINUE_STATUS,
	EXIT_STATUS,
	FAIL_STATUS,
}	t_update_status;

// Structure containing all the data of current scene and
// its state. The grid is an array of rows of nodes (meaning that
// in order to access node at (x, y) you index it like grid[y][x])
typedef struct s_scene {
	t_ivec2			size;
	t_node			**grid;
	t_string		*asset_path;
	t_image			*tileset[TILE_TYPE_COUNT];
	t_image			*item_images[ITEM_TYPE_COUNT];
	t_list			*actor_sprites[ACTOR_TYPE_COUNT][ACTOR_STATE_COUNT][4];
	t_list			*actors;
	t_list			*patrols;
	t_actor			*player;
	t_uint			required_item_count;
	t_ivec2			exit_pos;
	t_update_status	update_status;
	t_actor			*camera_focus_actor;
	struct s_scene_keystates {
		t_uint	map[KEYCOUNT];
		t_bool	down[KEYCOUNT];
	}	keys;
	struct s_scene_player_state {
		t_uint	move_count;
		t_bool	purple_keycard;
		t_bool	green_keycard;
		t_bool	orange_keycard;
	}	player_state;
}	t_scene;

#endif
