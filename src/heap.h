#ifndef TP_LOLLA_HEAP_H
#define TP_LOLLA_HEAP_H

#include <vector>
#include <queue>

// Definir una estructura para representar las tuplas
struct Tuple {
    int first;
    int second;
};

// Definir un comparador personalizado para las tuplas
struct TupleComparator {
    bool operator()(const std::pair<unsigned int, int>& t1, const std::pair<unsigned int, int>& t2) const {
        if (t1.first > t2.first) {
            return true;  // Ordenar por el primer elemento de mayor a menor
        } else if (t1.first == t2.first) {
            return t1.second < t2.second;  // Ordenar por el segundo elemento de menor a mayor si hay un empate
        } else {
            return false;
        }
    }
};

// Implementar la estructura de datos de cola de prioridad
template<typename T, typename Container = std::vector<T>, typename Compare = std::less<typename Container::value_type>>
class PriorityQueue {
    public:
        void push(const T& value) {
            elements.push_back(value);
            int index = elements.size() - 1;
            heapifyUp(index);
            heapifyDown(index);
        }

        void pop() {
            if (elements.empty()) {
                return;
            }

            std::swap(elements[0], elements.back());
            elements.pop_back();
            heapifyDown(0);
        }

        T top() const {
            return elements[0];
        }

        bool empty() const {
            return elements.empty();
        }

        typename Container::iterator begin() {
            return elements.begin();
        }

        typename Container::const_iterator begin() const {
            return elements.begin();
        }

        typename Container::iterator end() {
            return elements.end();
        }

        typename Container::const_iterator end() const {
            return elements.end();
        }

        void erase(typename Container::const_iterator position) {
            elements.erase(position);
            //std::make_heap(elements.begin(), elements.end(), comp);
        }

        void erase(typename Container::const_iterator first, typename Container::const_iterator last) {
            elements.erase(first, last);
        }

        std::size_t size() const {
            return elements.size();
        }

    private:
        Container elements;
        Compare comp;

        void heapifyUp(int index) {
            while (index > 0) {
                int parent = (index - 1) / 2;

                if (comp(elements[index], elements[parent])) {
                    std::swap(elements[index], elements[parent]);
                    index = parent;
                } else {
                    break;  // El padre es menor o igual, no es necesario intercambiar
                }
            }
        }

        void heapifyDown(int index) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int smallest = index;

            if (leftChild < elements.size() && comp(elements[leftChild], elements[smallest])) {
                smallest = leftChild;
            }

            if (rightChild < elements.size() && comp(elements[rightChild], elements[smallest])) {
                smallest = rightChild;
            }

            if (smallest != index) {
                std::swap(elements[index], elements[smallest]);
                heapifyDown(smallest);
            }
        }
};


#endif //TP_LOLLA_HEAP_H
