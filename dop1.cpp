#include <iostream>
using namespace std;

struct stack {
    char inf;
    stack* next;
};

void push(stack*& h, char x) {
    stack* r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

char pop(stack*& h) {
    char i = h->inf;
    stack* r = h;
    h = h->next;
    delete r;
    return i;
}

bool isEmpty(stack* h) {
    return h == nullptr;
}

char top(stack* h) {
    return h->inf;
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Разворот строки (работает с динамической памятью)
void reverseString(char* str, int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        swap(str[start], str[end]);
        start++;
        end--;
    }
}

// Преобразование инфиксной записи в префиксную (с динамической памятью)
void infixToPrefix(char* infix, char*& prefix, int maxSize) {
    stack* opStack = nullptr;
    stack* operandStack = nullptr;
    int prefixIndex = 0;
    int len = 0;

    // Вычисляем длину строки
    while (infix[len] != '\0') len++;

    // Разворачиваем инфиксное выражение
    reverseString(infix, len);

    for (int i = 0; i < len; i++) {
        if (infix[i] == ' ') continue;

        if (infix[i] == ')') {
            push(opStack, infix[i]);
        }
        else if (infix[i] == '(') {
            while (!isEmpty(opStack) && top(opStack) != ')') {
                push(operandStack, pop(opStack));
            }
            pop(opStack); // удаляем ')'
        }
        else if (isOperator(infix[i])) {
            while (!isEmpty(opStack) && precedence(top(opStack)) > precedence(infix[i])) {
                push(operandStack, pop(opStack));
            }
            push(opStack, infix[i]);
        }
        else { // операнд
            push(operandStack, infix[i]);
        }
    }

    // Выталкиваем оставшиеся операторы
    while (!isEmpty(opStack)) {
        push(operandStack, pop(opStack));
    }

    // Формируем префиксную строку
    while (!isEmpty(operandStack)) {
        if (prefixIndex >= maxSize - 1) {
            cout << "Ошибка: переполнение буфера!" << endl;
            break;
        }
        prefix[prefixIndex++] = pop(operandStack);
    }
    prefix[prefixIndex] = '\0';
}

int main() {
    setlocale(LC_ALL , "Russian");
    const int MAX_SIZE = 256; // Максимальный размер выражения
    char* infix = new char[MAX_SIZE];
    char* prefix = new char[MAX_SIZE];

    cout << "Введите инфиксное выражение: ";
    cin.getline(infix, MAX_SIZE);

    infixToPrefix(infix, prefix, MAX_SIZE);

    cout << "Префиксная форма: " << prefix << endl;

    // Освобождаем память
    delete[] infix;
    delete[] prefix;

    return 0;
}