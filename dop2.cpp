//Граф представлен в виде списка смежности. Реализовать обход в ширину, используя очередь, и нерекурсивный обход в глубину.
#include <iostream>   
#include <fstream>    
#include <vector>     
#include <queue>      
#include <stack>      
#include <algorithm>  
#include <string>
using namespace std;

vector<vector<int>> input() {// Функция для чтения графа из файла
    ifstream in("input.txt");  
    vector<vector<int>> vec;  
    string str;               

    while (getline(in, str)) {// Читаем файл
        vec.push_back(vector<int>()); 
        size_t pos_start = 0;          
        size_t pos_end;                
        do {
            pos_end = str.find(' ', pos_start);  // Пробел - разделитель между числами
            string num_str = str.substr(pos_start, pos_end - pos_start);
            if (!num_str.empty()) {
                vec.back().push_back(stoi(num_str)); 
            }
            pos_start = pos_end + 1;
        } while (pos_end != string::npos);
    }

    return vec;  // Возвращаем заполненный граф
}


void print(const vector<vector<int>>& vec) {// Функция для печати графа
    for (size_t i = 0; i < vec.size(); i++) {
        cout << i << ": "; 
        for (size_t j = 0; j < vec[i].size(); j++) {
            cout << vec[i][j] << " "; 
        }
        cout << endl;
    }
}

void bfs(const vector<vector<int>>& vec, int start) {// Обход в ширину (BFS)
    vector<bool> visited(vec.size(), false);  // Массив посещенных вершин
    queue<int> q;  

    q.push(start);
    visited[start] = true;

    cout << "BFS traversal: ";
    while (!q.empty()) {
        int current = q.front();
        q.pop(); 
        cout << current << " ";  
        for (int neighbor : vec[current]) { // Перебираем всех соседей текущей вершины
            if (!visited[neighbor]) {  // Если сосед не посещен
                visited[neighbor] = true;  // Помечаем как посещенный
                q.push(neighbor);  // Добавляем в очередь для дальнейшего обхода
            }
        }
    }
    cout << endl;
}

void dfs(const vector<vector<int>>& vec, int start) {// Нерекурсивный обход в глубину (DFS)
    vector<bool> visited(vec.size(), false);  // Массив посещенных вершин
    stack<int> s; 

    s.push(start);
    visited[start] = true;

    cout << "DFS traversal: ";
    while (!s.empty()) {
        int current = s.top(); 
        s.pop(); 
        cout << current << " ";  
        for (auto it = vec[current].rbegin(); it != vec[current].rend(); ++it) { // Чтобы сохранить порядок как в рекурсивном DFS, добавляем соседей в обратном порядке
            int neighbor = *it;
            if (!visited[neighbor]) {  // Если сосед не посещен
                visited[neighbor] = true;  // Помечаем как посещенный
                s.push(neighbor);  // Добавляем в стек для дальнейшего обхода
            }
        }
    }
    cout << endl;
}

int main() {
    vector<vector<int>> vec = input();

    cout << "Initial graph:" << endl;
    print(vec);

    bfs(vec, 2);  // Обход в ширину 
    dfs(vec, 2);  // Обход в глубину 
    
    return 0;  
}
/*ПРИМЕР ФАЙЛА input.txt
1 2
0 3 4
0 5
1
1 5
2 4
*/