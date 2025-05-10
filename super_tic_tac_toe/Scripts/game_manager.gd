extends Node

signal action_choosed(ction)

@export_category("TileMaps")
@export var tiles_tile_map: TileMapLayer
@export var pawns_tile_map:  TileMapLayer

@export_category("Actions Buttons")
@export var place_btn: Button
@export var replace_btn: Button
@export var ban_btn: Button
@export var switch_btn: Button

@export_category("Actions Labels")
@export var replace_label: Label
@export var ban_label: Label
@export var switch_label: Label

@export_category("Menus")
@export var game_over_menu: Control
@export var players_infos_container: Control
@export var pause_menu: Control

@export var current_player_label: Label

var human_player_action_type: int = Action.PLACE_PAWN
var ai_player_thread: Thread = null

var game_state: GameState

func _ready() -> void:
	action_choosed.connect(_on_action_choosed)
	
	game_state = GameState.new()
	var board = Board.new()
	board.rows = 6
	board.cols = 6
	board.cell_updated.connect(_on_board_cell_updated)
	game_state.set_board(board)
	
	assert(tiles_tile_map != null, "A TileMapLayer is needed to draw the board's tiles")
	assert(pawns_tile_map != null, "A TileMapLayer is needed to draw the player's pawns")
	var tiles_size = Config.board_tiles_size
	tiles_tile_map.tile_set.tile_size = Vector2(tiles_size, tiles_size)
	pawns_tile_map.tile_set.tile_size = Vector2(tiles_size, tiles_size)
	_scale_board()
	_center_board()
	_draw_tiles()
	
	_init_players()
	
	place_btn.pressed.connect(_on_place_btn_pressed)
	replace_btn.pressed.connect(_on_replace_btn_pressed)
	ban_btn.pressed.connect(_on_ban_btn_pressed)
	switch_btn.pressed.connect(_on_switch_btn_pressed)
	
	game_over_menu.visible = false
	pause_menu.visible = false
	
	player_turn_begin()

func _input(event: InputEvent) -> void:
	if event.is_action_pressed("pause_game"):
		pause_menu.visible = not pause_menu.visible
		if not pause_menu.visible:
			# Unpause the game
			player_turn_begin()
	elif event.is_action_pressed("action") and game_state.current_player().type == Player.HUMAN_PLAYER:
		var mouse_pos = get_viewport().get_mouse_position()
		mouse_pos = get_viewport().get_camera_2d().get_canvas_transform().affine_inverse() * mouse_pos
		var coords = world_to_cell(mouse_pos)
		var action = null
		match human_player_action_type:
			Action.PLACE_PAWN:
				action = ActionsFactory.create_place_pawn_action(coords)
			Action.REPLACE_PAWN:
				action = ActionsFactory.create_replace_pawn_action(coords)
			Action.BAN_CELL:
				action = ActionsFactory.create_ban_cell_action(coords)
		action_choosed.emit(action)

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
		
		var player = Player.new()
		player.type = Config.players_types[i]
		player.set_action_uses_left(Action.PLACE_PAWN, 10000)
		player.set_action_uses_left(Action.REPLACE_PAWN, 2)
		player.set_action_uses_left(Action.BAN_CELL, 2)
		player.set_action_uses_left(Action.SWITCH_PAWNS, 1)
		
		game_state.add_player(player)

# When a player turn begins
func player_turn_begin() -> void:
	var player = game_state.current_player()
	print("Begin of " + Config.players_names[player.id - 1] + " turn")
	update_actions_ui(player)
	current_player_label.text = Config.players_names[player.id - 1] + " turn"
	if player.type == Player.HUMAN_PLAYER:
		set_human_player_action(Action.PLACE_PAWN)
	else:
		ai_player_thread = Thread.new()
		ai_player_thread.start(Callable(ai_think))

# When a player turn end
func player_turn_end() -> void:
	if game_state.is_over():
		game_over_menu.visible = true
		var winner = game_state.winner()
		if winner > 0:
			game_over_menu.show_winner(Config.players_names[winner - 1])
		else:
			game_over_menu.show_draw()
	else:
		print("End of " + Config.players_names[game_state.current_player().id - 1] + " turn")
		game_state.next_player()
		player_turn_begin()

# When the current player has choosed an action for his turn
func _on_action_choosed(action: Action) -> void:
	if pause_menu.visible:
		return
	var success = action.execute(game_state)
	if success:
		player_turn_end()

