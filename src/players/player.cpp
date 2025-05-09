#include "players/player.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

Player::Player(): m_id(-1), m_type(-1) {
}

Player::~Player() {

}

void Player::_ready() {

}

int Player::get_id() const {
    return m_id;
}

int Player::get_type() const {
    return m_type;
}

int Player::get_action_uses_left(int action_type) const {
    if(m_actionsUsesLeft.count(action_type) > 0) {
        return m_actionsUsesLeft.at(action_type);
    }
    return 0;
}

void Player::set_id(int id) {
    m_id = id;
}

void Player::set_type(int type) {
    m_type = type;
}

void Player::set_action_uses_left(int action_type, int left) {
    m_actionsUsesLeft[action_type] = left;
}

bool Player::can_use_action(int action_type) const {
    return get_action_uses_left(action_type) > 0;
}

void Player::decrement_action(int action_type) {
    if(get_action_uses_left(action_type) > 0) {
        m_actionsUsesLeft[action_type] = m_actionsUsesLeft.at(action_type) - 1;
    }
}

Player* Player::duplicate() const {
    Player *copy = memnew(Player);
    
    copy->m_id = m_id;
    for(auto pair: m_actionsUsesLeft) {
        copy->m_actionsUsesLeft[pair.first] = pair.second;
    }

    return copy;
}

void Player::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_action_uses_left", "action_type"), &Player::get_action_uses_left);
    ClassDB::bind_method(D_METHOD("set_action_uses_left", "action_type", "uses_left"), &Player::set_action_uses_left);
    ClassDB::bind_method(D_METHOD("can_use_action", "action_type"), &Player::can_use_action);
    ClassDB::bind_method(D_METHOD("decrement_action", "action_type"), &Player::decrement_action);

    ClassDB::bind_method(D_METHOD("get_id"), &Player::get_id);
    ClassDB::bind_method(D_METHOD("set_id", "id"), &Player::set_id);

    ClassDB::bind_method(D_METHOD("get_type"), &Player::get_type);
    ClassDB::bind_method(D_METHOD("set_type", "type"), &Player::set_type);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "type"), "set_type", "get_type");

    BIND_CONSTANT(HUMAN_PLAYER);
    BIND_CONSTANT(AI_DUMB);
    BIND_CONSTANT(AI_EASY);
    BIND_CONSTANT(AI_MEDIUM);
    BIND_CONSTANT(AI_HARD);
    BIND_CONSTANT(AI_LEGENDARY);
}
