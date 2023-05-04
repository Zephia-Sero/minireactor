#include "common.h"
#include <rayex/spritesheet.h>
#include <rayex/texmode.h>
#include <rayex/tilemap.h>
#include <raylib.h>
#include <rayex/rayex.h>
#include <stdbool.h>

#define TITLE "MiniReactor"
#define VERSION "v0.1.0"
#define FULLTITLE TITLE " " VERSION

#define TILESIZE 8

#define CAMERA_SCALE 2
#define CAMERA_WIDTH (CAMERA_SCALE * 16 * TILESIZE)
#define CAMERA_HEIGHT (CAMERA_SCALE * 9 * TILESIZE)

// how big each pixel in sprites should be scaled up
#define WIN_SCALE 4
#define WIN_WIDTH (WIN_SCALE * CAMERA_WIDTH)
#define WIN_HEIGHT (WIN_SCALE * CAMERA_HEIGHT)

int main(int const argc, char const *const *const argv)
{
	InitWindow(WIN_WIDTH, WIN_HEIGHT, FULLTITLE);
	Spritesheet floorSheet = LoadSpritesheet("assets/img/floor.png", 8, 8);
	Tilemap floor = LoadTilemap(floorSheet, 3, 3, 8, 8, 0);
	for (u32 x = 0; x < 3; ++x) {
		for (u32 y = 0; y < 3; ++y) {
			TilemapSet(&floor, x, y, (x + y) % 2, WHITE);
		}
	}

	Texture2D floorTex = LoadTexture("assets/img/floor.png");
	RenderTexture2D toScale = LoadRenderTexture(CAMERA_WIDTH, CAMERA_HEIGHT);
	while (!IsRenderTextureReady(toScale));

	while (!WindowShouldClose()) {
		PushTextureMode(toScale);
		ClearBackground(BLACK);
		DrawTilemap(&floor, 0, 0, WHITE);
		PopTextureMode();

		BeginDrawing();
		DrawTexturePro(toScale.texture,
			       (Rectangle) {
				.x = 0,
				.y = 0,
				.width = CAMERA_WIDTH,
				.height = -CAMERA_HEIGHT
			       },
			       (Rectangle) {
				.x = (float)WIN_WIDTH / 2 - 3. * TILESIZE * WIN_SCALE / 2,
				.y = (float)WIN_HEIGHT / 2 - 3. * TILESIZE * WIN_SCALE / 2,
				.width = WIN_WIDTH,
				.height = WIN_HEIGHT
			       },
			       (Vector2) { .x = 0, .y = 0 },
			       0,
			       WHITE);
		EndDrawing();
	}

	UnloadRenderTexture(toScale);
	UnloadTilemap(floor, true, true);
	CloseWindow();
	return 0;
}
