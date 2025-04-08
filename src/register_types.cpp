#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "board/board.h"
#include "players/player.h"
#include "players/human_player.h"
#include "players/ai_player.h"
#include "players/ai_heuristics/ai_heuristic.h"
#include "players/ai_heuristics/random_heuristic.h"
#include "players/ai_heuristics/win_heuristic.h"
#include "players/ai_heuristics/max_pawns_heuristic.h"
#include "players/ai_heuristics/block_pawns_heuristic.h"
#include "players/ai_heuristics/no_specials_early_heuristic.h"
#include "players/ai_heuristics/control_center_heuristic.h"
#include "players/ai_heuristics/max_lines_heuristic.h"
#include "players/ai_heuristics/block_lines_heuristic.h"

using namespace godot;

void initialize_gdextension_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_CLASS(Board);
	GDREGISTER_ABSTRACT_CLASS(Player);
	GDREGISTER_CLASS(HumanPlayer);
	GDREGISTER_CLASS(AIPlayer);
	GDREGISTER_ABSTRACT_CLASS(AIHeuristic);
	
	GDREGISTER_CLASS(RandomHeuristic);
	GDREGISTER_CLASS(WinHeuristic);
	GDREGISTER_CLASS(MaxPawnsHeuristic);
	GDREGISTER_CLASS(BlockPawnsHeuristic);
	GDREGISTER_CLASS(NoSpecialsEarlyHeuristic);
	GDREGISTER_CLASS(ControlCenterHeuristic);
	GDREGISTER_CLASS(MaxLinesHeuristic);
	GDREGISTER_CLASS(BlockLinesHeuristic);
}

void uninitialize_gdextension_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT gdextension_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_gdextension_module);
	init_obj.register_terminator(uninitialize_gdextension_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}