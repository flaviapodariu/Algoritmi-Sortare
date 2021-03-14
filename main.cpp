#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
using namespace std::chrono;

typedef unsigned long long int big;

vector <long long> generate_test(big vect_size, big elem_size);
vector <long long> bubbleSort(vector <long long> vect);
void MergeSort(vector <long long>& vect, int low, int high);
void Merge(vector <long long>& vect, int low, int mid, int high);
void QuickSort(vector <long long>& vect, int low, int high);
int QuickDivide(vector <long long>& vect, int low, int high);
vector <long long> CountSort(vector <long long> vect);
vector <long long> RadixSort(vector <long long> vect);
vector <long long> generateConstTest(big vect_size, big elem_size);
void menu();
void user_menu();
void treatException()
{
    int choice;
    cout << "Pentru a alege alt algoritm apasati 1. Pentru a iesi din consola apasati 0."; cout << "\n";
    cin >> choice;
    if(choice)
        menu();
    else
        return;
}

void testPrint(vector <long long> vect)
{
    for (long long i : vect)
        cout << i << " ";
}

void test_sort(vector <long long> sorted, vector <long long>not_sorted)
{
    for(int i = 0; i < sorted.size() - 1; i++)
        if(sorted[i] > sorted[i+1])
        {
            cout << "Vectorul nu a fost sortat bine."; cout << "\n";
            return;
        }
    cout << "Vectorul a fost sortat corect!"; cout << "\n";
}

big string_to_int(char str[])
{   int p = 1;
    unsigned long long n = strlen(str) - 3;  // format 10^18 => vrem doar cifrele lui x,
    big putere = 0;                     // deci scadem 3 (lungimea coresp. 10^)
    for(int i = 0; i < n; i ++)
    {
        putere = putere + p * (str[strlen(str)-1-i]- '0'); // string to int
        p = p * 10;
    }
    p = int(putere);
    putere = 1;
    for (int i = 0; i < p; i++)
        putere = 10 * putere;
    return putere;
}


void user_menu()
{
    cout << "Podariu Flavia, grupa 134, Proiect sortari SDA";   cout << "\n";
    cout << "-----------------------------------------------";  cout << "\n";
    cout << "|       1.Bubble Sort                         |";  cout << "\n";
    cout << "|       2.Merge Sort                          |";  cout << "\n";
    cout << "|       3.Quick Sort                          |";  cout << "\n";
    cout << "|       4.Count Sort                          |";  cout << "\n";
    cout << "|       5.Radix Sort                          |";  cout << "\n";
    cout << "|       6.std::sort()                         |";  cout << "\n";
    cout << "|       Petru iesire apasati 0.               |";  cout << "\n";
    cout << "-----------------------------------------------";  cout << "\n";


}