# Update the current action a player will use
func set_human_player_action(type: int) -> void:
	human_player_action_type = type
	match type:
		Action.PLACE_PAWN:
			place_btn.grab_focus()
		Action.REPLACE_PAWN:
			replace_btn.grab_focus()
		Action.BAN_CELL:
			ban_btn.grab_focus()
		Action.SWITCH_PAWNS:
			switch_btn.grab_focus()

# Update the actions buttons and labels a player
func update_actions_ui(player: Player) -> void:
	# Update the buttons state
	replace_btn.disabled = player.get_action_uses_left(Action.REPLACE_PAWN) <= 0
	ban_btn.disabled = player.get_action_uses_left(Action.BAN_CELL) <= 0
	switch_btn.disabled = player.get_action_uses_left(Action.SWITCH_PAWNS) <= 0
	# Update the labels text
	replace_label.text = str(player.get_action_uses_left(Action.REPLACE_PAWN))
	ban_label.text = str(player.get_action_uses_left(Action.BAN_CELL))
	switch_label.text = str(player.get_action_uses_left(Action.SWITCH_PAWNS))

# Listeners for the actions buttons pressed signal
func _on_place_btn_pressed() -> void:
	human_player_action_type = Action.PLACE_PAWN

func _on_replace_btn_pressed() -> void:
	human_player_action_type = Action.REPLACE_PAWN

func _on_ban_btn_pressed() -> void:
	human_player_action_type = Action.BAN_CELL

func _on_switch_btn_pressed() -> void:
	var action = ActionsFactory.create_switch_pawns_action()
	action_choosed.emit(action)

func _on_pause_menu_unpause() -> void:
	pause_menu.visible = false
	player_turn_begin()

func _on_board_cell_updated(coords: Vector2i, value: int) -> void:
	match value:
		Board.EMPTY_CELL:
			pawns_tile_map.set_cell(coords, 0)
			tiles_tile_map.set_cell(coords, 0, Vector2i(0, 0))
		Board.BANNED_CELL:
			pawns_tile_map.set_cell(coords, 0)
			tiles_tile_map.set_cell(coords, 0, Vector2i(1, 0))
		_:
			pawns_tile_map.set_cell(coords, 0, Vector2i(value - 1, 0))
			tiles_tile_map.set_cell(coords, 0, Vector2i(0, 0))

# Convert a world position into a cell position
func world_to_cell(position: Vector2) -> Vector2i:
	var coords = tiles_tile_map.to_local(position)
	coords = coords / Config.board_tiles_size
	return coords

func ai_think() -> void:
	var nb_iters = 1
	match game_state.current_player().type:
		Player.AI_DUMB:
			nb_iters = 100
		Player.AI_EASY:
			nb_iters = 500
		Player.AI_MEDIUM:
			nb_iters = 1000
		Player.AI_HARD:
			nb_iters = 2000
		Player.AI_LEGENDARY:
			nb_iters = 10000
	print("Start thinking for " + str(nb_iters) + " iterations")
	var action = MCTS.search(game_state, nb_iters)
	await get_tree().create_timer(1.0).timeout
	action_choosed.emit(action)

# Draw only the tiles of the board (not the player's pawns)
func _draw_tiles() -> void:
	for r in range(6):
		for c in range(6):
			tiles_tile_map.set_cell(Vector2i(c, r), 0, Vector2i(0, 0), 0)

# Scale the board to fit in the window
func _scale_board() -> void:
	var tiles_size = Config.board_tiles_size
	var window_size = get_viewport().size
	var min = min(window_size.x, window_size.y)
	min = min(
		min / float(tiles_size * 7), 
		min / float(tiles_size * 7)
		)
	tiles_tile_map.scale = Vector2(min, min)
	pawns_tile_map.scale = Vector2(min, min)

# Center the board in the middle of the window
func _center_board() -> void:
	var tiles_size = Config.board_tiles_size
	var scaled_tiles_size = tiles_size * tiles_tile_map.scale
	var window_center = get_viewport().get_camera_2d().get_screen_center_position()
	var position = Vector2(
		window_center.x - scaled_tiles_size.x * 3, 
		window_center.y - scaled_tiles_size.y * 3
		)
	tiles_tile_map.position = position
	pawns_tile_map.position = position
