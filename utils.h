#pragma once
#include <vector>

struct Point {
    int x;
    int y;
};


int min(int a, int b);
int max(int a, int b);

class Tetrimino {  
public:
    static constexpr int SIZE_BLOCK = 8; // pixels
    static constexpr int FACTOR = 3;
    static constexpr int STEP = SIZE_BLOCK * FACTOR;
    Point m_window = Point{240, 480};
    Point m_pos = {0, 0};
    Tetrimino(Point a);
    Point* getT();
    int height();
    int width();
    void moveDown(int increment);
    void moveLeft(int increment);
    void moveRight(int increment);
    bool update(Point& a, Point& window);
      bool canMoveRight(int bound);
      bool canMoveLeft(int bound);
      bool canMoveDown(int bound);
    bool canMoveDown();
       std::vector<std::vector<bool>> m_grid;


private:
    Point m_piece[4] = {};
    bool lower(Point& a, Point& b);
    void buildGrid();
    
};

class Tetris {
public:
    Tetris();
    static constexpr int SIZE_BLOCK = 8; // pixels
    static constexpr int FACTOR = 3;
    static constexpr int STEP = SIZE_BLOCK * FACTOR;
    std::vector<std::vector<bool>> m_grid;
    std::vector<Tetrimino> m_tetriminos;

private:
    Point m_window = Point{240, 480};
    void buildGrid();
    
};