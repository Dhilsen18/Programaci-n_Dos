#pragma once
#include"Bus.h"
#include"Client.h"
class Feedback {
private:
    int feedbackID;
    Client<int>* client;
    Bus* bus;
    int rating;
    std::string comments;

public:
    Feedback(Client<int>* client, Bus* bus, int rating, std::string comments)
        : client(client), bus(bus), rating(rating), comments(comments) {
        static int id = 1;
        feedbackID = id++;
    }

    int GetFeedbackID() const { return feedbackID; }
    Client<int>* GetClient() const { return client; }
    Bus* GetBus() const { return bus; }
    int GetRating() const { return rating; }
    std::string GetComments() const { return comments; }

    std::string ToString() const {
        return "Feedback ID: " + std::to_string(feedbackID) + ", Rating: " + std::to_string(rating);
    }
};
