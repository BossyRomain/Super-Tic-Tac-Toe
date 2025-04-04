class_name BoardManager
extends Node

# Tile map layer where the tiles are drawned
@export var tiles_tile_map: TileMapLayer
@export var pawns_tile_map:  TileMapLayer

var board: Board

func _init() -> void:
	board = Board.new()
	board.rows = 6
	board.cols = 6

func _ready() -> void:
	assert(tiles_tile_map != null, "A TileMapLayer is needed to draw the board's tiles")
	assert(pawns_tile_map != null, "A TileMapLayer is needed to draw the player's pawns")
	var tiles_size = Config.board_tiles_size
	tiles_tile_map.tile_set.tile_size = Vector2(tiles_size, tiles_size)
	pawns_tile_map.tile_set.tile_size = Vector2(tiles_size, tiles_size)
	_scale_board()
	_center_board()
	_draw_tiles()

# Convert a world position into a cell position
func world_to_cell(position: Vector2) -> Vector2i:
	var coords = tiles_tile_map.to_local(position)
	coords = coords / Config.board_tiles_size
	return coords

# Places a player's pawn on an empty cell if possible
# Returns if the pawn was placed, else false
func place_pawn(coords: Vector2i, player_id: int) -> bool:
	var placed = false
	if board.get_cell_at(coords) == 0:
		placed = board.set_cell_at(coords, player_id)
		pawns_tile_map.set_cell(coords, 0, Vector2i(player_id - 1, 0))
	return placed

# Removes a player's pawn from a cell
# Returns true if a pawn was removed, else false
func remove_pawn(coords: Vector2i) -> bool:
	var removed = false
	if board.get_cell_at(coords) > 0:
		removed = board.set_cell_at(coords, 0)
		pawns_tile_map.set_cell(coords, 0)
	return removed

# Replace a player's pawn by another player's pawn
# Returns true in success, else false
func replace_pawn(coords: Vector2i, player_id: int) -> bool:
	var replaced = false
	if board.get_cell_at(coords) != player_id and board.get_cell_at(coords) > 0:
		replaced = board.set_cell_at(coords, player_id)
		if replaced:
			pawns_tile_map.set_cell(coords, 0, Vector2i(player_id - 1, 0))
	return replaced

# Ban a cell from be able to have pawns on it
# Returns true if the cell was banished, else false
func ban_cell(coords: Vector2i) -> bool:
	var banned = false
	if board.get_cell_at(coords) == 0:
		banned = board.set_cell_at(coords, -1)
		if banned:
			tiles_tile_map.set_cell(coords, 0, Vector2i(1, 1))
	return banned

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
	pawns_tile_map.scale = Vector2(min, min)

# Center the board in the middle of the window
func _center_board() -> void:
	var tiles_size = Config.board_tiles_size
	var scaled_tiles_size = tiles_size * tiles_tile_map.scale
	var window_center = get_viewport().get_camera_2d().get_screen_center_position()
	var position = Vector2(
		window_center.x - scaled_tiles_size.x * board.cols / 2, 
		window_center.y - scaled_tiles_size.y * board.rows / 2
		)
	tiles_tile_map.position = position
	pawns_tile_map.position = position
