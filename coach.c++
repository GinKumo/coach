#include <cstdio>
#include <limits>
#include <cstdlib>
#include <utility>
#include <vector>
#include <iostream>
using namespace std;
int main()
{
    int i, j, idx;
    int n, m;
    vector<int> sgrp(48);
    vector<int> gcnt(48);
    vector<int> gren(48);
    int curgroup=0, incgroup=0, tmpgroup=0;
   
    //while (!feof(stdin)) {
        m=-1;
        n=-1;
        if (fscanf(stdin,"%d %d",&n,&m) != 2) {
            exit(1);
        }
        fill(sgrp.begin(),sgrp.begin()+n,-1);
        fill(gcnt.begin(),gcnt.end(),0);
        fill(gren.begin(),gren.end(),-1);
        curgroup=0;

        //cerr << "n=" << n << " m=" << m << endl;
        for (idx=0;idx<m;++idx) {
            if (fscanf(stdin,"%d %d",&i,&j) != 2) {
                exit(1);
            }
            --i; --j;
            //cerr << "i=" << i << " j=" << j << endl;
            if (sgrp[i] == -1) {
                if (sgrp[j] == -1) {
                    incgroup = curgroup;
                    sgrp[i] = incgroup;
                    sgrp[j] = incgroup;
                    gcnt[incgroup] = 2;
                    incgroup = curgroup;
                    ++curgroup;
                } else {
                    incgroup = sgrp[j];
                    sgrp[i] = incgroup;
                    ++gcnt[incgroup];
                }
            } else if (sgrp[j] == -1) {
                incgroup = sgrp[i];
                sgrp[j] = incgroup;
                ++gcnt[incgroup];
            } else {
                if (sgrp[i] < sgrp[j]) {
                    incgroup = sgrp[i];
                    tmpgroup = sgrp[j];
                } else {
                    incgroup = sgrp[j];
                    tmpgroup = sgrp[i];
                }
                if (incgroup != tmpgroup) {
                    gcnt[incgroup] += gcnt[tmpgroup];
                    gcnt[tmpgroup] = 0;
                    gren[tmpgroup] = incgroup; // rename
                    //cerr << "rename " << tmpgroup << " to " << incgroup << endl;
                }
            }
            //cerr << "gcnt[0]=" << gcnt[0] << endl;
            // did we determine that we have too many in one group?
            if (gcnt[incgroup] > 3) {
                break;
            }
        }
        ++idx;
        for (;idx<m;++idx) {
            if (fscanf(stdin,"%d %d",&i,&j) != 2) {
                exit(1);
            }
        }
        //cerr << "----------------------------------------" << endl;
        // did we determine that we have too many in one group?
        if (gcnt[incgroup] > 3) {
            fprintf(stdout, "-1\n");
            exit(0);
        }

        // must have a solution here
        j = 0;
        for (i=0; i<=curgroup; ++i) {
            // assign loners to groups of two
            if (gcnt[i] == 2) {
                for (; j<n; ++j) {
                    if (sgrp[j] == -1) {
                        ++gcnt[i];
                        sgrp[j] = i;
                        break;
                    }
                }
                if (j == n) {
                    fprintf(stdout,"-1\n");
                    exit(0);
                }
            }
        }
        // assign loners to new groups
        for (j=0;j<n;++j) {
            if (sgrp[j] == -1) {
                // if the current group is full start a new one
                if (gcnt[curgroup] == 3) {
                    ++curgroup;
                }
                // add a member to the current group
                sgrp[j] = curgroup;
                //cerr << "adding " << j <<  " to " << curgroup << endl;
                ++gcnt[curgroup];
            }
        }
        // go through all groups and print out members
        m = 0;
        for (i=0;i<=curgroup;++i) {
            for (j=0; j<n; ++j) {
                tmpgroup = sgrp[j];
                while (gren[tmpgroup] != -1) { tmpgroup = gren[tmpgroup]; }
                sgrp[j] = tmpgroup;
                if (sgrp[j] == i) {
                    ++m;
                    //cout << j+1 << ((m%3) ? " " : "\n") ;
                    fprintf(stdout, "%d%s",j+1, ((m%3) ? " " : "\n"));
                }
            }
        }
    //}
}

