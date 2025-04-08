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

int Player::get_action_uses_left(int actionType) const {
    if(m_actionsUsesLeft.count(actionType) >= 0) {
        return m_actionsUsesLeft.at(actionType);
    }
    return -1;
}

void Player::set_id(int id) {
    m_id = id;
}

void Player::set_action_uses_left(int actionType, int left) {
    m_actionsUsesLeft[actionType] = left;
}

void Player::play(Board *board) {

}

void Player::_bind_methods() {
    ClassDB::add_virtual_method(get_class_static(), MethodInfo("play", PropertyInfo(Variant::OBJECT, "board")));

    ClassDB::bind_method(D_METHOD("get_action_uses_left", "actionType"), &Player::get_action_uses_left);
    ClassDB::bind_method(D_METHOD("set_action_uses_left", "actionType", "left"), &Player::set_action_uses_left);

    ClassDB::bind_method(D_METHOD("get_id"), &Player::get_id);
    ClassDB::bind_method(D_METHOD("set_id", "id"), &Player::set_id);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

    ADD_SIGNAL(MethodInfo("action_choosed", PropertyInfo(Variant::VECTOR2I, "coords"), PropertyInfo(Variant::INT, "type")));

    BIND_ENUM_CONSTANT(PLACE_PAWN);
    BIND_ENUM_CONSTANT(REMOVE_PAWN);
    BIND_ENUM_CONSTANT(REPLACE_PAWN);
    BIND_ENUM_CONSTANT(BAN_CELL);
}
