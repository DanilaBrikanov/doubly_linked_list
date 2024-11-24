#include <iostream>
#include <string>

using namespace std;

// Структура элемента списка
struct Elem {
    string word;         // Слово
    int pages[10];       // Номера страниц (максимум 10)
    int pageCount;       // Количество страниц
    Elem* next;          // Указатель на следующий элемент
    Elem* prev;          // Указатель на предыдущий элемент
};

// Глобальные указатели на начало и конец списка
Elem* list_head = NULL;
Elem* list_tail = NULL;

// Функция добавления элемента в отсортированный список
void add(string word, int pages[], int pageCount) {
    Elem* newElem = new Elem;
    newElem->word = word;
    newElem->pageCount = pageCount;
    for (int i = 0; i < pageCount; i++) {
        newElem->pages[i] = pages[i];
    }
    newElem->next = newElem->prev = NULL;

    if (!list_head) { // Если список пуст
        list_head = list_tail = newElem;
    } else {
        Elem* current = list_head;

        // Найти позицию для вставки
        while (current && current->word < word) {
            current = current->next;
        }

        if (!current) { // Добавить в конец
            list_tail->next = newElem;
            newElem->prev = list_tail;
            list_tail = newElem;
        } else if (current == list_head) { // Добавить в начало
            newElem->next = list_head;
            list_head->prev = newElem;
            list_head = newElem;
        } else { // Вставить в середину
            newElem->next = current;
            newElem->prev = current->prev;
            current->prev->next = newElem;
            current->prev = newElem;
        }
    }
}

// Функция удаления элемента по слову
void remove(string word) {
    Elem* current = list_head;

    while (current && current->word != word) {
        current = current->next;
    }

    if (!current) {
        cout << "Слово не найдено.\n";
        return;
    }

    if (current == list_head) { // Удаление из начала
        list_head = list_head->next;
        if (list_head) list_head->prev = NULL;
    } else if (current == list_tail) { // Удаление из конца
        list_tail = list_tail->prev;
        if (list_tail) list_tail->next = NULL;
    } else { // Удаление из середины
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    delete current;
    cout << "Слово удалено.\n";
}

// Функция поиска элемента по слову
void search(string word) {
    Elem* current = list_head;

    while (current && current->word != word) {
        current = current->next;
    }

    if (!current) {
        cout << "Слово не найдено.\n";
    } else {
        cout << "Слово: " << current->word << ", Страницы: ";
        for (int i = 0; i < current->pageCount; i++) {
            cout << current->pages[i] << " ";
        }
        cout << endl;
    }
}

// Функция вывода списка
void display() {
    if (!list_head) {
        cout << "Список пуст.\n";
        return;
    }

    Elem* current = list_head;
    while (current) {
        cout << "Слово: " << current->word << ", Страницы: ";
        for (int i = 0; i < current->pageCount; i++) {
            cout << current->pages[i] << " ";
        }
        cout << endl;
        current = current->next;
    }
}

// Функция подсчета длины списка
int length() {
    int len = 0;
    Elem* current = list_head;
    while (current) {
        len++;
        current = current->next;
    }
    return len;
}

// Главное меню
void menu() {
    int choice;

    do {
        cout << "\nМеню:\n";
        cout << "1. Добавить слово\n";
        cout << "2. Удалить слово\n";
        cout << "3. Определить длину списка\n";
        cout << "4. Поиск слова\n";
        cout << "5. Вывод списка\n";
        cout << "6. Выход\n";
        cout << "Введите ваш выбор: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string word;
                int numPages;
                int pages[10];

                cout << "Введите слово: ";
                cin >> word;

                cout << "Введите количество страниц (не более 10): ";
                cin >> numPages;

                if (numPages > 10) {
                    cout << "Ошибка: можно указать не более 10 страниц.\n";
                    break;
                }

                cout << "Введите номера страниц: ";
                for (int i = 0; i < numPages; i++) {
                    cin >> pages[i];
                }

                add(word, pages, numPages);
                break;
            }
            case 2: {
                string word;
                cout << "Введите слово для удаления: ";
                cin >> word;
                remove(word);
                break;
            }
            case 3:
                cout << "Длина списка: " << length() << endl;
                break;
            case 4: {
                string word;
                cout << "Введите слово для поиска: ";
                cin >> word;
                search(word);
                break;
            }
            case 5:
                display();
                break;
            case 6:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 6);
}

int main() {
    menu();
    return 0;
} 
