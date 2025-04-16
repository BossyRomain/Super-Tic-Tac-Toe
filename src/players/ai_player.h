#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "players/player.h"
#include "heuristics/heuristic.h"
#include <vector>

namespace godot {

class Heuristic;

/**
 * Represents an AI player. Use at least one child node of types AIHeuristic to change the behaviour of it.
 */
class AIPlayer: public Player {
    GDCLASS(AIPlayer, Player)

public:

    enum Level {
        DUMB,
        EASY,
        MEDIUM,
        HARD,
        LEGENDARY
    };

    AIPlayer();

    ~AIPlayer();

    void _ready();

    void choose_action(Board *board) override;

protected:

    static void _bind_methods();

private:

    /**
     * Gets the list of actions possibles for a board state.
     */
    std::vector<Action*> get_actions(Board *board) const;

    double min_max(Board *board, int depth, bool maximizing);
    
    std::vector<Heuristic*> m_heuristics;
};

}

VARIANT_ENUM_CAST(AIPlayer::Level);


#endif