//Maloth Dileep
//19MA20024


#include <bits/stdc++.h>
using namespace std;

vector<float> gauss_seidel2(vector<vector<float> >a, vector<float>b, vector<float>x) {
    for(int i=0; i<25; i++) {
        for(int j=0; j<b.size(); j++) {
            float c=b[j];
            for(int i=0; i<b.size(); i++) if(j!=i) c-=a[j][i]*x[i];
            x[j]=c/a[j][j];
        }
    }
    return x;
}

vector<vector<float>> gauss_seidel1(vector<vector<float> >a, vector<float>b, vector<float>x, int n, int m) {
    vector<vector<float> >xt;
    for(int i=0; i<n; i++) {
        vector<float>x1=x;
        x1.erase(x1.begin()+i);
        vector<vector<float> >anew;
        for(int j=0; j<a.size(); j++) {
            vector<float>anew1;
            for(int k=0; k<a[j].size(); k++) {
                if(i!=k) {
                    anew1.push_back(a[j][k]);
                }
            }
            anew.push_back(anew1);
        }
        if(x1.size()==m) {
            vector<float>x2;
            x2=gauss_seidel2(anew,b,x1);
            x2.insert(x2.begin()+i,0);
            xt.push_back(x2);
        }
        else {
            vector<vector<float> >xt1=gauss_seidel1(anew,b,x1,n-1,m);
            for(int j=0; j<xt1.size(); j++) xt1[j].insert(xt1[j].begin()+i,0);
            xt.insert(xt.end(),xt1.begin(),xt1.end());
        }
    }
    return xt;
}

void printBS(vector<vector<float> >ans,int n, int m,vector<float>z) {
    if(ans.size()) {
        for(int i=0; i<ans.size(); i++) {
            int p=0;
            for(int j=0; j<n-m; j++) if(ans[i][j]<0) p=1;
            if(p) {
                ans.erase(ans.begin()+i);
                i--;
            }
        }
    }
    else cout << "No Feasible solutions";
    if(ans.size()) {
        cout << endl << endl << "(";
        for(int i=0; i<ans[0].size(); i++) {
            cout << "x" << i+1 << ",";
        }
        cout << "z) = " << endl;
        for(int i=0; i<ans.size(); i++) {
            cout << "(";
            float z1=0;
            for(int j=0; j<z.size(); j++) z1+=(z[j]*ans[i][j]);
            for(int j=0; j<ans[0].size(); j++) cout << ans[i][j] << ",";
            cout << z1 << ")" << endl;
        }
    }
    else cout << "No Feasible solutions";

}

void printST(vector<vector<float> >st) {
    cout << endl;
    for(int i=0; i<st.size(); i++) {
        for(int j=0; j<st[i].size(); j++) {
            if(st[i][j]>=0) cout << " " << st[i][j] << " ";
            else cout << st[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<float> > ST(vector<vector<float> >a, vector<float>b, vector<float>x, int n, int m, vector<float>z, int q) {
    vector<vector<float> >st;
    for(int i=0; i<a.size(); i++) {
        vector<float>st1;
        for(int j=0; j<n-m; j++) {
            st1.push_back(a[i][j]);
        }
        st.push_back(st1);
    }
    st.push_back(z);
    for(int i=0; i<b.size(); i++) st[i].push_back(b[i]);
    st[st.size()-1].push_back(0);
    if(q==1) for(int i=0; i<st[st.size()-1].size()-1; i++) st[st.size()-1][i]*=(-1);
    return st;
}

vector<vector<float> > iterate(vector<vector<float> >st) {
    float p,min=100000000000000,pivot;
    for(int i=0; i<st[st.size()-1].size(); i++) {
        if(min>st[st.size()-1][i]) {
            min=st[st.size()-1][i];
            p=i;
        }
    }
    min=1000000000000000;
    for(int i=0; i<st.size()-1; i++) {
        if(min>(st[i][st[i].size()-1]/st[i][p]) && st[i][p]>0) {
            min=(st[i][st[i].size()-1]/st[i][p]);
            pivot=i;
        }
    }
    vector<vector<float> >newst=st;
    for(int i=0; i<st[0].size(); i++) {
        newst[pivot][i]=newst[pivot][i]/st[pivot][p];
    }
    for(int i=0; i<st.size(); i++) {
        newst[i][p]=(-1)*newst[i][p]/st[pivot][p];
    }
    newst[pivot][p]=1/st[pivot][p];
    for(int i=0; i<st.size(); i++) {
        if(i!=pivot) {
            for(int j=0; j<st[0].size(); j++) {
                if(j!=p) {
                    newst[i][j]=((((st[i][j])*(st[pivot][p]))-((st[pivot][j])*(st[i][p])))/st[pivot][p]);
                }
            }
        }
    }
    return newst;
}

int main() {
    vector<vector<float> >a;
    vector<float>b;
    int m,n;
    float k;
    cout << " m : ";
    cin >> m;
    cout << " n : ";
    cin >> n;
    for(int i=0; i<m; i++) {
        vector<float>a1;
        for(int j=0; j<n; j++) {
            cout << "Coefficient of x" << j+1 <<" : ";
            cin >> k;
            a1.push_back(k);
        }
        for(int j=0; j<m+1; j++) {
            if(j!=i) a1.push_back(0);
            else a1.push_back(1);
        }
        if(i==m-1) {
            a1[m-1]=-1;
            a1[m]=1;
        }
        cout << "value of constant "<< i+1<<"  : ";
        cin >> k;
        b.push_back(k);
        a.push_back(a1);
    }
    n+=m;
    vector<float>x(n,0);
    vector<vector<float> >ans1;
    if(m!=n) ans1=gauss_seidel1(a,b,x,n,m);
    else ans1.push_back(gauss_seidel2(a,b,x));
    vector<float>z;
    cout << endl << "Minimise Z value or Maximise Z value (0 or 1)?";
    int q;
    cin >> q;
    for(int i=0; i<n-m; i++) {
        cout << "Coefficient of x" << i+1 << " in Z equation : ";
        cin >> k;
        z.push_back(k);
    }
    vector<vector<float>>st;
    cout << "Basic Feasible solutions : " << endl;
    printBS(ans1,n,m,z);
    st=ST(a,b,x,n,m,z,q);
    cout << "Initial Simplex Matrix : " << endl;
    printST(st);
    cout << "Simplex matrix after first iteration : "<<endl;
    st=iterate(st);
    printST(st);
    st=iterate(st);
    cout << "Simplex matrix after second iteration : "<<endl;
    printST(st);
    int j=1;
    while(j++) {
        if(j==100) break;
        int i=0;
        for(; i<st[0].size(); i++) {
            if(st[st.size()-1][i]<0) break;
        }
        if(i==st[0].size()) break;
        else st=iterate(st);
    }
    if(j==100) cout << "No feasible solutions" << endl;
    else {
        cout << "Final simplex matrix : " << endl;
        printST(st);
    }
    return 0;
}
