#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "ClientDatabase.h"
#include <random>
#include <set>
#include <unordered_set>
#include"BusesData.h"
#include"Menu.h"
#include"HashTable.h"
#include "BST.hpp"
#define ARRIBA 72
#define ABAJO 80
#define DERECHA 77
#define IZQUIERDA 75

class Controller {
private:
	ClientDatabase<int>* database;
	Menu* menu;
	int option;
	int _option;
	char tecla;
	HashTable<int>* clientTable;
public:
	Controller() {
		srand(time(NULL));
		database = new ClientDatabase<int>();
		menu = new Menu();
		option = 1;
		_option = 1;
		clientTable = new HashTable<int>();// Tabla hash para los clientes
		vector<Client<int>*> clients = database->getAllClients(); 
		for (Client<int>* client : clients) {
			clientTable->insert(client);  // Inserta el cliente en la tabla hash
		}
	}
	~Controller() {
		delete database;
		delete clientTable;
	}
	void MainMenu() {
		bool refresh = true;
		menu->Fondo();  
		menu->Logo();   
		menu->Welcome(); 

		do {
			if (refresh) {  // Solo redibuja el menú si es necesario
				Console::ForegroundColor = ConsoleColor::White;
				Console::CursorVisible = false;

				// Muestra las opciones de menú en diferentes posiciones en la pantalla
				Console::SetCursorPosition(50, 14);
				cout << (option == 1 ? "   > REGISTRARSE <   " : "     REGISTRARSE     ");
				Console::SetCursorPosition(50, 16);
				cout << (option == 2 ? "  > INICIAR SESION < " : "    INICIAR SESION   ");
				Console::SetCursorPosition(50, 18);
				cout << (option == 3 ? "      > SALIR <       " : "        SALIR        ");
			}

			tecla = _getch();  // Captura la tecla presionada
			switch (tecla) {
			case ARRIBA:  // Si se presiona la tecla de arriba, se cambia la opción
				option--;
				if (option < 1) option = 3;
				refresh = true;
				break;
			case ABAJO:  // Si se presiona la tecla de abajo, se cambia la opción
				option++;
				if (option > 3) option = 1;
				refresh = true;
				break;
			default:
				refresh = false;  // No se redibuja si no hubo cambio
				break;
			}
		} while (tecla != 13);  // Continuar hasta que se presione Enter

		// Manejo de las opciones seleccionadas
		switch (option) {
		case 1:
			RegisterClient();  // Llama a la función para registrar cliente
			MainMenu();  // Vuelve al menú principal
			break;
		case 2:
			LoginClient();  // Llama a la función para iniciar sesión
			MainMenu();
			break;
		case 3:
			exit(0);  // Cierra el programa
		}
	}

	
	void ClientMenu(Client<int>* client) {
		bool refresh = true;
		menu->Fondo();  // Llama al fondo solo una vez
		menu->Logo();   // Llama al logo solo una vez

		do {
			if (refresh) {  // Solo redibuja las opciones si es necesario
				Console::ForegroundColor = ConsoleColor::White;

				// Muestra las opciones del menú de cliente
				Console::SetCursorPosition(42, 12);
				cout << (_option == 1 ? "> Mostrar datos del usuario <" : "  Mostrar datos del usuario  ");
				Console::SetCursorPosition(42, 14);
				cout << (_option == 2 ? "> Comprar Boletos <" : "  Comprar Boletos  ");
				Console::SetCursorPosition(42, 16);
				cout << (_option == 3 ? "> Mostrar boletos comprados <" : "  Mostrar boletos comprados  ");
				Console::SetCursorPosition(42, 18);
				cout << (_option == 4 ? "> Mostrar saldo <" : "  Mostrar saldo  ");
				Console::SetCursorPosition(42, 20);
				cout << (_option == 5 ? "> Recargar saldo <" : "  Recargar saldo  ");
				Console::SetCursorPosition(42, 22);
				cout << (_option == 6 ? "> Salir <" : "  Salir  ");
			}

			tecla = _getch();  // Captura la tecla presionada
			switch (tecla) {
			case ARRIBA:  // Mueve la selección hacia arriba
				_option--;
				if (_option < 1) _option = 6;
				refresh = true;
				break;
			case ABAJO:  // Mueve la selección hacia abajo
				_option++;
				if (_option > 6) _option = 1;
				refresh = true;
				break;
			default:
				refresh = false;  // No se redibuja si no hubo cambio
				break;
			}
		} while (tecla != 13);  // Continúa hasta que se presione Enter

		// Llama a las funciones correspondientes según la opción seleccionada
		switch (_option) {
		case 1:
			client->ToString();  // Muestra los datos del cliente
			_getch();
			ClientMenu(client);  // Vuelve al menú del cliente
			break;
		case 2:
			BuyTicket(client);  // Llama a la función para comprar boletos
			_getch();
			ClientMenu(client);
			break;
		case 3:
			ShowBoughtTickets(client);  // Muestra los boletos comprados por el cliente
			ClientMenu(client);
			break;
		case 4:
			ShowBalance(client);  // Muestra el saldo del cliente
			_getch();
			ClientMenu(client);
			break;
		case 5:
			RechargeBalance(client);  // Llama a la función para recargar saldo
			_getch();
			ClientMenu(client);
			break;
		case 6:
			return;  // Sale del menú del cliente
		}
	}


