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

var player: HumanPlayer

func _ready() -> void:
	place_btn.pressed.connect(on_place_btn_pressed)
	remove_btn.pressed.connect(on_remove_btn_pressed)
	replace_btn.pressed.connect(on_replace_btn_pressed)
	ban_btn.pressed.connect(on_ban_btn_pressed)
	
	var get_cell_coords_callable = Callable(board_manager, "world_to_cell")
	
	player = HumanPlayer.new()
	player.get_cell_coords = get_cell_coords_callable
	set_current_player_action(Player.PLACE_PAWN)
	add_child(player)
	player.action_choosed.connect(on_action_choosed)
	update_actions_ui(player)
	player.play()

# When the current player has choosed an action for his turn
func on_action_choosed(coords: Vector2i, type: int) -> void:
	var success = false
	match type:
		Player.PLACE_PAWN:
			success = board_manager.place_pawn(coords, 1)
		Player.REMOVE_PAWN:
			success = board_manager.remove_pawn(coords)
		Player.REPLACE_PAWN:
			success = board_manager.replace_pawn(coords, 2)
		Player.BAN_CELL:
			success = board_manager.ban_cell(coords)
	if success:
		player.set_action_uses_left(type, player.get_action_uses_left(type) - 1)
		set_current_player_action(Player.PLACE_PAWN)
	player.play()
	update_actions_ui(player)

# Update the current action the current player will use
func set_current_player_action(type: int) -> void:
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
	player.action = Player.PLACE_PAWN

func on_remove_btn_pressed() -> void:
	player.action = Player.REMOVE_PAWN

func on_replace_btn_pressed() -> void:
	player.action = Player.REPLACE_PAWN

func on_ban_btn_pressed() -> void:
	player.action = Player.BAN_CELL
