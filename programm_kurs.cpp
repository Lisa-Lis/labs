#include <iostream> 

#include <fstream> 

#include <iomanip> 

 

using namespace std; 

 

class  tMatrix 

{ 

public: 

tMatrix(); 

tMatrix(int R, int C, int Low, int High); //генерация матрицы 

tMatrix(const char* FileName); 

~tMatrix(); 

void Create(int R, int C); 

void readFile(const char* fileName); // чтение матрицы из файла 

void writeFile(const char* fileName); // сохранение матрицы в файл 

void setShadedAreaParams(); // установить параметры заштрихованной области (значения I1, J1) 

float srArifm(); // Вычислить среднее арифметическое элементов матрицы 

void minMoreSr(); //определить среди элементов, расположенных в заштрихованной области, больше этого среднего арифметического,  

//минимальный элемент. 

void fillArray(); // сформировать упорядоченный одномерный массив из злементов незаштрихованной области 

private: 

int** data; // указатель на данные 

int rowCount; // число строк матрицы 

int colCount; // число столбцов матрицы 

// параметры заштрихованной области 

int I1; 

int J1; 

void printMatrix(); // вывод матрицы в консоль 

bool isShadedArea(int i, int j); // возврашяет true если элемент (i, j) находится в 

// заштрихованной области или false в противном случае 

}; 

void tMatrix::Create(int R, int C) { 

rowCount = R; colCount = C; 

data = new int* [rowCount]; 

for (int i = 0; i < rowCount; i++)data[i] = new int[colCount]; 

} 

tMatrix::tMatrix(int R, int C, int Low, int High) { 

Create(R, C); 

for (int i = 0; i < rowCount; i++) 

for (int j = 0; j < colCount; j++)data[i][j] = Low + rand() % (High - Low + 1); 

} 

tMatrix::tMatrix(const char* FileName) { 

ifstream F(FileName); 

F >> rowCount >> colCount; 

Create(rowCount, colCount); 

for (int i = 0; i < rowCount; i++) 

for (int j = 0; j < colCount; j++)F >> data[i][j]; 

F.close(); 

} 

 

tMatrix::~tMatrix() 

{ 

if (data != NULL) 

{ 

// освобождаем память 

for (int i = 0; i < rowCount; i++) 

delete[] data[i]; 

delete[] data; 

} 

} 

 

// чтение матрицы из файла 

void tMatrix::readFile(const char* fileName) 

{ 

ifstream fin(fileName); 

if (!fin.is_open()) 

{ 

cout << "Ошибка открытия файла" << endl; 

return; 

} 

// считываем из файла первые 2 значения - размер матрицы 

fin >> rowCount; 

fin >> colCount; 

// выделяем память под матрицу 

data = new int * [rowCount]; 

for (int i = 0; i < rowCount; i++) 

data[i] = new int[colCount]; 

// заполняем матрицу значениями из файла 

for (int i = 0; i < rowCount; i++) 

{ 

for (int j = 0; j < colCount; j++) 

fin >> data[i][j]; 

} 

// закрываем файл 

fin.close(); 

cout << "Матрица размера " << rowCount << "x" << colCount << " считана из файла:" << endl; 

printMatrix(); // выводим матрицу в консоль 

} 

// сохранение матрицы в файл 

void tMatrix::writeFile(const char* fileName) 

{ 

ofstream fout(fileName); 

if (!fout.is_open()) 

{ 

cout << "Ошибка открытия файла" << endl; 

return; 

} 

// записываем в файл первые 2 значения - размер матрицы 

fout << rowCount << " "; 

fout << colCount << endl; 

// пишем в файл значения элементов матрицы 

for (int i = 0; i < rowCount; i++) 

{ 

for (int j = 0; j < colCount; j++) 

fout << data[i][j] << "\t"; 

fout << endl; 

} 

// закрываем файл 

fout.flush(); 

fout.close(); 

cout << "Матрица записана в файл" << endl; 

} 

