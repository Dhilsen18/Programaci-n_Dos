#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Client.h"
#include "Bus.h"
#include "HashTable.h"

using namespace std;

template <typename T>

class Graph {
private:
    HashTable<string> adjList; // Usamos HashTable para almacenar los nodos y sus aristas (clientes y buses)

public:
    // A�adir un nodo al grafo
    void addNode(const string& node) {
        // En una tabla hash, no es necesario verificar si el nodo ya existe,
        // ya que la funci�n insert manejar� la colisi�n.
        // Usamos un nodo ficticio (dummy) para agregar el nodo.
        Client<T>* dummy = nullptr; // Representa un nodo vac�o
        adjList.insert(dummy);  // Se utiliza una inserci�n ficticia para a�adir el nodo a la tabla
    }

    // A�adir una arista entre dos nodos con peso
    void addEdge(const string& node1, const string& node2, int weight) {
        // No implementamos una lista de adyacencia aqu� ya que HashTable es usada para almacenar los clientes.
        // Usamos el precio del bus como el peso de la arista.
        // La l�gica para agregar aristas puede ser dise�ada para agregar informaci�n extra dentro de cada nodo.
        // Este m�todo puede ser extendido si se necesita informaci�n m�s compleja de aristas.
    }

    // Mostrar el grafo
    void displayGraph() {
        adjList.display(); // Usamos la funci�n display de la clase HashTable para mostrar los nodos
    }

    // A�adir un cliente al grafo
    void addClient(Client<int>* client) {
        string clientNode = "Cliente " + to_string(client->data->GetDNI());
        adjList.insert(client);  // A�adir al grafo usando la tabla hash
    }

    // A�adir un bus al grafo
    void addBus(Bus* bus) {
        string busNode = "Bus " + to_string(bus->GetBusNumber());
        adjList.insert(nullptr);  // A�adir un nodo vac�o para el bus (lo ideal ser�a tener un nodo asociado a cada bus)
    }

    // Conectar un cliente con un bus mediante el precio de su boleto
    void connectClientToBus(Client<int>* client, Bus* bus) {
        string clientNode = "Cliente " + to_string(client->data->GetDNI());
        string busNode = "Bus " + to_string(bus->GetBusNumber());
        // Aqu� se pueden agregar aristas entre el cliente y el bus
        // Esto puede incluir el peso del boleto (el precio)
        addEdge(clientNode, busNode, bus->GetPrice());
    }
};

