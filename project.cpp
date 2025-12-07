#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <limits>

using namespace std;

class Browser {
private:
    stack<string> backStack;     // pages behind current
    stack<string> forwardStack;  // pages ahead of current
    queue<string> tabQueue;      // other tabs (FIFO)
    string currentPage;          // page in current tab

public:
    Browser() {
        currentPage = "home";
    }

    // visit a new page in current tab
    void visitPage(const string &url) {
        if (!currentPage.empty()) {
            backStack.push(currentPage);
        }
        currentPage = url;

        // once we go to a new page, forward history is cleared
        while (!forwardStack.empty()) {
            forwardStack.pop();
        }
        cout << "Opened: " << currentPage << endl;
    }

    // go back in history
    void goBack() {
        if (backStack.empty()) {
            cout << "No pages to go back to.\n";
            return;
        }
        forwardStack.push(currentPage);
        currentPage = backStack.top();
        backStack.pop();
        cout << "Current page: " << currentPage << endl;
    }

    // go forward in history
    void goForward() {
        if (forwardStack.empty()) {
            cout << "No pages to go forward to.\n";
            return;
        }
        backStack.push(currentPage);
        currentPage = forwardStack.top();
        forwardStack.pop();
        cout << "Current page: " << currentPage << endl;
    }

    // open a new tab; current tab is put into a queue
    void openNewTab(const string &url) {
        // store current tab's page into queue
        if (!currentPage.empty()) {
            tabQueue.push(currentPage);
        }
        // new tab starts fresh
        while (!backStack.empty()) backStack.pop();
        while (!forwardStack.empty()) forwardStack.pop();

        currentPage = url;
        cout << "New tab opened with: " << currentPage << endl;
    }

    // switch to next tab in queue (FIFO)
    void switchToNextTab() {
        if (tabQueue.empty()) {
            cout << "No other tabs available.\n";
            return;
        }
        // put current page at the back of queue
        tabQueue.push(currentPage);
        // move to front tab
        currentPage = tabQueue.front();
        tabQueue.pop();

        // history is cleared when switching tabs (simple model)
        while (!backStack.empty()) backStack.pop();
        while (!forwardStack.empty()) forwardStack.pop();

        cout << "Switched to tab with page: " << currentPage << endl;
    }

    void showStatus() {
        cout << "\n===== BROWSER STATUS =====\n";
        cout << "Current page: " << currentPage << endl;
        cout << "Back pages : " << backStack.size() << endl;
        cout << "Forward pages : " << forwardStack.size() << endl;
        cout << "Other open tabs (in queue): " << tabQueue.size() << endl;
        cout << "==========================\n";
    }
};

int main() {
    Browser browser;
    int choice;
    string url;

    do {
        cout << "\n===== Browser History Simulation (Stack + Queue) =====\n";
        cout << "1. Visit new page (current tab)\n";
        cout << "2. Go Back\n";
        cout << "3. Go Forward\n";
        cout << "4. Open New Tab\n";
        cout << "5. Switch to Next Tab (from queue)\n";
        cout << "6. Show Status\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // clear leftover newline for getline
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter URL: ";
            getline(cin, url);
            browser.visitPage(url);
            break;

        case 2:
            browser.goBack();
            break;

        case 3:
            browser.goForward();
            break;

        case 4:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter URL for new tab: ";
            getline(cin, url);
            browser.openNewTab(url);
            break;

        case 5:
            browser.switchToNextTab();
            break;

        case 6:
            browser.showStatus();
            break;

        case 0:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
