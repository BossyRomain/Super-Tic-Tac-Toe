extends Control

@onready var label: Label = $VBoxContainer/Label

func show_winner(winner: String) ->  void:
	label.text = winner + " wins!!"

func show_draw() -> void:
	label.text = "It's a draw..."
