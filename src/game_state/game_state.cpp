#include "game_state/game_state.h"
#include <godot_cpp/core/class_db.hpp>
#include "actions/actions_factory.h"

using namespace godot;

GameState::GameState(): m_current_player(0) {}

GameState::~GameState() {
    memdelete(m_board);

    for(Player *player: m_players) {
        memdelete(player);
    }
}

Board* GameState::get_board() const {
    return m_board;
}

void GameState::set_board(Board *board) {
    m_board = board;
}

Player* GameState::current_player() const {
    return m_players[m_current_player];
}

void GameState::next_player() {
    m_current_player = (m_current_player + 1) % nb_players();
}

int GameState::nb_players() const {
    return m_players.size();
}

void GameState::add_player(Player *player) {
    m_players.push_back(player);
}

bool GameState::is_over() const {
    return m_board->is_full() || m_board->get_winner() > 0;
}

int GameState::winner() const {
    return m_board->get_winner();
}

std::vector<Action*> GameState::available_actions() {
    std::vector<Action*> actions;

    const Player *player = current_player();
    for(int row = 0; row < m_board->get_rows(); row++) {
        for(int col = 0; col < m_board->get_cols(); col++) {
            Vector2i coords(col, row);
            int cell = m_board->get_cell_at(coords);

            if(player->can_use_action(PLACE_PAWN) && cell == EMPTY_CELL) {
                actions.push_back(ActionsFactory::create_place_pawn_action(coords));
            }
            if(player->can_use_action(REPLACE_PAWN) && cell > EMPTY_CELL && cell != player->get_id()) {
                actions.push_back(ActionsFactory::create_replace_pawn_action(coords));
            }
            if(player->can_use_action(BAN_CELL) && cell != BANNED_CELL) {
                actions.push_back(ActionsFactory::create_ban_cell_action(coords));
            }
        }
    }

    return actions;
}

GameState* GameState::duplicate() const {
    GameState *copy = memnew(GameState);

    copy->m_board = m_board->duplicate();
    for(Player *player: m_players) {
        copy->m_players.push_back(player->duplicate());
    }
    copy->m_current_player = m_current_player;

    return copy;
}

void GameState::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_board"), &GameState::get_board);
    ClassDB::bind_method(D_METHOD("set_board", "board"), &GameState::set_board);
    ClassDB::bind_method(D_METHOD("current_player"), &GameState::current_player);
    ClassDB::bind_method(D_METHOD("next_player"), &GameState::next_player);
    ClassDB::bind_method(D_METHOD("nb_players"), &GameState::nb_players);
    ClassDB::bind_method(D_METHOD("add_player", "player"), &GameState::add_player);
    ClassDB::bind_method(D_METHOD("is_over"), &GameState::is_over);
    ClassDB::bind_method(D_METHOD("winner"), &GameState::winner);
}