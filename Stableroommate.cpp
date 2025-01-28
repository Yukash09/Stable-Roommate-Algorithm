#include <bits/stdc++.h>
using namespace std;
#define int long long
#define float double
#define ilvaticano main
void enpassant(){
    int n = 6 ;
    // 1 - Ruby ; 2 - Aadi ; 3 - AVK ; 4 - Mikhi ; 5 - Arya  ; 6 - Peri ; 7 - Sameer ; 8 - Sato ; 9 - Shishu ; 10 - Srivats ; 11 - Suraj ; 12 - Tursan ; 13 - UG ; 14 - Rushi ; 15 - Venki ; 16 - Yukash ;
    vector<map<int,int>> preferences(n+1) ;
    vector<vector<int>> prefo(n+1) ;
    for(int i = 1 ; i <= n ; ++i){
        map<int,int> mp ;
        vector<int> listi ;
        for(int j = 0 ; j < n-1 ; ++j){
            int x ; cin >> x ;
            mp[x] = j ;
            listi.push_back(x) ;
        }
        preferences[i] = mp;
        prefo[i] = listi;
    }
    vector<int> proposo(n+1 , -1) ;
    vector<bool> hasproposed(n+1 , false) ;
    vector<vector<int>> rejaccun(n+1 , vector<int>(n+1 , 0)) ;
    int i = 1 ; int prev = 1 ;
    while(true){
        int cnt = 0 ;
        for(int i = 1 ; i <= n ; ++i){
            if(hasproposed[i]){
                cout << i << " has proposed" << endl ;
                cnt++ ;
                cout << "cnt " << cnt << endl ;
                continue ;
            }
            else{
                for(int j = 0 ; j < n-1 ; ++j){
                    int proposer = i ;
                    cout  << proposer << " proposes to  " << prefo[i][j] << endl ;
                    int proposed = prefo[i][j] ;
                    if(rejaccun[proposer][proposed] == 0){
                        cout << "Not rejected alr" << endl ;
                        int alrhol = proposo[proposed] ;
                        if(alrhol == -1){
                            proposo[proposed] = proposer ;
                            hasproposed[proposer] = true ;
                            break ;
                        }
                        else{
                            
                            if(preferences[proposed][alrhol] > preferences[proposed][proposer]){
                                proposo[proposed] = proposer ;
                                rejaccun[proposer][alrhol] = -1 ;
                                hasproposed[alrhol] = false ;
                                hasproposed[proposer] = true ;
                                break ;
                            }
                            else{
                                rejaccun[proposer][proposed] = -1 ;
                                hasproposed[proposer] = false ;
                                break ;
                            }
                        }
                    }
                    if(rejaccun[proposer][proposed] == -1){
                        cout << "Proposal rejected already" ;
                        if(j == n-2){
                            cout << "No stable matching" << endl ;
                            return ;
                        }
                        else{
                            continue ;
                        }
                    }
                }
            }
        }
        if(cnt == n){
            break ;
        }
    }
    // for(auto i : preferences[1]){
    //     cout << i.first << " " << i.second << endl;
    // }
    // cout << endl ;
    for(int i = 1 ; i <= n ; ++i){
        cout << i << " was proposed by " << proposo[i] << endl ;
        int index = 0 ;
        while(prefo[i][index] != proposo[i]){
            index++ ;
        }
        cout << index << endl ;
        int maxx = prefo[i].size() ;
        for(int j = index+1 ; j < maxx ; j++){
            int todel = prefo[i][index+1] ; 
            prefo[i].erase(prefo[i].begin()+index+1) ;
            int remo = 0 ;
            while(prefo[todel][remo] != i){
                remo++ ;
            }
            prefo[todel].erase(prefo[todel].begin() + remo) ;
            cout << "Preferences revamped" << endl ;
            for(int i = 1 ; i <= n ; ++i){
                cout << i << " : " << flush;
                for(int j = 0 ; j < prefo[i].size() ; ++j){
                    cout << prefo[i][j] << " " ;
                }
                cout << endl ;
            }
        }
    }
    cout << "Preferences revamped" << endl ;
    for(int i = 1 ; i <= n ; ++i){
        cout << i << " : " << flush;
        for(int j = 0 ; j < prefo[i].size() ; ++j){
            cout << prefo[i][j] << " " ;
        }
        cout << endl ;
    }

    while(true){
        int cnt = 0 ;
        for(int i = 1 ; i <= n ; ++i){
            vector<int> P ;
            vector<int> Q ;
            if(prefo[i].size() == 1){
                cout << i <<  " prefo size 1"  << endl ;
                cnt++ ;
                continue ;
            }
            else if(prefo[i].size() > 1){
                pair<int,int> start  ;
                int person2 = prefo[i][1] ;
                int person3 = prefo[person2][prefo[person2].size() - 1] ;
                start = {person2 , person3} ;
                P.push_back(person2) ;
                Q.push_back(person3) ;
                pair<int,int> curr = start ;
                do{
                    int per1 = curr.second ;
                    int per2 = prefo[per1][1] ;
                    int per3 = prefo[per2][prefo[per2].size() - 1] ;
                    curr = {per2 , per3} ;
                    P.push_back(per2) ;
                    Q.push_back(per3) ;
                }while(curr != start) ;
                cout << "Exited" << endl ;
                for(int j = 0 ; j < Q.size() - 1 ; j+= 1){
                    int a1 = Q[j] ; 
                    int a2 = P[j] ;
                    cout << a1 << " " << a2 << " to be removed " ;
                    int index1 = 0 ;
                    while(prefo[a1][index1] != a2){
                        index1++ ;
                    }
                    int index2 = 0 ;
                    while(prefo[a2][index2] != a1){
                        index2++ ;
                    }
                    cout << index1 << " " << index2 << endl ;
                    prefo[a1].erase(prefo[a1].begin() + index1) ;
                    prefo[a2].erase(prefo[a2].begin() + index2) ;
                    if(prefo[a1].size() == 0 || prefo[a2].size() == 0){
                    cout << "No stable matching exists" << endl ;
                    return ;
                    }
                } 
                cout << "Preferences revamped" << endl ;
                for(int i = 1 ; i <= n ; ++i){
                    cout << i << " : " << flush;
                    for(int j = 0 ; j < prefo[i].size() ; ++j){
                        cout << prefo[i][j] << " " ;
                    }
                    cout << endl ;
                }
            }
            else if(prefo[i].size() == 0){
                cout << "No stable matching exists" << endl ;
                return ;
            }
        }
        if(cnt == n){
            break ;
        }
    }
    cout << "Matching:" << endl ;
    for(int i = 1 ; i <= n ; i++){
        cout << i << " " << prefo[i][0] << endl ;
    }
    cout << "Done" << endl ;
}
int32_t ilvaticano(){
    ios_base::sync_with_stdio(false) ; 
    cin.tie(NULL) ; cout.tie(NULL) ;
    int TLE = 1 ;
    cin >> TLE ;
    while(TLE--){
        enpassant() ;
    }
}