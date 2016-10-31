#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <random>
using namespace std;

class random_walk
{
private:
    float matr[11][11];

public:
    int steps, n;
    float buf[11][11];
    float tv[11][11];


    void setData()
    {
        cout << "Enter the number of steps: ";
        cin >> steps;
        cout << "Enter the number of iterations: ";
        cin >> n;
    }

    inline void makeSteps()
    {
        int x = 5;
        int y = 5;
        for(int i = 0; i < steps; i++) {
            int buf = rand() % 4;
            if(buf == 0) {
                x -= 1;
                if(i == steps - 1)
                    matr[x][y] += 1;
                continue;
            }
            if(buf == 1) {
                y += 1;
                if(i == steps - 1)
                    matr[x][y] += 1;
                continue;
            }
            if(buf == 2) {
                x += 1;
                if(i == steps - 1)
                    matr[x][y] += 1;
                continue;
            }
            if(buf == 3) {
                y -= 1;
                if(i == steps - 1)
                    matr[x][y] += 1;
                continue;
            }
        }
    }

    void iteration()
    {
        for(int i = 1; i < n; i++)
            makeSteps();
    }

    void clearMatr()
    {
        for(int i = 0; i < 11; ++i) {
            for(int j = 0; j < 11; ++j) {
                matr[i][j] = 0;
                buf[i][j] = 0;
                tv[i][j] = 0;
            }
        }
    }

    void posteriorOut()
    {
        cout << endl << "posterior:" << endl;
        for(int i = 0; i < 11; i++) {
            for(int j = 0; j < 11; j++) {
                cout.width(9);
                if (matr[i][j] == 0){
                cout << ' ';
                }
                    else
                    {
                cout << round(matr[i][j]) / n;
                    }
            }
            cout << endl;
        }
    }

    void priorOut()
    {
		cout << "prior:" << endl;
        int tmp = 0;
        for(int i = 0; i < 11; ++i) {
            for(int j = 0; j < 11; ++j) {
                tv[i][j] = 0;
                buf[i][j] = 0;
            }
        }
        tv[5][5] = 1; //вероятность на нулевом шаге
        while(tmp < steps) {
            for(int i = 0; i < 11; i++)
                for(int j = 0; j < 11; j++) {
                    if(i == 0) {
                        if(j == 0) {
                            buf[i][j] = (tv[i + 1][j] + tv[i][j + 1]) / 4;
                            continue;
                        }
                        if(j == 10) {
                            buf[i][j] = (tv[i + 1][j] + tv[i][j - 1]) / 4;
                            continue;
                        }
                        buf[i][j] = (tv[i + 1][j] + tv[i][j - 1] + tv[i][j + 1]) / 4;
                        continue;
                    }
                    if(i == 10) {
                        if(j == 0) {
                            buf[i][j] = (tv[i - 1][j] + tv[i][j + 1]) / 4;
                            continue;
                        }
                        if(j == 10) {
                            buf[i][j] = (tv[i - 1][j] + tv[i][j - 1]) / 4;
                            continue;
                        }
                        buf[i][j] = (tv[i - 1][j] + tv[i][j - 1] + tv[i][j + 1]) / 4;
                        continue;
                    }

                    if(j == 0) {
                        buf[i][j] = (tv[i - 1][j] + tv[i + 1][j] + tv[i][j + 1]) / 4;
                        continue;
                    }
                    if(j == 10) {
                        buf[i][j] = (tv[i - 1][j] + tv[i + 1][j] + tv[i][j - 1]) / 4;
                        continue;
                    }
                    buf[i][j] = (tv[i - 1][j] + tv[i + 1][j] + tv[i][j - 1] + tv[i][j + 1]) / 4;
                }

            tmp += 1;
            for(int i = 0; i < 11; ++i) {
                for(int j = 0; j < 11; ++j) {
                    tv[i][j] = buf[i][j];
                }
            }
        }

        for(int i = 0; i < 11; ++i) {
            for(int j = 0; j < 11; ++j) {
                cout.width(9);
                    if (tv[i][j] == 0)
                    {
                        cout <<' ';
                    }
                    else
                    {
                    cout << round(tv[i][j] * n) / n;
                    }
                }
            
            cout << endl;
            }
    }
    