	void RegisterClient() {
		// Función para registrar un nuevo cliente
		string name, lastname, user, password;
		int dni, age, phone;
		menu->Fondo();
		menu->Logo();

		// Solicita la información del cliente
		Console::ForegroundColor = ConsoleColor::White;
		Console::SetCursorPosition(42, 12);
		cout << "Ingrese nombre: ";
		cin >> name;
		Console::SetCursorPosition(42, 14);
		cout << "Ingrese apellido: ";
		cin >> lastname;
		Console::SetCursorPosition(42, 16);
		cout << "Ingrese DNI: ";
		cin >> dni;
		Console::SetCursorPosition(42, 18);
		cout << "Ingrese edad: ";
		cin >> age;
		Console::SetCursorPosition(42, 20);
		cout << "Ingrese telefono: ";
		cin >> phone;
		Console::SetCursorPosition(42, 22);
		cout << "Ingrese usuario: ";
		cin >> user;
		Console::SetCursorPosition(42, 24);
		cout << "Ingrese password: ";
		cin >> password;

		// Registra el cliente en la base de datos
		database->registerClient(name, lastname, dni, age, phone, user, password);
	}


	void LoginClient() {
		menu->Fondo();
		menu->Logo();
		string user, password;
		Console::ForegroundColor = ConsoleColor::White;
		Console::SetCursorPosition(42, 12);
		cout << "Ingrese usuario: ";
		cin >> user;
		Console::SetCursorPosition(42, 14);
		cout << "Ingrese password: ";
		cin >> password;
		if (user == "admin" && password == "admin") {
			AdminMenu();  // Mostrar menú de administración
		}
		Client<int>* client = database->findClient(user, password);
		if (client) {
			ClientMenu(client);
		}
		else {
			Console::SetCursorPosition(42, 16);
			cout << "Usuario no encontrado";
			_getch();
		}

	}
	
	void AdminMenu() {
		int adminOption = 1;
		bool refresh = true;
		menu->Fondo();
		menu->Logo();

		do {
			if (refresh) {
				Console::ForegroundColor = ConsoleColor::White;
				Console::SetCursorPosition(42, 12);
				cout << (adminOption == 1 ? "> Listar Buses <" : "  Listar Buses  ");
				Console::SetCursorPosition(42, 14);
				cout << (adminOption == 2 ? "> Listar Clientes <" : "  Listar Clientes  ");
				Console::SetCursorPosition(42, 16);
				cout << (adminOption == 3 ? "> Buscar Cliente <" : "  Buscar Cliente  ");
				Console::SetCursorPosition(42, 18);
				cout << (adminOption == 4 ? "> Ver Tickets de Cliente <" : "  Ver Tickets de Cliente  ");
				Console::SetCursorPosition(42, 20);
				cout << (adminOption == 5 ? "> Salir <" : "  Salir  ");
			}


			tecla = _getch();
			switch (tecla) {
			case ARRIBA:
				adminOption--;
				if (adminOption < 1) adminOption = 5;
				refresh = true;
				break;
			case ABAJO:
				adminOption++;
				if (adminOption > 5) adminOption = 1;
				refresh = true;
				break;
			default:
				refresh = false;
				break;
			}
		} while (tecla != 13);

		switch (adminOption) {
		case 1:
			ListBuses();
			AdminMenu();
			break;
		case 2:
			ListClient();
			AdminMenu();
			break;
		case 3:
			BuscarClient();
			AdminMenu();
			break;
		case 4:
			ViewClientTickets();
			AdminMenu();
			break;
		case 5:
			MainMenu();
			break;
		}
	}
	// Función para ver los tickets de un cliente

