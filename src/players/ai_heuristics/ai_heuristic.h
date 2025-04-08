#ifndef AI_HEURISTIC_H
#define AI_HEURISTIC_H

#include <godot_cpp/classes/node.hpp>
#include "players/ai_player.h"
#include "board/board.h"

namespace godot {

class AIPlayer;

/**
 * The base class of the heuristics used by AI players to change their behaviour.
 */
class AIHeuristic: public Node {
    GDCLASS(AIHeuristic, Node);

public:

    AIHeuristic();

    ~AIHeuristic();

    double get_weight() const;

    void set_weight(double weight);

    /**
     * Calculate a score for a board state, a player and an action.
     * Returns a float value between [-1.0, 1.0].
     * Positive returned value means the action is advantagous for the player in the board state.
     * Negative returned value means the action is disadvantagous for the player in the board state.
     * When 0 is returned it means the action is nor advantagous nor disadvantagous for the player in the board state.
     */
    virtual double calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, int action_type);

protected:

    static void _bind_methods();

private:

    double m_weight;
};

}

#endif