#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <Windows.h>

struct Talk {
    std::string start, end, last_name, first_name, middle_name, theme;
    int duration() const {
        std::istringstream is(start);
        int h1, m1;
        char colon;
        if (!(is >> h1 >> colon >> m1) || h1 < 0 || h1 >= 24 || m1 < 0 || m1 >= 60) {
            throw std::invalid_argument("Invalid start time format");
        }
        is.clear();
        is.str(end);
        int h2, m2;
        if (!(is >> h2 >> colon >> m2) || h2 < 0 || h2 >= 24 || m2 < 0 || m2 >= 60) {
            throw std::invalid_argument("Invalid end time format");
        }
        return (h2 - h1) * 60 + (m2 - m1);
    }
};

std::istream& operator>>(std::istream& is, Talk& talk) {
    is >> talk.start >> talk.end >> talk.last_name >> talk.first_name >> talk.middle_name >> talk.theme;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Talk& talk) {
    os << talk.start << ' ' << talk.end << ' ' << talk.last_name << ' ' << talk.first_name << ' ' << talk.middle_name << ' ' << talk.theme << '\n';
    return os;
}

void merge_sort(std::vector<Talk>& talks) {
    if (talks.size() <= 1) {
        return;
    }
    std::vector<Talk> left(talks.begin(), talks.begin() + talks.size() / 2);
    std::vector<Talk> right(talks.begin() + talks.size() / 2, talks.end());
    merge_sort(left);
    merge_sort(right);
    std::merge(left.begin(), left.end(), right.begin(), right.end(), talks.begin(), [](const Talk& a, const Talk& b) {
        if (a.duration() != b.duration()) {
            return a.duration() > b.duration();
        }
        if (a.last_name != b.last_name) {
            return a.last_name < b.last_name;
        }
        return a.theme < b.theme;
        });
}

void heapify(std::vector<Talk>& talks, int n, int i) {
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
        std::swap(talks[i], talks[largest]);
        heapify(talks, n, largest);
    }
}
void heap_sort(std::vector<Talk>& talks) {
    int n = talks.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(talks, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        std::swap(talks[0], talks[i]);
        heapify(talks, i, 0);
    }
}

std::vector<Talk> search_numbers_by_time(const std::vector<Talk>& talks, const std::string& last_name, const std::string& first_name, const std::string& middle_name) {
    std::vector<Talk> numbers_by_time;
    for (const auto& t : talks) {
        if (t.last_name == last_name && t.first_name == first_name && t.middle_name == middle_name) {
            numbers_by_time.push_back(t);
        }
    }
    return numbers_by_time;
}