	void ViewClientTickets() {
		menu->Fondo();
		menu->Logo();
		Console::ForegroundColor = ConsoleColor::White;
		Console::SetCursorPosition(40, 12);
		string user;
		cout << "Ingrese el nombre de usuario para buscar: ";
		cin >> user;

		// Buscar al cliente en la base de datos
		Client<int>* client = database->findClientBus(user);
		if (client == nullptr) {
			Console::ForegroundColor = ConsoleColor::DarkRed;
			Console::SetCursorPosition(40, 14);
			cout << "Cliente no encontrado." << endl;
			_getch();
			return;
		}

		// Si el cliente tiene boletos
		if (!client->busdata.empty()) {
			Console::SetCursorPosition(40, 12);
			cout << "                                                 ";
			Console::ForegroundColor = ConsoleColor::White;
			Console::SetCursorPosition(40, 14);
			cout << "Tickets del cliente "<< client->GetLastName() << ":" << endl;

			// Iterar sobre los tickets y mostrarlos gráficamente
			int yPosition = 16; // Posición inicial en Y para mostrar los boletos
			int i = 1;
			
			for (Bus* bus : client->busdata) {
				Console::ForegroundColor = static_cast<ConsoleColor>(i);
				Console::SetCursorPosition(40, yPosition++);
				cout << "Bus: " << bus->GetBusNumber() << " | Empresa: " << bus->GetCompany();
				Console::SetCursorPosition(40, yPosition++);
				cout<< "Precio: " << bus->GetPrice();
				Console::SetCursorPosition(40, yPosition++);
				cout << "Ruta: " << bus->GetStartRoute() << " -> " << bus->GetEndRoute() << " | Horario: " << bus->GetSchedule();
				yPosition++;  // Espacio entre tickets
				i++;
			}

			_getch(); // Esperar para que el administrador vea la información
		}
		else {
			Console::ForegroundColor = ConsoleColor::DarkGreen;
			Console::SetCursorPosition(40, 14);
			cout << "El cliente no tiene boletos comprados." << endl;
			_getch();
		}
	}


