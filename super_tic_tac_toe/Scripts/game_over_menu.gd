extends Control

@onready var label: Label = $VBoxContainer/Label
@onready var victory_player: AudioStreamPlayer = $Victory_Player
@onready var draw_player: AudioStreamPlayer = $Draw_Player

func show_winner(winner: String) ->  void:
	victory_player.play()
	label.text = winner + " wins!!"

func show_draw() -> void:
	draw_player.play()
	label.text = "It's a draw..."

func _on_new_game_pressed() -> void:
	get_tree().change_scene_to_file("res://Scenes/game_creation_menu.tscn")


func _on_exit_pressed() -> void:
	get_tree().change_scene_to_file("res://Scenes/main_menu.tscn")
