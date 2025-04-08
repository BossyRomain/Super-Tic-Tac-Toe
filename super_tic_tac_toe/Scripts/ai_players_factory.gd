class_name AIPlayersFactory
extends Node

static func create_ai_player(level: int) -> AIPlayer:
	var player: AIPlayer = null
	match level:
		AIPlayer.DUMB:
			player = create_dumb_player()
		AIPlayer.EASY:
			player = create_easy_player()
		AIPlayer.MEDIUM:
			player = create_medium_player()
		AIPlayer.HARD:
			player = create_hard_player()
		AIPlayer.LEGENDARY:
			player = create_legendary_player()
	return player

static func create_dumb_player() -> AIPlayer:
	var player = AIPlayer.new()
	var heuristic = RandomHeuristic.new()
	player.add_child(heuristic)
	return player

static func create_easy_player() -> AIPlayer:
	var player = AIPlayer.new()
	var heuristic = RandomHeuristic.new()
	heuristic.weight = 0.1
	player.add_child(heuristic)
	heuristic = MaxPawnsHeuristic.new()
	player.add_child(heuristic)
	return player

static func create_medium_player() -> AIPlayer:
	var player = AIPlayer.new()
	var heuristic = RandomHeuristic.new()
	heuristic.weight = 0.05
	player.add_child(heuristic)
	heuristic = MaxPawnsHeuristic.new()
	heuristic.weight = 0.75
	player.add_child(heuristic)
	heuristic = NoSpecialsEarlyHeuristic.new()
	heuristic.weight = 2.0
	player.add_child(heuristic)
	heuristic = BlockPawnsHeuristic.new()
	player.add_child(heuristic)
	heuristic = WinHeuristic.new()
	heuristic.weight = 10.0
	player.add_child(heuristic)
	return player

static func create_hard_player() -> AIPlayer:
	var player = AIPlayer.new()
	var heuristic = RandomHeuristic.new()
	heuristic.weight = 0.01
	player.add_child(heuristic)
	heuristic = ControlCenterHeuristic.new()
	heuristic.weight = 1.2
	player.add_child(heuristic)
	heuristic = NoSpecialsEarlyHeuristic.new()
	heuristic.weight = 2.0
	player.add_child(heuristic)
	heuristic = BlockPawnsHeuristic.new()
	player.add_child(heuristic)
	heuristic = WinHeuristic.new()
	heuristic.weight = 10.0
	player.add_child(heuristic)
	return player

static func create_legendary_player() -> AIPlayer:
	var player = AIPlayer.new()
	var heuristic = RandomHeuristic.new()
	heuristic.weight = 0.001
	player.add_child(heuristic)
	heuristic = ControlCenterHeuristic.new()
	heuristic.weight = 1.2
	player.add_child(heuristic)
	heuristic = NoSpecialsEarlyHeuristic.new()
	heuristic.weight = 2.0
	player.add_child(heuristic)
	heuristic = BlockLinesHeuristic.new()
	heuristic.weight = 1.1
	player.add_child(heuristic)
	heuristic = MaxLinesHeuristic.new()
	player.add_child(heuristic)
	heuristic = WinHeuristic.new()
	heuristic.weight = 10.0
	player.add_child(heuristic)
	return player
