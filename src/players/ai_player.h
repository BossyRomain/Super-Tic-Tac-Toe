#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "players/player.h"
#include "players/ai_heuristics/ai_heuristic.h"
#include <vector>

namespace godot {

class AIHeuristic;

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

    void play(Board *board) override;

protected:

    static void _bind_methods();

private:

    /**
     * Gets the list of actions possibles for a board state.
     */
    std::vector<Vector3i> get_actions(Board *board) const;
    
    std::vector<AIHeuristic*> m_heuristics;
};

}

VARIANT_ENUM_CAST(AIPlayer::Level);


#endif