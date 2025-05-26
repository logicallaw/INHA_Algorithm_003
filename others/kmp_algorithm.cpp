#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> failureFunction(const string &P) {
  int m = P.size();
  vector<int> F(m);
  F[0] = 0;
  int i = 1;
  int j = 0;

  while (i < m) {
    if (P[i] == P[j]) {
      F[i] = j + 1;
      i++;
      j++;
    } else if (j > 0) {
      j = F[j - 1];
    } else {
      F[i] = 0;
      i++;
    }
  }
  return F;
}

int KMPMatch(const string &T, const string &P) {
  vector<int> F = failureFunction(P);

  int i = 0;
  int j = 0;
  int n = T.size();
  int m = P.size();
  while (i < n) {
    if (T[i] == P[j]) {
      cout << "부분 일치:(" << i << "," << j << ")" << endl;
      if (j == m - 1) {
        return i - j;
      }
      i++;
      j++;
    } else if (j > 0) {
      cout << "부분 일치지만 더이상 일치 안함:(" << i << "," << j << ")"
           << endl;
      j = F[j - 1];
    } else {
      cout << "처음부터 불일치:(" << i << "," << j << ")" << endl;
      i++;
    }
  }
  return -1;
}

int main() {
  string T;
  string P;

  cin >> T >> P;
  cout << KMPMatch(T, P) << endl;

  return 0;
}
// Sample Input:
// abacaabaccabacabaabb abacab

// Compile
// cmake .. && make && ./KMP_Algorithm