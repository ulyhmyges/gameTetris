#pragma once
#include <vector>

struct Point {
    int x;
    int y;
};


int min(int a, int b);
int max(int a, int b);

enum Type {
    T,
    O,
    L,
    J,
    Z,
    S,
    I
};

class Tetrimino {  
public:
    static constexpr int SIZE_BLOCK = 8; // pixels
    static constexpr int FACTOR = 3;
    static constexpr int STEP = SIZE_BLOCK * FACTOR;
    Point m_window = Point{240, 480};

    Point m_pos = {0, 0};

   //Tetrimino(Point a);
    virtual ~Tetrimino() = default;

    std::vector<Point> getShape();
 
    void moveDown(std::vector<std::vector<bool>>& grid);
    void moveLeft(std::vector<std::vector<bool>>& grid);
    void moveRight(std::vector<std::vector<bool>>& grid);
    virtual bool create(Point const& a, Point const& window) = 0;
    virtual bool rotateRight(std::vector<std::vector<bool>>& grid) = 0;
    virtual bool rotateLeft(std::vector<std::vector<bool>>& grid) = 0;


    bool canMoveRight(int bound);
    bool canMoveLeft(int bound);
    bool canMoveDown(int bound);
    bool canMove(std::vector<std::vector<bool>> grid, char direction);


protected:
    std::vector<Point> m_piece = {Point{0,0}, Point{0,0}, Point{0,0}, Point{0,0}};
    bool lower(Point const& a, Point const& b);
};

class Teewee : public Tetrimino {
public:
    Teewee(Point a);
    ~Teewee() = default;
    // virtual ~Teewee() is automatically generated
    bool create(Point const& a, Point const& window) override;
    bool rotateRight(std::vector<std::vector<bool>>& grid) override;
    bool rotateLeft(std::vector<std::vector<bool>>& grid) override;

};

class Smashboy : public Tetrimino {
public:
    Smashboy(Point a);
    ~Smashboy() = default; // virtual ~Teewee() is automatically generated
    bool create(Point const& a, Point const& window) override;
    bool rotateRight(std::vector<std::vector<bool>>& grid) override;
    bool rotateLeft(std::vector<std::vector<bool>>& grid) override;

};

// I
class Hero : public Tetrimino {
public:
    Hero(Point a);
    ~Hero() = default;
    bool create(Point const& a, Point const& window) override;
    bool rotateRight(std::vector<std::vector<bool>>& grid) override;
    bool rotateLeft(std::vector<std::vector<bool>>& grid) override;
};

// S
class RhodeIsland : public Tetrimino {
public:
    RhodeIsland(Point a);
    ~RhodeIsland() = default;
    bool create(Point const& a, Point const& window) override;
    bool rotateRight(std::vector<std::vector<bool>>& grid) override;
    bool rotateLeft(std::vector<std::vector<bool>>& grid) override;
};

// Z
class Cleveland : public Tetrimino {
public:
    Cleveland(Point a);
    ~Cleveland() = default;
    bool create(Point const& a, Point const& window) override;
    bool rotateRight(std::vector<std::vector<bool>>& grid) override;
    bool rotateLeft(std::vector<std::vector<bool>>& grid) override;
};

// L
class OrangeRicky : public Tetrimino {
public:
    OrangeRicky(Point a);
    ~OrangeRicky() = default;
    bool create(Point const& a, Point const& window) override;
    bool rotateRight(std::vector<std::vector<bool>>& grid) override;
    bool rotateLeft(std::vector<std::vector<bool>>& grid) override;
};

// J
class BlueRicky : public Tetrimino {
public:
    BlueRicky(Point a);
    ~BlueRicky() = default;
    bool create(Point const& a, Point const& window) override;
    bool rotateRight(std::vector<std::vector<bool>>& grid) override;
    bool rotateLeft(std::vector<std::vector<bool>>& grid) override;
};

class Tetris {
public:
    Tetris();
    static constexpr int SIZE_BLOCK = 8; // pixels
    static constexpr int FACTOR = 3;
    static constexpr int STEP = SIZE_BLOCK * FACTOR;
    std::vector<std::vector<bool>> m_grid;
    std::vector<std::unique_ptr<Tetrimino>> m_tetriminos;
    void add(std::unique_ptr<Tetrimino> tetrimino);
    Tetrimino& current();
  
    void updateGrid();
    std::unique_ptr<Tetrimino> block(Type type);
    std::unique_ptr<Tetrimino> block();

private:
    Point m_window = Point{240, 480};
    void buildGrid();
    
};