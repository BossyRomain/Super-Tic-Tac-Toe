#ifndef MCTS_H
#define MCTS_H

#include <godot_cpp/core/object.hpp>
#include "actions/action.h"
#include "game_state/game_state.h"
#include <vector>

namespace godot {

class MCTSNode {
public:

    MCTSNode();

    ~MCTSNode();

    MCTSNode* get_parent() const;

    std::vector<MCTSNode*> get_children() const;

    Action* get_action() const;

    GameState* get_game_state() const;

    int get_wins() const;

    int get_visits() const;

    void set_parent(MCTSNode *parent);

    void set_action(Action *action);

    void set_game_state(GameState *game_state);

    bool is_leaf() const;

    bool visited() const;

    void expand();

    void update(int result);

private:

    MCTSNode *m_parent;

    std::vector<MCTSNode*> m_children;

    Action *m_action;

    GameState *m_game_state;

    int m_wins;

    int m_visits;

};

class MCTS: public Object {
    GDCLASS(MCTS, Object);

public:

    MCTS();

    ~MCTS();

    static Action* search(GameState *game_state, int nb_iterations);

protected:

    static void _bind_methods();
};

}

#endif