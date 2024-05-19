#include <iostream>

using namespace std;

#include "book_subscription.h"
#include "file_reader.h"
#include "constants.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Лабораторная работа №8. GIT\n";
    cout << "Вариант №0. Библиотечный абонемент\n";
    cout << "Автор: Сергей Ермоченко\n\n";
    book_subscription* subscriptions[MAX_FILE_ROWS_COUNT];
    int size;
    try
    {
        read("data.txt", subscriptions, size);
        for (int i = 0; i < size; i++)
        {
            cout << subscriptions[i]->reader.last_name << '\n';
            cout << subscriptions[i]->reader.first_name << '\n';
            cout << subscriptions[i]->reader.middle_name << '\n';
            cout << subscriptions[i]->finish.day << ' ';
            cout << subscriptions[i]->finish.month << ' ';
            cout << subscriptions[i]->finish.year << '\n';
            cout << subscriptions[i]->start.day << ' ';
            cout << subscriptions[i]->start.month << ' ';
            cout << subscriptions[i]->start.year << '\n';
            cout << subscriptions[i]->author.last_name << '\n';
            cout << subscriptions[i]->author.first_name << '\n';
            cout << subscriptions[i]->author.middle_name << '\n';
            cout << subscriptions[i]->title << '\n';
            cout << '\n';
        }
        for (int i = 0; i < size; i++)
        {
            delete subscriptions[i];
        }
    }
    catch (const char* error)
    {
        cout << error << '\n';
    }
    return 0;
}
