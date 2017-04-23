#include <iostream>
#include <vector>

#include <thread>
#include "echo_server.h"

using namespace std;

echo_server* server;

void run_server() {
    cout << "HI I AM THREAD" << endl;
    try {
        server = new echo_server();
        server->start();
    } catch (exception* e) {
        cerr << "\nERROR: " << e->what() << endl;
    }
}

int main() {
    cout << "HI I AM SERVER" << endl;

    /* std::thread t_server = std::thread(run_server); */
    run_server();

    /* string n; */
    /* cin >> n; */

    server->close();

    /* t_server.join(); */

    cout << "BYE BYE <3 <3 <3" << endl;

    return 0;
}
