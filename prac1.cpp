#include <iostream>
using namespace std;
class Stack
{
    int *body;
    int top;
    int size;

public:
    Stack(int new_size)
    {
        body = new int[new_size];
        size = new_size;
        top = -1;
    }
    ~Stack() { delete[] body; }

    bool isEmpty() { return top == -1; }
    bool isFull() { return top == size - 1; }

    void push(int new_elem)
    {
        if (isFull())
        {
            throw "Stack overflow!";
        }
        top++;
        body[top] = new_elem;
    }
    int pop()
    {
        if (isEmpty())
        {
            throw "Stack underflow!";
        }
        int tmp = body[top];
        top--;
        return tmp;
    }
    int elem_top()
    {
        if (isEmpty())
        {
            throw "Stack is empty!";
        }
        return body[top];
    }
};

#define ROW 10
#define COL 10

int maze[ROW][COL] = {0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
                      1, 0, 0, 0, 0, 1, 0, 0, 1, 0,
                      0, 0, 0, 1, 1, 1, 0, 0, 1, 1,
                      0, 1, 0, 0, 0, 1, 0, 0, 1, 0,
                      0, 0, 0, 0, 1, 1, 1, 0, 1, 0,
                      0, 0, 1, 1, 1, 0, 1, 0, 0, 0,
                      0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
                      1, 1, 0, 1, 0, 0, 1, 1, 1, 0,
                      0, 1, 0, 0, 0, 0, 1, 0, 0, 0,
                      0, 1, 0, 0, 0, 0, 1, 0, 0, 0};
bool isValid(int x, int y)
{
    return (x >= 0 && y >= 0 && x <= ROW && y <= COL);
}
bool find_dfs(int row, int col, int endRow, int endCol, bool visited[][COL], Stack &path)
{
    if (!isValid(row, col))
        return false;
    if (maze[row][col] == 1 || visited[row][col])
    {
        return false;
    }
    visited[row][col] = true;
    path.push(row * COL + col); // записываем координаты текущего квадрата в стек
    if (row == endRow && col == endCol)
    {
        return true; // мы достигли конечной точки
    }

    // dfs
    if (find_dfs(row - 1, col, endRow, endCol, visited, path))
    {
        return true;
    }
    if (find_dfs(row + 1, col, endRow, endCol, visited, path))
    {
        return true;
    }
    if (find_dfs(row, col - 1, endRow, endCol, visited, path))
    {
        return true;
    }
    if (find_dfs(row, col + 1, endRow, endCol, visited, path))
    {
        return true;
    }
    path.pop();
    return false;
}

void printPath(Stack &path)
{
    cout << "Path: ";
    while (!path.isEmpty())
    {
        int square = path.pop();
        int row = square / COL;
        int col = square % COL;
        cout << '(' << row << ", " << col << ')' << endl;
    }
}

int main()
{
    int startRow, startCol, endRow, endCol;
    cout << "Enter starting row and column: ";
    cin >> startRow >> startCol;
    cout << "Enter ending row and column: ";
    cin >> endRow >> endCol;

    bool visited[ROW][COL] = {false}; // массив для отслеживания посещенных квадратов
    Stack path(ROW * COL);
    if (find_dfs(startRow, startCol, endRow, endCol, visited, path))
    {
        printPath(path);
    }
    else
    {
        cout << "No path found." << endl;
    }
    return 0;
}
