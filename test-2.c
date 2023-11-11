#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Размер игрового поля
#define SIZE_Y 15 // Кол-во клеток по вертикали
#define SIZE_Z 15 // Кол-во клеток по горизонтали

// Функция для генерации игрового поля
void init_board(int board[]) {
    for (int i = 0; i < SIZE_Y * SIZE_Z; i++) {
        board[i] = rand() % 2; // // случайно заполняем клетки значением 0(пустые клетки) или 1(живые клетки)
    }
}

// Функция для отображения сгенерированного поля
void print_board(int board[]) {
    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_Z; j++) {
            if (board[i * SIZE_Z + j] == 1) {
                printf("+ "); // отображаем живые клетки символом "+", "пробел" для доп.расстояния между клеток
            } else {
                printf("- "); // отображаем мертвые клетки символом "-", "пробел" для доп.расстояния между клеток
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Функция для проверки соседних клеток
int count_neighbors(int board[], int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // Пропускаем текущую клетку, при 0
            int nRow = row + i;
            int nCol = col + j;
            // Проверяем, чтобы соседняя клетка не выходила за границы поля
            if (nRow >= 0 && nRow < SIZE_Y && nCol >= 0 && nCol < SIZE_Z) {
                if (board[nRow * SIZE_Z + nCol] == 1) {
                    count++;
                }
            }
        }
    }
    return count;
}

// Функция для обновления состояния клеток на игровом поле реализация правил самой игры
void update_board(int board[]) {
    int new_board[SIZE_Y * SIZE_Z];
    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_Z; j++) {
            int neighbors = count_neighbors(board, i, j);
            if (board[i * SIZE_Z + j] == 1) {
                if (neighbors < 2 || neighbors > 3) {
                    new_board[i * SIZE_Z + j] = 0; // Мертвая клетка из-за отсутствия соседей или наоборот, перенаселения вокруг
                } else {
                    new_board[i * SIZE_Z + j] = 1; // Или же клетка останется живой
                }
            } else {
                if (neighbors == 3) {
                    new_board[i * SIZE_Z + j] = 1; // Рождение новой клетки, при трёх живых соседях
                } else {
                    new_board[i * SIZE_Z + j] = 0; // Или же клетка остается мертвой
                }
            }
        }
    }
    // Копируем новое сгенерированное поле в изначальное, тем самым обновляя его
    for (int i = 0; i < SIZE_Y * SIZE_Z; i++) {
        board[i] = new_board[i];
    }
}

int main() {
    int board[SIZE_Y * SIZE_Z];
    srand(time(NULL)); // Задаём генератор случайных чисел

    init_board(board); // Генерируем игровое поле
    print_board(board); // Выводим начальное состояние поля

    for (int generation = 0; generation < 27; generation++) { // Можно задать n-ое кол-во игровых дней
        update_board(board); // Обновляем состояние игрового поля
        print_board(board); // Выводим обновленное состояние поля
    }
    getchar(); // ПРИ НЕОБХОДИМОСТИ 
    //  system("pause"); ПРИ НЕОБХОДИМОСТИ, ЕСЛИ НЕ ПОМОГЛА КОМАНДА ВЫШЕ
    return 0;
}