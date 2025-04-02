class_name BoardManager
extends Node

# Tile map layer where the tiles are drawned
@export var tiles_tile_map: TileMapLayer

var board: Board

func _init() -> void:
	board = Board.new()
	board.rows = 6
	board.cols = 6

func _ready() -> void:
	assert(tiles_tile_map != null, "A TileMapLayer is needed to draw the board's tiles")
	var tiles_size = Config.board_tiles_size
	tiles_tile_map.tile_set.tile_size = Vector2(tiles_size, tiles_size)
	_scale_board()
	_center_board()
	_draw_tiles()

# Draw only the tiles of the board (not the player's pawns)
func _draw_tiles() -> void:
	for r in range(board.rows):
		for c in range(board.cols):
			tiles_tile_map.set_cell(Vector2i(c, r), 0, Vector2i(0, 1), 0)

# Scale the board to fit in the window
func _scale_board() -> void:
	var tiles_size = Config.board_tiles_size
	var window_size = get_viewport().size
	var min = min(window_size.x, window_size.y)
	min = min(
		min / float(tiles_size * (board.cols + 1)), 
		min / float(tiles_size * (board.rows + 1))
		)
	tiles_tile_map.scale = Vector2(min, min)

# Center the board in the middle of the window
func _center_board() -> void:
	var tiles_size = Config.board_tiles_size
	var scaled_tiles_size = tiles_size * tiles_tile_map.scale
	var window_center = get_viewport().get_camera_2d().get_screen_center_position()
	tiles_tile_map.position = Vector2(
		window_center.x - scaled_tiles_size.x * board.cols / 2, 
		window_center.y - scaled_tiles_size.y * board.rows / 2
		)
