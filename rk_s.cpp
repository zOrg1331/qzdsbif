/*-----------------------------------------------
��� ������������ ������ ���������� �����������:

double f(int i, double x, ap::real_1d_array y);
-----------------------------------------------*/

void systemrungekutt(double x, double x1, int m, int n, QVector<double>& y);
void systemrungekuttstep(double x, double h, int n, QVector<double>& y);

/*************************************************************************
����� �����-����� ���������� ������� ��� �������
������� ��������������� ���������.

procedure SystemRungeKutt(
    const   x   :   Real;
    const   x1  :   Real;
    const   m   :   Integer;
    const   n   :   Integer;
    var     y   :   array of Real);

�������� ������ ������� �������� y[i]'=F(i,x,y) ��� i=1..n
������� �����-����� 4 �������.

��������� ����� ����� ��������� (x,y[1], ..., y[n])

�� �������� ����� �� ���������� ����� n �������������
� ���������� ����� h=(x1-x)/m

��������� ���������� � ���������� y
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
���� ��� ������ �����-����� ���������� ������� ��� �������
������� ��������������� ���������.

procedure SystemRungeKuttStep(
    const   x   :   Real;
    const   h   :   Real;
    const   n   :   Integer;
    var     y   :   array of Real);

�������� ��������� ���� ��� ������ ��� �������
�������� y[i]'=F(i,x,y) ��� i=1..n

��������� ����� ����� ��������� (x,y[1], ..., y[n])

����� ���������� ��������� � ���������� y ���������� ���������
������� � ����� x+h
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
