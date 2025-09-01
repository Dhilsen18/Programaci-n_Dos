#pragma once
#include <vector>
#include <iostream>
#include <algorithm>  // Para std::swap
#include <conio.h>    // Para _getch()

template <typename T>
class Node {
public:
    T data;
    Node* next;

    // Constructor por defecto
    Node() : data(T()), next(nullptr) {}

    // Constructor con valor
    Node(T data) : data(data), next(nullptr) {}
};

template <typename T>
class BusInfo {
private:
    Node<T>* head;  // Cabeza de la lista

public:
    BusInfo() : head(nullptr) {}

    ~BusInfo() {
        Node<T>* temp = head;
        while (temp != nullptr) {
            Node<T>* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
    }
    std::vector<T> getBusesAsVector() const {
        return toVector();  // Utiliza la función toVector que convierte la lista enlazada en un vector
    }
    // Método para agregar un nuevo autobús al final de la lista
    void addBus(const T& bus) {
        Node<T>* newNode = new Node<T>(bus);
        if (!head) {
            head = newNode;
        }
        else {
            Node<T>* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Método para mostrar todos los autobuses en la lista
    void showBuses() const {
        if (!head) {
            return;
        }
        Node<T>* temp = head;
        int i = 1;
        while (temp != nullptr) {
            Console::SetCursorPosition(42, 12);
            Console::ForegroundColor = ConsoleColor::DarkMagenta;
            cout << "Bus - " << i;
            temp->data.ShowBus();
            _getch();
            i++;
            temp = temp->next;
        }
    }

    // Método para buscar un autobús por número
    T* searchBus(int busNumber) const {
        Node<T>* temp = head;
        while (temp != nullptr) {
            if (temp->data.GetBusNumber() == busNumber) {
                return &temp->data;
            }
            temp = temp->next;
        }
        return nullptr;  // No se encontró el autobús
    }

    // Método para ordenar los buses por número de bus usando BubbleSort
    void sortBuses() {
        if (!head || !head->next) return; // No hace falta ordenar si hay 0 o 1 buses

        bool swapped;
        Node<T>* ptr1;
        Node<T>* lptr = nullptr;

        do {
            swapped = false;
            ptr1 = head;

            while (ptr1->next != lptr) {
                if (ptr1->data.GetBusNumber() > ptr1->next->data.GetBusNumber()) {
                    std::swap(ptr1->data, ptr1->next->data);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;  // El último nodo ya está ordenado
        } while (swapped);
    }

    // Método para convertir la lista enlazada a un vector
    std::vector<T> toVector() const {
        std::vector<T> result;
        Node<T>* temp = head;
        while (temp != nullptr) {
            result.push_back(temp->data);
            temp = temp->next;
        }
        return result;
    }

    // Método para actualizar la lista enlazada desde un vector
    void fromVector(const std::vector<T>& vec) {
        Node<T>* temp = head;
        int index = 0;
        while (temp != nullptr && index < vec.size()) {
            temp->data = vec[index];
            temp = temp->next;
            index++;
        }
    }

    // Método para ordenar usando QuickSort en un vector temporal
    template <typename Compare>
    void sortBusesWithQuickSort(Compare comp) {
        if (!head || !head->next) return;

        // Convertir lista enlazada a vector
        std::vector<T> vec = toVector();

        // Ordenar el vector usando QuickSort
        quickSort(vec, 0, vec.size() - 1, comp);

        // Actualizar la lista enlazada desde el vector ordenado
        fromVector(vec);
    }

    // Método para obtener el tamaño de la lista
    int size() const {
        int count = 0;
        Node<T>* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }
};

// Función partition para Quick Sort
template <typename T, typename Compare>
int partition(std::vector<T>& arr, int low, int high, Compare comp) {
    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (comp(arr[j], pivot)) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Función Quick Sort - Ordenamiento Avanzado
template <typename T, typename Compare>
void quickSort(std::vector<T>& arr, int low, int high, Compare comp) {
    if (low < high) {
        int pi = partition(arr, low, high, comp);
        quickSort(arr, low, pi - 1, comp);
        quickSort(arr, pi + 1, high, comp);
    }
}
