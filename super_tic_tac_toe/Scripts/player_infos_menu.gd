extends Control

@export var name_label: Label
@export var type_label: Label
@export var pawn_texture_rect: TextureRect

func set_player_name(name: String) -> void:
	name_label.text = name

func set_player_type(type: int) -> void:
	match type:
		Player.HUMAN_PLAYER:
			type_label.text = "Human"
		Player.AI_DUMB:
			type_label.text = "AI DUMB"
		Player.AI_EASY:
			type_label.text = "AI EASY"
		Player.AI_MEDIUM:
			type_label.text = "AI MEDIUM"
		Player.AI_HARD:
			type_label.text = "AI HARD"
		Player.AI_LEGENDARY:
			type_label.text = "AI LEGENDARY"

func set_pawn_texture(texture: Texture2D) -> void:
	pawn_texture_rect.texture = texture
