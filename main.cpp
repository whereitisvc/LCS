/*
LCS - longest common subsequence
Implement and analyze the time complexity of an algorithm CountLCS that, given
n in the range [3:20], and two integers x and y that are each in the range
[0:2n-1], determines the number of distinct strings that are LCS's of
binstring(n,x) and binstring(n,y) and displays them.
*/

#include <iostream>
#include <cmath>
#include <set>

using namespace std;

int** dp;

// find all LCS string
set<string> findLCS(string X, string Y, int xi, int yi);

// caculate LCS by dynamic programming
int LCS(string X, string Y, int n);

// convert string to number
int string2num(string str);

// convert number to string
string num2string(int num, int n);

// get n value
short unsigned int getn(short int, short int);
// get x value or y value
long unsigned int getxy(char, short int, long unsigned int);

int main()
{
    // initialize 3 integers n, x, y
    short unsigned int n; // [3, 20]
    long unsigned int x, y; // [0, 2^n-1]

    // declared for the range test z = 2^n - 1
    long unsigned int z;

    char again = 'n'; // control user input switch

    // // get n
    // n = getn(3, 20);

    // // calculate the max value for x and y
    // z = pow(2, n) - 1;
    // cout << "z value is " << z << endl;

    // // get x and y
    // x = getxy('x', 0, z);
    // y = getxy('y', 0, z);

    //n = 14; x = 12642; y = 5735;
    // n = 20;  x = 1048575; y = 1;//355;
    // int shift = 8; x = x >> shift; n = n - shift;
    // string X = num2string(x, n);
    // string Y = num2string(y, n);

    // // confirm inputs
    // cout << "n is recorded as " << n << endl;
    // cout << "x is recorded as " << x << ", " << X << endl;
    // cout << "y is recorded as " << y << ", " << Y << endl;

    // dp = new int*[n+1];
    // for(int i=0; i<n+1; i++){
    //     dp[i] = new int[n+1];
    // }

    // cout << "LCS = " << LCS(X, Y, n) << endl;

    // set<string> s = findLCS(X, Y, n, n);
    // for(string str: s)  
    //     cout << str << ", " << string2num(str) << endl;

    n = 5;
    z = pow(2, n) - 1;

    dp = new int*[n+1];
    for(int i=0; i<n+1; i++){
        dp[i] = new int[n+1];
    }

    int threshold = 4;
    for(x = 0; x <= z; x++){
        for(y = 0; y <= z; y++){

            // init dp[][]
            for(int i=0; i<n+1; i++)
                for(int j=0; j<n+1; j++)
                    dp[i][j] = 0;


            string X = num2string(x, n);
            string Y = num2string(y, n);
            int lcs = LCS(X, Y, n);
            set<string> s = findLCS(X, Y, n, n);
            if(s.size() >= threshold){
                cout << "x is recorded as " << x << ", " << X << endl;
                cout << "y is recorded as " << y << ", " << Y << endl;
                cout << "LCS = " << lcs << endl;
                for(string str: s)  cout << str << ", " << string2num(str) << endl;
            }
        }
    }

    return 0;
}

set<string> findLCS(string X, string Y, int xi, int yi) 
{ 

	set<string> s; 

    // if reach the end of string, return empty set
	if(xi == 0 || yi == 0){ //cout << xi << ", " << yi << endl;
		s.insert(""); 
		return s; 
	} 

	// If the last characters of X and Y are same 
	if(X[xi - 1] == Y[yi - 1]){ 
		// recurse for X[0..m-2] and Y[0..n-2] in the matrix 
		set<string> tmp = findLCS(X, Y, xi - 1, yi - 1); 

		// append current character to all possible LCS of substring X[0..m-2] and Y[0..n-2]. 
		for (string str : tmp) 
			s.insert(str + X[xi - 1]); 
	} 

	// If the last characters of X and Y are not same 
	else{ 
		// If LCS can be constructed from top side of the matrix, recurse for X[0..m-2] and Y[0..n-1] 
		if (dp[xi - 1][yi] >= dp[xi][yi - 1]) 
			s = findLCS(X, Y, xi - 1, yi); 

		// If LCS can be constructed from left side of the matrix, recurse for X[0..m-1] and Y[0..n-2] 
		if (dp[xi][yi - 1] >= dp[xi - 1][yi]) 
		{ 
			set<string> tmp = findLCS(X, Y, xi, yi - 1); 

			// merge two sets if L[m-1][n] == L[m][n-1] Note s will be empty if L[m-1][n] != L[m][n-1] 
			s.insert(tmp.begin(), tmp.end()); 
		} 
	} 
	return s; 
}

