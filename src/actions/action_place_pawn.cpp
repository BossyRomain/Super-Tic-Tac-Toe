#include "actions/action_place_pawn.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

ActionPlacePawn::ActionPlacePawn(): m_coords(-1, -1) {}

ActionPlacePawn::~ActionPlacePawn() {}

Vector2i ActionPlacePawn::get_coords() {
    return m_coords;
}

void ActionPlacePawn::set_coords(Vector2i coords) {
    m_coords = coords;
}

bool ActionPlacePawn::execute(GameState *game_state) {
    Board *board = game_state->get_board();
    Player *player = game_state->current_player();

    if(board->get_cell_at(m_coords) == EMPTY_CELL) {
        board->set_cell_at(m_coords, player->get_id());
        player->decrement_action(PLACE_PAWN);
        return true;
    }

    return false;
}

Action* ActionPlacePawn::duplicate() const {
    ActionPlacePawn *copy = memnew(ActionPlacePawn);
    copy->m_coords = m_coords;
    return copy;
}

void ActionPlacePawn::_bind_methods() {
    ClassDB::bind_method(D_METHOD("execute", "game_state"), &ActionPlacePawn::execute);
}