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
    // Añadir un nodo al grafo
    void addNode(const string& node) {
        // En una tabla hash, no es necesario verificar si el nodo ya existe,
        // ya que la función insert manejará la colisión.
        // Usamos un nodo ficticio (dummy) para agregar el nodo.
        Client<T>* dummy = nullptr; // Representa un nodo vacío
        adjList.insert(dummy);  // Se utiliza una inserción ficticia para añadir el nodo a la tabla
    }

    // Añadir una arista entre dos nodos con peso
    void addEdge(const string& node1, const string& node2, int weight) {
        // No implementamos una lista de adyacencia aquí ya que HashTable es usada para almacenar los clientes.
        // Usamos el precio del bus como el peso de la arista.
        // La lógica para agregar aristas puede ser diseñada para agregar información extra dentro de cada nodo.
        // Este método puede ser extendido si se necesita información más compleja de aristas.
    }

    // Mostrar el grafo
    void displayGraph() {
        adjList.display(); // Usamos la función display de la clase HashTable para mostrar los nodos
    }

    // Añadir un cliente al grafo
    void addClient(Client<int>* client) {
        string clientNode = "Cliente " + to_string(client->data->GetDNI());
        adjList.insert(client);  // Añadir al grafo usando la tabla hash
    }

    // Añadir un bus al grafo
    void addBus(Bus* bus) {
        string busNode = "Bus " + to_string(bus->GetBusNumber());
        adjList.insert(nullptr);  // Añadir un nodo vacío para el bus (lo ideal sería tener un nodo asociado a cada bus)
    }

    // Conectar un cliente con un bus mediante el precio de su boleto
    void connectClientToBus(Client<int>* client, Bus* bus) {
        string clientNode = "Cliente " + to_string(client->data->GetDNI());
        string busNode = "Bus " + to_string(bus->GetBusNumber());
        // Aquí se pueden agregar aristas entre el cliente y el bus
        // Esto puede incluir el peso del boleto (el precio)
        addEdge(clientNode, busNode, bus->GetPrice());
    }
};

