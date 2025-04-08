extends Control

@export var start_game_btn: Button

@export var players_creation_menus: Array[PlayerCreationMenu]

var nb_players: int = 2
var players_types: Array[int] = []
var players_names: Array[String] = []

func _ready() ->  void:
	for i in range(players_creation_menus.size()):
		players_creation_menus[i].id = i + 1
		players_creation_menus[i].name_changed.connect(_on_name_changed)
		players_creation_menus[i].type_changed.connect(_on_type_changed)
		
		players_names.append("Player " + str(i + 1))
		players_types.append(-1)

func _on_add_player_pressed() -> void:
	players_creation_menus[2].visible = true
	nb_players = 3

func _on_name_changed(id: int, new_name: String) -> void:
	if new_name.is_empty():
		players_names[id - 1] = "Player " + str(id)
	else:
		players_names[id - 1] = new_name

func _on_type_changed(id: int, type: int) -> void:
	players_types[id - 1] = type - 1

func _on_player_creation_menu_3_hidden() -> void:
	nb_players = 2


func _on_start_game_pressed() -> void:
	print("Nb players : " + str(nb_players))
	print("Players names : " + str(players_names))
	print("Players types : " + str(players_types))
	
	Config.nb_players = nb_players
	Config.players_names.clear()
	Config.players_types.clear()
	for i in range(nb_players):
		Config.players_types.append(players_types[i])
	get_tree().change_scene_to_file("res://Scenes/game.tscn")
