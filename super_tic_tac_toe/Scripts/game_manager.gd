extends Node

@export var board_manager: BoardManager

func _ready() -> void:
	board_manager.place_pawn(Vector2i(2, 4), 1)
	board_manager.place_pawn(Vector2i(3, 5), 2)
	board_manager.place_pawn(Vector2i(1, 2), 3)
