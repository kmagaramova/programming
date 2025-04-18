#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Структура для хранения координат клетки на шахматной доске
struct Cell {
    int x, y; // x - номер столбца (0..7), y - номер строки (0..7)
    Cell(int x = 0, int y = 0) : x(x), y(y) {}

    // Перегрузка оператора сравнения для использования в map
    bool operator==(const Cell& other) const {
        return x == other.x && y == other.y;
    }
    bool operator<(const Cell& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

// Функция преобразования шахматной нотации (например, "A2") в координаты Cell
Cell parseCell(const string& s) {
    if (s.size() < 2) return Cell(-1, -1); // Некорректный ввод

    char col = toupper(s[0]); // Буква столбца (A-H)
    char row = s[1];          // Цифра строки (1-8)

    // Преобразование буквы в число (A=0, B=1, ..., H=7)
    int x = col - 'A';
    // Преобразование цифры в число (1=0, 2=1, ..., 8=7)
    int y = row - '1';

    // Проверка, что координаты в пределах доски
    if (x < 0 || x >= 8 || y < 0 || y >= 8) return Cell(-1, -1);

    return Cell(x, y);
}

// Функция преобразования координат Cell в шахматную нотацию
string cellToString(const Cell& c) {
    string s;
    s += char('A' + c.x); // Преобразование x в букву
    s += char('1' + c.y); // Преобразование y в цифру
    return s;
}

// Возможные направления хода коня (8 вариантов)
const int dx[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
const int dy[] = { 1, 2, 2, 1, -1, -2, -2, -1 };

// Функция поиска кратчайшего пути коня между двумя клетками
vector<Cell> findShortestPath(Cell start, Cell end) {
    // Проверка на корректность входных данных
    if (start.x == -1 || start.y == -1 || end.x == -1 || end.y == -1) {
        return {}; // Возвращаем пустой вектор, если клетки некорректны
    }

    // Очередь для BFS (поиска в ширину)
    queue<Cell> q;
    // Словарь для хранения родительских клеток (чтобы восстанавливать путь)
    map<Cell, Cell> parent;

    q.push(start); // Добавляем начальную клетку в очередь
    parent[start] = Cell(-1, -1); // Маркируем начало пути

    // Основной цикл BFS
    while (!q.empty()) {
        Cell current = q.front(); // Берем первую клетку из очереди
        q.pop();

        if (current == end) {
            break; // Если достигли конечной клетки, выходим из цикла
        }

        // Проверяем все 8 возможных ходов коня
        for (int i = 0; i < 8; ++i) {
            Cell next(current.x + dx[i], current.y + dy[i]); // Вычисляем следующую клетку

            // Проверяем, что клетка в пределах доски и еще не посещалась
            if (next.x >= 0 && next.x < 8 && next.y >= 0 && next.y < 8) {
                if (parent.find(next) == parent.end()) {
                    parent[next] = current; // Запоминаем родителя
                    q.push(next);          // Добавляем в очередь для дальнейшего исследования
                }
            }
        }
    }

    // Восстановление пути от конечной клетки к начальной
    vector<Cell> path;
    if (parent.find(end) == parent.end()) {
        return {}; // Если путь не найден, возвращаем пустой вектор
    }

    // Идем от конца к началу, записывая клетки
    Cell current = end;
    while (!(current == start)) {
        path.push_back(current);
        current = parent[current]; // Переходим к родительской клетке
    }
    path.push_back(start); // Добавляем начальную клетку

    // Разворачиваем путь, чтобы он шел от начала к концу
    reverse(path.begin(), path.end());

    return path;
}

int main() {
    string startStr, endStr;

    // Ввод начальной и конечной клеток
    cout << "Введите начальную клетку (например, A2): ";
    cin >> startStr;
    cout << "Введите конечную клетку (например, E6): ";
    cin >> endStr;

    // Преобразование в координаты
    Cell start = parseCell(startStr);
    Cell end = parseCell(endStr);

    // Проверка корректности ввода
    if (start.x == -1 || start.y == -1 || end.x == -1 || end.y == -1) {
        cout << "Некорректный ввод клеток!" << endl;
        return 1;
    }

    // Поиск пути
    vector<Cell> path = findShortestPath(start, end);

    // Вывод результата
    if (path.empty()) {
        cout << "Путь не найден!" << endl;
    }
    else {
        cout << "Кратчайший путь коня: ";
        for (size_t i = 0; i < path.size(); ++i) {
            if (i != 0) cout << " ";
            cout << cellToString(path[i]);
        }
        cout << endl;
    }

    return 0;
}