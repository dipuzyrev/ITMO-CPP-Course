#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

// 100 40 0.001 2
double func1(double x) {
    return - x * log(x);
}

// 100 40 1 20
double func2(double x) {
    return sqrt(x);
}

// 100 40 -1 1
double func3(double x) {
    return -x * x - 0.5;
}

int main() {
    std::ofstream fout("graph1.txt");

    int n, m;
    double x0, x1;
    
    std::cout << "Enter columns number (m): ";
    std::cin >> m;

    std::cout << "Enter rows number (n): ";
    std::cin >> n;

    std::cout << "Enter variable (x0): ";
    std::cin >> x0;

    std::cout << "Enter variable (x1): ";
    std::cin >> x1;
    
    vector<double> columns(m);
    vector<vector<char>> graph(n + 1, vector<char>(m, ' '));
    
    double init_value = func2(x0);
    double min = init_value;
    double max = init_value;
    int zero_axis;
    
    // 1. для каждого столбца находим значение функции
    
    for (int i = 0; i < m; i++) {
        double x = x0 + (((x1 - x0) / m) * i);
        double y = func2(x);
        columns[i] = y;
        
        if (y > max) {
            max = y;
        }
        
        if (y < min) {
            min = y;
        }
    }
    
//    std::cout << std::endl << "Cols:" << std::endl;
//    for (int i = 0; i < m; i++) {
//        std::cout << columns[i] << ", ";
//    }
    
    // 2. на основе определенных минимумов/максимов находим кол-во решеток на будущем графике (+-)
    
    for (int i = 0; i < m; i++) {
        double sharps_count = ((columns[i] - min) * n) / (max - min);
        
        columns[i] = sharps_count;
    }
    
//    std::cout << std::endl << "###:" << std::endl;
//    for (int i = 0; i < m; i++) {
//        std::cout << columns[i] << ", ";
//    }
    
    // 3. находим положение оси X на будущем графике
    
    if (max < 0) {
        zero_axis = 0;
    } else if (min > 0) {
        zero_axis = n - 1;
    } else {
        zero_axis = round(max / (max - min) * n) - 1;
    }
    
//    std::cout << std::endl << "Zero:" << std::endl;
//    std::cout << zero_axis;
    
    // 4. строим гафик
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int y = zero_axis - i;
            
            if (y == 0) {
                graph[i][j] = '-';
            } else if ((y > 0) && (y <= columns[j])) {
                graph[i][j] = '#';
            } else if ((y < 0) && (y >= columns[j])) {
                graph[i][j] = '#';
            }
        }
    }
    
    // 5. выводим график в файл
    
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < m; ++j) {
            fout << graph[i][j];
        }
        fout << '\n';
    }
    
    return 0;
}
