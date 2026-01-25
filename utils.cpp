#include "utils.h"

int min(int a, int b){
    if (a < b)
        return a;
    return b;
}

int max(int a, int b){
    if (a > b)
        return a;
    return b;
}

// class Tetris
Tetris::Tetris(){
    buildGrid();
}

void Tetris::buildGrid() {
    for (int x = 0; x < m_window.x / STEP; ++x) {
        m_grid.push_back(std::vector<bool>{});
        for (int y = 0; y < m_window.y / STEP; ++y){
            m_grid[x].push_back(true);
        }
    }
}


// class Tetrimino
Tetrimino::Tetrimino(Point a) {
    // T 
    update(a, m_window);
    buildGrid();
}

bool Tetrimino::update(Point& a, Point& dim){
    bool isUpdated = false;
    m_pos.x = a.x;
    m_pos.y = a.y;
  
    Point un = Point{m_pos.x, m_pos.y + STEP};
    Point deux = Point{m_pos.x,  m_pos.y + STEP * 2};
    Point trois = Point{m_pos.x + STEP, m_pos.y + STEP};

    if (lower(m_pos, dim) && lower(un, dim) && lower(deux, dim) && lower(trois, dim)) {
        m_piece[0] = m_pos;
        m_piece[1] = un;
        m_piece[2] = deux;
        m_piece[3] = trois;
        isUpdated = true;
    }
  
    return isUpdated;
}
bool Tetrimino::canMoveDown(int bound){
    bool move = true;
    for (int i = 0; i < 4; ++i){
        if (m_piece[i].y >= bound){
            move = false;
            break;
        }
    }
    return move;
}
bool Tetrimino::canMoveDown(){
    bool move = true;
    for (int i = 0; i < 4; ++i){
        if (!m_grid[m_piece[i].x / STEP][ (m_piece[i].y + STEP) / STEP]){
            move = false;
            break;
        }
    }
    return move;
}

bool Tetrimino::canMoveLeft(int bound){
    bool move = true;
    for (int i = 0; i < 4; ++i){
        if (m_piece[i].x < bound){
            move = false;
            break;
        }
    }
    return move;
}

bool Tetrimino::canMoveRight(int bound){
    bool move = true;
    for (int i = 0; i < 4; ++i){
        if (m_piece[i].x >= bound){
            move = false;
            break;
        }
    }
    return move;
}

bool Tetrimino::lower(Point& a, Point& b) {
    bool islower = false;
    if (a.x < b.x || a.y < b.y){
        islower = true;
    }
    return islower;
}

Point* Tetrimino::getT()
{
    return m_piece;
}

void Tetrimino::moveDown(int increment){
    m_pos.y += increment;
    update(m_pos, m_window);
}

void Tetrimino::moveRight(int increment){
    m_pos.x += increment;
    update(m_pos, m_window);
}

void Tetrimino::moveLeft(int increment){
    m_pos.x -= increment;
    update(m_pos, m_window);
}

int Tetrimino::height() {
    int minimum = m_piece[0].y;
    int maximum = m_piece[0].y;
    for (int i = 1; i < 4; ++i) {
        minimum = min(minimum, m_piece[i].y);
        maximum = max(maximum,m_piece[i].y);
    }
    return 0;
}

void Tetrimino::buildGrid() {
    for (int x = 0; x < m_window.x / STEP; ++x) {
        m_grid.push_back(std::vector<bool>{});
        for (int y = 0; y < m_window.y / STEP; ++y){
            m_grid[x].push_back(true);
        }
    }
}