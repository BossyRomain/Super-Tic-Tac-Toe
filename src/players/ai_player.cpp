#include "players/ai_player.h"
#include <godot_cpp/core/defs.hpp>
#include <stdexcept>

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
            Heuristic *heuristic = Object::cast_to<Heuristic>(child);
            if(heuristic) {
                m_heuristics.push_back(heuristic);
            }
        }
    }

    UtilityFunctions::print("An IAPlayer must have at least one child node of type Heuristic");
}

void AIPlayer::choose_action(Board *board) {
    std::vector<Action*> actions = get_actions(board);

    double score_max = -99999999.0;
    Action *choosed_action = nullptr;
    for(Action *action: actions) {
        // Calculate the score
        double score = 0.0;
        for(Heuristic *heuristic: m_heuristics) {
            score += heuristic->get_weight() * heuristic->calculate_action_score(board, this, action->get_coords(), action->get_type());
        }

        if(score > score_max) {
            score_max = score;
            choosed_action = action;
        }
    }

    emit_signal("action_choosed", choosed_action);
}

std::vector<Action*> AIPlayer::get_actions(Board *board) const {
    std::vector<Action*> actions;

    for(int row = 0; row < board->get_rows(); row++) {
        for(int col = 0; col < board->get_cols(); col++) {
            Vector2i coords(col, row);
            int cell_val = board->get_cell_at(coords);
            
            if(can_use_action(ActionType::PLACE_PAWN) && cell_val == EMPTY_CELL) {
                Action *action = memnew(Action);
                action->set_type(ActionType::PLACE_PAWN);
                action->set_coords(coords);
                action->set_player((Player*) this);

                actions.push_back(action);
            }
            if(can_use_action(ActionType::REMOVE_PAWN) && cell_val > EMPTY_CELL && cell_val != get_id()) {
                Action *action = memnew(Action);
                action->set_type(ActionType::REMOVE_PAWN);
                action->set_coords(coords);
                action->set_player((Player*) this);

                actions.push_back(action);
            }
            if(can_use_action(ActionType::REPLACE_PAWN) && cell_val > EMPTY_CELL && cell_val != get_id()) {
                Action *action = memnew(Action);
                action->set_type(ActionType::REPLACE_PAWN);
                action->set_coords(coords);
                action->set_player((Player*) this);

                actions.push_back(action);
            }
            if(can_use_action(ActionType::BAN_CELL) && cell_val == 0) {
                Action *action = memnew(Action);
                action->set_type(ActionType::BAN_CELL);
                action->set_coords(coords);
                action->set_player((Player*) this);

                actions.push_back(action);
            }
        }
    }

    return actions;
}

void AIPlayer::_bind_methods() {
    ClassDB::bind_method(D_METHOD("choose_action", "board"), &AIPlayer::choose_action);

    BIND_ENUM_CONSTANT(DUMB);
    BIND_ENUM_CONSTANT(EASY);
    BIND_ENUM_CONSTANT(MEDIUM);
    BIND_ENUM_CONSTANT(HARD);
    BIND_ENUM_CONSTANT(LEGENDARY);
}