void menu()
{   int optiune, tests;
    char sizeV[6], sizeElem[6];
    big sizeV_big, sizeElem_big;
    cout << "Cifra corespunzatoare sortarii alese de dvs. este: ";
    cin >> optiune;

    if(optiune == 0)
        return;

    cout << "\n";
    cout << "Numarul de teste pe care va rula algoritmul ales este: ";
    cin >> tests;

    vector <long long> sorted;
    vector <long long> not_sorted;

    for(int i = 0; i < tests ; i++)
    {
        cout << "\n";
        cout << "Introduceti dimensiunea vectorului in format 10^x: ";
        cin >> sizeV;
        cout << "\n";
        sizeV_big = string_to_int(sizeV);
        cout << "Introduceti dimensiunea maxima a elementelor in format 10^x: ";
        cin >> sizeElem;
        cout << "\n";
        sizeElem_big = string_to_int(sizeElem);

            if(optiune == 1)  // BUBBLE SORT
            {
                if (sizeV_big >=1e5)
                    {
                        cout << "Pentru a sorta acest input, algoritmul ales ia prea mult timp!";  cout << "\n";
                        treatException();
                    }

                not_sorted = generate_test(sizeV_big ,sizeElem_big);
                auto startBubble = steady_clock::now();
                sorted = bubbleSort(not_sorted);
                auto stopBubble = steady_clock::now();
                auto durationBubble = duration_cast <nanoseconds>(stopBubble - startBubble);
                cout<< "Sortarea vectorului random s-a realizat in "<<durationBubble.count()/(1e9)<< " secunde"<<"\n";

//              test_sort(sorted, not_sorted);

                not_sorted = generateConstTest(sizeV_big, sizeElem_big);
                startBubble = steady_clock::now();
                sorted = bubbleSort(not_sorted);
                stopBubble = steady_clock::now();
                durationBubble = duration_cast <nanoseconds>(stopBubble - startBubble);
                cout<< "Sortarea vectorului constant s-a realizat in "<<durationBubble.count()/(1e9)<< " secunde"<<"\n";
//                    test_sort(sorted, not_sorted);
            }

            else
            if (optiune == 2)  // MERGE SORT
            {   not_sorted = generate_test(sizeV_big ,sizeElem_big);

                auto startMS = steady_clock::now();
                MergeSort(not_sorted, 0, int(sizeV_big)-1);
                auto stopMS = steady_clock::now();

                auto durationMS = duration_cast<nanoseconds>(stopMS - startMS);
                cout << "Sortarea vectorului random s-a realizat in "<<durationMS.count()/(1e9)<< " secunde"<<"\n";

                not_sorted = generateConstTest(sizeV_big, sizeElem_big);
                startMS = steady_clock::now();
                MergeSort(not_sorted, 0, int(sizeV_big)-1);
                stopMS = steady_clock::now();
                durationMS = duration_cast<nanoseconds>(stopMS - startMS);
                cout << "Sortarea vectorului constant s-a realizat in "<<durationMS.count()/(1e9)<< " secunde"<<"\n";


            }
            else

            if (optiune == 3)   // QUICK SORT
               { not_sorted = generate_test(sizeV_big, sizeElem_big);

                 auto startQuick = steady_clock::now();
                 QuickSort(not_sorted, 0, int(sizeV_big)-1);
                 auto stopQuick = steady_clock::now();

                 auto durationQuick = duration_cast<nanoseconds>(stopQuick - startQuick);
                 cout << "Sortarea elementelor random s-a realizat in "<<durationQuick.count()/(1e9)<< " secunde"<<"\n";

                 if(sizeV_big >= 1e5)
                 {
                     cout << "Algoritmul ales nu poate sorta pentru input-ul ales. (stack overflow)";  cout << "\n";
                     treatException();
                 }


                 not_sorted = generateConstTest(sizeV_big, sizeElem_big);
                 startQuick = steady_clock::now();
                 QuickSort(not_sorted, 0, int(sizeV_big) - 1);
                 stopQuick = steady_clock::now();
                 durationQuick = duration_cast<nanoseconds>(stopQuick - startQuick);
                 cout << "Sortarea elementelor constante s-a realizat in "<<durationQuick.count()/(1e9)<< " secunde"<<"\n";
//                 testPrint(not_sorted);
               }


            else
            if (optiune == 4)   // COUNT SORT
            {
                if(sizeElem_big / sizeV_big >= 10 || sizeElem_big >= 1e9)
                {
                    cout << "Algoritmul ales nu poate sorta pentru input-ul ales.";  cout << "\n";
                    treatException();
                }


                not_sorted = generate_test(sizeV_big, sizeElem_big);

                auto startCount = steady_clock::now();
                sorted = CountSort(not_sorted);
                auto stopCount = steady_clock::now();
                auto durationCount = duration_cast<nanoseconds>(stopCount - startCount);
                cout << "Sortarea vectorului random s-a realizat in "<< durationCount.count()/(1e9)<< " secunde"<<"\n";

                not_sorted = generateConstTest(sizeV_big, sizeElem_big);
                startCount = steady_clock::now();
                sorted = CountSort(not_sorted);
                stopCount = steady_clock::now();
                durationCount = duration_cast<nanoseconds>(stopCount - startCount);
                cout << "Sortarea vectorului constant s-a realizat in "<< durationCount.count()/(1e9)<< " secunde"<<"\n";
//                testPrint(sorted);

            }

            else
            if (optiune == 5)
            {
             not_sorted = generate_test(sizeV_big, sizeElem_big);
             auto startRadix = steady_clock::now();
             sorted = RadixSort(not_sorted);
             auto stopRadix = steady_clock::now();
             auto durationRadix = duration_cast<nanoseconds>(stopRadix - startRadix);
             cout << "Sortarea vectorului random s-a realizat in "<<durationRadix.count()/1e9<< " secunde"<<"\n";

             not_sorted = generateConstTest(sizeV_big, sizeElem_big);
             startRadix = steady_clock::now();
             sorted = RadixSort(not_sorted);
             stopRadix = steady_clock::now();
             durationRadix = duration_cast<nanoseconds>(stopRadix - startRadix);
             cout << "Sortarea vectorului constant s-a realizat in "<<durationRadix.count()/1e9<< " secunde"<<"\n";
//             testPrint(sorted);
            }
            else
            if (optiune == 6)
            {
                not_sorted = generate_test(sizeV_big, sizeElem_big);
                auto startCppSort = steady_clock::now();
                sort(not_sorted.begin(), not_sorted.end());
                auto stopCppSort = steady_clock::now();
                auto durationCppSort = duration_cast<nanoseconds>(stopCppSort - startCppSort);
                cout << "Sortarea vectorului random s-a realizat in "<<durationCppSort.count()/1e9<< " secunde"<<"\n";

                not_sorted = generateConstTest(sizeV_big, sizeElem_big);
                startCppSort = steady_clock::now();
                sort(not_sorted.begin(), not_sorted.end());
                stopCppSort = steady_clock::now();
                durationCppSort = duration_cast<nanoseconds>(stopCppSort - startCppSort);
                cout << "Sortarea vectorului constant s-a realizat in "<<durationCppSort.count()/1e9<< " secunde"<<"\n";
//                testPrint(not_sorted);
            }
            if(optiune < 0 || optiune > 6)
            {
                system("cls");
                user_menu();
                cout << "Optiune invalida. Incercati din nou!"; cout << "\n";
                menu();
            }

        }


    cout << "Pentru a incerca un alt algoritm apasati 1, pentru iesire apasati 0.  ";
    cin >> optiune;
    cout << "\n\n";
    if (optiune)
        menu();
    else return;
}

