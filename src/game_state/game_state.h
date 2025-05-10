#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <godot_cpp/core/object.hpp>
#include "players/player.h"
#include <vector>
#include "board/board.h"
#include "actions/action.h"

namespace godot {

class Action;
class Player;

/**
 * Represents a state of game at a given time, this means it contains
 * informations about the players and the board's state.
 */
class GameState: public Object {
    GDCLASS(GameState, Object);

public:

    GameState();

    ~GameState();

    Board* get_board() const;

    void set_board(Board *board);

    /**
     * Returns the player who must play in this state.
     */
    Player* current_player() const;

    /**
     * Change the current player to be next player that need to play.
     */
    void next_player();

    /**
     * Returns the number of players.
     */
    int nb_players() const;

    /**
     * Add a new player to the game.
     */
    void add_player(Player *player);

    /**
     * Returns true if the state is a terminal state, else returns false.
     */
    bool is_over() const;

    /**
     * Returns the id of the winner, if there is no winner returns 0.
     */
    int winner() const;

    /**
     * Returns the list of all the available actions for this state.
     */
    std::vector<Action*> available_actions();

    GameState* duplicate() const;

protected:

    static void _bind_methods();

private:

    Board *m_board;

    std::vector<Player*> m_players;

    int m_current_player;
};

}

#endif