#include "mcts/mcts.h"
#include <godot_cpp/core/class_db.hpp>
#include "actions/action_place_pawn.h"
#include "actions/action_remove_pawn.h"
#include "actions/action_replace_pawn.h"
#include "actions/action_ban_cell.h"
#include "actions/actions_factory.h"

using namespace godot;

std::vector<Action*> actions_for_state(GameState *game_state) {
    std::vector<Action*> actions;

    const Board *board = game_state->get_board();
    const Player *player = game_state->current_player();

    for(int row = 0; row < board->get_rows(); row++) {
        for(int col = 0; col < board->get_cols(); col++) {
            Vector2i coords(col, row);
            int cell = board->get_cell_at(coords);

            if(player->can_use_action(PLACE_PAWN) && cell == EMPTY_CELL) {
                actions.push_back(ActionsFactory::create_place_pawn_action(coords));
            }
            if(player->can_use_action(REMOVE_PAWN) && cell > EMPTY_CELL && cell != player->get_id()) {
                actions.push_back(ActionsFactory::create_remove_pawn_action(coords));
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



double ucb1(MCTSNode *node) {
    if(!node->visited()) {
        return 999999999.0;
    } else {
        return ((double) node->get_wins() / node->get_visits()) + 2.0 * sqrt(log(node->get_parent()->get_visits()) / node->get_visits());
    }
}

MCTSNode* select(MCTSNode *root) {
    MCTSNode *selected = root;
    while(!selected->is_leaf()) {
        double max = -999999.0;;
        for(MCTSNode *child: selected->get_children()) {
            double score = ucb1(child);
            if(score > max) {
                max = score;
                selected = child;
            }
        }
    }
    return selected;
}

MCTSNode* expand(MCTSNode *node) {
    if(node->visited()) {
        node->expand();
        return node->get_children()[0];
    }
    return node;
}

int rollout(MCTSNode *node, int player_id) {
    GameState *game_state = node->get_game_state()->duplicate();
    while(!game_state->is_over()) {
        std::vector<Action*> actions = actions_for_state(game_state);
        Action *action = actions[rand() % actions.size()]->duplicate();
        for(Action *action: actions) {
            memdelete(action);
        }

        GameState *copy = game_state->duplicate();
        action->execute(copy);
        memdelete(game_state);
        game_state = copy;
        game_state->next_player();
    }

    int winner = game_state->winner();
    memdelete(game_state);

    if(winner == 0) {
        return 0;
    } else if(winner == player_id) {
        return 1;
    } else {
        return -1;
    }
}

MCTSNode::MCTSNode(): m_parent(nullptr), m_action(nullptr), m_game_state(nullptr), m_wins(0), m_visits(0) {}

MCTSNode::~MCTSNode() {
    for(MCTSNode *child: m_children) {
        delete child;
    }

    memdelete(m_action);
    memdelete(m_game_state);
}

MCTSNode* MCTSNode::get_parent() const {
    return m_parent;
}

std::vector<MCTSNode*> MCTSNode::get_children() const {
    return m_children;
}

Action* MCTSNode::get_action() const {
    return m_action;
}

GameState* MCTSNode::get_game_state() const {
    return m_game_state;
}

int MCTSNode::get_wins() const {
    return m_wins;
}

int MCTSNode::get_visits() const {
    return m_visits;
}

void MCTSNode::set_parent(MCTSNode *parent) {
    m_parent = parent;
}

void MCTSNode::set_action(Action *action) {
    m_action = action;
}

void MCTSNode::set_game_state(GameState *game_state) {
    m_game_state = game_state;
}

bool MCTSNode::is_leaf() const {
    return m_children.size() == 0;
}

bool MCTSNode::visited() const {
    return m_visits > 0;
}

void MCTSNode::expand() {
    if(is_leaf()) {
        std::vector<Action*> actions = actions_for_state(m_game_state);
        for(Action *action: actions) {
            MCTSNode *child = new MCTSNode();
            child->set_parent(this);
            child->set_action(action);

            GameState *copy = m_game_state->duplicate();
            action->execute(copy);
            child->set_game_state(copy);

            m_children.push_back(child);
        }
    }
}

void MCTSNode::update(int result) {
    m_visits++;
    m_wins += result;

    if(m_parent != nullptr) {
        m_parent->update(result);
    }
}

MCTS::MCTS() {}

MCTS::~MCTS() {}

Action* MCTS::search(GameState *game_state, int nb_iterations) {
    MCTSNode *root = new MCTSNode();
    root->set_game_state(game_state->duplicate());
    root->expand();

    const int player_id = game_state->current_player()->get_id();
    for(int i = 0; i < nb_iterations; i++) {
        // UtilityFunctions::print("Select");
        MCTSNode *selected = select(root);
        // UtilityFunctions::print("Expand");
        selected = expand(selected);
        // UtilityFunctions::print("Rollout");
        int result = rollout(selected, player_id);
        // UtilityFunctions::print("Update");
        selected->update(result);
        // UtilityFunctions::print("Result of iter " + UtilityFunctions::str(i + 1) + ": " + UtilityFunctions::str(result));
        // UtilityFunctions::print("End of iter " + UtilityFunctions::str(i + 1));
    }

    // UtilityFunctions::print("Searching best action");
    int max = -1;
    MCTSNode *selected = nullptr;
    for(MCTSNode *child: root->get_children()) {
        if(child->get_visits() > max) {
            max = child->get_visits();
            selected = child;
        }
    }
    // UtilityFunctions::print("Max: " + UtilityFunctions::str(max));

    Action *selected_action = selected->get_action()->duplicate();
    // delete root;
    return selected_action;
}

void MCTS::_bind_methods() {
    ClassDB::bind_static_method(get_class_static(), D_METHOD("search", "game_state", "nb_iterations"), &MCTS::search);
}