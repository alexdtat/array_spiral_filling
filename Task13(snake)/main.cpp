#include <iostream>
#include <iomanip>

using namespace std;

int main() {

    int dx[4] = {1, 0, -1, 0}; // current shift
    int dy[4] = {0, 1, 0, -1}; // depending on the direction (mod 4)

    int direction = -1; // current direction

    int x_coord = 0; // current coordinates
    int y_coord = 0;

    int n, m; // field (array) sizes
    int counter = 0; // current number

    cin >> n >> m;

    int **array = new int*[n];
    for (int i = 0; i < n; i++){
        array[i] = new int[m];
    }

    bool **was_changed = new bool*[n + 2]; // array with field boundaries and passed elements
    for (int i = 0; i < n + 2; i++){
        was_changed[i] = new bool[m + 2];
    }

    for (int i = 0; i < n + 2; i++){
        for (int j = 0; j < m + 2; j++){
            if ((i > 0) && (j > 0) && (i <= n) && (j <= m)) was_changed[i][j] = 0;
            else was_changed[i][j] = 1;
        }
    }

    /* We fill the array up to the number n * m. If the next element in the current direction
     * is out of bounds or has already been changed previously, the direction is changed.
     * Further, the coordinates change with a shift depending on the current direction. */

    while (counter < n * m){
        if (m == 1) direction = 0; // Degenerate case in which the direction changes twice.
        if (was_changed[y_coord + dy[direction % 4] + 1][x_coord + dx[direction % 4] + 1] == 1) direction++;
        array[y_coord][x_coord] = ++counter;
        was_changed[y_coord + 1][x_coord + 1] = 1;
        x_coord += dx[direction % 4];
        y_coord += dy[direction % 4];
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cout << setw(4) << array[i][j];
        }
        cout << '\n';
    }

    for (int i = 0; i < n; i++){
        delete [] array[i];
    }
    delete [] array;

    for (int i = 0; i < n + 2; i++){
        delete [] was_changed[i];
    }
    delete [] was_changed;

    return 0;
}