int LCS(string X, string Y, int n){ 
	// Build dp[n+1][n+1] in bottom up fashion 
	for (int i = 0; i <= n; i++) { 
		for (int j = 0; j <= n; j++) {
			if (i == 0 || j == 0) 
                dp[i][j] = 0; 
			else if (X[i - 1] == Y[j - 1]) 
				dp[i][j] = dp[i - 1][j - 1] + 1; 
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); 
		} 
	} 
	return dp[n][n]; 
}

int string2num(string str){ 
	int num = 0; 
	int shift = 0; 
	for(int i = str.length() - 1; i >= 0; i--){ 
		if(str[i] == '1') num += pow(2, shift); 
		shift++; 
	}
	return num; 
}

string num2string(int num, int n){ 
	string str; 
	while (num > 0){ 
		int digit = num % 2; 
		str.push_back(48 + digit); 
		num /= 2; 
        n--;
	} 
    
    for(int i=0; i<n; i++) str.push_back(48);

	reverse(str.begin(), str.end()); 
	return str; 
} 

short unsigned int getn(short int low = 3, short int high = 20){
    // initialize n
    short unsigned int n; // [3, 20]
    char again = 'n'; // control user input switch
    // get n
    while (again != 'y' || again != 'Y')
    {
        // instruction message
        cout <<"Please enter an integer between 3 and 20 as n: " << endl;
        // test if the input is an integer
        while (!(cin >> n)){
            cout << "Invalid character. Please enter an integer between " << low << " and " << high << " as n: " << endl;
            cin.clear();
            cin.ignore(100, '\n');
            if (cin >> n)
                break;
            else
                continue;
        }
        // test if the input is in the range [3, 20]
        if (n<low || n>high){
            cout << "Integer out of range. ";
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        // confirm the input
        while (n >= low && n <= high){
            cout << "You entered " << n << ". Confirm? (y/n)" << endl;
            cin >> again;
            break;
        }
        // if confirmed, turn off the switch and continue the inputs
        if (again == 'y' || again == 'Y')
            break;
        // if not, clear inputs and re-enter n value
        else
        {
            cin.clear();
            cin.ignore(100, '\n');\
        }
    }
    return n;
}

long unsigned int getxy(char c, short int low, long unsigned int high){
    // initialize x or y
    long unsigned int y;

    char again = 'n'; // control user input switch
    while (again != 'y' || again != 'Y')
    {
        // instruction message
        cout <<"Please enter an integer between " << low << " and " << high << " as " << c << ": " << endl;
        // test if the input is an integer
        while (!(cin >> y)){
            cout << "Invalid character. Please enter an integer between " << low << " and " << high << " as " << c << ": " << endl;
            cin.clear();
            cin.ignore(100, '\n');
            if (cin >> y)
                break;
            else
                continue;
        }
        // test if the input is in the range [3, 20]
        if (y < low || y > high){
            cout << "Integer out of range.";
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        // confirm the input
        while (y >= low && y <= high){
            cout << "You entered " << y << ". Confirm? (y/n)" << endl;
            cin >> again;
            break;
        }
        // if confirmed, turn off the switch and continue the inputs
        if (again == 'y' || again == 'Y')
            break;
        // if not, clear inputs and re-enter n value
        else
        {
            cin.clear();
            cin.ignore(100, '\n');\
        }
    }
    return y;
}
