extends Control


func _on_new_game_pressed() -> void:
	get_tree().change_scene_to_file("res://Scenes/game_creation_menu.tscn")


func _on_exit_pressed() -> void:
	get_tree().quit(0)