// вывод матрицы в консоль 

void tMatrix::printMatrix() 

{ 

for (int i = 0; i < rowCount; i++) 

{ 

for (int j = 0; j < colCount; j++) 

cout << setw(6) << data[i][j]; 

cout << endl; 

} 

cout << endl; 

} 

// установить параметры заштрихованной области (значения I1, J1) 

void tMatrix::setShadedAreaParams() 

{ 

cout << "Введите параметры заштрихованной области:" << endl; 

cout << "I1 = "; cin >> I1; 

cout << "J1 = "; cin >> J1; 

} 

// проверка на попадание в заштрихованную область 

bool tMatrix::isShadedArea(int i, int j) 

{ 

return (rowCount - i <= I1) && (colCount - j <= J1); 

} 

 

//находим среднее арифметическое матрицы 

float tMatrix::srArifm() { 

float arifm = 0; 

for (int i = 0; i < rowCount; i++) 

for (int j = 0; j < colCount; j++) { 

arifm += data[i][j]; //ищем сумму всех элементов матрицы 

} 

arifm /= colCount * rowCount; //делим сумму на количество элементов  в матрице  

cout << "Среднее арифметическое матрицы: " << arifm << endl; 

return arifm; 

} 

 

//Находим минимальный элемент, больше среднего арифметического 

void tMatrix::minMoreSr() { 

float arifm = srArifm(); 

int min = data[rowCount -  1][colCount - 1]; //последний элемент матрицы 

for (int i = 0; i < rowCount; i++) { 

for (int j = 0; j < colCount; j++) { 

if (isShadedArea(i, j) && data[i][j] > arifm) {	//если элемент из заштрихованной области больше среднего арифметического		 

if (data[i][j] < min) { // ищем минимальный элемент 

min = data[i][j];				 

} 

}			 

}	 

} 

cout << "Минимальный элемент, больше среднего арифметического: " << min << endl; 

} 

// сформировать упорядоченный одномерный массив из злементов заштрихованной области 

void tMatrix::fillArray() 

{ 

// вычисляем размер массива 

int arrSize = I1 * J1; 

// выделяем память 

int* arr = new int[arrSize]; 

int c = 0; 

for (int i = 0; i < rowCount; i++) 

for (int j = 0; j < colCount; j++) 

if (isShadedArea(i, j)) // если элемент входит в заштрихованную область 

arr[c++] = data[i][j]; // добавляем его в массив 

// сортируем массив 

int tmp; // временная переменная для обмена элементов местами 

// сортировка массива пузырьком 

for (int i = 0; i < arrSize - 1; i++) 

{ 

for (int j = 0; j < arrSize - i - 1; j++) 

{ 

if (arr[j] > arr[j + 1]) 

{ 

// меняем элементы местами 

tmp = arr[j]; 

arr[j] = arr[j + 1]; 

arr[j + 1] = tmp; 

} 

} 

} 

cout << "Упорядоченный одномерный массив из злементов заштрихованной области:"<<endl; 

for (int i = 0; i < arrSize; i++) 

cout << arr[i] << " "; 

cout << endl << endl; 

// освобождаем память 

delete[] arr; 

} 

int main() 

{ 

setlocale(LC_ALL, "Russian"); 

// инициализируем матрицу значениями из файла (задание 1, ч.1) 

tMatrix* X = new tMatrix("matrix.txt"); 

X->readFile("matrix.txt"); 

// вводим параметры заштрихованной области 

X->setShadedAreaParams(); 

//Определяем минимальный элемент, матрицы больше среднего арифметического (Задание 2) 

X->minMoreSr();  

// формируем упорядоченный одномерный массив из злементов заштрихованной области (задание 3) 

X->fillArray(); 

// сохраняем матрицу в файл (задание 1, ч. 2) 

X->writeFile("matrix.txt"); 

system("Pause"); 

return 0; 

} 