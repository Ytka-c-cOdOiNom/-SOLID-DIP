/*
Код вісилання email або sms
Неправильний код:

#include <iostream>
#include <string>

class EmailSender {
public:
    void send(const string& message) {
        cout << "Sending Email: " << message << endl;
    }
};

class Notification {
private:
    EmailSender emailSender; // Пряма залежність від конкретного класу EmailSender

public:
    void notify(const string& message) {
        emailSender.send(message);
    }
};

int main() {
    Notification notification;
    notification.notify("Hello!");

    У цьому прикладі клас Notification напряму залежить від конкретної реалізації EmailSender.
    Якщо потрібно додати інший тип відправлення (наприклад, SMS), доведеться змінювати Notification, що порушує гнучкість та розширюваність
} */

#include <iostream>
#include <string>
#include <memory>
using namespace std;
// Абстрактний інтерфейс для надсилання повідомлень
class MessageSender {
public:
    virtual void send(const string& message) const = 0;
    virtual ~MessageSender() = default;
};

// Реалізація для надсилання електронної пошти
class EmailSender : public MessageSender {
public:
    void send(const string& message) const override {
        cout << "Sending Email: " << message << endl;
    }
};

// Реалізація для надсилання SMS
class SmsSender : public MessageSender {
public:
    void send(const string& message) const override {
        cout << "Sending SMS: " << message << endl;
    }
};

// Клас верхнього рівня, який залежить від інтерфейсу MessageSender
class Notification {
private:
    shared_ptr<MessageSender> sender;

public:
    Notification(shared_ptr<MessageSender> sender) : sender(sender) {}

    void notify(const string& message) {
        sender->send(message);
    }
};

int main() {
    auto emailSender = make_shared<EmailSender>();
    auto smsSender = make_shared<SmsSender>();

    Notification emailNotification(emailSender);
    emailNotification.notify("Hello Email!");

    Notification smsNotification(smsSender);
    smsNotification.notify("Hello SMS!");

}