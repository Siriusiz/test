#include <iostream>
using namespace std;
/* 把拿钉子问题抽象为完全背包问题（即可拿的物品数量为2，重量分别为4和9，代价为1和1），目标是对给定的N（容量上限）求出最优解，使得数量最少。
   在最后的位置加入判断，若总共的钉子数量不等于N，则返回-1；否则返回总数量。
   用f(N)代表输入容量为N时的最优解，则f(N) = f(i) + f(N - i)，且钉子的总数最接近N，其中i的范围是[1, N/2]。这里的思想和动态规划剪绳子那个题类似，可以去看剑指offer。
   */

struct Results                             //声明一个结构体，用来存储每个位置的最优解
{
    int number_of_9;                       //存储N位置时9的最优个数
    int number_of_4;                       //存储N位置时4的最优个数
};

int Min_Number(int n)                       //输入n，返回总共的数量，若不能刚好拿够N个钉子，则返回-1
{
    Results* cache = new Results[n];        //创建一个动态结构体数组，长度为N
    for(int i = 0; i <= n; ++i)             //初始化
    {
        if(i == 3)                          //在第四项（cache[3]）的位置赋值(1, 0), 因为N=4时只有唯一解
        {
            cache[i].number_of_4 = 1;       
            cache[i].number_of_9 = 0;
        }
        else if(i == 8)                     //在第九项(cache[8])的位置赋值(0, 1)，因为N=9时只有唯一解
        {
            cache[i].number_of_4 = 0;
            cache[i].number_of_9 = 1;
        }
        else                                //其余初始化为(0, 0)
        {
            cache[i].number_of_4 = 0;
            cache[i].number_of_9 = 0;
        }
    }

    for(int i = 4; i <= n; i++)             //从第五项开始(N=5)。
    {
        int temp = 0, temp_1 = 0;           //temp存储当前最优解可以拿到的钉子总数，temp_1存储最接近N的钉子总数
        int data_1 = 0, data_2 = 0;         //data_1存储最后的得到的第N项最优解中4的数量，data_2存储最后的得到的第N项最优解中9的数量
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
    // cout << cache[n].number_of_4 << endl;
    // cout << cache[n].number_of_9 << endl;
    int final_number_of_9 = cache[n].number_of_9;
    int final_number_of_4 = cache[n].number_of_4;
    delete[] cache;
    if(final_number_of_9* 9 + final_number_of_4 * 4 != n)
        return -1;
    else
        return final_number_of_4 + final_number_of_9;
}

int main()
{
    int n;
    cin >> n;
    cout << Min_Number(n);

    return 0;
}
