#include "../header.hpp"

//接尾辞配列および最長共通接頭辞の配列(lcp)を求める(O(nlog^2(n)))
//SA_ISの方が速い
//lcp(高さ配列)も計算するときはコメントアウトをはずす
class suffixarray{
public:
    int sz,index1,index2;
    vector<int> rnk,tmp,sa,lcp;
    string recs;
    suffixarray(string s){
        recs = s;
        sz = (int)s.size();
        rnk.resize(sz+1),tmp.resize(sz+1);
        make_sa();
        // make_lcp();
    }
    void make_sa(){
        index1 = sz;
        sa.resize(index1+1);
        rep(i,index1+1){
            sa[i] = i;
            rnk[i] = i<index1?recs[i]:-1;
        }
        auto comp = [&](int i,int j){
            if(rnk[i] != rnk[j]){
                return rnk[i] < rnk[j];
            }else{
                int ri = (i+index2<=index1)?rnk[i+index2]:-1;
                int rj = (j+index2<=index1)?rnk[j+index2]:-1;
                return ri < rj;
            }
        };
        for(index2=1;index2<=index1;index2*=2){
            sort(sa.begin(),sa.end(),comp);
            tmp[sa[0]] = 0;
            for(int i=1;i<=index1;i++){
                tmp[sa[i]] = tmp[sa[i-1]]+(comp(sa[i-1],sa[i])?1:0);
            }
            rep(i,index1+1){
                rnk[i] = tmp[i];
            }
        }
    }
    void make_lcp(){
        lcp.resize(sz+1);
        rep(i,sz+1){
            rnk[sa[i]] = i;
        }
        int h = 0;
        lcp[0] = 0;
        rep(i,sz){
            int j = sa[rnk[i]-1];
            if(h > 0){
                h--;
            }
            for(;j+h<sz&&i+h<sz;h++){
                if(recs[j+h] != recs[i+h]){
                    break;
                }
            }
            lcp[rnk[i]-1] = h;
        }
    }
};