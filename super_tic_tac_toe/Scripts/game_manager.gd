extends Node

@export_category("Tile Maps")
@export var tiles_tile_map: TileMapLayer
@export var pawns_tile_map:  TileMapLayer

@export_category("Actions Buttons")
@export var place_btn: Button
@export var remove_btn: Button
@export var replace_btn: Button
@export var ban_btn: Button

@export_category("Actions Labels")
@export var remove_label: Label
@export var replace_label: Label
@export var ban_label: Label

@export_category("Menus")
@export var game_over_menu: Control
@export var players_infos_container: Control
@export var pause_menu: Control

@export var current_player_label: Label

var board: Board = Board.new()
var players: Array[Player] = []
var current_player: int = 0

func _ready() -> void:
	_init_board()
	
	game_over_menu.visible = false
	pause_menu.visible = false
	
	_init_players()
	
	player_turn_begin()

func _input(event: InputEvent) -> void:
	if event.is_action_pressed("pause_game"):
		pause_menu.visible = not pause_menu.visible
		if not pause_menu.visible:
			# Unpause the game
			player_turn_begin()

#############################
###  Game Initialization  ###
#############################

# Init the board at the start of a game
func _init_board() -> void:
	board.rows = 6
	board.cols = 6
	
	assert(tiles_tile_map != null, "A TileMapLayer is needed to draw the board's tiles")
	assert(pawns_tile_map != null, "A TileMapLayer is needed to draw the player's pawns")
	var tiles_size = Config.board_tiles_size
	tiles_tile_map.tile_set.tile_size = Vector2(tiles_size, tiles_size)
	pawns_tile_map.tile_set.tile_size = Vector2(tiles_size, tiles_size)
	_scale_board()
	_center_board()
	_draw_tiles()
	
	board.cell_updated.connect(_on_cell_updated)

# Init the players at the start of a game
func _init_players() -> void:
	var player_infos_scene = load("res://Scenes/player_infos_menu.tscn")
	var pawns_texture = null
	
	for i in range(Config.nb_players):
		var texture = AtlasTexture.new()
		texture.atlas = load("res://Assets/pawns.png")
		texture.region = Rect2(300 * i, 0, 300, 300)
		var player_infos = player_infos_scene.instantiate()
		player_infos.set_player_name(Config.players_names[i])
		player_infos.set_player_type(Config.players_types[i])
		player_infos.set_pawn_texture(texture)
		players_infos_container.add_child(player_infos)
		
		var player: Player = null
		match Config.players_types[i]:
			-1:
				player = create_human_player()
			0:
				player = create_dumb_player()
			1:
				player = create_easy_player()
			2:
				player = create_medium_player()
			3:
				player = create_hard_player()
			4:
				player = create_legendary_player()
		
		player.id = i + 1
		players.append(player)
		add_child(player)

# Draw only the tiles of the board (not the player's pawns)
func _draw_tiles() -> void:
	for r in range(board.rows):
		for c in range(board.cols):
			tiles_tile_map.set_cell(Vector2i(c, r), 0, Vector2i(0, 0), 0)

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

# Creates a human player
func create_human_player() -> HumanPlayer:
	var player = HumanPlayer.new()
	#player.action = Player.PLACE_PAWN
	player.get_cell_coords = Callable(self, "world_to_cell")
	# Connecting the actions buttons to the player
	place_btn.pressed.connect(func(): if current_player + 1 == player.id: player.action_type = Action.PLACE_PAWN)
	remove_btn.pressed.connect(func(): if current_player + 1 == player.id: player.action_type = Action.REMOVE_PAWN)
	replace_btn.pressed.connect(func(): if current_player + 1 == player.id: player.action_type = Action.REPLACE_PAWN)
	ban_btn.pressed.connect(func(): if current_player + 1 == player.id: player.action_type = Action.BAN_CELL)
	return player

func create_dumb_player() -> AIPlayer:
	var player = AIPlayer.new()
	var heuristic = RandomHeuristic.new()
	player.add_child(heuristic)
	return player

func create_easy_player() -> AIPlayer:
	var player = AIPlayer.new()
	var heuristic = RandomHeuristic.new()
	heuristic.weight = 0.1
	player.add_child(heuristic)
	heuristic = MaxPawnsHeuristic.new()
	player.add_child(heuristic)
	return player

