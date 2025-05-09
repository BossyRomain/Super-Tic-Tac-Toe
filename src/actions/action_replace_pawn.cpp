#include "actions/action_replace_pawn.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

ActionReplacePawn::ActionReplacePawn(): m_coords(-1, -1) {}

ActionReplacePawn::~ActionReplacePawn() {}

Vector2i ActionReplacePawn::get_coords() {
    return m_coords;
}

void ActionReplacePawn::set_coords(Vector2i coords) {
    m_coords = coords;
}

bool ActionReplacePawn::execute(GameState *game_state) {
    Board *board = game_state->get_board();
    Player *player = game_state->current_player();

    int cell_val = board->get_cell_at(m_coords);
    if(cell_val > EMPTY_CELL && cell_val != player->get_id()) {
        board->set_cell_at(m_coords, player->get_id());
        player->decrement_action(REPLACE_PAWN);
        return true;
    }

    return false;
}

Action* ActionReplacePawn::duplicate() const {
    ActionReplacePawn *copy = memnew(ActionReplacePawn);
    copy->m_coords = m_coords;
    return copy;
}

void ActionReplacePawn::_bind_methods() {
    ClassDB::bind_method(D_METHOD("execute", "game_state"), &ActionReplacePawn::execute);
}