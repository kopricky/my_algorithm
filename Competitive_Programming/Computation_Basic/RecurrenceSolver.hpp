#include "../header.hpp"
#include "../Matrix/matrix.hpp"

// 定数項の存在する線形漸化式
// powかmod_powかはその都度変更する
// 係数の順番に注意する!!!
// 第1引数 : A[n] = a[0] + a[1] * A[n-k] + a[2] * A[n-k+1] + ... + a[k] * A[n-1]
// 第2引数 : A[0] = x[0], A[1] = x[1], ... , A[k-1] = x[k-1]
// 第3引数 : A[n]の値を求める
template<typename T>
T solve(vector<T>& a, vector<T>& x, long long n)
{
    int k = (int)a.size() - 1;
    if(n < k){
        return x[n];
    }
    mat<T> A(k+1,k+1);
    for(int i = 0; i < k+1; i++){
        A[0][i] = a[k-i];
    }
    for(int i = 0; i < k-1; i++){
        A[i+1][i] = 1;
    }
    A[k][k] = 1;
    mat<T> B = mod_pow(A,n-k+1);
    T res = 0;
    for(int i = 0; i < k; i++){
        res = (res + B[0][i]*x[k-1-i]%MOD) % MOD;
    }
    res = (res + B[0][k]) % MOD;
    return res;
}
