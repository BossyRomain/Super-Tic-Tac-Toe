#include "actions/actions_factory.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

ActionsFactory::ActionsFactory() {}
    
ActionsFactory::~ActionsFactory() {}

Action* ActionsFactory::create_place_pawn_action(Vector2i coords) {
    ActionPlacePawn *action = memnew(ActionPlacePawn);
    action->set_coords(coords);
    return action;
}

Action* ActionsFactory::create_replace_pawn_action(Vector2i coords) {
    ActionReplacePawn *action = memnew(ActionReplacePawn);
    action->set_coords(coords);
    return action;
}

Action* ActionsFactory::create_ban_cell_action(Vector2i coords) {
    ActionBanCell *action = memnew(ActionBanCell);
    action->set_coords(coords);
    return action;
}

void ActionsFactory::_bind_methods() {
    ClassDB::bind_static_method(get_class_static(), D_METHOD("create_place_pawn_action", "coords"), &ActionsFactory::create_place_pawn_action);
    ClassDB::bind_static_method(get_class_static(), D_METHOD("create_replace_pawn_action", "coords"), &ActionsFactory::create_replace_pawn_action);
    ClassDB::bind_static_method(get_class_static(), D_METHOD("create_ban_cell_action", "coords"), &ActionsFactory::create_ban_cell_action);
}