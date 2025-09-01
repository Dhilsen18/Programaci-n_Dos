#pragma once
#include<string>
#include"Bus.h"
#include"Client.h"
using namespace std;
class Promotion {
private:
    int promotionID;
    std::string description;
    double discountPercentage;
    std::string startDate;
    std::string endDate;

public:
    Promotion(std::string description, double discountPercentage, std::string startDate, std::string endDate)
        : description(description), discountPercentage(discountPercentage), startDate(startDate), endDate(endDate) {
        static int id = 1;
        promotionID = id++;
    }

    int GetPromotionID() const { return promotionID; }
    std::string GetDescription() const { return description; }
    double GetDiscountPercentage() const { return discountPercentage; }
    std::string GetStartDate() const { return startDate; }
    std::string GetEndDate() const { return endDate; }

    double ApplyPromotion(Client<int>* client, Bus* bus) {
        // Lógica para aplicar promoción, devuelve precio con descuento
        return bus->GetPrice() * (1 - discountPercentage / 100);
    }
};
