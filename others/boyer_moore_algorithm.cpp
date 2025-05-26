#include <iostream>
#include <map>
#include <string>

using namespace std;

// O(m + n*lg(n)) -> O(m)
map<char, int> lastOccurenceFunction(const string &P) {
  map<char, int> map;
  for (char c = 0; c < 127; c++) {
    map[c] = -1; // ASCII 문자 모두 초기화
  }

  const int loop_size = P.size();
  for (int i = 0; i < loop_size; i++) {
    map[P[i]] = i;
  }

  cout << "<<lastOccurenceFunction 출력 시작>>" << endl;
  cout << "a: " << map['a'] << ", b: " << map['b'] << ", c: " << map['c']
       << ", d: " << map['d'] << endl;
  cout << "<<lastOccurenceFunction 출력 시작>>" << endl;

  return map;
}

int BoyerMooreMatch(const string &T, const string &P) {
  if (P.empty() || T.empty() || P.size() > T.size())
    return -1;

  map<char, int> map = lastOccurenceFunction(P);

  const int n = T.size();
  const int m = P.size();
  int i = m - 1;
  int j = m - 1;

  do {
    if (T[i] == P[j]) {
      if (j == 0) {
        cout << "패턴과 모두 일치하는 문자열 찾음: (" << i << "," << j << ")"
             << endl;
        return i;
      } else {
        cout << "부분일치하면서 계속 검증 중: (" << i << "," << j << ")"
             << endl;
        i--;
        j--;
      }
    } else {
      cout << "bad-char 발생: (" << i << "," << j << ")" << endl;
      int l = map[T[i]];
      i = i + m - min(j, 1 + l);
      j = m - 1;
      cout << "bad-char로 인한 i와 j 인덱스 업데이트: (" << i << "," << j << ")"
           << endl;
    }
  } while (i < n);

  return -1;
}

int main() {
  string T, P;
  cin >> T >> P;

  cout << BoyerMooreMatch(T, P) << endl;

  return 0;
}
// Sample Input:
// abacaabadcabacabaabb abacab

// Compile
// cmake .. && make && ./BoyerMooreAlgorithm