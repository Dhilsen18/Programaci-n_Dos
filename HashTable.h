#pragma once
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include "Client.h"
#include"Menu.h"
using namespace std;

template <typename T>
class HashTable {
private:
    static const int TABLE_SIZE = 100; // Tamaño fijo de la tabla hash
    vector<list<Client<T>*>> table; // Vector de listas enlazadas para manejar colisiones

    // Función hash 
    int hashFunction(const string& key) const {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % TABLE_SIZE; // Algoritmo de hash básico
        }
        return hash;
    }
    Menu* menu;
public:
    // Constructor
    HashTable() : table(TABLE_SIZE) {
        menu = new Menu();
    }

    // Insertar un cliente en la tabla
    void insert(Client<T>* client) {
        string key = client->GetUser();
        int index = hashFunction(key);
        table[index].push_back(client);
    }

    // Buscar un cliente por nombre de usuario
    Client<T>* search(const string& user) {
        int index = hashFunction(user);
        for (Client<T>* client : table[index]) {
            if (client->GetUser() == user) {
                return client;
            }
        }
        return nullptr; // Cliente no encontrado
    }

    // Eliminar un cliente
    void remove(const string& user) {
        int index = hashFunction(user);
        auto& chain = table[index];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if ((*it)->GetUser() == user) {
                chain.erase(it);
                break;
            }
        }
    }

    // Mostrar contenido de la tabla hash
    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (!table[i].empty()) {
                cout << "Index " << i << ": ";
                for (Client<T>* client : table[i]) {
                    cout << client->GetUser() << " ";
                }
                cout << endl;
            }
        }
    }

    // Función para pedir una clave y mostrar el cliente
    void showClientInfo() {
        menu->Fondo();
        menu->Logo();
        Console::ForegroundColor = ConsoleColor::White;
        Console::SetCursorPosition(42, 12);
        string user;
        cout << "Ingrese el nombre de usuario para buscar: ";
        cin >> user;

        Client<T>* client = search(user);
        if (client != nullptr) {
            Console::ForegroundColor = ConsoleColor::DarkGreen;
            // Si se encuentra el cliente, muestra su información
            Console::SetCursorPosition(42, 14);
            cout << "Cliente encontrado: " << endl;
            client->ShowData(); // Mostrar la información del cliente utilizando ToString
            _getch();
        }
        else {
            // Si el cliente no se encuentra
            Console::ForegroundColor = ConsoleColor::DarkRed;
            Console::SetCursorPosition(42, 14);
            cout << "Cliente no encontrado." << endl;
            _getch();
        }
    }
};
