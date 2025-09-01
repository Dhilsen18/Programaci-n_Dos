#pragma once
#include"Client.h"
using namespace std;
class Invoice {
private:

    long invoiceID;
    Client<int>* client;
    Bus* bus;
    double amount;
    std::string date;

public:
    Invoice(Client<int>* client, Bus* bus, double amount, std::string date)
        : client(client), bus(bus), amount(amount), date(date) {
        static long id = 1;
        invoiceID = id++;
    }

    long GetInvoiceID() const { return invoiceID; }
    Client<int>* GetClient() const { return client; }
    Bus* GetBus() const { return bus; }
    double GetAmount() const { return amount; }
    std::string GetDate() const { return date; }
    
};
