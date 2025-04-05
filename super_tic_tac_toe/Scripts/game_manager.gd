extends Node

@export var board_manager: BoardManager

@export_category("Actions Buttons")
@export var place_btn: Button
@export var remove_btn: Button
@export var replace_btn: Button
@export var ban_btn: Button

@export_category("Actions Labels")
@export var place_label: Label
@export var remove_label: Label
@export var replace_label: Label
@export var ban_label: Label

var players: Array[Player] = []
var current_player: int = 0

func _ready() -> void:
	place_btn.pressed.connect(on_place_btn_pressed)
	remove_btn.pressed.connect(on_remove_btn_pressed)
	replace_btn.pressed.connect(on_replace_btn_pressed)
	ban_btn.pressed.connect(on_ban_btn_pressed)
	
	# Init the players
	var get_cell_coords_callable = Callable(board_manager, "world_to_cell")
	for i in range(Config.nb_players):
		var player = HumanPlayer.new()
		player.get_cell_coords = get_cell_coords_callable
		players.append(player)
		add_child(player)
	player_turn_begin()

# Returns the current player playing
func get_current_player() -> Player:
	return players[current_player]

# When a player turn begins
func player_turn_begin() -> void:
	var player = get_current_player()
	player.action_choosed.connect(on_action_choosed)
	update_actions_ui(player)
	set_player_action(player, Player.PLACE_PAWN)
	player.play()

# When a player turn end
func player_turn_end() -> void:
	var player = get_current_player()
	player.action_choosed.disconnect(on_action_choosed)
	if is_party_over():
		var winner = board_manager.board.get_winner()
		if winner > 0:
			print("The winner is " + str(winner))
		else:
			print("It's a draw")
	else:
		current_player = (current_player + 1) % Config.nb_players
		player_turn_begin()

# Returns true if the party has ended, else false
func is_party_over() -> bool:
	return board_manager.board.is_full() or board_manager.board.get_winner() > 0

# When the current player has choosed an action for his turn
func on_action_choosed(coords: Vector2i, type: int) -> void:
	var success = false
	match type:
		Player.PLACE_PAWN:
			success = board_manager.place_pawn(coords, current_player + 1)
		Player.REMOVE_PAWN:
			success = board_manager.remove_pawn(coords)
		Player.REPLACE_PAWN:
			success = board_manager.replace_pawn(coords, current_player + 1)
		Player.BAN_CELL:
			success = board_manager.ban_cell(coords)
	var player = get_current_player()
	if success:
		player.set_action_uses_left(type, player.get_action_uses_left(type) - 1)
		player_turn_end()
	else:
		player.play()

# Update the current action a player will use
func set_player_action(player: Player, type: int) -> void:
	match type:
		Player.PLACE_PAWN:
			player.action = Player.PLACE_PAWN
			place_btn.grab_focus()
		Player.REMOVE_PAWN:
			player.action = Player.REMOVE_PAWN
			remove_btn.grab_focus()
		Player.REPLACE_PAWN:
			player.action = Player.REPLACE_PAWN
			replace_btn.grab_focus()
		Player.BAN_CELL:
			player.action = Player.BAN_CELL
			ban_btn.grab_focus()

# Update the actions buttons and labels a player
func update_actions_ui(player: Player) -> void:
	# Update the buttons state
	place_btn.disabled = player.get_action_uses_left(Player.PLACE_PAWN) == 0
	remove_btn.disabled = player.get_action_uses_left(Player.REMOVE_PAWN) == 0
	replace_btn.disabled = player.get_action_uses_left(Player.REPLACE_PAWN) == 0
	ban_btn.disabled = player.get_action_uses_left(Player.BAN_CELL) == 0
	# Update the labels text
	place_label.text = str(player.get_action_uses_left(Player.PLACE_PAWN))
	remove_label.text = str(player.get_action_uses_left(Player.REMOVE_PAWN))
	replace_label.text = str(player.get_action_uses_left(Player.REPLACE_PAWN))
	ban_label.text = str(player.get_action_uses_left(Player.BAN_CELL))

# Listeners for the actions buttons pressed signal
func on_place_btn_pressed() -> void:
	get_current_player().action = Player.PLACE_PAWN

func on_remove_btn_pressed() -> void:
	get_current_player().action = Player.REMOVE_PAWN

func on_replace_btn_pressed() -> void:
	get_current_player().action = Player.REPLACE_PAWN

func on_ban_btn_pressed() -> void:
	get_current_player().action = Player.BAN_CELL
