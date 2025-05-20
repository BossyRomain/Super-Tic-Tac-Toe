class_name PlayerCreationMenu
extends Control

signal name_changed(id, name)
signal type_changed(id, type)

@export var optional: bool = false

@onready var label: Label = $VBoxContainer/Label
@onready var remove: Button = $VBoxContainer/Remove
@onready var texture_rect: TextureRect = $VBoxContainer/TextureRect

var pawn_texture: AtlasTexture

var id: int = 0:
	set(value):
		id = value
		_on_line_edit_text_changed("")
		pawn_texture.region = Rect2i((id - 1) * 300, 0, 300, 300)

func _ready() -> void:
	if not optional:
		remove.visibility_layer = 0
		remove.disabled = true
	else:
		visible = false
	
	pawn_texture = AtlasTexture.new()
	pawn_texture.atlas = load("res://Assets/Textures/pawns.png")
	texture_rect.texture = pawn_texture

func _on_line_edit_text_changed(new_text: String) -> void:
	if new_text.is_empty():
		label.text = "Player " + str(id)
	else:
		label.text = new_text
	
	name_changed.emit(id, new_text)


func _on_option_button_item_selected(index: int) -> void:
	type_changed.emit(id, index)


func _on_remove_pressed() -> void:
	if optional:
		visible = false
