#include "players/ai_player.h"
#include <godot_cpp/core/defs.hpp>

using namespace godot;

AIPlayer::AIPlayer() {

}

AIPlayer::~AIPlayer() {

}

void AIPlayer::_ready() {
    Player::_ready();

    Array children = get_children();
    for(int i = 0; i < children.size(); i++) {
        Node *child = Object::cast_to<Node>(children[i]);
        if(child) {
            AIHeuristic *heuristic = Object::cast_to<AIHeuristic>(child);
            if(heuristic) {
                m_heuristics.push_back(heuristic);
            }
        }
    }

    UtilityFunctions::print("Nb heuristics for the player " + UtilityFunctions::str(get_id()) + ": " + UtilityFunctions::str(m_heuristics.size()));
}

void AIPlayer::play(Board *board) {
    std::vector<Vector3i> actions = get_actions(board);

    double score_max = -99999999.0;
    int index = -1;
    for(int i = 0; i < actions.size(); i++) {
        // Calculate the score
        double score = 0.0;
        for(AIHeuristic *heuristic: m_heuristics) {
            score += heuristic->get_weight() * heuristic->calculate_action_score(board, this, Vector2i(actions[i].x, actions[i].y), actions[i].z);
        }

        if(score > score_max) {
            score_max = score;
            index = i;
        }
    }

    Vector3i action = actions[index];
    UtilityFunctions::print("Player " + UtilityFunctions::str(get_id()) + " make action of type " + UtilityFunctions::str(action.z) + " on cell " + UtilityFunctions::str(Vector2i(action.x, action.y)));
    emit_signal("action_choosed", Vector2i(action.x, action.y), action.z);
}

std::vector<Vector3i> AIPlayer::get_actions(Board *board) const {
    std::vector<Vector3i> actions;

    for(int row = 0; row < board->get_rows(); row++) {
        for(int col = 0; col < board->get_cols(); col++) {
            Vector2i coords(col, row);
            int cell_val = board->get_cell_at(coords);
            
            if(get_action_uses_left(Player::Actions::PLACE_PAWN) > 0 && cell_val == 0) {
                actions.push_back(Vector3i(coords.x, coords.y, Player::Actions::PLACE_PAWN));
            }
            if(get_action_uses_left(Player::Actions::REMOVE_PAWN) > 0 && cell_val > 0 && cell_val != get_id()) {
                actions.push_back(Vector3i(coords.x, coords.y, Player::Actions::REMOVE_PAWN));
            }
            if(get_action_uses_left(Player::Actions::REPLACE_PAWN) > 0 && cell_val > 0 && cell_val != get_id()) {
                actions.push_back(Vector3i(coords.x, coords.y, Player::Actions::REPLACE_PAWN));
            }
            if(get_action_uses_left(Player::Actions::BAN_CELL) > 0 && cell_val == 0) {
                actions.push_back(Vector3i(coords.x, coords.y, Player::Actions::BAN_CELL));
            }
        }
    }

    return actions;
}

void AIPlayer::_bind_methods() {
    ClassDB::bind_method(D_METHOD("play", "board"), &AIPlayer::play);

    BIND_ENUM_CONSTANT(DUMB);
    BIND_ENUM_CONSTANT(EASY);
    BIND_ENUM_CONSTANT(MEDIUM);
    BIND_ENUM_CONSTANT(HARD);
    BIND_ENUM_CONSTANT(LEGENDARY);
}