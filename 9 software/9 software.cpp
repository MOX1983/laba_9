#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <Windows.h>

using namespace std;

struct Talk {
    string start, end, last_name, first_name, middle_name, theme;
    int duration() const {
        istringstream is(start);
        int h1, m1;
        char colon;
        if (!(is >> h1 >> colon >> m1) || h1 < 0 || h1 >= 24 || m1 < 0 || m1 >= 60) {
            throw invalid_argument("Invalid start time format");
        }
        is.clear();
        is.str(end);
        int h2, m2;
        if (!(is >> h2 >> colon >> m2) || h2 < 0 || h2 >= 24 || m2 < 0 || m2 >= 60) {
            throw invalid_argument("Invalid end time format");
        }
        return (h2 - h1) * 60 + (m2 - m1);
    }
};

istream& operator>>(istream& is, Talk& talk) {
    is >> talk.start >> talk.end >> talk.last_name >> talk.first_name >> talk.middle_name >> talk.theme;
    return is;
}

ostream& operator<<(ostream& os, const Talk& talk) {
    os << talk.start << ' ' << talk.end << ' ' << talk.last_name << ' ' << talk.first_name << ' ' << talk.middle_name << ' ' << talk.theme << '\n';
    return os;
}
void heapify_duration(vector<Talk>& talks, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && talks[left].duration() > talks[largest].duration()) {
        largest = left;
    }

    if (right < n && talks[right].duration() > talks[largest].duration()) {
        largest = right;
    }

    if (largest != i) {
        swap(talks[i], talks[largest]);
        heapify_duration(talks, n, largest);
    }
}

void heap_sort_duration(vector<Talk>& talks) {
    int n = talks.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify_duration(talks, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        swap(talks[0], talks[i]);
        heapify_duration(talks, i, 0);
    }
}

void heapify_last_name(vector<Talk>& talks, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && (talks[left].last_name < talks[i].last_name ||
        (talks[left].last_name == talks[i].last_name &&
            talks[left].theme < talks[i].theme))) {
        largest = left;
    }

    if (right < n && (talks[right].last_name < talks[largest].last_name ||
        (talks[right].last_name == talks[largest].last_name &&
            talks[right].theme < talks[largest].theme))) {
        largest = right;
    }

    if (largest != i) {
        swap(talks[i], talks[largest]);
        heapify_last_name(talks, n, largest);
    }
}

void heap_sort_last_name(vector<Talk>& talks) {
    int n = talks.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify_last_name(talks, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        swap(talks[0], talks[i]);
        heapify_last_name(talks, i, 0);
    }
}
vector<Talk> search_numbers_by_time(const vector<Talk>& talks, const string& last_name, const string& first_name, const string& middle_name) {
    vector<Talk> numbers_by_time;
    for (const auto& t : talks) {
        if (t.last_name == last_name && t.first_name == first_name && t.middle_name == middle_name) {
            numbers_by_time.push_back(t);
        }
    }
    return numbers_by_time;
}
void merge_sort_duration(vector<Talk>& talks) {
    if (talks.size() <= 1) {
        return;
    }
    vector<Talk> left(talks.begin(), talks.begin() + talks.size() / 2);
    vector<Talk> right(talks.begin() + talks.size() / 2, talks.end());
    merge_sort_duration(left);
    merge_sort_duration(right);
    merge(left.begin(), left.end(), right.begin(), right.end(), talks.begin(), [](const Talk& a, const Talk& b) {
        return a.duration() > b.duration();
        });
}
void merge_sort_last_name(vector<Talk>& talks) {
    if (talks.size() <= 1) {
        return;
    }
    vector<Talk> left(talks.begin(), talks.begin() + talks.size() / 2);
    vector<Talk> right(talks.begin() + talks.size() / 2, talks.end());
    merge_sort_last_name(left);
    merge_sort_last_name(right);
    merge(left.begin(), left.end(), right.begin(), right.end(), talks.begin(), [](const Talk& a, const Talk& b) {
        if (a.last_name != b.last_name) {
            return a.last_name < b.last_name; // сортировка по возрастанию фамилии
        }
        return a.theme < b.theme; // сортировка по возрастанию темы в рамках одного автора
        });
}
void vibor(vector<Talk>& talks) {
    int choice, choice2;
    cout << "каким методом сортировать:\n";
    cout << "1. Heap sort\n";
    cout << "2. Merge sort\n";
    cin >> choice;
    cout << "Критерии сортировки:\n";
    cout << "1.По убыванию длительности доклада\n";
    cout << "2.По возрастанию фамилии автора доклада, а в рамках одного автора по возрастанию темы доклада\n";
    cin >> choice2;

    if (choice == 1 && choice2 == 1)
        heap_sort_duration(talks);
    else if (choice == 1 && choice2 == 2)
        heap_sort_last_name(talks);
    else if (choice == 2 && choice2 == 1)
        merge_sort_duration(talks);
    else
        merge_sort_last_name(talks);
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string f = "9.txt";
    fstream file;
    vector<Talk> talks;
    Talk talk;

    file.open(f, ios::in | ios::app);
    if (file.is_open()) {
        while (file >> talk)
        {
            talks.push_back(talk);
        }
        int n;
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> talk;
            talks.push_back(talk);
        }
        file.close();
    }
    else {
        cerr << "Не удалось открыть файл для записи " << endl;
        return 1;
    }

    file.open(f, ios::out | ios::trunc);
    if (file.is_open()) {

        vibor(talks);

        for (const Talk& talk : talks) {
            file << talk;
        }
        for (const Talk& talk : talks) {
            cout << talk;
        }
        file.close();
    }
    else {
        cerr << "Не удалось открыть файл для записи " << endl;
        return 1;
    }
    string last_name;
    string first_name;
    string middle_name;
    cout << "Введите  ФИО : ";
    cin >> last_name >> first_name >> middle_name;

    vector<Talk> numbers = search_numbers_by_time(talks, last_name, first_name, middle_name);

    if (numbers.size() != 0) {
        cout << "ФИО " << last_name <<" " << first_name << " " << middle_name <<  endl;
        for (const auto& t : numbers) {
            cout << t;
        }
    }
    else
    {
        cout << "тагого нет :(" << endl;
    }

    return 0;
}
