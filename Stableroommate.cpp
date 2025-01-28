#include <bits/stdc++.h>
using namespace std;
#define int long long
#define float double
#define ilvaticano main
void enpassant(){
    int n = 16 ;
    // cout << "Input number of people" << endl ;
    // cin >> n ;
    // 1 - Ruby ; 2 - Aadi ; 3 - AVK ; 4 - Mikhi ; 5 - Arya  ; 6 - Peri ; 7 - Sameer ; 8 - Sato ; 9 - Shishu ; 10 - Srivats ; 11 - Suraj ; 12 - Tursan ; 13 - UG ; 14 - Rushi ; 15 - Venki ; 16 - Yukash ;

/* Example preferences (n = 6):
    1: 4 6 2 5 3
    2: 6 3 5 1 4
    3: 4 5 1 6 2
    4: 2 6 5 1 3
    5: 4 2 3 6 1
    6: 5 1 4 2 3
*/

    vector<map<int,int>> preferences(n+1) ; // Contains map of preferences with index in which they appear
/* For eg:
    preferences[1] = map --> [ {4 , 0} , {6 , 1} , {2 , 2} , {5 , 3} , {3 , 4}]
    preferences[2] = map --> [ {6 , 0} , {3 , 1} , {5 , 2} , {1 , 3} , {4 , 2}]
*/ 
    vector<vector<int>> prefo(n+1) ; // Contains just the preferences (This will be used for modifications)
/* For eg:
    prefo[1][0] = 4 ; prefo[1][1] = 6 etc.
*/
    
// Take inputs properly and initialize accordingly 
    cout << "Input preference orders" << endl ;
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

// Phase-1 

    vector<int> proposo(n+1 , -1) ; // Let A proposes to B. Then proposo[B] = A ;
    vector<bool> hasproposed(n+1 , false) ; // Boolean array to check if a person has already made a proposal that has not been rejected.
    vector<vector<int>> rejaccun(n+1 , vector<int>(n+1 , 0)) ; // Boolean array to check if person A got rejected by person B already i.e., rejaccun[A][B] = -1 if A's proposal to B was rejected at some point of time

    int i = 1 ; int prev = 1 ;
    while(true){
        int cnt = 0 ;
        for(int i = 1 ; i <= n ; ++i){
            if(hasproposed[i]){ // If the person has already made a proposal that has not been rejected, continue
                cout << i << " has proposed" << endl ;
                cnt++ ;
                cout << "cnt " << cnt << endl ;
                continue ;
            }
            else{
                for(int j = 0 ; j < n-1 ; ++j){ // Try proposing to the person with highest preference who has not rejected already. Let's say A proposes to B
                    int proposer = i ;
                    cout  << proposer << " proposes to  " << prefo[i][j] << endl ;
                    int proposed = prefo[i][j] ;
                    if(rejaccun[proposer][proposed] == 0){ // Not rejected already
                        cout << "Not rejected alr" << endl ;
                        int alrhol = proposo[proposed] ; // Current consideration of B
                        if(alrhol == -1){ // No person has proposed to B ==> B will consider the proposal of A
                            proposo[proposed] = proposer ; // proposo[B] = A
                            hasproposed[proposer] = true ;
                            break ;
                        }
                        else{                             
                            if(preferences[proposed][alrhol] > preferences[proposed][proposer]){ // If the current consideration of B (let's say C) has lower preference , then reject that proposal and consider this proposal
                                proposo[proposed] = proposer ; // proposo[B] = A && hasproposed[C] = false , rejaccun[C][B] = -1
                                rejaccun[alrhol][proposed] = -1 ;
                                hasproposed[alrhol] = false ;
                                hasproposed[proposer] = true ;
                                break ;
                            }
                            else{ // Reject the current proposal
                                rejaccun[proposer][proposed] = -1 ; // proposo[B] = C 
                                hasproposed[proposer] = false ;
                                break ;
                            }
                        }
                    }
                    if(rejaccun[proposer][proposed] == -1){
                        cout << "Proposal rejected already" ;
                        if(j == n-2){ // If all the proposal for a particular person gets rejected then there is no stable matching.
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
        if(cnt == n){ // If all the person has proposed which hasn't gotten rejected then phase 1 is complete.
            break ;
        }
    }
    // for(auto i : preferences[1]){
    //     cout << i.first << " " << i.second << endl;
    // }
    // cout << endl ;

// Reducing Preference List
// Task is to reduce the size of preference list by removing pairs that can't be in the stable matching
    for(int i = 1 ; i <= n ; ++i){
        // Debug:
        // cout << i << " was proposed by " << proposo[i] << endl ;
        
        int index = 0 ;
        while(prefo[i][index] != proposo[i]){
            index++ ;
        }

        int maxx = prefo[i].size() ;
        for(int j = index+1 ; j < maxx ; j++){  // For each pair in proposo - {i , proposo[i]} --> remove all preferences of i , lower than proposo[i] symmetrically.
            int todel = prefo[i][index+1] ; 
            prefo[i].erase(prefo[i].begin()+index+1) ;
            
            int remo = 0 ;
            while(prefo[todel][remo] != i){
                remo++ ;
            }
            prefo[todel].erase(prefo[todel].begin() + remo) ;

            // Debug:
            // cout << "Preferences revamped" << endl ;
            // for(int i = 1 ; i <= n ; ++i){
            //     cout << i << " : " << flush;
            //     for(int j = 0 ; j < prefo[i].size() ; ++j){
            //         cout << prefo[i][j] << " " ;
            //     }
            //     cout << endl ;
            // }
        }
    }

    // Debug:
    // cout << "Preferences revamped" << endl ;
    // for(int i = 1 ; i <= n ; ++i){
    //     cout << i << " : " << flush;
    //     for(int j = 0 ; j < prefo[i].size() ; ++j){
    //         cout << prefo[i][j] << " " ;
    //     }
    //     cout << endl ;
    // }

// Phase-2 : 
// Task is to find all rotations and eliminate the pairs that can be removed.
    while(true){
        int cnt = 0 ;
        for(int i = 1 ; i <= n ; ++i){
            vector<int> P ; // Lists to keep track of the pairs to be rejected/removed
            vector<int> Q ;
            if(prefo[i].size() == 1){ // If size of preference list is 1, then continue 
                cout << i <<  " prefo size 1"  << endl ;
                cnt++ ;
                continue ;
            }
            else if(prefo[i].size() > 1){ 

                pair<int,int> start  ; // Find the starting pair 
                int person2 = prefo[i][1] ; // Second preference of this person (let's say B)
                int person3 = prefo[person2][prefo[person2].size() - 1] ; // Last preference of B (let's say C)
                start = {person2 , person3} ; // start pair = {B , C}
                P.push_back(person2) ; 
                Q.push_back(person3) ;
                pair<int,int> curr = start ;

                do{
                    int per1 = curr.second ;
                    int per2 = prefo[per1][1] ; // second preference of C (let's say D)
                    int per3 = prefo[per2][prefo[per2].size() - 1] ; // last preference of D
                    curr = {per2 , per3} ; // Recursively find the next pair = {C's second preference (let's say D) , D's last preference}
                    P.push_back(per2) ;
                    Q.push_back(per3) ;
                }while(curr != start) ; // Do this while start pair != curr pair. The condition breaks when a cycle is found

                // Remove the pairs encountered in the cycle
                for(int j = 0 ; j < Q.size() - 1 ; j+= 1){
                    int a1 = Q[j] ; 
                    int a2 = P[j] ;

                    int index1 = 0 ;
                    while(prefo[a1][index1] != a2){ // Naively find where a2 is in preference list of a1
                        index1++ ;
                    }
                    int index2 = 0 ;
                    while(prefo[a2][index2] != a1){ // Naively find where a1 is in preference list of a2
                        index2++ ;
                    }

                    prefo[a1].erase(prefo[a1].begin() + index1) ;
                    prefo[a2].erase(prefo[a2].begin() + index2) ;

                // If the preference list size goes to zero --> No stable matching
                    if(prefo[a1].size() == 0 || prefo[a2].size() == 0){
                        cout << "No stable matching exists" << endl ;
                        return ;
                    }
                } 
                // Debug:
                // cout << "Preferences revamped" << endl ;
                // for(int i = 1 ; i <= n ; ++i){
                //     cout << i << " : " << flush;
                //     for(int j = 0 ; j < prefo[i].size() ; ++j){
                //         cout << prefo[i][j] << " " ;
                //     }
                //     cout << endl ;
                // }
            }

            else if(prefo[i].size() == 0){ // If the preference list size goes to zero --> No stable matching
                cout << "No stable matching exists" << endl ;
                return ;
            }
        }
        if(cnt == n){ // If all preference lists have size 1 --> stable matching found
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
    // cin >> TLE ;
    while(TLE--){
        enpassant() ;
    }
}