	void BuscarClient() {
		clientTable->showClientInfo();
}
	void ListBuses() {
		menu->Fondo();
		menu->Logo();
		Console::ForegroundColor = ConsoleColor::White;

		BusInfo<Bus> businfo;
		BusesData(businfo);  // Método que agrega los buses a businfo

		// Obtener el vector de buses
		std::vector<Bus> buses = businfo.getBusesAsVector();

		// Comparador que ordena los buses por número de bus
		auto BusComparator = [](const Bus& a, const Bus& b) {
			return a.GetBusNumber() < b.GetBusNumber();  
			};

		// Ordena el vector de buses por número de bus usando Quick Sort
		quickSort(buses, 0, buses.size() - 1, BusComparator);

		// Actualiza la lista enlazada desde el vector ordenado
		businfo.fromVector(buses);
		businfo.showBuses();
		_getch();
	}
	void ListClient() {
		menu->Fondo();
		menu->Logo();
		Console::ForegroundColor = ConsoleColor::White;

		vector<Client<int>*> clientes = database->getAllClients();

		if (clientes.empty()) {
			Console::SetCursorPosition(42, 12);
			Console::ForegroundColor = ConsoleColor::DarkRed;
			cout << "No hay clientes registrados.";
			_getch();
			return;
		}

		// Usamos std::sort para ordenar a los clientes
		auto clientComparator = [](Client<int>* a, Client<int>* b) {
			return a->GetName() < b->GetName();  // Compara por el nombre, usando punteros
			};

		// Ordenar la lista de clientes
		sort(clientes.begin(), clientes.end(), clientComparator);
		Console::SetCursorPosition(42, 12);
		Console::ForegroundColor = ConsoleColor::DarkMagenta;
		cout << "Nombres y Apellidos: ";
		Console::ForegroundColor = ConsoleColor::White;
		for (size_t i = 0; i < clientes.size(); i++) {
			Console::SetCursorPosition(42, 14 + i);
			cout << i + 1 << ". " << clientes[i]->GetName() << " " << clientes[i]->GetLastName();  // Acceso mediante '->' para punteros
		}

		_getch();
	}


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
	void BuyTicket(Client<int>* client) {
		// Rutas predefinidas
		vector<string> routes = {
			"Lima", "Arequipa", "Cusco", "Trujillo", "Chiclayo",
			"Piura", "Iquitos", "Tacna", "Puno", "Chimbote",
			"Huancayo", "Ayacucho", "Juliaca", "Cajamarca", "Huaraz"
		};

		// Configuración inicial del menú
		menu->Fondo();
		menu->Logo();
		Console::ForegroundColor = ConsoleColor::White;

		// Generar aleatoriamente entre 5 y 10 combinaciones de rutas
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> numCombDist(10, 13);  // Generar entre 5 y 10 combinaciones
		uniform_int_distribution<> routeDist(0, routes.size() - 1);  // Para seleccionar rutas aleatorias

		int numCombinations = numCombDist(gen);  // Número de combinaciones aleatorias
		vector<pair<string, string>> routeCombinations;  // Almacenará las combinaciones de rutas

		// Generar combinaciones únicas de rutas
		while (routeCombinations.size() < numCombinations) {
			string startRoute = routes[routeDist(gen)];  // Ruta de inicio aleatoria
			string endRoute = routes[routeDist(gen)];  // Ruta de destino aleatoria

			// Asegurarse de que la ruta de destino no sea la misma que la de inicio
			while (endRoute == startRoute) {
				endRoute = routes[routeDist(gen)];  // Si es la misma, generamos una nueva ruta de destino
			}

			routeCombinations.push_back(make_pair(startRoute, endRoute));  // Agregar la combinación de rutas
		}

		// Mostrar las combinaciones generadas como un menú
		Console::SetCursorPosition(42, 12);  // Posicionamos el cursor en la pantalla
		cout << "Seleccione una ruta:" << endl;  // Título del menú de selección

		// Mostrar cada combinación de rutas en el menú
		for (int i = 0; i < routeCombinations.size(); i++) {
			
			Console::ForegroundColor = ConsoleColor::White;
			Console::SetCursorPosition(43, 14 + i);  // Desplazar el cursor hacia abajo para cada opción
			cout << " " << " " << routeCombinations[i].first << " -> " << routeCombinations[i].second;
			if (i == 0) {
				Console::ForegroundColor = ConsoleColor::Yellow;
				Console::SetCursorPosition(43, 14);
				cout << ">" << " " << routeCombinations[0].first << " -> " << routeCombinations[0].second;
			}
		}
		// Inicializar la opción seleccionada (empezamos con la primera opción)
		// Inicializar la opción seleccionada (empezamos con la primera opción)
		int selectedOption = 0;
		bool take = false;

		do {
			tecla = _getch();  // Capturar la tecla presionada por el usuario

			// Moverse hacia arriba en el menú
			if (tecla == ARRIBA && selectedOption > 0) {
				selectedOption--;  // Decrementar la opción seleccionada
			}
			// Moverse hacia abajo en el menú
			else if (tecla == ABAJO && selectedOption < routeCombinations.size() - 1) {
				selectedOption++;  // Incrementar la opción seleccionada
			}
			// Confirmar la selección con la tecla Enter
			else if (tecla == 13) {
				take = true;  // La selección es válida al presionar Enter
			}

			

			// Mostrar las opciones de rutas
			for (int i = 0; i < routeCombinations.size(); i++) {
				if (i == selectedOption) {
					// Resaltar la opción seleccionada con un ">" y color amarillo
					Console::ForegroundColor = ConsoleColor::Yellow;
					Console::SetCursorPosition(43, 14 + i);  // Establecer la posición para la opción seleccionada
					cout << "> " << routeCombinations[i].first << " -> " << routeCombinations[i].second;
				}
				else {
					// Para las opciones no seleccionadas, mostrar en blanco
					Console::ForegroundColor = ConsoleColor::White;
					Console::SetCursorPosition(43, 14 + i);  // Establecer la posición para cada opción
					cout << "  " << routeCombinations[i].first << " -> " << routeCombinations[i].second;
				}
			}

		} while (!take);  // Repetir hasta que se haga una selección válida

		
		// Una vez seleccionada la opción, obtenemos las rutas seleccionadas
		string startRoute = routeCombinations[selectedOption].first;
		string endRoute = routeCombinations[selectedOption].second;
	
		// Creación del BST para buses
		BST<Bus> buses([](Bus bus) {}); // No imprimimos nada durante la creación

		// Generar buses aleatorios usando las rutas proporcionadas
		GenerateRandomBuses(buses, startRoute, endRoute);

		// Vector temporal para almacenar punteros a los buses en orden
		vector<Bus*> busList;

		buses.collectInOrder(busList); // Método para recolectar los buses en orden en el vector

		// Iterar sobre los buses uno a uno
		int index = 0;
		bool busSelected = false;
		Bus* selectedBus = nullptr;

		while (index < busList.size() && !busSelected) {
			// Mostrar la información del bus actual
			busList[index]->ToString();
			Console::ForegroundColor = ConsoleColor::DarkGreen;
			Console::SetCursorPosition(48, 12);
			cout << "Buses encontrados     ";
			Console::ForegroundColor = ConsoleColor::DarkMagenta;
			cout << (index + 1) << " - " << busList.size();
			tecla = _getch();

			// Si se presiona ESC, selecciona el bus actual
			if (tecla == 27) { // Código ASCII para ESC
				menu->Fondo();
				menu->Logo();
				Console::ForegroundColor = ConsoleColor::White;
				Console::SetCursorPosition(50, 12);
				cout << "ASIENTOS DISPONIBLES:" << endl;
				busList[index]->displaySeats();

				int seatNumber;
				Console::ForegroundColor = ConsoleColor::White;
				Console::SetCursorPosition(37, 16);
				cout << "Seleccione el asiento: ";
				cin >> seatNumber;

				if (busList[index]->selectSeat(seatNumber)) {
					Console::ForegroundColor = ConsoleColor::DarkGreen;
					Console::SetCursorPosition(37, 18);
					cout << "Asiento " << seatNumber << " seleccionado correctamente." << endl;
				}
				else {
					Console::ForegroundColor = ConsoleColor::DarkRed;
					Console::SetCursorPosition(37, 18);
					cout << "Asiento no disponible o numero invalido." << endl;
					return;
				}

				_getch();

				selectedBus = busList[index];
				busSelected = true;
			}

			// Avanzar al siguiente bus si se presiona Enter
			else if (tecla == 13) { // Código ASCII para Enter
				index++;
			}
		}

		// Verificar si se seleccionó un bus
		if (selectedBus != nullptr) {
			menu->Fondo();
			menu->Logo();
			Console::ForegroundColor = ConsoleColor::White;

			// Validar si el cliente tiene suficiente saldo para comprar el boleto
			if (client->GetBalance() >= selectedBus->GetPrice()) {
				client->SetBalance(client->GetBalance() - selectedBus->GetPrice());
				client->AddBusData(selectedBus->GetBusNumber(), selectedBus->GetCompany(), selectedBus->GetPrice(), selectedBus->GetSchedule());
				client->AddBusRoute(selectedBus->GetBusNumber(), startRoute, endRoute);
				database->saveClientsToFile();
				Console::SetCursorPosition(42, 22);
				cout << "Boleto comprado con exito.";
			}
			else {
				Console::SetCursorPosition(42, 22);
				cout << "Saldo insuficiente.";
			}
		}
		else {
			Console::SetCursorPosition(42, 22);
			cout << "No se selecciono ningun bus.";
		}
	}
	void GenerateRandomBuses(BST<Bus>& buses, string startRoute, string endRoute) {
		// Crear un generador de números aleatorios con semilla
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> numBusesDist(10, 17); // Entre 10 y 16 buses
		uniform_int_distribution<> busNumberDist(1, 100); // Números de bus entre 1 y 100
		uniform_int_distribution<> priceDist(30, 60); // Precio entre 30 y 60
		uniform_int_distribution<> hourDist(0, 23); // Horas entre 0 y 23

		int numBuses = numBusesDist(gen);
		vector<Bus> busList;

		for (int i = 0; i < numBuses; i++) {
			int busNumber = busNumberDist(gen);
			string company = GenerateRandomCompany();
			int price = priceDist(gen);
			string schedule = to_string(hourDist(gen)) + ":00";

			Bus bus(busNumber, company, price, schedule);
			bus.SetStartRoute(startRoute);
			bus.SetEndRoute(endRoute);

			busList.push_back(bus);
			buses.insertar(bus);
		}
	}
	string GenerateRandomCompany() {
		ifstream file("Empresas.txt");
		vector<string> companies;
		string company;
		while (getline(file, company)) {
			companies.push_back(company);
		}
		file.close();

		if (companies.empty()) {
			return "Unknown Company";  // Devuelve un valor por defecto si no hay datos en el archivo
		}

		// Crear un generador de números aleatorios
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(0, companies.size() - 1);

		return companies[dist(gen)];
	}
	void ShowBoughtTickets(Client<int>* client) {
		if (client->busdata.empty()) {
			menu->Fondo();  // Llama a Fondo solo una vez
			menu->Logo();   // Llama a Logo solo una vez
			Console::ForegroundColor = ConsoleColor::White;
			Console::SetCursorPosition(42, 12);
			cout << "No han comprado boletos";
			_getch();
		}
		else {
			for (Bus* bus : client->busdata) {
				bus->ToStringData();
				_getch();

			}
		}
	}
	void ShowBalance(Client<int>* client) {
		menu->Fondo();  // Llama a Fondo solo una vez
		menu->Logo();   // Llama a Logo solo una vez
		Console::ForegroundColor = ConsoleColor::White;
		Console::SetCursorPosition(42, 12);
		cout << "Su saldo actual es: " << client->GetBalance() << " soles.\n";
	}
	void RechargeBalance(Client<int>* client) {
		int option = 1;
		char tecla;
		bool refresh = true;

		// Mostrar fondo y logo una sola vez
		menu->Fondo();
		menu->Logo();

		do {
			if (refresh) {  // Redibuja las opciones del menú si es necesario
				Console::ForegroundColor = ConsoleColor::White;

				// Opciones del menú de recarga de saldo
				Console::SetCursorPosition(42, 12);
				cout << (option == 1 ? "> Usar tarjeta existente <" : "  Usar tarjeta existente  ");
				Console::SetCursorPosition(42, 14);
				cout << (option == 2 ? "> Agregar nueva tarjeta <" : "  Agregar nueva tarjeta  ");
				Console::SetCursorPosition(42, 16);
				cout << (option == 3 ? "> Volver <" : "  Volver  ");
			}

			tecla = _getch();  // Captura la tecla presionada
			switch (tecla) {
			case ARRIBA:
				option--;
				if (option < 1) option = 3;
				refresh = true;
				break;
			case ABAJO:
				option++;
				if (option > 3) option = 1;
				refresh = true;
				break;
			default:
				refresh = false;
				break;
			}
		} while (tecla != 13);  // Se sale del bucle cuando se presiona Enter

		// Limpia la pantalla antes de pedir los datos para la opción seleccionada
		for (int i = 12; i <= 16; i++) {  // Borra las opciones anteriores
			Console::SetCursorPosition(42, i);
			cout << string(40, ' ');  // Limpia la línea
		}

		// Recolocar el cursor y manejar las opciones seleccionadas
		Console::SetCursorPosition(42, 12);

		if (option == 1) {
			// Usar tarjeta existente
			if (client->creditData.empty()) {
				Console::SetCursorPosition(42, 12);
				cout << "No tiene tarjetas registradas.\n";
			}
			else {
				int cvv;
				Console::SetCursorPosition(42, 12);
				cout << "Ingrese el CVV de su tarjeta: ";
				cin >> cvv;

				bool cardFound = false;
				for (CreditCard* card : client->creditData) {
					if (card->GetCVV() == cvv) {
						Console::SetCursorPosition(42, 14);
						card->ToString();
						int amount;
						Console::SetCursorPosition(42, 20);
						cout << "Seleccione monto de recarga (40, 60, 80): ";
						cin >> amount;

						if (amount == 40 || amount == 60 || amount == 80) {
							client->SetBalance(client->GetBalance() + amount);
							database->saveClientsToFile();
							Console::SetCursorPosition(42, 22);
							cout << "Recarga exitosa.\n";
						}
						else {
							Console::SetCursorPosition(42, 22);
							cout << "Monto no válido.\n";
						}
						cardFound = true;
						break;
					}
				}
				if (!cardFound) {
					Console::SetCursorPosition(42, 18);
					cout << "Tarjeta no encontrada.\n";
				}
			}
		}
		else if (option == 2) {
			// Agregar nueva tarjeta
			string type;
			long long number;
			int date, cvv;
			Console::SetCursorPosition(42, 12);
			cout << "Ingrese tipo de tarjeta (VISA/MASTERCARD): ";
			cin >> type;
			Console::SetCursorPosition(42, 14);
			cout << "Ingrese numero de tarjeta: ";
			cin >> number;
			Console::SetCursorPosition(42, 16);
			cout << "Ingrese fecha de vencimiento (mm/aa): ";
			cin >> date;
			Console::SetCursorPosition(42, 18);
			cout << "Ingrese CVV: ";
			cin >> cvv;

			if (number > 0 && cvv > 0) {
				try {
					client->AddCreditCard(type, number, date, cvv);
					int amount;
					Console::SetCursorPosition(42, 20);
					cout << "Seleccione monto de recarga (40, 60, 80): ";
					cin >> amount;

					if (amount == 40 || amount == 60 || amount == 80) {
						client->SetBalance(client->GetBalance() + amount);
						database->saveClientsToFile();  // Guardar cambios
						Console::SetCursorPosition(42, 22);
						cout << "Recarga exitosa.\n";
					}
					else {
						Console::SetCursorPosition(42, 22);
						cout << "Monto no valido.\n";
					}
				}
				catch (exception& e) {
					Console::SetCursorPosition(42, 22);
					cout << "Error al agregar tarjeta o recargar: " << e.what() << endl;
				}
			}
			else {
				Console::SetCursorPosition(42, 22);
				cout << "Datos de la tarjeta no validos.\n";
			}
		}
		else if (option == 3) {
			// Volver al menú anterior
			ClientMenu(client);
		}
	}



	void BusesData(BusInfo<Bus>& buses) {
		// Crear un generador de números aleatorios con semilla
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> numBusesDist(20, 27); // Entre 10 y 17 buses
		uniform_int_distribution<> busNumberDist(1, 100); // Números de bus entre 1 y 100
		uniform_int_distribution<> priceDist(30, 60); // Precio entre 30 y 60
		uniform_int_distribution<> hourDist(0, 23); // Horas entre 0 y 23

		// Número aleatorio de buses a crear
		int numBuses = numBusesDist(gen);

		// Generar y agregar buses a la lista
		for (int i = 0; i < numBuses; i++) {
			// Generar datos aleatorios para un bus
			int busNumber = busNumberDist(gen);
			string company = GenerateRandomCompany();  
			int price = priceDist(gen);
			string schedule = to_string(hourDist(gen)) + ":00 ";

			// Crear un nuevo objeto Bus
			Bus bus(busNumber, company, price, schedule);

			// Agregar el bus a la lista de buses (usando el método addBus)
			buses.addBus(bus);
		}
	}
	
	
};