func create_medium_player() -> AIPlayer:
	var player = AIPlayer.new()
	var heuristic = RandomHeuristic.new()
	heuristic.weight = 0.05
	player.add_child(heuristic)
	heuristic = MaxPawnsHeuristic.new()
	heuristic.weight = 0.75
	player.add_child(heuristic)
	heuristic = NoSpecialsEarlyHeuristic.new()
	heuristic.weight = 2.0
	player.add_child(heuristic)
	heuristic = BlockPawnsHeuristic.new()
	player.add_child(heuristic)
	heuristic = WinHeuristic.new()
	heuristic.weight = 10.0
	player.add_child(heuristic)
	return player

func create_hard_player() -> AIPlayer:
	var player = AIPlayer.new()
	var heuristic = RandomHeuristic.new()
	heuristic.weight = 0.01
	player.add_child(heuristic)
	heuristic = ControlCenterHeuristic.new()
	heuristic.weight = 1.2
	player.add_child(heuristic)
	heuristic = NoSpecialsEarlyHeuristic.new()
	heuristic.weight = 2.0
	player.add_child(heuristic)
	heuristic = BlockPawnsHeuristic.new()
	player.add_child(heuristic)
	heuristic = WinHeuristic.new()
	heuristic.weight = 10.0
	player.add_child(heuristic)
	return player

func create_legendary_player() -> AIPlayer:
	var player = AIPlayer.new()
	var heuristic = RandomHeuristic.new()
	heuristic.weight = 0.001
	player.add_child(heuristic)
	heuristic = ControlCenterHeuristic.new()
	heuristic.weight = 1.2
	player.add_child(heuristic)
	heuristic = NoSpecialsEarlyHeuristic.new()
	heuristic.weight = 2.0
	player.add_child(heuristic)
	heuristic = BlockLinesHeuristic.new()
	heuristic.weight = 1.1
	player.add_child(heuristic)
	heuristic = MaxLinesHeuristic.new()
	player.add_child(heuristic)
	heuristic = WinHeuristic.new()
	heuristic.weight = 10.0
	player.add_child(heuristic)
	return player

#############################
###       Game Loop       ###
#############################

# Returns the current player playing
func get_current_player() -> Player:
	return players[current_player]

# When a player turn begins
func player_turn_begin() -> void:
	var player = get_current_player()
	update_actions_ui(player)
	place_btn.grab_focus()
	current_player_label.text = Config.players_names[current_player] + " turn"
	player.action_choosed.connect(_on_action_choosed)
	player.choose_action(board)

# When a player turn end
func player_turn_end() -> void:
	var player = get_current_player()
	player.action_choosed.disconnect(_on_action_choosed)
	if is_party_over():
		game_over_menu.visible = true
		var winner = board.get_winner()
		if winner > 0:
			game_over_menu.show_winner(Config.players_names[winner - 1])
		else:
			game_over_menu.show_draw()
	else:
		await get_tree().create_timer(0.5).timeout
		current_player = (current_player + 1) % Config.nb_players
		player_turn_begin()

# Returns true if the party has ended, else false
func is_party_over() -> bool:
	return board.is_full() or board.get_winner() > 0

# When the current player has choosed an action for his turn
func _on_action_choosed(action: Action) -> void:
	if pause_menu.visible:
		return
	var success = action.execute(board)
	var player = get_current_player()
	if success:
		player_turn_end()
	else:
		player.choose_action(board)

# Convert a world position into a cell position
func world_to_cell(position: Vector2) -> Vector2i:
	var coords = tiles_tile_map.to_local(position)
	coords = coords / Config.board_tiles_size
	return coords

# When a cell on the board has been updated
func _on_cell_updated(coords: Vector2i, value: int) -> void:
	if value == Board.EMPTY_CELL:
		pawns_tile_map.set_cell(coords, 0)
	elif value == Board.BANNED_CELL:
		tiles_tile_map.set_cell(coords, 0, Vector2i(1, 0))
	else:
		pawns_tile_map.set_cell(coords, 0, Vector2i(value - 1, 0))

# Update the actions buttons and labels a player
func update_actions_ui(player: Player) -> void:
	# Update the buttons state
	remove_btn.disabled = not player.can_use_action(Action.REMOVE_PAWN)
	replace_btn.disabled = not player.can_use_action(Action.REPLACE_PAWN)
	ban_btn.disabled = not player.can_use_action(Action.REPLACE_PAWN)
	# Update the labels text
	remove_label.text = str(player.get_action_uses_left(Action.REMOVE_PAWN))
	replace_label.text = str(player.get_action_uses_left(Action.REPLACE_PAWN))
	ban_label.text = str(player.get_action_uses_left(Action.BAN_CELL))

#############################
###     Other methods     ###
#############################

func _on_pause_menu_unpause() -> void:
	pause_menu.visible = false
	player_turn_begin()
