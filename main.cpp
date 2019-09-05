#include <iostream>
using namespace std;

struct Results                             //
{
    int number_of_9;
    int number_of_4;
};

int Min_Number(int n)
{
    Results* cache = new Results[n];
    for(int i = 0; i <= n; ++i)
    {
        if(i == 3)
        {
            cache[i].number_of_4 = 1;
            cache[i].number_of_9 = 0;
        }
        else if(i == 8)
        {
            cache[i].number_of_4 = 0;
            cache[i].number_of_9 = 1;
        }
        else
        {
            cache[i].number_of_4 = 0;
            cache[i].number_of_9 = 0;
        }
    }

    for(int i = 4; i <= n; i++)
    {
        int temp = 0, temp_1 = 0;
        int data_1 = 0, data_2 = 0;
        if(cache[i].number_of_4 == 0 && cache[i].number_of_9 == 0)
        {
            for(int j = 1; j <= i / 2; j++)
            {
                temp = (cache[j].number_of_9 + cache[i - j].number_of_9) * 9 +
                        (cache[j].number_of_4 + cache[i - j].number_of_4) * 4;
                if(temp <= i && temp >= temp_1)
                {
                    temp_1 = temp;
                    data_1 = cache[j].number_of_4 + cache[i - j].number_of_4;
                    data_2 = cache[j].number_of_9 + cache[i - j].number_of_9;
                }
            }
            cache[i].number_of_4 = data_1;
            cache[i].number_of_9 = data_2;
        }
    }
    cout << cache[n].number_of_4 << endl;
    cout << cache[n].number_of_9 << endl;
    // return cache[n].number_of_9 + cache[n].number_of_4;
    if(cache[n].number_of_9 * 9 + cache[n].number_of_4 * 4 != n)
        return -1;
    else
        return cache[n].number_of_4 + cache[n].number_of_9;
}

int main()
{
    int n;
    cin >> n;
    cout << Min_Number(n);

    return 0;
}