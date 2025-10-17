#include "error.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;

void injectSingleBitError(string &data)
{
    /* flip a single random bit */
    srand(time(0));
    int bit_to_flip = rand() % data.length();
    // if (data != "00011101")
    // {
    //     int bit_to_flip = 0;
    //     data[bit_to_flip] = (data[bit_to_flip] == '0') ? '1' : '0';
    // }
    data[bit_to_flip] = (data[bit_to_flip] == '0') ? '1' : '0';
}

void injectTwoBitError(string &data)
{
    /* Inject two isolated single-bit errors */
    srand(time(0));
    int length = data.length();
    int pos1 = rand() % length, pos2 = rand() % length;

    /* finding two different positions */
    while (pos1 == pos2)
        pos2 = rand() % length;

    data[pos1] = (data[pos1] == '0' ? '1' : '0');
    data[pos2] = (data[pos2] == '0' ? '1' : '0');
}

void injectBurstError(string &data)
{
    /* Inject a burst error of given length */
    srand(time(0));
    int n = data.length();
    int burstLength = rand() % n + 1;
    int start = rand() % (n - burstLength + 1);
    for (int i = start; i < start + burstLength; i++)
        data[i] = (data[i] == '0') ? '1' : '0';
}

void injectOddError(string &data)
{
    /* Inject an odd number of single-bit errors */
    int n = data.length();

    int numErrors = (rand() % (n / 2)) * 2 + 1;
    set<int> indices;

    while (indices.size() < numErrors)
        indices.insert(rand() % n);

    for (int pos : indices)
        data[pos] = (data[pos] == '0') ? '1' : '0';
}