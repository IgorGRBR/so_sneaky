/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhrabar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:43:34 by ihhrabar          #+#    #+#             */
/*   Updated: 2023/05/04 12:43:37 by ihhrabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slgame.h"
#include "yprint.h"
#include "ydefines.h"
#include "mlx.h"
#include <stdlib.h>
#include <time.h>

#ifdef OSX

static const char	*g_cfg_path = "config.txt";
#else

static const char	*g_cfg_path = "configlx.txt";
#endif

static const char	*g_asset_path = "assets.txt";

// TODO: XMP doesn't support alpha channel. Figure out what to do with that.
// -> Done.
// TODO: Negative scaling when drawing causes crashes. -> Fixed.
// TODO: Integrate clock() from time.h -> Done.
// TODO: Viewports. Test viewport functionality. -> Done.
// TODO: Performance of scaled sprite is absolutely terrible. Figure out how to 
// speed it up. -> Done.
// TODO: Key events and asset loading not working on linux. -> Done.
// TODO: Colors might get fucked if varying endianness is enabled. Verify that
// everything is alright.
// TODO: Asset library loading. -> Done.
// TODO: Basic scene loading. -> Done.
// TODO: Scene drawing. -> Done.
// TODO: View culling.
// TODO: Sprite data structure. -> Done.
// TODO: Player actor and sprite animations. -> Done.
// TODO: Camera should follow the player smoothly. -> Done.
// TODO: Proper control handling. -> Done.
// TODO: Basic game loop. -> Done.
// TODO: Basic autotiling. -> Done.
// TODO: EXT parsing. -> Done.
// TODO: Graphical display of step count. -> Done.
// TODO: Basic area patrol (a bandit). Turn based movement.
// Turn skips. -> Done.
// TODO: Various patroling strategies. -> Done.
// TODO: Locked doors, unlockable by keycards. -> Done.
// TODO: Stealth/vision mechanics. -> Done.
// TODO: Go back to realtime gameplay. -> Done.
// TODO: Hiding in lockers and boxes.
// TODO: Levels.
// TODO: Norminette.
// TODO: Code cleanup.

// Note: the use of any function from ANYWHERE is allowed as long as the use
// of that function is justified.

// Disabling color blending significantly improves the framerate.
// Setting resolution scale to 2x instead of 3x also improved things.
// Idk what else can I improve right now, so I guess I'll go with 2x
// resolution scale. Also, decreasing window size to 854x480 (~2x perfect 
// pixel scale) granted me extra 5ms. Good stuff.

// Note: make sure to include GCC 12 as a requirement to compile this project
// (at least on linux).

// Bug: image drawing routine seems to overflow a bit when drawn content is
// near/colliding with the left side of the drawing surface.
// Its fixed now.

// Added basic opponents that walk randomly across the map. Also added fail
// condition, step count output and turn skips.

int	main(int argc, char **argv)
{
	t_game_data	*game;

	if (argc < 2)
	{
		yprintf("Error\nNo level was provided/not enough arguments.\n");
		exit(0);
	}
	srandom(time(NULL));
	game = game_new(g_cfg_path, g_asset_path, argv[1]);
	yprintf("hey there\n");
	mlx_loop(game->mlx_ctx.mlx);
	return (0);
}
