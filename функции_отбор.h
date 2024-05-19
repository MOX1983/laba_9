std::vector<Talk> vibor(std::vector<Talk>& talks) {
    int choice;
    std::cout << "каким методом сортировать:\n";
    std::cout << "1. Heap sort\n";
    std::cout << "2. Merge sort\n";
    std::cin >> choice;

    if (choice == 1)
        merge_sort(talks);
    else
        heap_sort(talks);
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
