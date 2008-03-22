/*-----------------------------------------------
Эти подпрограммы должен определить программист:

double f(int i, double x, ap::real_1d_array y);
-----------------------------------------------*/

void systemrungekutt(double x, double x1, int m, int n, QVector<double>& y);
void systemrungekuttstep(double x, double h, int n, QVector<double>& y);

/*************************************************************************
Метод Рунге-Кутта четвертого порядка для решения
системы дифферециальных уравнений.

procedure SystemRungeKutt(
    const   x   :   Real;
    const   x1  :   Real;
    const   m   :   Integer;
    const   n   :   Integer;
    var     y   :   array of Real);

Алгоритм решает систему диффуров y[i]'=F(i,x,y) для i=1..n
методом Рунге-Кутта 4 порядка.

Начальная точка имеет кординаты (x,y[1], ..., y[n])

До конечной точки мы добираемся через n промежуточных
с постоянным шагом h=(x1-x)/m

Результат помещается в переменную y
*************************************************************************/
void systemrungekutt(double x, double x1, int m, int n, QVector<double>& y)
{
    double h;
    int i;

    for(i = 0; i <= m-1; i++)
    {
	systemrungekuttstep(x+double(i*(x1-x))/double(m), double(x1-x)/double(m), n, y);
    }
}


/*************************************************************************
Один шаг метода Рунге-Кутта четвертого порядка для решения
системы дифферециальных уравнений.

procedure SystemRungeKuttStep(
    const   x   :   Real;
    const   h   :   Real;
    const   n   :   Integer;
    var     y   :   array of Real);

Алгоритм совершает один шаг метода для системы
диффуров y[i]'=F(i,x,y) для i=1..n

Начальная точка имеет кординаты (x,y[1], ..., y[n])

После выполнения алгоритма в переменной y содержится состояние
системы в точке x+h
*************************************************************************/
void systemrungekuttstep(double x, double h, int n, QVector<double>& y)
{
    int i;
    QVector<double> yt, k1, k2, k3, k4;

    for(i = 1; i <= n; i++)
    {
	k1[i] = h*f(i, x, y);
    }
    for(i = 1; i <= n; i++)
    {
	yt[i] = y.at(i)+0.5*k1.at(i);
    }
    for(i = 1; i <= n; i++)
    {
	k2[i] = h*f(i, x+h*0.5, yt);
    }
    for(i = 1; i <= n; i++)
    {
	yt[i] = y.at(i)+0.5*k2.at(i);
    }
    for(i = 1; i <= n; i++)
    {
	k3[i] = h*f(i, x+h*0.5, yt);
    }
    for(i = 1; i <= n; i++)
    {
	yt[i] = y.at(i)+k3.at(i);
    }
    for(i = 1; i <= n; i++)
    {
	k4[i] = h*f(i, x+h, yt);
    }
    for(i = 1; i <= n; i++)
    {
	y.at(i) = y.at(i)+double(k1.at(i)+2.0*k2.at(i)+2.0*k3.at(i)+k4.at(i))/double(6);
    }
}
