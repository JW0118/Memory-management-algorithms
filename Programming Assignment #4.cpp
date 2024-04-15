//josh wells
//P676W568
//PA4
//15Apr24
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

//Printing function
void printCurrentStep(int step, int page, const unordered_set<int>& currentPageSet, int faults) {
    //Print the step number page fault and page table
    cout << "Step " << step << ": Page fault (" << page << ") - Page Table: {";

    bool isFirst = true;

    //Traverse over the current page set to print its contents
    for (int currentPage : currentPageSet) {

        //Check if it's not the first variable
        if (!isFirst) cout << ", ";
        cout << currentPage;
        isFirst = false;
    }
    //Printing the frames
    cout << "}, Frames: [";

    isFirst = true;
    for (int currentPage : currentPageSet) {

        if (!isFirst) cout << ", ";
        cout << currentPage; 
        isFirst = false;

    }
    //Printing the total number of faults
    cout << "], Faults: " << faults << endl;
}
//LRU replacement algoritm
int lruRep(const vector<int>& refString, int numFrames) {
    vector<int> loadedPages; //stores current loaded pages
    int faults = 0; //count of faults

    //Loop through each page in the reference string
    for (int page : refString) {
   

        auto it = find(loadedPages.begin(), loadedPages.end(), page);

        if (it != loadedPages.end()) {
            //move the page to the end of the list to indicate it's the most recently used
            loadedPages.erase(it);
            loadedPages.push_back(page);
         
        }
        else {
            //increment page faults
            ++faults;

            //if memory is not full ad page to memory
            if (loadedPages.size() < numFrames) {
                loadedPages.push_back(page);
            }
            else {

                //if memory is full erase the first page in the list
                loadedPages.erase(loadedPages.begin());
                // Add the new page to memory
                loadedPages.push_back(page);
            }
        }
        //Print the current step of page replacement
        printCurrentStep(distance(refString.begin(), find(refString.begin(), refString.end(), page)) + 1, page, unordered_set<int>(loadedPages.begin(), loadedPages.end()), faults);
    }

    return faults;
}


//Optimal rreplacement algorithm
int optRep(const vector<int>& refString, int numFrames) {

    unordered_set<int> currentPageSet; //stores current loaded pages
    int faults = 0; //Count of page faults

    // loop through each page in the string
    for (int i = 0; i < refString.size(); ++i) {
        int page = refString[i]; //Current page
        //if the page is already in memory continue to the next page
        if (currentPageSet.find(page) != currentPageSet.end()) {
            continue;
        }
        ++faults; // Increment page faults
        // If memory is full find the page that will not be used for the longest time
        if (currentPageSet.size() == numFrames) {

            int farthest = -1, farthestPage = -1;
            //iterating over page currently loaded
            for (int myPage : currentPageSet) {

                int nextOccurrence = INT_MAX;
                // searching for the next occurrence of the current page in the reference string
                for (int j = i + 1; j < refString.size(); ++j) {

                    if (refString[j] == myPage) {

                        nextOccurrence = j;
                        break;
                    }
                }
                //finding page that will be used least
                if (nextOccurrence > farthest) {

                    farthest = nextOccurrence;

                    farthestPage = myPage;
                }
            }
            currentPageSet.erase(farthestPage);
        }
        currentPageSet.insert(page);
        //printing
        printCurrentStep(i + 1, page, currentPageSet, faults);
    }

    return faults;
}

// FIFO Page Replacement Algorithm
int fifoRep(const vector<int>& refString, int numFrames) {

    unordered_set<int> loadedPages; // stores currently loaded pages
    queue<int> pageQueue; //keep track of order

    int faults = 0; // Count of page faults


    // Loop through each page in the reference string
    for (int page : refString) {

        // If the page is already in memory continue to the next page
        if (loadedPages.find(page) != loadedPages.end()) {

            continue;
        }
        ++faults; //incrementing page fault count
        // if memory is full removeing the oldest page
        if (loadedPages.size() == numFrames) {


            int val = pageQueue.front();

            pageQueue.pop();

            loadedPages.erase(val);

        }

        loadedPages.insert(page);
        pageQueue.push(page);

        // printing
        printCurrentStep(distance(refString.begin(), find(refString.begin(), refString.end(), page)) + 1, page, loadedPages, faults);
    }

    return faults;
}


int main() {
    vector<int> refString = { 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5 };
    int numFrames = 4;

    //calling lruRep function
    cout << "For LRU Algorithm:" << endl;
    int lruErrors = lruRep(refString, numFrames);
    cout << "Total Errors: " << lruErrors << endl << endl;

    //calling optRep function
    cout << "For Optimal Algorithm:" << endl;
    int optErrors = optRep(refString, numFrames);
    cout << "Total Errors: " << optErrors << endl << endl;

    //calling fifoRep function
    cout << "For FIFO Algorithm:" << endl;
    int fifoErrors = fifoRep(refString, numFrames);
    cout << "Total Errors: " << fifoErrors << endl << endl;
}
