#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Cấu trúc sản phẩm
struct Product {
    string name;
    int price;
    int quantity;
};

// Cấu trúc node của hàng đợi
struct Node {
    string customerName;
    vector<Product> products;
    Node* next;
};

// Hàng đợi
class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    // Thêm khách hàng vào hàng đợi
    void enqueue(string customerName, vector<Product> products) {
        Node* newNode = new Node{ customerName, products, nullptr };
        if (rear == nullptr) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Loại bỏ khách hàng ra khỏi hàng đợi
    void dequeue() {
        if (front == nullptr) {
            cout << "Hàng đợi rỗng!\n";
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front == nullptr) rear = nullptr; // Nếu hàng đợi rỗng
        delete temp;
    }

    // Tính tổng số tiền thu được
    int calculateTotalRevenue() {
        int total = 0;
        Node* current = front;
        while (current != nullptr) {
            for (const auto& product : current->products) {
                total += product.price * product.quantity;
            }
            current = current->next;
        }
        return total;
    }

    // Đếm số lượng sản phẩm A đã được bán
    int countProduct(string productName) {
        int count = 0;
        Node* current = front;
        while (current != nullptr) {
            for (const auto& product : current->products) {
                if (product.name == productName) {
                    count += product.quantity;
                }
            }
            current = current->next;
        }
        return count;
    }

    // Hiển thị hàng đợi
    void displayQueue() {
        Node* current = front;
        while (current != nullptr) {
            cout << "Khách hàng: " << current->customerName << "\n";
            for (const auto& product : current->products) {
                cout << "  - Sản phẩm: " << product.name
                    << ", Giá: " << product.price
                    << ", Số lượng: " << product.quantity << "\n";
            }
            current = current->next;
        }
    }
};

int main() {
    Queue queue;

    // Thêm một số khách hàng
    queue.enqueue("Nguyen Van Anh", { {"Sữa", 20000, 2}, {"Bánh", 10000, 1} });
    queue.enqueue("Tran Thi Bao", { {"Sữa", 20000, 1}, {"Trứng", 30000, 2} });
    queue.enqueue("Le Van Chi", { {"Bánh", 10000, 3}, {"Sữa", 20000, 1} });

    cout << "Hàng đợi ban đầu:\n";
    queue.displayQueue();

    // Thanh toán cho khách hàng đầu tiên
    cout << "\nThanh toán cho khách hàng đầu tiên...\n";
    queue.dequeue();
    queue.displayQueue();

    // Tính tổng doanh thu
    cout << "\nTổng doanh thu: " << queue.calculateTotalRevenue() << " VND\n";

    // Đếm số lượng sản phẩm "Sữa" đã bán
    cout << "Số lượng 'Sữa' đã bán: " << queue.countProduct("Sữa") << "\n";

    return 0;
}
