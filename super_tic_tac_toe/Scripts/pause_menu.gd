extends Control

signal pause
signal resume

func _ready() -> void:
	visible = false

func _input(event: InputEvent) -> void:
	if event.is_action_pressed("pause_game"):
		get_tree().paused = true
		visible = true
		pause.emit()

func _on_resume_pressed() -> void:
	get_tree().paused = false
	visible = false
	resume.emit()

func _on_quit_pressed() -> void:
	get_tree().change_scene_to_file("res://Scenes/main_menu.tscn")
