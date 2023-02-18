#include <iostream>
#include <string>
#include <fstream>
#include "math.h"

using namespace std;
double func(double x, double y)
{
    double task= 0.0;
    if (task == 1.0)
        return 0.39 * y;
   if (x == 0)
       throw "devision by zero";
   if (y<0)
       throw "logarithm of negative number";
    return -y/x*(pow(x,3)+log(y)); // функция 
}
double funcy(double  x,double y, double z)
{
    
    return y - z; // функция y'
}
double funcz(double  x, double y, double z)
{
    
    return y*z; // функция  z'
}

void sysRKII(double& x, double& y, double &z, double& h) {
    double yhalf, xhalf,zhalf;
    xhalf = x + h / 2.0;
    yhalf =y+ h * (funcy(x, y, z)) / 2.0;
    zhalf = z + h * (funcz(x, y, z)) / 2.0;
    z += h * funcz(xhalf, yhalf, zhalf);
    y += h * funcy(xhalf, yhalf, zhalf);
    x += h;
}
void sysRKIV(double& x, double& y, double& z, double& h) {
    double x1, y1, z1, k1y, k1z, k2y, k2z, k3y, k3z, k4y, k4z;
    k1y = h * funcy(x, y, z);
    k1z = h * funcz(x, y, z);
    x1 = x + h / 2.0;
    y1 = y + k1y / 2.0;
    z1 = z + k1z / 2.0;
    k2y = h * funcy(x1, y1,z1);
    k2z = h * funcz(x1, y1, z1);
    y1 = y + k2y / 2.0;
    z1 = z + k2z / 2.0;
    k3y = h * funcy(x1, y1, z1);
    k3z = h * funcz(x1, y1, z1);
    x += h;
    y1 = y + k3y;
    z1 = z + k3z;
    k4y = h * funcy(x, y1,z1);
    k4z = h * funcz(x, y1, z1);
    y += (k1y + 2.0 * k2y + 2.0 * k3y + k4y) / 6.0;
    z += (k1z + 2.0 * k2z + 2.0 * k3z + k4z) / 6.0;
}
void sysRKIII(double& x, double& y, double& z, double& h) {
    double x1, y1,z1, k1y,k1z, k2y,k2z, k3y,k3z;
    k1y = h * funcy(x, y, z);
    k1z = h * funcz(x, y, z);

    x1 = x + h / 2.0;
    y1 = y + k1y / 2.0;
    z1 = y + k1z / 2.0;
    k2y = h * funcy(x1, y1,z1);
    k2z = h * funcz(x1, y1,z1);
    x1 = x + h;
    y1 = y + 2.0 * k2y - k1y;
    z1 = z + 2.0 * k2z - k1z;
    k3y = h * funcy(x1, y1,z1);
    k3z= h * funcz(x1, y1, z1);
    x += h;
    y += (k1y + 4.0 * k2y + k3y) / 6.0;
    z += (k1z + 4.0 * k2z + k3z) / 6.0;
}

