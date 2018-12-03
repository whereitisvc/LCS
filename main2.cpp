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

// the node for dp matrix
class Node{
public:
    int val; // for determining LCS
    bool visited; // record visited or not in the search tree
    set<string> list; // record the set of matched string below current node in the search tree
    Node(){
        val = 0;
        visited = false;
    }
};

// dp matrix for determining LCS and finding LCS strings
Node** dp;

// handle the correctness of the inputs
int getn(int, int);
int getxy(char c, int low, int high);

// handle the transformence between binstring and value
int string2num(string str);
string binstring(int n, int num);

// determine the number of distinct strings that are LCS and record them
int LCS(string X, string Y, int n);
void findLCS(string X, string Y, int xi, int yi, string str, set<string>& ans);
int CountLCS(string X, string Y, int n, set<string>& ans);

int main()
{
    
    int n, x, y;
    int z;

    //n = 14; x = 12642; y = 5735;
    //n = 20;  x = 1048575; y = 355;

    // get inputs n, x, y
    n = getn(3, 20);
    z = pow(2, n) - 1;
    x = getxy('x', 0, z);
    y = getxy('y', 0, z);

    // determine LCS
    string X = binstring(n, x);
    string Y = binstring(n, y);
    set<string> ans;
    int lcs = CountLCS(X, Y, n, ans); 

    // display the result
    cout << endl;
    cout << "n = " << n << ", " << "x = " << x << ", " << "y = " << y << endl;
    cout << "binstring(n, x) = " << X << endl;
    cout << "binstring(n, y) = " << Y << endl;   

    cout << endl;
    cout << "the determined number of distinct LCS's = " << lcs << endl;

    cout << endl;
    cout << "the list of those LCS's: " << endl;
    int count = 1;
    for(string s: ans){
        printf("%2d. ", count++);
        cout << "string = " << s << ", value = " << string2num(s) << endl;
    }

    cout << endl;
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

string binstring(int n, int num){ 
	string str; 
	while (num > 0){ 
		int digit = num % 2; 
		str.push_back(48 + digit); 
		num /= 2; 
        n--;
	} 
    
    // add zeros if the size < n 
    for(int i=0; i<n; i++) str.push_back(48);

	reverse(str.begin(), str.end()); 
	return str; 
} 

int LCS(string X, string Y, int n){ 
	// Build dp matrix
	for (int i = 0; i <= n; i++) { 
		for (int j = 0; j <= n; j++) {

            // row 0 and col 0 are the initial values
			if (i == 0 || j == 0) 
                dp[i][j].val = 0;

            // if character in X and Y are same, then increase the value by one
            // else keep the max value 
			else 
            {
                if (X[i - 1] == Y[j - 1]) 
                    dp[i][j].val = dp[i - 1][j - 1].val + 1; 
                else
                    dp[i][j].val = max(dp[i - 1][j].val, dp[i][j - 1].val); 
		    }
        } 
	} 
	return dp[n][n].val; 
}

void findLCS(string X, string Y, int xi, int yi, string str, set<string>& ans) 
{ 
    // base case: when reach the end of a string, add the current str into ans
    if(xi == 0 || yi == 0){
        string temp(str);
        reverse(temp.begin(), temp.end());
		ans.insert(temp);

        // insert empty string 
        dp[xi][yi].list.insert("");
		return; 
	} 

    // if current node is visited, then compose current str and the string in node list 
    if(dp[xi][yi].visited){
        for(string s: dp[xi][yi].list){
            string temp(str);
            reverse(temp.begin(), temp.end());
		    ans.insert(s + temp);
        }
        return;
    }

    // record current node as visited
    dp[xi][yi].visited = true;

    // If the last characters of X and Y are same, go diagonal
    if(X[xi - 1] == Y[yi - 1]){        
        findLCS(X, Y, xi-1, yi-1, str+X[xi - 1], ans);
        for(string s: dp[xi-1][yi-1].list){
            dp[xi][yi].list.insert(s + X[xi - 1]);
        }
        
    }

    // If the last characters of X and Y are not same, go to the direction with larger value
    // If the values are same, go both
    else{

        if( dp[xi - 1][yi].val >= dp[xi][yi - 1].val ){
            findLCS(X, Y, xi-1, yi, str, ans);
            for(string s: dp[xi-1][yi].list){
                dp[xi][yi].list.insert(s);
            }
        }
        if( dp[xi][yi - 1].val >= dp[xi - 1][yi].val ){
            findLCS(X, Y, xi, yi-1, str, ans);
            for(string s: dp[xi][yi-1].list){
                dp[xi][yi].list.insert(s);
            }
        }

    }
}

int CountLCS(string X, string Y, int n, set<string>& ans){

    // initialize dp matrix
    dp = new Node*[n+1];
    for(int i=0; i<n+1; i++){
        dp[i] = new Node[n+1];
    }

    // caculate LCS by building up dp matrix
    int lcs = LCS(X, Y, n);

    // find all distinct LCS strings
    findLCS(X, Y, n, n, "", ans);

    return lcs;
}

int getn(int low = 3, int high = 20){
    int n; // [3, 20]
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

int getxy(char c, int low, int high){
    // initialize x or y
    int y;

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


