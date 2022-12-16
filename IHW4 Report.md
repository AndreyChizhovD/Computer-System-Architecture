# Отчет по ИДЗ-4
# Чижов Андрей Дмитриевич БПИ218
# вариант 14
```
Задача о гостинице - 3 (дамы и джентльмены). 
В гостинице 10 номеров рассчитаны на одного человека и 15 номеров рассчитаны на двух человек. 
В гостиницу случайно приходят клиенты дамы и клиенты джентльмены,
и конечно они могут провести ночь в номере только с представителем своего
пола. Если для клиента не находится подходящего номера, он уходит искать
ночлег в другое место. Клиенты порождаются динамически и уничтожаются
при освобождении номера или уходе из гостиницы при невозможности поселиться. 
Создать многопоточное приложение, моделирующее работу гостиницы.
```
## 7
## C++
## подключенные библиотеки
```cpp
#include <iostream>
#include <vector>
#include <time.h>
#include <pthread.h>
#include <fstream>

```
## определим фигурирующие в задаче объекты и имплементируем вспомогательные структуры
### будем представлять клиента как объект с двумя признаками: пол и номер(имя)
```cpp
using namespace std;

struct Client {
    int sex = 1;
    int number = 0;
};

```
### далее определим два вида комнат в гостинице
### Room1 - одноместная, Room2 - двухместная.
```cpp

struct Room1 {
    Client *client;
};

struct Room2 {
    Client *first_client;
    Client *second_client;
};

```
### будем хранить информацию о комнатах в соответствующих массивах,
### с размерами - задаваемыми параметрами
```cpp

int n, m;
vector<Room1> rooms1 = {};
vector<Room2> rooms2 = {};

```
### так будет генерироваться новопришедший гость
```cpp
Client *createRandomClient() {
    Client *client = new Client;

    int sex = rand() % 2;
    int number = rand() % 100 + 1;

    client->sex = sex;
    client->number = number;

    cout << "client (";
    if (client->sex == 1) {
        cout << "M";
    } else {
        cout << "W";
    }
    cout << ") " << client->number;

    return client;
}
```
### концептуально можно вообразить гостиницу с двумя опциями при заселении - в одноместную или двухместную комнату
### тогда при заселении человек подходит либо к одной стойке, либо к другой
### все это происходит одновременно
### что-то подобное можно реализовать с помощью двух параллельных итеративных потоков, каждый из которых будет "заполнять номера гостиницы" суть массивы
```cpp

    pthread_t thread1;
    pthread_t thread2;

    clock_t start_time = clock();

    if (pthread_create(&thread1, nullptr, thread1_func, nullptr)) {
        return EXIT_FAILURE;
    }

    if (pthread_create(&thread2, nullptr, thread2_func, nullptr)) {
        return EXIT_FAILURE;
    }
    
```
## далее определим функции, которые будем передавать в потоки
### thread_func1 совершает 2n итераций динамического "создания клиента", выводя на экран информацию о заселении или незаселении пришедшего гостя 

```cpp

void *thread1_func(void *) {
    for (int i = 0; i < 2 * n; ++i) {
        func1();
    }
}
```
```cpp

void func1() {
    auto client = createRandomClient();

    if (rooms1.size() == n) {
        cout << " can't take single room because all single rooms are taken.\n";
        delete client;
    } else {
        rooms1.push_back(Room1{client});
        cout << " took single room number " << rooms1.size() << "\n";
    }
}
```
### по аналогии работает thread_func2 за исключением дополнительных проверок
### проверям можно ли заселиться в комнату вторым, т.е. осуществляем проверку на совпадение пола пришедшего и уже живущего в комнате
```cpp
void *thread2_func(void *) {
    for (int i = 0; i < 2 * m; ++i) {
        func2();
    }
}
```
```cpp
void func2() {
    auto client = createRandomClient();

    if (rooms2.size() == m) {
        cout << " can't take double room because all rooms are taken.\n";
        delete client;
        return;
    }
    int room = findSpareRoom(client);

    if (room == -1) {
        rooms2.push_back(Room2{client, nullptr});
        cout << " took double room number " << rooms2.size() << "\n";
    }
}
```
```cpp
int findSpareRoom(Client *client) {
    for (int i = 0; i < rooms2.size(); ++i) {
        if (rooms2[i].first_client == nullptr) {
            rooms2[i].first_client = client;
            cout << " took double room number " << i + 1 << "\n";
            return i;
        } else if (rooms2[i].second_client == nullptr &&
                   rooms2[i].first_client->sex == client->sex) {
            rooms2[i].second_client = client;
            cout << " took double room number " << i + 1 << " with client "
                 << rooms2[i].first_client->number << "\n";
            return i;
        }
    }

    return -1;
}
```
### получаем что-то похожее на случайную последовательность обработок случайных запросов
## input.txt
```
10 15
```
## output.txt
```
client (M) 68 took double room number 1
client (W) 1 took single room number 2
client (W) 1 took double room number 2
client (W) 25 took double room number 1 with client 68
client (W) 59 took double room number 2 with client 1
client (W) 65 took double room number 3
client (M) 46 took double room number 4
client (M) 28 took double room number 4 with client 46
client (M) 92 took double room number 5
client (M) 43 took double room number 5 with client 92
client (M) 37 took double room number 6
client (M) 5 took double room number 6 with client 37
client (W) 54 took double room number 3 with client 65
client (W) 83 took double room number 7
client (M) 17 took double room number 8
client (M) 25 took single room number 3
client (W) 59 took single room number 4
client (W) 96 took double room number 7 with client 83
client (M) 27 took double room number 8 with client 17
client (M) 39 took double room number 9
client (W) 13 took double room number 9 with client 39
client (M) 100 took double room number 10
client (M) 95 took double room number 10 with client 100
client (M) 12 took double room number 11
client (W) 34 took double room number 12
client (M) 65 took double room number 11 with client 12
client (M) 12 took double room number 13
client (M) 69 took double room number 13 with client 12
client (M) 45 took double room number 14
client (W) 58 took double room number 12 with client 34
client (M) 60 took double room number 14 with client 45
client (M) 42 took double room number 15
client (W) 65 took single room number 5
client (M) 46 took single room number 6
client (M) 28 took single room number 7
client (M) 92 took single room number 8
client (M) 43 took single room number 9
client (M) 37 took single room number 10
client (M) 5 can't take single room because all single rooms are taken.
client (W) 54 can't take single room because all single rooms are taken.
client (W) 83 can't take single room because all single rooms are taken.
client (M) 17 can't take single room because all single rooms are taken.
client (W) 96 can't take single room because all single rooms are taken.
client (M) 27 can't take single room because all single rooms are taken.
client (M) 39 can't take single room because all single rooms are taken.
client (M) 13 can't take single room because all single rooms are taken.
client (M) 79 can't take double room because all rooms are taken.
client (M) 100 can't take single room because all single rooms are taken.
client (M) 95 can't take single room because all single rooms are taken.

068ms
```
