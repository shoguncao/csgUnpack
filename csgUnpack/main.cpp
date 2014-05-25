//
//  main.cpp
//  csgUnpack
//
//  Created by 曹寿刚 on 14-5-25.
//  Copyright (c) 2014年 YiXing. All rights reserved.
//

#include <iostream>
#include "CSGUnpack.h"

int main(int argc, const char * argv[])
{
    string in = "/Users/caoshougang/shoguncao/数据/Project/csgUnpack/ANRISONOZAKI.rar";
    string out = "/Users/caoshougang/shoguncao/数据/Project/csgUnpack/ANRISONOZAKI.avi";
    
    CSGUnpack unpack = CSGUnpack(in, out);
    
    unpack.unpack();
    
    return 0;
}

