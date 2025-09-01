#pragma once
#include"Bus.h"
#include"Client.h"
class Ticket {
private:
    long ticketID;
    Client<int>* client;
    Bus* bus;
    double price;
    std::string purchaseDate;

public:
    Ticket(Client<int>* client, Bus* bus, double price, std::string purchaseDate)
        : client(client), bus(bus), price(price), purchaseDate(purchaseDate) {
        static long id = 1;
        ticketID = id++;
    }

    long GetTicketID() const { return ticketID; }
    Client<int>* GetClient() const { return client; }
    Bus* GetBus() const { return bus; }
    double GetPrice() const { return price; }
    std::string GetPurchaseDate() const { return purchaseDate; }

   
};