void RKII(double &x, double &y, double &h) {
    
        double yhalf, xhalf;
        xhalf = x + h / 2.0;
        yhalf = y + h * func(x, y) / 2.0;
        y += h * func(xhalf, yhalf); // вычисление yi+1
        x += h;
}
void RKIV(double& x, double& y, double& h) {
       
     double x1, y1, k1, k2, k3, k4;
     k1 = h * func(x, y);
     x1 = x + h / 2.0;
     y1 = y + k1 / 2.0;
     k2 = h * func(x1, y1);
     y1 = y + k2 / 2.0;
     k3 = h * func(x1, y1);
     x += h;
     y1 = y + k3;
     k4 = h * func(x, y1);
     y += (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;// вычисление yi+1
}
void RKIII(double& x, double& y, double& h) {

    double x1, y1, k1, k2, k3;
    k1 = h * func(x, y);
    x1 = x + h / 2.0;
    y1 = y + k1 / 2.0;
    k2 = h * func(x1, y1);
    x1 = x + h;
    y1 = y + 2.0*k2-k1;
    k3 = h * func(x1, y1);
    x += h;
    y += (k1 + 4.0 * k2 + k3) / 6.0;// вычисление yi+1
}

double sysLEEII(double x, double y, double z, double  h) {
    double res1 = 0.0, res2=0.0, xprev = x, yprev = y, zprev=z;
    sysRKII(x, y, z, h);
    double hhalf = h / 2.0;
    sysRKII(xprev, yprev, zprev, hhalf);
    sysRKII(xprev, yprev, zprev, hhalf);
    res1 = (yprev - y) / 3.0;
    res2 = (zprev - z) / 3.0;
    if (res1 > res2)
        return res1;
    else return res2;
}
double sysLEEIV(double x, double y, double z, double  h) {
    double res1 = 0.0, res2 = 0.0, xprev = x, yprev = y, zprev = z;
    sysRKIV(x, y, z, h);
    double hhalf = h / 2.0;
    sysRKIV(xprev, yprev, zprev, hhalf);
    sysRKIV(xprev, yprev, zprev, hhalf);
    res1 = (yprev - y) / 15.0;
    res2 = (zprev - z) / 15.0;
    if (res1 > res2)
        return res1;
    else return res2;
}
double sysLEEIII(double x, double y, double z, double  h) {
    double res1 = 0.0, res2 = 0.0, xprev = x, yprev = y, zprev = z;
    sysRKIII(x, y, z, h);
    double hhalf = h / 2.0;
    sysRKIII(xprev, yprev, zprev, hhalf);
    sysRKIII(xprev, yprev, zprev, hhalf);
    res1 = (yprev - y) / 7.0;
    res2 = (zprev - z) / 7.0;
    if (res1 > res2)
        return res1;
    else return res2;
}

double LEEII(double x, double y, double  h) {
    double res = 0.0, xprev = x, yprev = y;
    RKII(x, y, h);
    double hhalf = h / 2.0;
    RKII(xprev, yprev, hhalf);
    RKII(xprev, yprev, hhalf);
    res = (yprev - y) / 3.0;
    return res;
}
double LEEIV(double x, double y, double  h) {
    double res = 0.0, xprev = x, yprev = y;
    RKIV(x, y, h);
    double hhalf = h / 2.0;
    RKIV(xprev, yprev, hhalf);
    RKIV(xprev, yprev, hhalf);
    res = (yprev - y) / 15.0;
    return res;
}
double LEEIII(double x, double y, double  h) {
    double res = 0.0, xprev = x, yprev = y;
    RKIII(x, y, h);
    double hhalf = h / 2.0;
    RKIII(xprev, yprev, hhalf);
    RKIII(xprev, yprev, hhalf);
    res = (yprev - y) / 7.0;
    return res;
}

int main(int argc, char** argv)
{
    int choice;
    cout << "Print 1 for DU or 2 for system";
    cin >> choice;
    if (choice == 1) {
        ofstream fout;
        int n;
        double x, y, h, p, e, b, flag, c1 = 0, c2 = 0, lee;
        ifstream fin;
        fin.open("InputFile.txt");
        string data;
        while (!fin.eof()) {
            getline(fin, data);
            if (data.find("//") != string::npos)
                continue;
            if (data.find("h") != string::npos) {
                h = atof(data.substr(data.find("=") + 1).c_str());
            }
            if (data.find("n") != string::npos) {
                n = atof(data.substr(data.find("=") + 1).c_str());
            }
            if (data.find("p") != string::npos) {
                p = atof(data.substr(data.find("=") + 1).c_str());
            }
            if (data.find("e") != string::npos) {
                e = atof(data.substr(data.find("=") + 1).c_str());
            }
            if (data.find("b") != string::npos) {
                b = atof(data.substr(data.find("=") + 1).c_str());
            }
            if (data.find("x") != string::npos) {
                x = atof(data.substr(data.find("=") + 1).c_str());
            }
            if (data.find("y") != string::npos) {
                y = atof(data.substr(data.find("=") + 1).c_str());
            }
            if (data.find("flag") != string::npos) {
                flag = atof(data.substr(data.find("=") + 1).c_str());
            }
        }
        fin.close();
        fout.open("OutputFile.txt");
        for (int i = 0; i < n; i++)
        {
            if ((x + h > b) && (x > b))
                break;
            double xprev = x, yprev = y;
            if (p == 4.0) {
                lee = fabs(LEEIV(x, y, h));
                RKIV(x, y, h);
            }
            if (p == 3.0) {
                lee = fabs(LEEIII(x, y, h));
                RKIII(x, y, h);
            }
            if (p == 2.0) {
                lee = fabs(LEEII(x, y, h));
                RKII(x, y, h);
            }
            if (flag == 1.0) {
                if (lee < (e / pow(2, p + 1))) {
                    fout << i+1 << " xi = " << x << " yi = " << y << " LEE =  " << lee << " h = " << h << " с1= " << c1 << " c2= " << c2 << "\n";
                    
                    h = h * 2;
                    c2++;
                    if (x == b)
                        break;
                    continue;
                }
                if (lee > e) {
                    h = h / 2;
                    c1++;
                    x = xprev;
                    y = yprev;
                    i--;
                    continue;
                }
            }
            fout << i+1 << " xi = " << x << " yi = " << y << " LEE =  " << lee << " h = " << h << " с1= " << c1 << " c2= " << c2 << "\n";
           
            if (x == b)
                break;
        }
        fout.close();

        return 0;
    }
    if (choice == 2) {
        ofstream fout1;
        int n;
        double x, y,z, h, p, e, b, flag, c1 = 0, c2 = 0, lee;
        ifstream fin;
        fin.open("InputFileSys.txt");
        string data;
        while (!fin.eof()) {
            getline(fin, data);
            if (data.find("//") != string::npos)
                continue;
            if (data.find("h") != string::npos) {
                h = atof(data.substr(data.find("=") + 1).c_str());
            }
            if (data.find("n") != string::npos) {
                n = atof(data.substr(data.find("=") + 1).c_str());
            }
            if (data.find("p") != string::npos) {
                p = atof(data.substr(data.find("=") + 1).c_str());
            }
            if (data.find("e") != string::npos) {
                e = atof(data.substr(data.find("=") + 1).c_str());
            }
            if (data.find("b") != string::npos) {
                b = atof(data.substr(data.find("=") + 1).c_str());
            }
            if (data.find("x") != string::npos) {
                x = atof(data.substr(data.find("=") + 1).c_str());
            }
            if (data.find("y") != string::npos) {
                y = atof(data.substr(data.find("=") + 1).c_str());
            }
            if (data.find("z") != string::npos) {
                z = atof(data.substr(data.find("=") + 1).c_str());
            }
            if (data.find("flag") != string::npos) {
                flag = atof(data.substr(data.find("=") + 1).c_str());
            }
        }
        fin.close();
        fout1.open("OutputFileSys.txt");
        for (int i = 0; i < n; i++)
        {
            if ((x + h > b) && (x > b))
                break;
            double xprev = x, yprev = y,zprev=z;
            if (p == 4.0) {
                lee = fabs(sysLEEIV(x, y,z, h));
                sysRKIV(x, y,z, h);
            }
            if (p == 3.0) {
                lee = fabs(sysLEEIII(x, y,z, h));
                sysRKIII(x, y, z, h);
            }
            if (p == 2.0) {
                lee = fabs(sysLEEII(x, y,z, h));
               sysRKII(x, y,z, h);
            }
            if (flag == 1.0) {
                if (lee < (e / pow(2, p + 1))) {
                    fout1 << i+1 << " xi = " << x << " yi = " << y <<"zi = "<<z << " LEE =  " << lee << " h = " << h << " с1= " << c1 << " c2= " << c2 << "\n";
                    
                    h = h * 2;
                    c2++;
                    if (x == b)
                        break;
                    continue;
                }
                if (lee > e) {
                    h = h / 2;
                    c1++;
                    x = xprev;
                    y = yprev;
                    z = zprev;
                    i--;
                    continue;
                }
            }
            fout1 << i+1 << " xi = " << x << " yi = " << y << " zi = " << z << " LEE =  " << lee << " h = " << h << " с1= " << c1 << " c2= " << c2 << "\n";
            
            if (x == b)
                break;
        }
        fout1.close();

        return 0;
    }
}