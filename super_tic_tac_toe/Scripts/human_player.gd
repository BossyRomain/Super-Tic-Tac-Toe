class_name HumanPlayer
extends Player

# The type of action the player will make
var action: int = PLACE_PAWN

# Turns world coordinnates into cells coordinnates
var get_cell_coords: Callable

func _input(event: InputEvent) -> void:
	if event.is_action_pressed("action"):
		var mouse_pos = get_viewport().get_mouse_position()
		mouse_pos = get_viewport().get_camera_2d().get_canvas_transform().affine_inverse() * mouse_pos
		set_process_input(false)
		action_choosed.emit(get_cell_coords.call(mouse_pos), action)

func play() -> void:
	set_process_input(true)
