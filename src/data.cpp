#include <iostream>
#include <stdio.h>

#include "./lib/pair.h"
#include "./lib/polynominal.h"

#define debug(x) cout << #x << " = " << x << endl;
using namespace std;

int main()
{
	freopen("DATA1", "r", stdin);
	freopen("DATA2", "w", stdout);

	int n, c;
	cin >> n;
	Polynomial P(n);
	cin >> P;
	cin >> c;

	Pair<Polynomial, float> ans((P / c));

	cout << ans.first() << endl;
	cout << ans.second();
	return 0;
}