    void priorOutLimited()
    {
		cout << "prior with limitations:" << endl;
        int tmp = 0;
        for(int i = 0; i < 11; ++i) {
            for(int j = 0; j < 11; ++j) {
                tv[i][j] = 0;
                buf[i][j] = 0;
            }
        }
        tv[5][5] = 1; //вероятность на нулевом шаге
        while(tmp < steps) {
            for(int i = 0; i < 11; i++)
                for(int j = 0; j < 11; j++) {
                    if(i == 0) {
                        if(j == 0) {
                            buf[i][j] = (tv[i + 1][j] + tv[i][j + 1]) / 4;
                            continue;
                        }
                        if(j == 10) {
                            buf[i][j] = (tv[i + 1][j] + tv[i][j - 1]) / 4;
                            continue;
                        }
                        buf[i][j] = (tv[i + 1][j] + tv[i][j - 1] + tv[i][j + 1]) / 4;
                        continue;
                    }
                    if(i == 10) {
                        if(j == 0) {
                            buf[i][j] = (tv[i - 1][j] + tv[i][j + 1]) / 4;
                            continue;
                        }
                        if(j == 10) {
                            buf[i][j] = (tv[i - 1][j] + tv[i][j - 1]) / 4;
                            continue;
                        }
                        buf[i][j] = (tv[i - 1][j] + tv[i][j - 1] + tv[i][j + 1]) / 4;
                        continue;
                    }

                    if(j == 0) {
                        buf[i][j] = (tv[i - 1][j] + tv[i + 1][j] + tv[i][j + 1]) / 4;
                        continue;
                    }
                    if(j == 10) {
                        buf[i][j] = (tv[i - 1][j] + tv[i + 1][j] + tv[i][j - 1]) / 4;
                        continue;
                    }
                    
                    if (((i == 5) && (j == 6))) {
                        buf[i][j] = (tv[i + 1][j] + tv[i][j - 1] + tv[i][j + 1]) / 4;
                        continue;
                    }
                    
                    if (((i == 4) && (j == 6))) {
                        buf[i][j] = (tv[i - 1][j] + tv[i][j - 1] + tv[i][j + 1]) / 4;
                        continue;
                    }
                    buf[i][j] = (tv[i - 1][j] + tv[i + 1][j] + tv[i][j - 1] + tv[i][j + 1]) / 4;
                }

            tmp += 1;
            for(int i = 0; i < 11; ++i) {
                for(int j = 0; j < 11; ++j) {
                    tv[i][j] = buf[i][j];
                }
            }
        }

        for(int i = 0; i < 11; ++i) {
            for(int j = 0; j < 11; ++j) {
                cout.width(9);
                    if (tv[i][j] == 0)
                    {
                        cout <<' ';
                    }
                    else
                    {
                    cout << round(tv[i][j] * n) / n;
                    }
                }
            
            cout << endl;
            }
    }
    
    inline void makeStepsLimited()  //ATTENTION!!! IMPORTANT!!! 
    {                               //x is row, y is column
        int x = 5;                  //0 up, 1 right, 2 down, 3 left
        int y = 5;
        for(int i = 0; i < steps; i++) {
            if ((x == 5) && (y == 6)) {
                int buflim1 = rand() % 3;
                if(buflim1 == 0) {
                   y += 1;
                if(i == steps - 1)
                    matr[x][y] += 1;
                continue;
            }
            if(buflim1 == 1) {
                x += 1;
                if(i == steps - 1)
                    matr[x][y] += 1;
                continue;
            }
            if(buflim1 == 2) {
                y -= 1;
                if(i == steps - 1)
                    matr[x][y] += 1;
                continue;
            }
            }
            
            if ((x == 4) && (y == 6)) {
                int buflim2 = rand() % 3;
                if(buflim2 == 0) {
                   x -= 1;
                if(i == steps - 1)
                    matr[x][y] += 1;
                continue;
            }
            if(buflim2 == 1) {
                y += 1;
                if(i == steps - 1)
                    matr[x][y] += 1;
                continue;
            }
            if(buflim2 == 2) {
                y -= 1;
                if(i == steps - 1)
                    matr[x][y] += 1;
                continue;
            }
            }
            
            int buf = rand() % 4;
            if(buf == 0) {
                x -= 1;
                if(i == steps - 1)
                    matr[x][y] += 1;
                continue;
            }
            if(buf == 1) {
                y += 1;
                if(i == steps - 1)
                    matr[x][y] += 1;
                continue;
            }
            if(buf == 2) {
                x += 1;
                if(i == steps - 1)
                    matr[x][y] += 1;
                continue;
            }
            if(buf == 3) {
                y -= 1;
                if(i == steps - 1)
                    matr[x][y] += 1;
                continue;
            }
        }
    }
    
    void iterationLimited()
    {
        for(int i = 1; i < n; i++)
            makeStepsLimited();
    }
    
    void posteriorOutLimited()
    {
        cout << endl << "posterior with limitations:" << endl;
        for(int i = 0; i < 11; i++) {
            for(int j = 0; j < 11; j++) {
                cout.width(9);
                if (matr[i][j] == 0){
                cout << ' ';
                }
                    else
                    {
                cout << round(matr[i][j]) / n;
                    }
            }
            cout << endl;
        }
    }
    
};

int main()
{
    random_walk walk1;
    start: {
    cout << "Press 1 to start free walking" << endl << "Press 2 to start walk with limitations" << endl << "Press x to exit" << endl;
    char key;
    while((key = getchar()) != 'x') {
        switch(key) {
        case '1':
			walk1.clearMatr();
			walk1.setData(); 
			int start_timer1 = clock(); 
			walk1.priorOut(); 
			walk1.iteration(); 
			walk1.posteriorOut(); 
			walk1.clearMatr();
			int stop_timer1 = clock(); cout << "Wasted time: " << stop_timer1 - start_timer1 << "ms" << endl;
			goto start;
        }
        switch(key) {
            case '2':
            walk1.clearMatr();
			walk1.setData();
            int start_timer2 = clock(); 
            walk1.priorOutLimited();
            walk1.iterationLimited(); 
			walk1.posteriorOutLimited(); 
			walk1.clearMatr();
            int stop_timer2 = clock(); cout << "Wasted time: " << stop_timer2 - start_timer2 << "ms" << endl;
            goto start;
        }
        }
    }
    return 0;
}
