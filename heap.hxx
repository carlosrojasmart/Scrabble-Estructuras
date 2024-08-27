#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

// Función para intercambiar dos elementos en un vector
template <typename T>
void swap(vector<T>& v, int a, int b) {
  T temp = v[a];
  v[a] = v[b];
  v[b] = temp;
}

// Función para eliminar los ceros a la izquierda de un número entero
template <typename T>
T removeLeadingZeros(T value) {
   if (value == 0) {
       return value;
   }
   while (value % 10 == 0) {
       value /= 10;
   }
   return value;
}

// Función para medir el tiempo de ejecución de una función
template <typename Func, typename... Args>
double measureExecutionTime(Func func, Args... args) {
  auto start = std::chrono::high_resolution_clock::now();
  func(args...);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;
  return duration.count();
}

// Clase para representar un montículo
template <typename T>
class Heap {
  private:
    vector<T> data; // Vector para almacenar los datos del montículo
    bool isMaxHeap; // Indica si el montículo es un máximo o un mínimo

  public:
    // Constructor del montículo
    Heap(bool isMaxHeap = true) {
      this->isMaxHeap = isMaxHeap;
    }

    // Función para insertar un elemento en el montículo
    void insert(T value) {
        data.push_back(value);
        heapifyUp(data.size() - 1);
    }

    // Función para insertar un elemento inverso en el montículo

    void insertWordReverse(const string& word) {
      for (int i = word.size() - 1; i >= 0; --i) {
        insert_R(string(1, word[i]));
      }
    }

    //Funcion para insertar un elemento R en el monticulo
    void insert_R(const T& value) {
      insertWordReverse(value);
      heapifyUp(data.size() - 1);
    }

    // Función para eliminar el elemento superior del montículo
    T extractTop() {
        if (isEmpty()) {
            return T();
        }
        T top = data[0];
        swap(data, 0, data.size() - 1);
        data.pop_back();
        heapifyDown(0);
        return top;
    }

  //funcion para organizar el monticulo
  void sortHeap(Heap<T>& sortedHeap) {
    while (!isEmpty()) {
      sortedHeap.insert(extractTop());
    }
  }

    // Función para obtener el elemento superior del montículo
    T top() {
      if (isEmpty()) {
        return T();
      }
      return data[0];
    }

    // Función para verificar si el montículo está vacío
    bool isEmpty() {
      return data.empty();
    }

    //funcion para imprimir el monticulo
    void imprimir(const Heap<T>& heap) {
    if (isEmpty()) {
        cout << "El monticulo esta vacio." << endl;
        return;
    }
    cout << "Heap elements:" << endl;
    for (const T& element : data) {
        cout << element << " ";
    }
    cout << endl;
    }

    // Funcion palabras por prefijo
    void prefijo(const string& prefix) const {
      for (const T& word : data) {
        if (word.find(prefix) == 0) {
          cout << word << " ";
        }
      }
        cout << endl;
    }

    // Funcion palabras por sufijo
    void subfijo(const string& suffix) const {
    for (const T& word : data) {
        size_t pos = word.rfind(suffix);
        if (pos != string::npos && pos == word.size() - suffix.size()) {
            cout << word << " ";
        }
    }
    cout << endl;
}


  private:
    // Función para reordenar el montículo después de insertar un elemento
    void heapifyUp(int index) {
      if (index == 0) {
        return;
      }
    int parent = (index - 1) / 2;
      if (isMaxHeap ? data[index] < data[parent] : data[index] > data[parent]) {
        swap(data, index, parent);
        heapifyUp(parent);
      }
    }

    // Función para reordenar el montículo después de eliminar un elemento
    void heapifyDown(int index) {
      int left = 2 * index + 1;
      int right = 2 * index + 2;
      int smallest = index;
        if (left < data.size() && (isMaxHeap ? data[left] < data[smallest] : data[left] > data[smallest])) {
          smallest = left;
        }
        if (right < data.size() && (isMaxHeap ? data[right] < data[smallest] : data[right] > data[smallest])) {
          smallest = right;
        }
    if (smallest != index) {
        swap(data, index, smallest);
        heapifyDown(smallest);
      }
    }
};
