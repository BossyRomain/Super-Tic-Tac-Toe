#include "board/board.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

Board::Board(): m_rows(DEFAULT_ROWS), m_cols(DEFAULT_COLS) {
    m_cells = new int*[m_rows];
    for(int r = 0; r < m_rows; r++) {
        m_cells[r] = new int[m_cols];
        for(int c = 0; c < m_cols; c++) {
            m_cells[r][c] = 0;
        }
    }
}

Board::Board(const Board& board): m_rows(board.m_rows), m_cols(board.m_cols) {
    m_cells = new int*[m_rows];
    for(int r = 0; r < m_rows; r++) {
        m_cells[r] = new int[m_cols];
        for(int c = 0; c < m_cols; c++) {
            m_cells[r][c] = board.m_cells[r][c];
        }
    }
}

Board::~Board() {
    delete_cells();
}

int Board::get_rows() const {
    return m_rows;
}

int Board::get_cols() const {
    return m_cols;
}

int Board::get_cell_at(Vector2i coords) const {
    if(coords_in(coords)) {
        return m_cells[coords.y][coords.x];
    }
    return -1;
}

void Board::set_rows(int rows) {
    if(rows > 0 && m_rows != rows) {
        resize(rows, m_cols);
    }
}

void Board::set_cols(int cols) {
    if(cols > 0 && m_cols != cols) {
        resize(m_rows, cols);
    }
}

bool Board::set_cell_at(Vector2i coords, int value) {
    if(coords_in(coords)) {
        m_cells[coords.y][coords.x] = value;
        return true;
    }
    return false;
}

void Board::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_rows"), &Board::get_rows);
    ClassDB::bind_method(D_METHOD("set_rows", "rows"), &Board::set_rows);

    ClassDB::bind_method(D_METHOD("get_cols"), &Board::get_cols);
    ClassDB::bind_method(D_METHOD("set_cols", "cols"), &Board::set_cols);

    ClassDB::bind_method(D_METHOD("get_cell_at", "coords"), &Board::get_cell_at);
    ClassDB::bind_method(D_METHOD("set_cell_at", "coords", "value"), &Board::set_cell_at);

    ClassDB::bind_method(D_METHOD("get_winner"), &Board::get_winner);
    ClassDB::bind_method(D_METHOD("is_full"), &Board::is_full);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "rows"), "set_rows", "get_rows");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "cols"), "set_cols", "get_cols");
}

bool Board::coords_in(Vector2i coords) const {
    return coords.x >= 0 && coords.x < m_cols && coords.y >= 0 && coords.y < m_rows;
}

int Board::get_winner() const {
    int winner = 0;
    const int NB_TO_WIN = 4;

    Vector2i dirs[5] = {
        Vector2i(-1, 0), // Left
        Vector2i(1, 0), // Right
        Vector2i(0, 1), // Down
        Vector2i(1, 1), // Down Right
        Vector2i(-1, 1), // Down Left
    };

    for(int r = 0; r < m_rows && winner == 0; r++) {
        for(int c = 0; c < m_cols && winner == 0; c++) {
            Vector2i coords(c, r);
            int player_id = get_cell_at(coords);

            if(player_id <= 0) {
                continue;
            }

            for(int d = 0; d < 5 && winner == 0; d++) {
                int i = 1;
                while(i < NB_TO_WIN && get_cell_at(coords + dirs[d] * i) == player_id) {
                    i++;
                }

                if(i == NB_TO_WIN) {
                    winner = player_id;
                }
            }
        }
    }

    return winner;
}

bool Board::is_full() const {
    bool full = true;

    for(int r = 0; r < m_rows && full; r++) {
        for(int c = 0; c < m_cols && full; c++) {
            full = get_cell_at(Vector2i(c, r)) != 0;
        }
    }

    return full;
}

Board* Board::clone() const {
    Board *copy = memnew(Board);

    copy->resize(m_rows, m_cols);
    for(int r = 0; r < m_rows; r++) {
        for(int c = 0; c < m_cols; c++) {
            copy->m_cells[r][c] = m_cells[r][c];
        }
    }

    return copy;
}

void Board::resize(int rows, int cols) {
    if(rows == m_rows && cols == m_cols) {
        // if the dimensions are unchanged
        return;
    }

    int **p_newCells = new int*[rows];
    for(int r = 0; r < rows; r++) {
        p_newCells[r] = new int[cols];
        for(int c = 0; c < cols; c++) {
            if(r < m_rows && c < m_cols) {
                // Cell keeped
                p_newCells[r][c] = m_cells[r][c];
            } else {
                // Creates new cell
                p_newCells[r][c] = 0;
            }
        }
    }

    delete_cells();

    m_rows = rows;
    m_cols = cols;
    m_cells = p_newCells;
}

void Board::delete_cells() {
    for(int r = 0; r < m_rows; r++) {
        delete m_cells[r];
    }
    delete m_cells;
}