vector<long long> generate_test(big vect_size, big elem_size)
{   vector<long long> vect;

    srand(time(nullptr));

    for (big j = 0; j < vect_size; j++)
        vect.push_back(rand()%(elem_size+1)*rand()%(elem_size+1));
    return vect;
}

vector <long long> generateConstTest(big vect_size, big elem_size)
{   long long val = rand()%(elem_size+1);
    vector<long long> vect;
    vect.reserve(vect_size);
    for(big i = 0 ; i < vect_size; i++)
        vect.push_back(val);
    return vect;

}

vector<long long> bubbleSort(vector <long long> vect)
{
    for(unsigned int i = 0; i< vect.size(); i++)
        for(unsigned int j = 0; j <vect.size()-i-1; j++)
            if(vect[j]> vect[j+1])
                swap(vect[j], vect[j+1]);
    return vect;
}
//------------------------------------------ Functiile pt Merge Sort ------------------------------------------------------------------

void Merge(vector<long long>& vect, int low, int mid, int high) {
    vector <long long> Left;
    vector <long long> Right;

    int size1 = mid - low + 1;
    int size2 = high - mid;

    Left.reserve(size1);
    Right.reserve(size2);

    for (int i = 0; i < size1; i++)
        Left.push_back(vect[low+i]);

    for (int j = 0; j < size2; j++)
        Right.push_back(vect[mid+j+1]);

    int idxLeft = 0, idxRight = 0, idxVect = low;

    while(idxLeft < size1 && idxRight < size2)
    {
        if(Left[idxLeft] <= Right[idxRight])
            vect[idxVect++] = Left[idxLeft++];
        else
            vect[idxVect++] = Right[idxRight++];
    }
    if(idxLeft < size1)
        for(int i = idxLeft; i < size1; i++)
            vect[idxVect++] = Left[i];

    if(idxRight < size2)
        for(int i = idxRight; i < size2; i++)
            vect[idxVect++] = Right[i];

}

void MergeSort(vector <long long>& vect, int low, int high)
{
    if (low >= high)
        return;
    int mid = low + (high - low) / 2;
    MergeSort(vect, low, mid);
    MergeSort(vect, mid+1, high);
    Merge(vect, low, mid ,high);

}
//----------------------------------------------Functiile pt Quick Sort-------------------------------------------------------------------------------

void QuickSort(vector <long long>& vect, int low, int high)
{
    if(low >= high)
        return;
    int sorted_elem = QuickDivide(vect, low, high);
    QuickSort(vect, low, sorted_elem-1);
    QuickSort(vect, sorted_elem+1, high);
}

int QuickDivide(vector <long long>& vect, int low, int high)
{   long long  pivot = vect[high];
    int pos = low;
    for(int i = low; i < high; i++)
    {
        if (vect[i] <= pivot)
        {
            swap(vect[i], vect[pos]);
            pos++;
        }
    }

    swap(vect[pos], vect[high]);
    return pos;
}
//-----------------------------------------------------Count Sort----------------------------------------------------
vector <long long> CountSort(vector <long long> vect)
{
    vector <long long> counter(vect.size(), 0);
    long long maxi = -1;
    for(long long i: vect)
    {
        counter[i]++;
        if (i > maxi)
            maxi = i;
    }
    vect.clear();
    vect.reserve(maxi);
    for(int i = 0; i < maxi; i++)
        if (counter[i] != 0)
            for(int j = 0 ; j < counter[i]; j++)
                vect.push_back(i);
    return vect;
}
//--------------------------------------------------------- Functii Radix Sort --------------------------------------------------------------------
int bit(long long number, int shiftValue)
{
    int mask = 1 << shiftValue;
    if ((number & mask) != 0)
        return 1;
    return 0;
}

vector <long long> RadixSort(vector <long long> vect)
{
    for(int bitVal = 0; bitVal <= 64; bitVal++)
    {
        long long *queue0 = new long long[vect.size()];
        long long *queue1 = new long long[vect.size()];
        long long idx0 = 0, idx1 = 0;

        for(long long elem: vect)
            if(bit(elem, bitVal) == 0)
                queue0[idx0++] = elem;
            else
                queue0[idx1++] = elem;
        if(idx1 == 0)
            return vect;
        int index = 0;
        long long i0 = 0, i1= 0;

        while(i0 < idx0)
            vect[index++] = queue0[i0++];

        while(i1 < idx1)
            vect[index++] = queue1[i1++];
//      testPrint(vect);

    }
    return vect;
}

int main() {
    user_menu();
    menu();
    return 0;
}