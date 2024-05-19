#include <vector>

int* filter_function(int* array[], int size, bool (*check)(int* element), int& result_size) {
    std::vector<int*> result_vector;

    for (int i = 0; i < size; i++) {
        if (check(array[i])) == true) {
            result_vector.push_back(array[i]);
        }
    }

    result_size = result_vector.size();
    int* result_array = new int[result_size];

    for (int i = 0; i < result_size; i++) {
        result_array[i] = *result_vector[i];
    }

    return result_array;
}

bool check_function(int* element) {
    return (*element % 2 == 0);

