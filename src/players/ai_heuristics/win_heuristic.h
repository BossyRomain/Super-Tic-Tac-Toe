#ifndef WIN_HEURISTIC_H
#define WIN_HEURISTIC_H

#include "players/ai_heuristics/ai_heuristic.h"

namespace godot {

/**
 * Plays a winning action as soon as possible.
 */
class WinHeuristic: public AIHeuristic {
    GDCLASS(WinHeuristic, AIHeuristic)

public:

    WinHeuristic();    

    ~WinHeuristic();

    double calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, int action_type) override;

protected:

    static void _bind_methods();

private:
};

}

#endif