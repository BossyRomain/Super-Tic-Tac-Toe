extends Control

@export var name_label: Label
@export var type_label: Label
@export var pawn_texture_rect: TextureRect

func set_player_name(name: String) -> void:
	name_label.text = name

func set_player_type(type: int) -> void:
	if type < 0:
		type_label.text = "Human"
	else:
		match type:
			AIPlayer.DUMB:
				type_label.text = "AI DUMB"
			AIPlayer.EASY:
				type_label.text = "AI EASY"
			AIPlayer.MEDIUM:
				type_label.text = "AI MEDIUM"
			AIPlayer.HARD:
				type_label.text = "AI HARD"
			AIPlayer.LEGENDARY:
				type_label.text = "AI LEGENDARY"

func set_pawn_texture(texture: Texture2D) -> void:
	pawn_texture_rect.texture = texture
