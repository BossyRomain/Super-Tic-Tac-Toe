#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "board/board.h"
#include "players/player.h"
#include "actions/action.h"
#include "actions/action_place_pawn.h"
#include "actions/action_replace_pawn.h"
#include "actions/action_ban_cell.h"
#include "actions/action_switch_pawns.h"
#include "game_state/game_state.h"
#include "actions/actions_factory.h"
#include "mcts/mcts.h"

using namespace godot;

void initialize_gdextension_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_CLASS(Board);
	GDREGISTER_CLASS(Player);
	GDREGISTER_CLASS(GameState);
	GDREGISTER_ABSTRACT_CLASS(Action);
	GDREGISTER_CLASS(ActionPlacePawn);
	GDREGISTER_CLASS(ActionReplacePawn);
	GDREGISTER_CLASS(ActionBanCell);
	GDREGISTER_CLASS(ActionSwitchPawns);
	GDREGISTER_CLASS(ActionsFactory);
	GDREGISTER_CLASS(MCTS);
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