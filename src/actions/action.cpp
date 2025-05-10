#include "actions/action.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

Action::Action() {}

Action::~Action() {}

bool Action::execute(GameState *game_state) {
    return false;
}

void Action::_bind_methods() {
    ClassDB::bind_method(D_METHOD("execute", "game_state"), &Action::execute);

    BIND_CONSTANT(PLACE_PAWN);
    BIND_CONSTANT(REPLACE_PAWN);
    BIND_CONSTANT(BAN_CELL);
}