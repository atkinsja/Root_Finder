#include <iostream>

using namespace std;

double f(double);
double fprime(double);
void bisection();
void bisectionCalculation(double, double, double&, int&);
void newton();
void newtonCalculation(double, double&, bool&, int&);
void secant();
void secantCalculation(double, double, double&, int&);

int main()
{
	int choice;
	char response;
	do {
		cout << "1. Bisection method" << endl;
		cout << "2. Newton's method" << endl;
		cout << "3. Secant method" << endl;

		cout << "Select the method of calculation to be used to find the root of x^3 - x - 1: ";
		cin >> choice;

		switch (choice)
		{
			case 1: {
				bisection();
				break;
			}
			case 2: {
				newton();
				break;
			}
			case 3: {
				secant();
				break;
			}
			default:
				cout << "Invalid choice." << endl;
		}
		cout << "\n\nWould you like to try another method? (y/n): ";
		cin >> response;
		system("cls");
		
		
	} while (response == 'y' || response == 'Y');
	
	return 0;
}

double f(double x)
{
	return pow(x, 3) - x - 1;
}

double fprime(double x)
{
	return 3 * pow(x, 2) - 1;
}

void bisection()
{
	double end_a, end_b;
	bool valid;
	int count = 0;
	double root;
	do {
		cout << "Input the lower bound of the interval to be bisected: ";
		cin >> end_a;
		cout << "Input the upper bound of the interval to be bisected: ";
		cin >> end_b;
		if (f(end_a)*f(end_b) >= 0)
		{
			cout << "Invalid interval." << endl;
			valid = false;
		}
		else
			valid = true;
	} while (!valid);
	bisectionCalculation(end_a, end_b, root, count);
	cout << "In the interval [" << end_a << ", " << end_b << "], the root is " << root << " and it took " << count << " iterations to find." << endl;


}

void bisectionCalculation(double end_a, double end_b, double& root, int& iters)
{
	const double TOL = 0.0000001;
	const int MAX_COUNT = 100;
	double mid_point = end_a;
	while (((end_b - end_a) >= TOL)&&(iters < MAX_COUNT))
	{
		iters++;
		mid_point = (end_a + end_b) / 2;
		if ((f(mid_point) == 0))
			break;
		else if (f(mid_point)*f(end_a) < 0)
			end_b = mid_point;
		else
			end_a = mid_point;
	}
	root = mid_point;
}

void newton()
{
	double x_0, ans;
	int count;
	bool found;

	cout << "Enter the initial estimate: ";
	cin >> x_0;
	if (fprime(x_0) == 0)
		x_0 += 0.1;
	found = false;
	count = 0;
	newtonCalculation(x_0, ans, found, count);
	if (found)
		cout << "The root is " << ans << " and it took " << count << " iterations." << endl;
	else
		cout << "No root found using initial estimate." << endl;
}

void newtonCalculation(double x_0, double& root, bool& valid, int& iters)
{
	double const TOL = 0.000001;
	int const MAX_COUNT = 100;
	double x_1, diff;
	x_1 = x_0 - f(x_0) / fprime(x_0);
	iters++;
	diff = fabs(x_1 - x_0);
	while ((diff > TOL) && (!valid) && iters < MAX_COUNT)
	{
		x_0 = x_1;
		if (fprime(x_0) == 0)
			x_0 += 0.1;
		x_1 = x_0 - f(x_0) / fprime(x_0);
		iters++;
		diff = fabs(x_1 - x_0);
	}
	if (diff <= TOL)
	{
		valid = true;
		root = x_1;
	}
}

void secant()
{
	double x_1, x_2, root;
	int iters;
	cout << "Input the lower bound of the interval of the secant: ";
	cin >> x_1;
	cout << "Input the upper bound of the interval of the secant: ";
	cin >> x_2;
	if (f(x_1)*f(x_2) < 0)
		secantCalculation(x_1, x_2, root, iters);
	else
		cout << "Invalid interval" << endl;

	cout << "In the interval [" << x_1 << ", " << x_2 << "], the root is " << root << " and it took " << iters << " iterations to find." << endl;

}

void secantCalculation(double x_1, double x_2, double& root, int& iters)
{
	const double TOL = 0.000001;
	iters = 0;
	double x_0, x_temp, diff;
	do {
		x_0 = (x_1*f(x_2) - x_2 * f(x_1)) / (f(x_2) - f(x_1));
		diff = f(x_1)*f(x_0);

		x_1 = x_2;
		x_2 = x_0;
		iters++;

		if (diff == 0)
			break;
		x_temp = (x_1*f(x_2) - x_2 * f(x_1)) / (f(x_2) - f(x_1));
	} while (fabs(x_temp - x_0) >= TOL);
	root = x_0;
}