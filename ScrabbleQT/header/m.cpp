

#include <cstdio>
 
static bool next_rec(int n, int k, int *i, int j) {
i[j]++;
 
if (i[j] == n - (k - j) + 1) {
 
 
    if (j == 0) {
 
      return false;
}
 
 
    if (!next_rec(n, k, i, j - 1)) {
 
      return false;
}
 
 
    i[j] = i[j - 1] + 1;
}
 
return true;
}
 
static bool next(int n, int k, int *i) {
return next_rec(n, k, i, k - 1);
}
 
//int main() {
//const int n = 7;
//const int k = 2;
// 
//int *i = new int[k];
// 
//int x = 0;
// 
//for (int j = 0; j < k; ++j) {
// 
//    i[j] = j;
//}
// 
//do {
// 
//    x++;
// 
// 
//    std::printf("%i:", x);
// 
// 
//    for (int j = 0; j < k; ++j) {
// 
//      std::printf(" %i", i[j]);
//}
// 
// 
//    std::printf("\n");
//} while (next(n, k, i));
// 
//return 0;
//}
