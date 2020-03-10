//
//  binary_search.cpp
//  linear_structure
//
//  Created by dahye Jeong on 2017. 5. 30..
//  Copyright © 2017년 dahye Jeong. All rights reserved.
//

#include "binary_search.hpp"

int find(int s, int e)
{
    while(s<=e)
    {
        // s시작 인덱스 e끝 인덱스 m 가운데
        int m = (s+e)/2;
        if(S[m]==k) return m;
        if(S[m]>k) e=m-1;
        else s = m+1;
    }
    return -1;
}
