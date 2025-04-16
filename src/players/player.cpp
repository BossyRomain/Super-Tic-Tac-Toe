#include "players/player.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

Player::Player(): m_id(-1) {
    m_actionsUsesLeft[PLACE_PAWN] = INT32_MAX;
    m_actionsUsesLeft[REMOVE_PAWN] = 3;
    m_actionsUsesLeft[REPLACE_PAWN] = 2;
    m_actionsUsesLeft[BAN_CELL] = 2;
}

Player::~Player() {

}

void Player::_ready() {

}

int Player::get_id() const {
    return m_id;
}

int Player::get_action_uses_left(ActionType action_type) const {
    if(m_actionsUsesLeft.count(action_type) > 0) {
        return m_actionsUsesLeft.at(action_type);
    }
    return -1;
}

void Player::set_id(int id) {
    m_id = id;
}

bool Player::can_use_action(ActionType action_type) const {
    return get_action_uses_left(action_type) > 0;
}

void Player::decrement_uses_action(ActionType action_type) {
    int left = m_actionsUsesLeft.at(action_type);
    m_actionsUsesLeft[action_type] = left - 1;
}

void Player::choose_action(Board *board) {
}

void Player::_bind_methods() {
    ClassDB::add_virtual_method(get_class_static(), MethodInfo("choose_action", PropertyInfo(Variant::OBJECT, "board")));

    ClassDB::bind_method(D_METHOD("get_action_uses_left", "action_type"), &Player::get_action_uses_left);
    ClassDB::bind_method(D_METHOD("can_use_action", "action_type"), &Player::can_use_action);

    ClassDB::bind_method(D_METHOD("get_id"), &Player::get_id);
    ClassDB::bind_method(D_METHOD("set_id", "id"), &Player::set_id);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

    ADD_SIGNAL(MethodInfo("action_choosed", PropertyInfo(Variant::OBJECT, "action")));
}



Action::Action(): m_type(ActionType::PLACE_PAWN), m_coords(Vector2i(-1, -1)), m_player(nullptr) {

}

Action::~Action() {

}

ActionType Action::get_type() const {
    return m_type;
}

Vector2i Action::get_coords() const {
    return m_coords;
}

Player* Action::get_player() const {
    return m_player;
}

void Action::set_type(ActionType type) {
    m_type = type;
}

void Action::set_coords(Vector2i coords) {
    m_coords = coords;
}

void Action::set_player(Player *player) {
    m_player = player;
}

bool Action::execute(Board *board) {
    if(m_player->can_use_action(m_type)) {
        bool success = false;
        const int cell_val = board->get_cell_at(m_coords);

        switch (m_type)
        {
        case PLACE_PAWN:
            if(cell_val == EMPTY_CELL) {
                success = board->set_cell_at(m_coords, m_player->get_id());
            }
            break;

        case REMOVE_PAWN:
            if(cell_val > EMPTY_CELL) {
                success = board->set_cell_at(m_coords, EMPTY_CELL);
            }
            break;
        
        case REPLACE_PAWN:
            if(cell_val > EMPTY_CELL && cell_val != m_player->get_id()) {
                success = board->set_cell_at(m_coords, m_player->get_id());
            }
            break;

        case BAN_CELL:
            if(cell_val == EMPTY_CELL) {
                success = board->set_cell_at(m_coords, BANNED_CELL);
            }
            break;
        }

        if(success) {
            m_player->decrement_uses_action(m_type);
        }
        return success;
    }

    return false;
}

void Action::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_type"), &Action::get_type);
    ClassDB::bind_method(D_METHOD("set_type", "type"), &Action::set_type);
    ClassDB::bind_method(D_METHOD("get_coords"), &Action::get_coords);
    ClassDB::bind_method(D_METHOD("set_coords", "coords"), &Action::set_coords);
    ClassDB::bind_method(D_METHOD("get_player"), &Action::get_player);
    ClassDB::bind_method(D_METHOD("set_player", "player"), &Action::set_player);

    ClassDB::bind_method(D_METHOD("execute", "board"), &Action::execute);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "type"), "set_type", "get_type");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "coords"), "set_coords", "get_coords");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "player"), "set_player", "get_player");

    BIND_ENUM_CONSTANT(PLACE_PAWN);
    BIND_ENUM_CONSTANT(REMOVE_PAWN);
    BIND_ENUM_CONSTANT(REPLACE_PAWN);
    BIND_ENUM_CONSTANT(BAN_CELL);
}