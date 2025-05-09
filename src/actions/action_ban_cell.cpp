#include "actions/action_ban_cell.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

ActionBanCell::ActionBanCell(): m_coords(-1, -1) {}

ActionBanCell::~ActionBanCell() {}

Vector2i ActionBanCell::get_coords() {
    return m_coords;
}

void ActionBanCell::set_coords(Vector2i coords) {
    m_coords = coords;
}

bool ActionBanCell::execute(GameState *game_state) {
    Board *board = game_state->get_board();
    Player *player = game_state->current_player();

    if(board->get_cell_at(m_coords) != BANNED_CELL) {
        board->set_cell_at(m_coords, BANNED_CELL);
        player->decrement_action(BAN_CELL);
        return true;
    }

    return false;
}

Action* ActionBanCell::duplicate() const {
    ActionBanCell *copy = memnew(ActionBanCell);
    copy->m_coords = m_coords;
    return copy;
}

void ActionBanCell::_bind_methods() {
    ClassDB::bind_method(D_METHOD("execute", "game_state"), &ActionBanCell::execute);
}