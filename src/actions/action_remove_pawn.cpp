#include "actions/action_remove_pawn.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

ActionRemovePawn::ActionRemovePawn(): m_coords(-1, -1) {}

ActionRemovePawn::~ActionRemovePawn() {}

Vector2i ActionRemovePawn::get_coords() {
    return m_coords;
}

void ActionRemovePawn::set_coords(Vector2i coords) {
    m_coords = coords;
}

bool ActionRemovePawn::execute(GameState *game_state) {
    Board *board = game_state->get_board();
    Player *player = game_state->current_player();

    int cell_val = board->get_cell_at(m_coords);
    if(cell_val > EMPTY_CELL && cell_val != player->get_id()) {
        board->set_cell_at(m_coords, EMPTY_CELL);
        player->decrement_action(REMOVE_PAWN);
        return true;
    }

    return false;
}

Action* ActionRemovePawn::duplicate() const {
    ActionRemovePawn *copy = memnew(ActionRemovePawn);
    copy->m_coords = m_coords;
    return copy;
}

void ActionRemovePawn::_bind_methods() {
    ClassDB::bind_method(D_METHOD("execute", "game_state"), &ActionRemovePawn::execute);
}