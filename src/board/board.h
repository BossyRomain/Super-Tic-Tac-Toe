#ifndef BOARD_H
#define BOARD_H

#include <godot_cpp/core/object.hpp>

namespace godot {

#define DEFAULT_ROWS 3
#define DEFAULT_COLS 3

#define EMPTY_CELL 0
#define BANNED_CELL -1

/**
 * Represents a state of the board.
 * A board must have at least one row and one column.
 * By default the cells are initialized with the value 0, it's there default value.
 */
class Board: public Object {
    GDCLASS(Board, Object)

public:

    Board();
    Board(const Board& board);
    
    ~Board();

    int get_rows() const;
    
    int get_cols() const;

    /**
     * Returns the value in the cell at the given coordinnates.
     * Returns -1 if the coordinnates are outside of the board.
     */
    int get_cell_at(Vector2i coords) const;
    
    /**
     * Change the number of rows of the board.
     * Do nothing if the new numbers of rows if less or equal to 0.
     */
    void set_rows(int rows);

    /**
     * Change the number of columns of the board.
     * Do nothing if the new numbers of columns if less or equal to 0.
     */
    void set_cols(int cols);

    /**
     * Change the value in the cell at the given coordinnates.
     * Returns true if the change was successfull, else false.
     */
    bool set_cell_at(Vector2i coords, int value);

    /**
     * Returns true if the coordinnates are on the board, else false.
     */
    bool coords_in(Vector2i coords) const;

    /**
     * Returns the id of the winner if there is one, else returns 0.
     */
    int get_winner() const;

    /**
     * Returns true if the board is full, it means that there is no empty cell, else returns false.
     */
    bool is_full() const;

    Board* duplicate() const;

protected:

    static void _bind_methods();

private:

    /**
     * Resize the board to match the new dimensions.
     * If new cells are created, there value is the default value for the cells (0).
     */
    void resize(int rows, int cols);

    void delete_cells();

    int m_rows;

    int m_cols;

    int **m_cells;
};

}

#endif