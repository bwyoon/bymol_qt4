#include <math.h>

int EdgeTable[256]=
{
        0x000, 0x109, 0x203, 0x30a, 0x406, 0x50f, 0x605, 0x70c, 0x80c, 0x905, 0xa0f, 0xb06, 0xc0a, 0xd03, 0xe09, 0xf00, 
        0x190, 0x099, 0x393, 0x29a, 0x596, 0x49f, 0x795, 0x69c, 0x99c, 0x895, 0xb9f, 0xa96, 0xd9a, 0xc93, 0xf99, 0xe90, 
        0x230, 0x339, 0x033, 0x13a, 0x636, 0x73f, 0x435, 0x53c, 0xa3c, 0xb35, 0x83f, 0x936, 0xe3a, 0xf33, 0xc39, 0xd30, 
        0x3a0, 0x2a9, 0x1a3, 0x0aa, 0x7a6, 0x6af, 0x5a5, 0x4ac, 0xbac, 0xaa5, 0x9af, 0x8a6, 0xfaa, 0xea3, 0xda9, 0xca0, 
        0x460, 0x569, 0x663, 0x76a, 0x066, 0x16f, 0x265, 0x36c, 0xc6c, 0xd65, 0xe6f, 0xf66, 0x86a, 0x963, 0xa69, 0xb60, 
        0x5f0, 0x4f9, 0x7f3, 0x6fa, 0x1f6, 0x0ff, 0x3f5, 0x2fc, 0xdfc, 0xcf5, 0xfff, 0xef6, 0x9fa, 0x8f3, 0xbf9, 0xaf0, 
        0x650, 0x759, 0x453, 0x55a, 0x256, 0x35f, 0x055, 0x15c, 0xe5c, 0xf55, 0xc5f, 0xd56, 0xa5a, 0xb53, 0x859, 0x950, 
        0x7c0, 0x6c9, 0x5c3, 0x4ca, 0x3c6, 0x2cf, 0x1c5, 0x0cc, 0xfcc, 0xec5, 0xdcf, 0xcc6, 0xbca, 0xac3, 0x9c9, 0x8c0, 
        0x8c0, 0x9c9, 0xac3, 0xbca, 0xcc6, 0xdcf, 0xec5, 0xfcc, 0x0cc, 0x1c5, 0x2cf, 0x3c6, 0x4ca, 0x5c3, 0x6c9, 0x7c0, 
        0x950, 0x859, 0xb53, 0xa5a, 0xd56, 0xc5f, 0xf55, 0xe5c, 0x15c, 0x055, 0x35f, 0x256, 0x55a, 0x453, 0x759, 0x650, 
        0xaf0, 0xbf9, 0x8f3, 0x9fa, 0xef6, 0xfff, 0xcf5, 0xdfc, 0x2fc, 0x3f5, 0x0ff, 0x1f6, 0x6fa, 0x7f3, 0x4f9, 0x5f0, 
        0xb60, 0xa69, 0x963, 0x86a, 0xf66, 0xe6f, 0xd65, 0xc6c, 0x36c, 0x265, 0x16f, 0x066, 0x76a, 0x663, 0x569, 0x460, 
        0xca0, 0xda9, 0xea3, 0xfaa, 0x8a6, 0x9af, 0xaa5, 0xbac, 0x4ac, 0x5a5, 0x6af, 0x7a6, 0x0aa, 0x1a3, 0x2a9, 0x3a0, 
        0xd30, 0xc39, 0xf33, 0xe3a, 0x936, 0x83f, 0xb35, 0xa3c, 0x53c, 0x435, 0x73f, 0x636, 0x13a, 0x033, 0x339, 0x230, 
        0xe90, 0xf99, 0xc93, 0xd9a, 0xa96, 0xb9f, 0x895, 0x99c, 0x69c, 0x795, 0x49f, 0x596, 0x29a, 0x393, 0x099, 0x190, 
        0xf00, 0xe09, 0xd03, 0xc0a, 0xb06, 0xa0f, 0x905, 0x80c, 0x70c, 0x605, 0x50f, 0x406, 0x30a, 0x203, 0x109, 0x000
};

int TriTable[256][16] =  
{
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 8, 3, 9, 8, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 8, 3, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {9, 2, 10, 0, 2, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {2, 8, 3, 2, 10, 8, 10, 9, 8, -1, -1, -1, -1, -1, -1, -1},
        {3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 11, 2, 8, 11, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 9, 0, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 11, 2, 1, 9, 11, 9, 8, 11, -1, -1, -1, -1, -1, -1, -1},
        {3, 10, 1, 11, 10, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 10, 1, 0, 8, 10, 8, 11, 10, -1, -1, -1, -1, -1, -1, -1},
        {3, 9, 0, 3, 11, 9, 11, 10, 9, -1, -1, -1, -1, -1, -1, -1},
        {9, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {4, 3, 0, 7, 3, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 1, 9, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {4, 1, 9, 4, 7, 1, 7, 3, 1, -1, -1, -1, -1, -1, -1, -1},
        {1, 2, 10, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {3, 4, 7, 3, 0, 4, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1},
        {9, 2, 10, 9, 0, 2, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1},
        {2, 10, 9, 2, 9, 7, 2, 7, 3, 7, 9, 4, -1, -1, -1, -1},
        {8, 4, 7, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {11, 4, 7, 11, 2, 4, 2, 0, 4, -1, -1, -1, -1, -1, -1, -1},
        {9, 0, 1, 8, 4, 7, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1},
        {4, 7, 11, 9, 4, 11, 9, 11, 2, 9, 2, 1, -1, -1, -1, -1},
        {3, 10, 1, 3, 11, 10, 7, 8, 4, -1, -1, -1, -1, -1, -1, -1},
        {1, 11, 10, 1, 4, 11, 1, 0, 4, 7, 11, 4, -1, -1, -1, -1},
        {4, 7, 8, 9, 0, 11, 9, 11, 10, 11, 0, 3, -1, -1, -1, -1},
        {4, 7, 11, 4, 11, 9, 9, 11, 10, -1, -1, -1, -1, -1, -1, -1},
        {9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {9, 5, 4, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 5, 4, 1, 5, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {8, 5, 4, 8, 3, 5, 3, 1, 5, -1, -1, -1, -1, -1, -1, -1},
        {1, 2, 10, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {3, 0, 8, 1, 2, 10, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1},
        {5, 2, 10, 5, 4, 2, 4, 0, 2, -1, -1, -1, -1, -1, -1, -1},
        {2, 10, 5, 3, 2, 5, 3, 5, 4, 3, 4, 8, -1, -1, -1, -1},
        {9, 5, 4, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 11, 2, 0, 8, 11, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1},
        {0, 5, 4, 0, 1, 5, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1},
        {2, 1, 5, 2, 5, 8, 2, 8, 11, 4, 8, 5, -1, -1, -1, -1},
        {10, 3, 11, 10, 1, 3, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1},
        {4, 9, 5, 0, 8, 1, 8, 10, 1, 8, 11, 10, -1, -1, -1, -1},
        {5, 4, 0, 5, 0, 11, 5, 11, 10, 11, 0, 3, -1, -1, -1, -1},
        {5, 4, 8, 5, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1},
        {9, 7, 8, 5, 7, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {9, 3, 0, 9, 5, 3, 5, 7, 3, -1, -1, -1, -1, -1, -1, -1},
        {0, 7, 8, 0, 1, 7, 1, 5, 7, -1, -1, -1, -1, -1, -1, -1},
        {1, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {9, 7, 8, 9, 5, 7, 10, 1, 2, -1, -1, -1, -1, -1, -1, -1},
        {10, 1, 2, 9, 5, 0, 5, 3, 0, 5, 7, 3, -1, -1, -1, -1},
        {8, 0, 2, 8, 2, 5, 8, 5, 7, 10, 5, 2, -1, -1, -1, -1},
        {2, 10, 5, 2, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1},
        {7, 9, 5, 7, 8, 9, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1},
        {9, 5, 7, 9, 7, 2, 9, 2, 0, 2, 7, 11, -1, -1, -1, -1},
        {2, 3, 11, 0, 1, 8, 1, 7, 8, 1, 5, 7, -1, -1, -1, -1},
        {11, 2, 1, 11, 1, 7, 7, 1, 5, -1, -1, -1, -1, -1, -1, -1},
        {9, 5, 8, 8, 5, 7, 10, 1, 3, 10, 3, 11, -1, -1, -1, -1},
        {5, 7, 0, 5, 0, 9, 7, 11, 0, 1, 0, 10, 11, 10, 0, -1},
        {11, 10, 0, 11, 0, 3, 10, 5, 0, 8, 0, 7, 5, 7, 0, -1},
        {11, 10, 5, 7, 11, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 8, 3, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {9, 0, 1, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 8, 3, 1, 9, 8, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1},
        {1, 6, 5, 2, 6, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 6, 5, 1, 2, 6, 3, 0, 8, -1, -1, -1, -1, -1, -1, -1},
        {9, 6, 5, 9, 0, 6, 0, 2, 6, -1, -1, -1, -1, -1, -1, -1},
        {5, 9, 8, 5, 8, 2, 5, 2, 6, 3, 2, 8, -1, -1, -1, -1},
        {2, 3, 11, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {11, 0, 8, 11, 2, 0, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1},
        {0, 1, 9, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1},
        {5, 10, 6, 1, 9, 2, 9, 11, 2, 9, 8, 11, -1, -1, -1, -1},
        {6, 3, 11, 6, 5, 3, 5, 1, 3, -1, -1, -1, -1, -1, -1, -1},
        {0, 8, 11, 0, 11, 5, 0, 5, 1, 5, 11, 6, -1, -1, -1, -1},
        {3, 11, 6, 0, 3, 6, 0, 6, 5, 0, 5, 9, -1, -1, -1, -1},
        {6, 5, 9, 6, 9, 11, 11, 9, 8, -1, -1, -1, -1, -1, -1, -1},
        {5, 10, 6, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {4, 3, 0, 4, 7, 3, 6, 5, 10, -1, -1, -1, -1, -1, -1, -1},
        {1, 9, 0, 5, 10, 6, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1},
        {10, 6, 5, 1, 9, 7, 1, 7, 3, 7, 9, 4, -1, -1, -1, -1},
        {6, 1, 2, 6, 5, 1, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1},
        {1, 2, 5, 5, 2, 6, 3, 0, 4, 3, 4, 7, -1, -1, -1, -1},
        {8, 4, 7, 9, 0, 5, 0, 6, 5, 0, 2, 6, -1, -1, -1, -1},
        {7, 3, 9, 7, 9, 4, 3, 2, 9, 5, 9, 6, 2, 6, 9, -1},
        {3, 11, 2, 7, 8, 4, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1},
        {5, 10, 6, 4, 7, 2, 4, 2, 0, 2, 7, 11, -1, -1, -1, -1},
        {0, 1, 9, 4, 7, 8, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1},
        {9, 2, 1, 9, 11, 2, 9, 4, 11, 7, 11, 4, 5, 10, 6, -1},
        {8, 4, 7, 3, 11, 5, 3, 5, 1, 5, 11, 6, -1, -1, -1, -1},
        {5, 1, 11, 5, 11, 6, 1, 0, 11, 7, 11, 4, 0, 4, 11, -1},
        {0, 5, 9, 0, 6, 5, 0, 3, 6, 11, 6, 3, 8, 4, 7, -1},
        {6, 5, 9, 6, 9, 11, 4, 7, 9, 7, 11, 9, -1, -1, -1, -1},
        {10, 4, 9, 6, 4, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {4, 10, 6, 4, 9, 10, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1},
        {10, 0, 1, 10, 6, 0, 6, 4, 0, -1, -1, -1, -1, -1, -1, -1},
        {8, 3, 1, 8, 1, 6, 8, 6, 4, 6, 1, 10, -1, -1, -1, -1},
        {1, 4, 9, 1, 2, 4, 2, 6, 4, -1, -1, -1, -1, -1, -1, -1},
        {3, 0, 8, 1, 2, 9, 2, 4, 9, 2, 6, 4, -1, -1, -1, -1},
        {0, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {8, 3, 2, 8, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1},
        {10, 4, 9, 10, 6, 4, 11, 2, 3, -1, -1, -1, -1, -1, -1, -1},
        {0, 8, 2, 2, 8, 11, 4, 9, 10, 4, 10, 6, -1, -1, -1, -1},
        {3, 11, 2, 0, 1, 6, 0, 6, 4, 6, 1, 10, -1, -1, -1, -1},
        {6, 4, 1, 6, 1, 10, 4, 8, 1, 2, 1, 11, 8, 11, 1, -1},
        {9, 6, 4, 9, 3, 6, 9, 1, 3, 11, 6, 3, -1, -1, -1, -1},
        {8, 11, 1, 8, 1, 0, 11, 6, 1, 9, 1, 4, 6, 4, 1, -1},
        {3, 11, 6, 3, 6, 0, 0, 6, 4, -1, -1, -1, -1, -1, -1, -1},
        {6, 4, 8, 11, 6, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {7, 10, 6, 7, 8, 10, 8, 9, 10, -1, -1, -1, -1, -1, -1, -1},
        {0, 7, 3, 0, 10, 7, 0, 9, 10, 6, 7, 10, -1, -1, -1, -1},
        {10, 6, 7, 1, 10, 7, 1, 7, 8, 1, 8, 0, -1, -1, -1, -1},
        {10, 6, 7, 10, 7, 1, 1, 7, 3, -1, -1, -1, -1, -1, -1, -1},
        {1, 2, 6, 1, 6, 8, 1, 8, 9, 8, 6, 7, -1, -1, -1, -1},
        {2, 6, 9, 2, 9, 1, 6, 7, 9, 0, 9, 3, 7, 3, 9, -1},
        {7, 8, 0, 7, 0, 6, 6, 0, 2, -1, -1, -1, -1, -1, -1, -1},
        {7, 3, 2, 6, 7, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {2, 3, 11, 10, 6, 8, 10, 8, 9, 8, 6, 7, -1, -1, -1, -1},
        {2, 0, 7, 2, 7, 11, 0, 9, 7, 6, 7, 10, 9, 10, 7, -1},
        {1, 8, 0, 1, 7, 8, 1, 10, 7, 6, 7, 10, 2, 3, 11, -1},
        {11, 2, 1, 11, 1, 7, 10, 6, 1, 6, 7, 1, -1, -1, -1, -1},
        {8, 9, 6, 8, 6, 7, 9, 1, 6, 11, 6, 3, 1, 3, 6, -1},
        {0, 9, 1, 11, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {7, 8, 0, 7, 0, 6, 3, 11, 0, 11, 6, 0, -1, -1, -1, -1},
        {7, 11, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {3, 0, 8, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 1, 9, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {8, 1, 9, 8, 3, 1, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1},
        {10, 1, 2, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 2, 10, 3, 0, 8, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1},
        {2, 9, 0, 2, 10, 9, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1},
        {6, 11, 7, 2, 10, 3, 10, 8, 3, 10, 9, 8, -1, -1, -1, -1},
        {7, 2, 3, 6, 2, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {7, 0, 8, 7, 6, 0, 6, 2, 0, -1, -1, -1, -1, -1, -1, -1},
        {2, 7, 6, 2, 3, 7, 0, 1, 9, -1, -1, -1, -1, -1, -1, -1},
        {1, 6, 2, 1, 8, 6, 1, 9, 8, 8, 7, 6, -1, -1, -1, -1},
        {10, 7, 6, 10, 1, 7, 1, 3, 7, -1, -1, -1, -1, -1, -1, -1},
        {10, 7, 6, 1, 7, 10, 1, 8, 7, 1, 0, 8, -1, -1, -1, -1},
        {0, 3, 7, 0, 7, 10, 0, 10, 9, 6, 10, 7, -1, -1, -1, -1},
        {7, 6, 10, 7, 10, 8, 8, 10, 9, -1, -1, -1, -1, -1, -1, -1},
        {6, 8, 4, 11, 8, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {3, 6, 11, 3, 0, 6, 0, 4, 6, -1, -1, -1, -1, -1, -1, -1},
        {8, 6, 11, 8, 4, 6, 9, 0, 1, -1, -1, -1, -1, -1, -1, -1},
        {9, 4, 6, 9, 6, 3, 9, 3, 1, 11, 3, 6, -1, -1, -1, -1},
        {6, 8, 4, 6, 11, 8, 2, 10, 1, -1, -1, -1, -1, -1, -1, -1},
        {1, 2, 10, 3, 0, 11, 0, 6, 11, 0, 4, 6, -1, -1, -1, -1},
        {4, 11, 8, 4, 6, 11, 0, 2, 9, 2, 10, 9, -1, -1, -1, -1},
        {10, 9, 3, 10, 3, 2, 9, 4, 3, 11, 3, 6, 4, 6, 3, -1},
        {8, 2, 3, 8, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1},
        {0, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 9, 0, 2, 3, 4, 2, 4, 6, 4, 3, 8, -1, -1, -1, -1},
        {1, 9, 4, 1, 4, 2, 2, 4, 6, -1, -1, -1, -1, -1, -1, -1},
        {8, 1, 3, 8, 6, 1, 8, 4, 6, 6, 10, 1, -1, -1, -1, -1},
        {10, 1, 0, 10, 0, 6, 6, 0, 4, -1, -1, -1, -1, -1, -1, -1},
        {4, 6, 3, 4, 3, 8, 6, 10, 3, 0, 3, 9, 10, 9, 3, -1},
        {10, 9, 4, 6, 10, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {4, 9, 5, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 8, 3, 4, 9, 5, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1},
        {5, 0, 1, 5, 4, 0, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1},
        {11, 7, 6, 8, 3, 4, 3, 5, 4, 3, 1, 5, -1, -1, -1, -1},
        {9, 5, 4, 10, 1, 2, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1},
        {6, 11, 7, 1, 2, 10, 0, 8, 3, 4, 9, 5, -1, -1, -1, -1},
        {7, 6, 11, 5, 4, 10, 4, 2, 10, 4, 0, 2, -1, -1, -1, -1},
        {3, 4, 8, 3, 5, 4, 3, 2, 5, 10, 5, 2, 11, 7, 6, -1},
        {7, 2, 3, 7, 6, 2, 5, 4, 9, -1, -1, -1, -1, -1, -1, -1},
        {9, 5, 4, 0, 8, 6, 0, 6, 2, 6, 8, 7, -1, -1, -1, -1},
        {3, 6, 2, 3, 7, 6, 1, 5, 0, 5, 4, 0, -1, -1, -1, -1},
        {6, 2, 8, 6, 8, 7, 2, 1, 8, 4, 8, 5, 1, 5, 8, -1},
        {9, 5, 4, 10, 1, 6, 1, 7, 6, 1, 3, 7, -1, -1, -1, -1},
        {1, 6, 10, 1, 7, 6, 1, 0, 7, 8, 7, 0, 9, 5, 4, -1},
        {4, 0, 10, 4, 10, 5, 0, 3, 10, 6, 10, 7, 3, 7, 10, -1},
        {7, 6, 10, 7, 10, 8, 5, 4, 10, 4, 8, 10, -1, -1, -1, -1},
        {6, 9, 5, 6, 11, 9, 11, 8, 9, -1, -1, -1, -1, -1, -1, -1},
        {3, 6, 11, 0, 6, 3, 0, 5, 6, 0, 9, 5, -1, -1, -1, -1},
        {0, 11, 8, 0, 5, 11, 0, 1, 5, 5, 6, 11, -1, -1, -1, -1},
        {6, 11, 3, 6, 3, 5, 5, 3, 1, -1, -1, -1, -1, -1, -1, -1},
        {1, 2, 10, 9, 5, 11, 9, 11, 8, 11, 5, 6, -1, -1, -1, -1},
        {0, 11, 3, 0, 6, 11, 0, 9, 6, 5, 6, 9, 1, 2, 10, -1},
        {11, 8, 5, 11, 5, 6, 8, 0, 5, 10, 5, 2, 0, 2, 5, -1},
        {6, 11, 3, 6, 3, 5, 2, 10, 3, 10, 5, 3, -1, -1, -1, -1},
        {5, 8, 9, 5, 2, 8, 5, 6, 2, 3, 8, 2, -1, -1, -1, -1},
        {9, 5, 6, 9, 6, 0, 0, 6, 2, -1, -1, -1, -1, -1, -1, -1},
        {1, 5, 8, 1, 8, 0, 5, 6, 8, 3, 8, 2, 6, 2, 8, -1},
        {1, 5, 6, 2, 1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 3, 6, 1, 6, 10, 3, 8, 6, 5, 6, 9, 8, 9, 6, -1},
        {10, 1, 0, 10, 0, 6, 9, 5, 0, 5, 6, 0, -1, -1, -1, -1},
        {0, 3, 8, 5, 6, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {10, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {11, 5, 10, 7, 5, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {11, 5, 10, 11, 7, 5, 8, 3, 0, -1, -1, -1, -1, -1, -1, -1},
        {5, 11, 7, 5, 10, 11, 1, 9, 0, -1, -1, -1, -1, -1, -1, -1},
        {10, 7, 5, 10, 11, 7, 9, 8, 1, 8, 3, 1, -1, -1, -1, -1},
        {11, 1, 2, 11, 7, 1, 7, 5, 1, -1, -1, -1, -1, -1, -1, -1},
        {0, 8, 3, 1, 2, 7, 1, 7, 5, 7, 2, 11, -1, -1, -1, -1},
        {9, 7, 5, 9, 2, 7, 9, 0, 2, 2, 11, 7, -1, -1, -1, -1},
        {7, 5, 2, 7, 2, 11, 5, 9, 2, 3, 2, 8, 9, 8, 2, -1},
        {2, 5, 10, 2, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1},
        {8, 2, 0, 8, 5, 2, 8, 7, 5, 10, 2, 5, -1, -1, -1, -1},
        {9, 0, 1, 5, 10, 3, 5, 3, 7, 3, 10, 2, -1, -1, -1, -1},
        {9, 8, 2, 9, 2, 1, 8, 7, 2, 10, 2, 5, 7, 5, 2, -1},
        {1, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 8, 7, 0, 7, 1, 1, 7, 5, -1, -1, -1, -1, -1, -1, -1},
        {9, 0, 3, 9, 3, 5, 5, 3, 7, -1, -1, -1, -1, -1, -1, -1},
        {9, 8, 7, 5, 9, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {5, 8, 4, 5, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1},
        {5, 0, 4, 5, 11, 0, 5, 10, 11, 11, 3, 0, -1, -1, -1, -1},
        {0, 1, 9, 8, 4, 10, 8, 10, 11, 10, 4, 5, -1, -1, -1, -1},
        {10, 11, 4, 10, 4, 5, 11, 3, 4, 9, 4, 1, 3, 1, 4, -1},
        {2, 5, 1, 2, 8, 5, 2, 11, 8, 4, 5, 8, -1, -1, -1, -1},
        {0, 4, 11, 0, 11, 3, 4, 5, 11, 2, 11, 1, 5, 1, 11, -1},
        {0, 2, 5, 0, 5, 9, 2, 11, 5, 4, 5, 8, 11, 8, 5, -1},
        {9, 4, 5, 2, 11, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {2, 5, 10, 3, 5, 2, 3, 4, 5, 3, 8, 4, -1, -1, -1, -1},
        {5, 10, 2, 5, 2, 4, 4, 2, 0, -1, -1, -1, -1, -1, -1, -1},
        {3, 10, 2, 3, 5, 10, 3, 8, 5, 4, 5, 8, 0, 1, 9, -1},
        {5, 10, 2, 5, 2, 4, 1, 9, 2, 9, 4, 2, -1, -1, -1, -1},
        {8, 4, 5, 8, 5, 3, 3, 5, 1, -1, -1, -1, -1, -1, -1, -1},
        {0, 4, 5, 1, 0, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {8, 4, 5, 8, 5, 3, 9, 0, 5, 0, 3, 5, -1, -1, -1, -1},
        {9, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {4, 11, 7, 4, 9, 11, 9, 10, 11, -1, -1, -1, -1, -1, -1, -1},
        {0, 8, 3, 4, 9, 7, 9, 11, 7, 9, 10, 11, -1, -1, -1, -1},
        {1, 10, 11, 1, 11, 4, 1, 4, 0, 7, 4, 11, -1, -1, -1, -1},
        {3, 1, 4, 3, 4, 8, 1, 10, 4, 7, 4, 11, 10, 11, 4, -1},
        {4, 11, 7, 9, 11, 4, 9, 2, 11, 9, 1, 2, -1, -1, -1, -1},
        {9, 7, 4, 9, 11, 7, 9, 1, 11, 2, 11, 1, 0, 8, 3, -1},
        {11, 7, 4, 11, 4, 2, 2, 4, 0, -1, -1, -1, -1, -1, -1, -1},
        {11, 7, 4, 11, 4, 2, 8, 3, 4, 3, 2, 4, -1, -1, -1, -1},
        {2, 9, 10, 2, 7, 9, 2, 3, 7, 7, 4, 9, -1, -1, -1, -1},
        {9, 10, 7, 9, 7, 4, 10, 2, 7, 8, 7, 0, 2, 0, 7, -1},
        {3, 7, 10, 3, 10, 2, 7, 4, 10, 1, 10, 0, 4, 0, 10, -1},
        {1, 10, 2, 8, 7, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {4, 9, 1, 4, 1, 7, 7, 1, 3, -1, -1, -1, -1, -1, -1, -1},
        {4, 9, 1, 4, 1, 7, 0, 8, 1, 8, 7, 1, -1, -1, -1, -1},
        {4, 0, 3, 7, 4, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {4, 8, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {9, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {3, 0, 9, 3, 9, 11, 11, 9, 10, -1, -1, -1, -1, -1, -1, -1},
        {0, 1, 10, 0, 10, 8, 8, 10, 11, -1, -1, -1, -1, -1, -1, -1},
        {3, 1, 10, 11, 3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 2, 11, 1, 11, 9, 9, 11, 8, -1, -1, -1, -1, -1, -1, -1},
        {3, 0, 9, 3, 9, 11, 1, 2, 9, 2, 11, 9, -1, -1, -1, -1},
        {0, 2, 11, 8, 0, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {3, 2, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {2, 3, 8, 2, 8, 10, 10, 8, 9, -1, -1, -1, -1, -1, -1, -1},
        {9, 10, 2, 0, 9, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {2, 3, 8, 2, 8, 10, 0, 1, 8, 1, 10, 8, -1, -1, -1, -1},
        {1, 10, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {1, 3, 8, 9, 1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 9, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {0, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};

int TriCountTable[256];  

void MakeTriCountTable()
{
    int n, m;

    for (n = 0; n < 256; n++) {
	for (m = 0; m < 16; m++) {
	    if (TriTable[n][m] == -1) break;
	}
	TriCountTable[n] = m/3;
    }
}

void CubeIndex(double *data, unsigned char *cubeindex, int nx, int ny, int nz, double val)
{
    int i, j, k;
    int ii, jj, iip, jjp;

    for (i = 0; i < nx-1; i++) {
	ii = i*ny*nz;
	iip = ii+ny*nz;
	for (j = 0; j < ny-1; j++) {
	    jj = j*nz;
	    jjp = jj+nz;
	    for (k = 0; k < nz-1; k++) {
		cubeindex[ii+jj+k] = 0;
                if (val < 0.0) {
		    if (data[ii+jjp+k] < val) cubeindex[ii+jj+k] |= 1;
		    if (data[iip+jjp+k] < val) cubeindex[ii+jj+k] |= 2;
		    if (data[iip+jj+k] < val) cubeindex[ii+jj+k] |= 4;
		    if (data[ii+jj+k] < val) cubeindex[ii+jj+k] |= 8;
		    if (data[ii+jjp+k+1] < val) cubeindex[ii+jj+k] |= 16;
		    if (data[iip+jjp+k+1] < val) cubeindex[ii+jj+k] |= 32;
		    if (data[iip+jj+k+1] < val) cubeindex[ii+jj+k] |= 64;
		    if (data[ii+jj+k+1] < val) cubeindex[ii+jj+k] |= 128;
                } else {
                    if (data[ii+jjp+k] > val) cubeindex[ii+jj+k] |= 1;
                    if (data[iip+jjp+k] > val) cubeindex[ii+jj+k] |= 2;
                    if (data[iip+jj+k] > val) cubeindex[ii+jj+k] |= 4;
                    if (data[ii+jj+k] > val) cubeindex[ii+jj+k] |= 8;
                    if (data[ii+jjp+k+1] > val) cubeindex[ii+jj+k] |= 16;
                    if (data[iip+jjp+k+1] > val) cubeindex[ii+jj+k] |= 32;
                    if (data[iip+jj+k+1] > val) cubeindex[ii+jj+k] |= 64;
                    if (data[ii+jj+k+1] > val) cubeindex[ii+jj+k] |= 128;

                }
	    }
	}
    }
}

int TriCount(unsigned char *cubeindex, int nx, int ny, int nz)
{
    int i, j, k, ii, jj;
    int count = 0;

    for (i = 0; i < nx-2; i++) {
	ii = i*ny*nz;
	for (j = 0; j < ny-2; j++) {
	    jj = j*nz;
	    for (k = 0; k < nz-2; k++) {
		count += TriCountTable[(int)cubeindex[ii+jj+k]];
	    }
	}
    }
    return count;
}

void InterpolateVertex(double *pos1, double *pos2, double val1, double val2, double isoval, double *pos)
{
    double q;

    if (fabs((double)(val1-isoval)) < 1.0E-30) {
	pos[0] = pos1[0];
	pos[1] = pos1[1];
	pos[2] = pos1[2];
    }
    if (fabs((double)(val2-isoval)) < 1.0E-30) {
	pos[0] = pos2[0];
	pos[1] = pos2[1];
	pos[2] = pos2[2];
    }
    if (fabs((double)(val2-val1)) < 1.0E-30) {
	pos[0] = pos1[0];
	pos[1] = pos1[1];
	pos[2] = pos1[2];
    }
    q = (isoval-val1)/(val2-val1);
    pos[0] = pos1[0]+q*(pos2[0]-pos1[0]);
    pos[1] = pos1[1]+q*(pos2[1]-pos1[1]);
    pos[2] = pos1[2]+q*(pos2[2]-pos1[2]);
}

double TriVertexPos[12][3];

void FindVertices2(double *data, unsigned char *cubeindex, 
                   int i, int j, int k, int nx, int ny, int nz,
                   double orgpos[3], double bv[3][3], double isoval)
{
    int ijk = i*ny*nz+j*nz+k;
    double x0[3], x1[3], x2[3];

    x0[0] = orgpos[0]+bv[0][0]*(double)i+bv[0][1]*(double)j+bv[0][2]*(double)k;
    x0[1] = orgpos[1]+bv[1][0]*(double)i+bv[1][1]*(double)j+bv[1][2]*(double)k;
    x0[2] = orgpos[2]+bv[2][0]*(double)i+bv[2][1]*(double)j+bv[2][2]*(double)k;

    if (EdgeTable[cubeindex[ijk]] & 1) {
	//x1[0] = x0[0];
	//x1[1] = x0[1]+dely;
	//x1[2] = x0[2];
        x1[0] = x0[0]+bv[0][1];
        x1[1] = x0[1]+bv[1][1];
        x1[2] = x0[2]+bv[2][1];
	//x2[0] = x0[0]+delx;
	//x2[1] = x0[1]+dely;
	//x2[2] = x0[2];
        x2[0] = x0[0]+bv[0][0]+bv[0][1];
        x2[1] = x0[1]+bv[1][0]+bv[1][1];
        x2[2] = x0[2]+bv[2][0]+bv[2][1];
	InterpolateVertex(x1, x2, data[ijk+nz], data[ijk+ny*nz+nz], isoval, TriVertexPos[0]);
    }
    if (EdgeTable[cubeindex[ijk]] & 2) {
	//x1[0] = x0[0]+delx;
	//x1[1] = x0[1]+dely;
	//x1[2] = x0[2];
        x1[0] = x0[0]+bv[0][0]+bv[0][1];
        x1[1] = x0[1]+bv[1][0]+bv[1][1];
        x1[2] = x0[2]+bv[2][0]+bv[2][1];
	//x2[0] = x0[0]+delx;
	//x2[1] = x0[1];
	//x2[2] = x0[2];
        x2[0] = x0[0]+bv[0][0];
        x2[1] = x0[1]+bv[1][0];
        x2[2] = x0[2]+bv[2][0];
	InterpolateVertex(x1, x2, data[ijk+ny*nz+nz], data[ijk+ny*nz], isoval, TriVertexPos[1]);
    }
    if (EdgeTable[cubeindex[ijk]] & 4) {
	//x1[0] = x0[0]+delx;
	//x1[1] = x0[1];
	//x1[2] = x0[2];
        x1[0] = x0[0]+bv[0][0];
        x1[1] = x0[1]+bv[1][0];
        x1[2] = x0[2]+bv[2][0];
	x2[0] = x0[0];
	x2[1] = x0[1];
	x2[2] = x0[2];
	InterpolateVertex(x1, x2, data[ijk+ny*nz], data[ijk], isoval, TriVertexPos[2]);
    }
    if (EdgeTable[cubeindex[ijk]] & 8) {
	x1[0] = x0[0];
	x1[1] = x0[1];
	x1[2] = x0[2];
	//x2[0] = x0[0];
	//x2[1] = x0[1]+dely;
	//x2[2] = x0[2];
        x2[0] = x0[0]+bv[0][1];
        x2[1] = x0[1]+bv[1][1];
        x2[2] = x0[2]+bv[2][1];
	InterpolateVertex(x1, x2, data[ijk], data[ijk+nz], isoval, TriVertexPos[3]);
    }

    if (EdgeTable[cubeindex[ijk]] & 16) {
	//x1[0] = x0[0];
	//x1[1] = x0[1]+dely;
	//x1[2] = x0[2]+delz;
	//x2[0] = x0[0]+delx;
	//x2[1] = x0[1]+dely;
	//x2[2] = x0[2]+delz;
        x1[0] = x0[0]+bv[0][1]+bv[0][2];
        x1[1] = x0[1]+bv[1][1]+bv[1][2];
        x1[2] = x0[2]+bv[2][1]+bv[2][2];
        x2[0] = x0[0]+bv[0][0]+bv[0][1]+bv[0][2];
        x2[1] = x0[1]+bv[1][0]+bv[1][1]+bv[1][2];
        x2[2] = x0[2]+bv[2][0]+bv[2][1]+bv[2][2];
	InterpolateVertex(x1, x2, data[ijk+nz+1], data[ijk+ny*nz+nz+1], isoval, TriVertexPos[4]);
    }
    if (EdgeTable[cubeindex[ijk]] & 32) {
	//x1[0] = x0[0]+delx;
	//x1[1] = x0[1]+dely;
	//x1[2] = x0[2]+delz;
	//x2[0] = x0[0]+delx;
	//x2[1] = x0[1];
	//x2[2] = x0[2]+delz;
        x1[0] = x0[0]+bv[0][0]+bv[0][1]+bv[0][2];
        x1[1] = x0[1]+bv[1][0]+bv[1][1]+bv[1][2];
        x1[2] = x0[2]+bv[2][0]+bv[2][1]+bv[2][2];
        x2[0] = x0[0]+bv[0][0]+bv[0][2];
        x2[1] = x0[1]+bv[1][0]+bv[1][2];
        x2[2] = x0[2]+bv[2][0]+bv[2][2];
	InterpolateVertex(x1, x2, data[ijk+ny*nz+nz+1], data[ijk+ny*nz+1], isoval, TriVertexPos[5]);
    }
    if (EdgeTable[cubeindex[ijk]] & 64) {
	//x1[0] = x0[0]+delx;
	//x1[1] = x0[1];
	//x1[2] = x0[2]+delz;
	//x2[0] = x0[0];
	//x2[1] = x0[1];
	//x2[2] = x0[2]+delz;
        x1[0] = x0[0]+bv[0][0]+bv[0][2];
        x1[1] = x0[1]+bv[1][0]+bv[1][2];
        x1[2] = x0[2]+bv[2][0]+bv[2][2];
        x2[0] = x0[0]+bv[0][2];
        x2[1] = x0[1]+bv[1][2];
        x2[2] = x0[2]+bv[2][2];
	InterpolateVertex(x1, x2, data[ijk+ny*nz+1], data[ijk+1], isoval, TriVertexPos[6]);
    }
    if (EdgeTable[cubeindex[ijk]] & 128) {
	//x1[0] = x0[0];
	//x1[1] = x0[1];
	//x1[2] = x0[2]+delz;
	//x2[0] = x0[0];
	//x2[1] = x0[1]+dely;
	//x2[2] = x0[2]+delz;
        x1[0] = x0[0]+bv[0][2];
        x1[1] = x0[1]+bv[1][2];
        x1[2] = x0[2]+bv[2][2];
        x2[0] = x0[0]+bv[0][1]+bv[0][2];
        x2[1] = x0[1]+bv[1][1]+bv[1][2];
        x2[2] = x0[2]+bv[2][1]+bv[2][2];
	InterpolateVertex(x1, x2, data[ijk+1], data[ijk+nz+1], isoval, TriVertexPos[7]);
    }


    if (EdgeTable[cubeindex[ijk]] & 256) {
	//x1[0] = x0[0];
	//x1[1] = x0[1]+dely;
	//x1[2] = x0[2];
	//x2[0] = x0[0];
	//x2[1] = x0[1]+dely;
	//x2[2] = x0[2]+delz;
        x1[0] = x0[0]+bv[0][1];
        x1[1] = x0[1]+bv[1][1];
        x1[2] = x0[2]+bv[2][1];
        x2[0] = x0[0]+bv[0][1]+bv[1][2];
        x2[1] = x0[1]+bv[1][1]+bv[1][2];
        x2[2] = x0[2]+bv[2][1]+bv[2][2];
	InterpolateVertex(x1, x2, data[ijk+nz], data[ijk+nz+1], isoval, TriVertexPos[8]);
    }
    if (EdgeTable[cubeindex[ijk]] & 512) {
	//x1[0] = x0[0]+delx;
	//x1[1] = x0[1]+dely;
	//x1[2] = x0[2];
	//x2[0] = x0[0]+delx;
	//x2[1] = x0[1]+dely;
	//x2[2] = x0[2]+delz;
        x1[0] = x0[0]+bv[0][0]+bv[0][1];
        x1[1] = x0[1]+bv[1][0]+bv[1][1];
        x1[2] = x0[2]+bv[2][0]+bv[2][1];
        x2[0] = x0[0]+bv[0][0]+bv[0][1]+bv[0][2];
        x2[1] = x0[1]+bv[1][0]+bv[1][1]+bv[1][2];
        x2[2] = x0[2]+bv[2][0]+bv[2][1]+bv[2][2];
	InterpolateVertex(x1, x2, data[ijk+ny*nz+nz], data[ijk+ny*nz+nz+1], isoval, TriVertexPos[9]);
    }
    if (EdgeTable[cubeindex[ijk]] & 1024) {
	//x1[0] = x0[0]+delx;
	//x1[1] = x0[1];
	//x1[2] = x0[2];
	//x2[0] = x0[0]+delx;
	//x2[1] = x0[1];
	//x2[2] = x0[2]+delz;
        x1[0] = x0[0]+bv[0][0];
        x1[1] = x0[1]+bv[1][0];
        x1[2] = x0[2]+bv[2][0];
        x2[0] = x0[0]+bv[0][0]+bv[0][2];
        x2[1] = x0[1]+bv[1][0]+bv[1][2];
        x2[2] = x0[2]+bv[2][0]+bv[2][2];
	InterpolateVertex(x1, x2, data[ijk+ny*nz], data[ijk+ny*nz+1], isoval, TriVertexPos[10]);
    }
    if (EdgeTable[cubeindex[ijk]] & 2048) {
	//x1[0] = x0[0];
	//x1[1] = x0[1];
	//x1[2] = x0[2];
	//x2[0] = x0[0];
	//x2[1] = x0[1];
	//x2[2] = x0[2]+delz;
	x1[0] = x0[0];
	x1[1] = x0[1];
	x1[2] = x0[2];
        x2[0] = x0[0]+bv[0][2];
        x2[1] = x0[1]+bv[1][2];
        x2[2] = x0[2]+bv[2][2];
	InterpolateVertex(x1, x2, data[ijk], data[ijk+1], isoval, TriVertexPos[11]);
    } 
}

void FindVertices(double *data, unsigned char *cubeindex, int i, int j, int k, int nx, int ny, int nz, 
		  double xorg, double yorg, double zorg, double delx, double dely, double delz, double isoval)
{
    int ijk = i*ny*nz+j*nz+k;
    double x0[3], x1[3], x2[3];
    
    x0[0] = xorg+(double)i*delx;
    x0[1] = yorg+(double)j*dely;
    x0[2] = zorg+(double)k*delz;

    if (EdgeTable[cubeindex[ijk]] & 1) {
	x1[0] = x0[0];
	x1[1] = x0[1]+dely;
	x1[2] = x0[2];
	x2[0] = x0[0]+delx;
	x2[1] = x0[1]+dely;
	x2[2] = x0[2];
	InterpolateVertex(x1, x2, data[ijk+nz], data[ijk+ny*nz+nz], isoval, TriVertexPos[0]);
    }
    if (EdgeTable[cubeindex[ijk]] & 2) {
	x1[0] = x0[0]+delx;
	x1[1] = x0[1]+dely;
	x1[2] = x0[2];
	x2[0] = x0[0]+delx;
	x2[1] = x0[1];
	x2[2] = x0[2];
	InterpolateVertex(x1, x2, data[ijk+ny*nz+nz], data[ijk+ny*nz], isoval, TriVertexPos[1]);
    }
    if (EdgeTable[cubeindex[ijk]] & 4) {
	x1[0] = x0[0]+delx;
	x1[1] = x0[1];
	x1[2] = x0[2];
	x2[0] = x0[0];
	x2[1] = x0[1];
	x2[2] = x0[2];
	InterpolateVertex(x1, x2, data[ijk+ny*nz], data[ijk], isoval, TriVertexPos[2]);
    }
    if (EdgeTable[cubeindex[ijk]] & 8) {
	x1[0] = x0[0];
	x1[1] = x0[1];
	x1[2] = x0[2];
	x2[0] = x0[0];
	x2[1] = x0[1]+dely;
	x2[2] = x0[2];
	InterpolateVertex(x1, x2, data[ijk], data[ijk+nz], isoval, TriVertexPos[3]);
    }

    if (EdgeTable[cubeindex[ijk]] & 16) {
	x1[0] = x0[0];
	x1[1] = x0[1]+dely;
	x1[2] = x0[2]+delz;
	x2[0] = x0[0]+delx;
	x2[1] = x0[1]+dely;
	x2[2] = x0[2]+delz;
	InterpolateVertex(x1, x2, data[ijk+nz+1], data[ijk+ny*nz+nz+1], isoval, TriVertexPos[4]);
    }
    if (EdgeTable[cubeindex[ijk]] & 32) {
	x1[0] = x0[0]+delx;
	x1[1] = x0[1]+dely;
	x1[2] = x0[2]+delz;
	x2[0] = x0[0]+delx;
	x2[1] = x0[1];
	x2[2] = x0[2]+delz;
	InterpolateVertex(x1, x2, data[ijk+ny*nz+nz+1], data[ijk+ny*nz+1], isoval, TriVertexPos[5]);
    }
    if (EdgeTable[cubeindex[ijk]] & 64) {
	x1[0] = x0[0]+delx;
	x1[1] = x0[1];
	x1[2] = x0[2]+delz;
	x2[0] = x0[0];
	x2[1] = x0[1];
	x2[2] = x0[2]+delz;
	InterpolateVertex(x1, x2, data[ijk+ny*nz+1], data[ijk+1], isoval, TriVertexPos[6]);
    }
    if (EdgeTable[cubeindex[ijk]] & 128) {
	x1[0] = x0[0];
	x1[1] = x0[1];
	x1[2] = x0[2]+delz;
	x2[0] = x0[0];
	x2[1] = x0[1]+dely;
	x2[2] = x0[2]+delz;
	InterpolateVertex(x1, x2, data[ijk+1], data[ijk+nz+1], isoval, TriVertexPos[7]);
    }


    if (EdgeTable[cubeindex[ijk]] & 256) {
	x1[0] = x0[0];
	x1[1] = x0[1]+dely;
	x1[2] = x0[2];
	x2[0] = x0[0];
	x2[1] = x0[1]+dely;
	x2[2] = x0[2]+delz;
	InterpolateVertex(x1, x2, data[ijk+nz], data[ijk+nz+1], isoval, TriVertexPos[8]);
    }
    if (EdgeTable[cubeindex[ijk]] & 512) {
	x1[0] = x0[0]+delx;
	x1[1] = x0[1]+dely;
	x1[2] = x0[2];
	x2[0] = x0[0]+delx;
	x2[1] = x0[1]+dely;
	x2[2] = x0[2]+delz;
	InterpolateVertex(x1, x2, data[ijk+ny*nz+nz], data[ijk+ny*nz+nz+1], isoval, TriVertexPos[9]);
    }
    if (EdgeTable[cubeindex[ijk]] & 1024) {
	x1[0] = x0[0]+delx;
	x1[1] = x0[1];
	x1[2] = x0[2];
	x2[0] = x0[0]+delx;
	x2[1] = x0[1];
	x2[2] = x0[2]+delz;
	InterpolateVertex(x1, x2, data[ijk+ny*nz], data[ijk+ny*nz+1], isoval, TriVertexPos[10]);
    }
    if (EdgeTable[cubeindex[ijk]] & 2048) {
	x1[0] = x0[0];
	x1[1] = x0[1];
	x1[2] = x0[2];
	x2[0] = x0[0];
	x2[1] = x0[1];
	x2[2] = x0[2]+delz;
	InterpolateVertex(x1, x2, data[ijk], data[ijk+1], isoval, TriVertexPos[11]);
    }
}

double TriNorVecPos0[8][3];
double TriNorVecPos[12][3];

//void FindNormalVectors(double *data, unsigned char *cubeindex, int i, int j, int k, int nx, int ny, int nz, 
//		  double xorg, double yorg, double zorg, double delx, double dely, double delz, double isoval)
void FindNormalVectors(double *data, unsigned char *cubeindex, 
                    int i, int j, int k, int nx, int ny, int nz,  double isoval)
{
    int ijk = i*ny*nz+j*nz+k, ijk1;
    double nvec[8][3], v[3];
    double q;

    ijk1 = ijk+nz;
    nvec[0][0] = data[ijk1+ny*nz]-data[ijk1];
    nvec[0][1] = data[ijk1+nz]-data[ijk1];
    nvec[0][2] = data[ijk1+1]-data[ijk1];
    ijk1 = ijk+ny*nz+nz;
    nvec[1][0] = data[ijk1+ny*nz]-data[ijk1];
    nvec[1][1] = data[ijk1+nz]-data[ijk1];
    nvec[1][2] = data[ijk1+1]-data[ijk1];
    ijk1 = ijk+ny*nz;
    nvec[2][0] = data[ijk1+ny*nz]-data[ijk1];
    nvec[2][1] = data[ijk1+nz]-data[ijk1];
    nvec[2][2] = data[ijk1+1]-data[ijk1];
    ijk1 = ijk;
    nvec[3][0] = data[ijk1+ny*nz]-data[ijk1];
    nvec[3][1] = data[ijk1+nz]-data[ijk1];
    nvec[3][2] = data[ijk1+1]-data[ijk1];
    ijk1 = ijk+nz+1;
    nvec[4][0] = data[ijk1+ny*nz]-data[ijk1];
    nvec[4][1] = data[ijk1+nz]-data[ijk1];
    nvec[4][2] = data[ijk1+1]-data[ijk1];
    ijk1 = ijk+ny*nz+nz+1;
    nvec[5][0] = data[ijk1+ny*nz]-data[ijk1];
    nvec[5][1] = data[ijk1+nz]-data[ijk1];
    nvec[5][2] = data[ijk1+1]-data[ijk1];
    ijk1 = ijk+ny*nz+1;
    nvec[6][0] = data[ijk1+ny*nz]-data[ijk1];
    nvec[6][1] = data[ijk1+nz]-data[ijk1];
    nvec[6][2] = data[ijk1+1]-data[ijk1];
    ijk1 = ijk+1;
    nvec[7][0] = data[ijk1+ny*nz]-data[ijk1];
    nvec[7][1] = data[ijk1+nz]-data[ijk1];
    nvec[7][2] = data[ijk1+1]-data[ijk1];
    
    if (EdgeTable[cubeindex[ijk]] & 1) {
	InterpolateVertex(nvec[0], nvec[1], data[ijk+nz], data[ijk+ny*nz+nz], isoval, v);
	q = (double)sqrt((double)(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]));
	TriNorVecPos[0][0] = v[0]/q;
	TriNorVecPos[0][1] = v[1]/q;
	TriNorVecPos[0][2] = v[2]/q;
    }
    if (EdgeTable[cubeindex[ijk]] & 2) {
	InterpolateVertex(nvec[1], nvec[2], data[ijk+ny*nz+nz], data[ijk+ny*nz], isoval, v);
	q = (double)sqrt((double)(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]));
	TriNorVecPos[1][0] = v[0]/q;
	TriNorVecPos[1][1] = v[1]/q;
	TriNorVecPos[1][2] = v[2]/q;
    }
    if (EdgeTable[cubeindex[ijk]] & 4) {
	InterpolateVertex(nvec[2], nvec[3], data[ijk+ny*nz], data[ijk], isoval, v);
	q = (double)sqrt((double)(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]));
	TriNorVecPos[2][0] = v[0]/q;
	TriNorVecPos[2][1] = v[1]/q;
	TriNorVecPos[2][2] = v[2]/q;
    }
    if (EdgeTable[cubeindex[ijk]] & 8) {
	InterpolateVertex(nvec[3], nvec[0], data[ijk], data[ijk+nz], isoval, v);
	q = (double)sqrt((double)(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]));
	TriNorVecPos[3][0] = v[0]/q;
	TriNorVecPos[3][1] = v[1]/q;
	TriNorVecPos[3][2] = v[2]/q;
    }

    if (EdgeTable[cubeindex[ijk]] & 16) {
	InterpolateVertex(nvec[4], nvec[5], data[ijk+nz+1], data[ijk+ny*nz+nz+1], isoval, v);
	q = (double)sqrt((double)(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]));
	TriNorVecPos[4][0] = v[0]/q;
	TriNorVecPos[4][1] = v[1]/q;
	TriNorVecPos[4][2] = v[2]/q;
    }
    if (EdgeTable[cubeindex[ijk]] & 32) {
	InterpolateVertex(nvec[5], nvec[6], data[ijk+ny*nz+nz+1], data[ijk+ny*nz+1], isoval, v);
	q = (double)sqrt((double)(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]));
	TriNorVecPos[5][0] = v[0]/q;
	TriNorVecPos[5][1] = v[1]/q;
	TriNorVecPos[5][2] = v[2]/q;
    }
    if (EdgeTable[cubeindex[ijk]] & 64) {
	InterpolateVertex(nvec[6], nvec[7], data[ijk+ny*nz+1], data[ijk+1], isoval, v);
	q = (double)sqrt((double)(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]));
	TriNorVecPos[6][0] = v[0]/q;
	TriNorVecPos[6][1] = v[1]/q;
	TriNorVecPos[6][2] = v[2]/q;
    }
    if (EdgeTable[cubeindex[ijk]] & 128) {
	InterpolateVertex(nvec[7], nvec[4], data[ijk+1], data[ijk+nz+1], isoval, v);
	q = (double)sqrt((double)(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]));
	TriNorVecPos[7][0] = v[0]/q;
	TriNorVecPos[7][1] = v[1]/q;
	TriNorVecPos[7][2] = v[2]/q;
    }


    if (EdgeTable[cubeindex[ijk]] & 256) {
	InterpolateVertex(nvec[0], nvec[4], data[ijk+nz], data[ijk+nz+1], isoval, v);
	q = (double)sqrt((double)(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]));
	TriNorVecPos[8][0] = v[0]/q;
	TriNorVecPos[8][1] = v[1]/q;
	TriNorVecPos[8][2] = v[2]/q;
    }
    if (EdgeTable[cubeindex[ijk]] & 512) {
	InterpolateVertex(nvec[1], nvec[5], data[ijk+ny*nz+nz], data[ijk+ny*nz+nz+1], isoval, v);
	q = (double)sqrt((double)(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]));
	TriNorVecPos[9][0] = v[0]/q;
	TriNorVecPos[9][1] = v[1]/q;
	TriNorVecPos[9][2] = v[2]/q;
    }
    if (EdgeTable[cubeindex[ijk]] & 1024) {
	InterpolateVertex(nvec[2], nvec[6], data[ijk+ny*nz], data[ijk+ny*nz+1], isoval, v);
	q = (double)sqrt((double)(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]));
	TriNorVecPos[10][0] = v[0]/q;
	TriNorVecPos[10][1] = v[1]/q;
	TriNorVecPos[10][2] = v[2]/q;
    }
    if (EdgeTable[cubeindex[ijk]] & 2048) {
	InterpolateVertex(nvec[3], nvec[7], data[ijk], data[ijk+1], isoval, v);
	q = (double)sqrt((double)(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]));
	TriNorVecPos[11][0] = v[0]/q;
	TriNorVecPos[11][1] = v[1]/q;
	TriNorVecPos[11][2] = v[2]/q;
    }
}

void MakeTris(double *data, unsigned char *cubeindex, int nx, int ny, int nz, 
              double xorg, double yorg, double zorg, 
	      double delx, double dely, double delz, 
              double isoval, double *tris, double *nvec)
{
    int i, j, k, m, count = 0;
    int ii, jj, ci;

    for (i = 0; i < nx-2; i++) {
	ii = i*ny*nz;
	for (j = 0; j < ny-2; j++) {
	    jj = j*nz;
	    for (k = 0; k < nz-2; k++) {
		FindVertices(data, cubeindex, i, j, k, nx, ny, nz, xorg, yorg, zorg, delx, dely, delz, isoval);
		FindNormalVectors(data, cubeindex, i, j, k, nx, ny, nz, isoval);
		ci = (int)cubeindex[ii+jj+k];
		for (m = 0; TriTable[ci][m] != -1; m += 3) {
		    
		    tris[count*9+0] = TriVertexPos[TriTable[ci][m]][0];
		    tris[count*9+1] = TriVertexPos[TriTable[ci][m]][1];
		    tris[count*9+2] = TriVertexPos[TriTable[ci][m]][2];
		    tris[count*9+3] = TriVertexPos[TriTable[ci][m+1]][0];
		    tris[count*9+4] = TriVertexPos[TriTable[ci][m+1]][1];
		    tris[count*9+5] = TriVertexPos[TriTable[ci][m+1]][2];
		    tris[count*9+6] = TriVertexPos[TriTable[ci][m+2]][0];
		    tris[count*9+7] = TriVertexPos[TriTable[ci][m+2]][1];
		    tris[count*9+8] = TriVertexPos[TriTable[ci][m+2]][2];

                   if (isoval > 0.0) {
		        nvec[count*9+0] = -TriNorVecPos[TriTable[ci][m]][0];
		        nvec[count*9+1] = -TriNorVecPos[TriTable[ci][m]][1];
		        nvec[count*9+2] = -TriNorVecPos[TriTable[ci][m]][2];
		        nvec[count*9+3] = -TriNorVecPos[TriTable[ci][m+1]][0];
		        nvec[count*9+4] = -TriNorVecPos[TriTable[ci][m+1]][1];
		        nvec[count*9+5] = -TriNorVecPos[TriTable[ci][m+1]][2];
		        nvec[count*9+6] = -TriNorVecPos[TriTable[ci][m+2]][0];
		        nvec[count*9+7] = -TriNorVecPos[TriTable[ci][m+2]][1];
		        nvec[count*9+8] = -TriNorVecPos[TriTable[ci][m+2]][2];
                    } else {
                        nvec[count*9+0] = TriNorVecPos[TriTable[ci][m]][0];
                        nvec[count*9+1] = TriNorVecPos[TriTable[ci][m]][1];
                        nvec[count*9+2] = TriNorVecPos[TriTable[ci][m]][2];
                        nvec[count*9+3] = TriNorVecPos[TriTable[ci][m+1]][0];
                        nvec[count*9+4] = TriNorVecPos[TriTable[ci][m+1]][1];
                        nvec[count*9+5] = TriNorVecPos[TriTable[ci][m+1]][2];
                        nvec[count*9+6] = TriNorVecPos[TriTable[ci][m+2]][0];
                        nvec[count*9+7] = TriNorVecPos[TriTable[ci][m+2]][1];
                        nvec[count*9+8] = TriNorVecPos[TriTable[ci][m+2]][2];

                    }
		    count++;
		}
	    }
	}
    }
}

void MakeTris2(double *data, unsigned char *cubeindex, int nx, int ny, int nz, 
              double orgpos[3], double bv[3][3],
              double isoval, double *tris, double *nvec)
{
    int i, j, k, m, count = 0;
    int ii, jj, ci;

    for (i = 0; i < nx-2; i++) {
	ii = i*ny*nz;
	for (j = 0; j < ny-2; j++) {
	    jj = j*nz;
	    for (k = 0; k < nz-2; k++) {
		FindVertices2(data, cubeindex, i, j, k, nx, ny, nz, 
                              orgpos, bv, isoval);
		FindNormalVectors(data, cubeindex, i, j, k, nx, ny, nz, isoval);
		ci = (int)cubeindex[ii+jj+k];
		for (m = 0; TriTable[ci][m] != -1; m += 3) {
		    
		    tris[count*9+0] = TriVertexPos[TriTable[ci][m]][0];
		    tris[count*9+1] = TriVertexPos[TriTable[ci][m]][1];
		    tris[count*9+2] = TriVertexPos[TriTable[ci][m]][2];
		    tris[count*9+3] = TriVertexPos[TriTable[ci][m+1]][0];
		    tris[count*9+4] = TriVertexPos[TriTable[ci][m+1]][1];
		    tris[count*9+5] = TriVertexPos[TriTable[ci][m+1]][2];
		    tris[count*9+6] = TriVertexPos[TriTable[ci][m+2]][0];
		    tris[count*9+7] = TriVertexPos[TriTable[ci][m+2]][1];
		    tris[count*9+8] = TriVertexPos[TriTable[ci][m+2]][2];

                   if (isoval > 0.0) {
		        nvec[count*9+0] = -TriNorVecPos[TriTable[ci][m]][0];
		        nvec[count*9+1] = -TriNorVecPos[TriTable[ci][m]][1];
		        nvec[count*9+2] = -TriNorVecPos[TriTable[ci][m]][2];
		        nvec[count*9+3] = -TriNorVecPos[TriTable[ci][m+1]][0];
		        nvec[count*9+4] = -TriNorVecPos[TriTable[ci][m+1]][1];
		        nvec[count*9+5] = -TriNorVecPos[TriTable[ci][m+1]][2];
		        nvec[count*9+6] = -TriNorVecPos[TriTable[ci][m+2]][0];
		        nvec[count*9+7] = -TriNorVecPos[TriTable[ci][m+2]][1];
		        nvec[count*9+8] = -TriNorVecPos[TriTable[ci][m+2]][2];
                    } else {
                        nvec[count*9+0] = TriNorVecPos[TriTable[ci][m]][0];
                        nvec[count*9+1] = TriNorVecPos[TriTable[ci][m]][1];
                        nvec[count*9+2] = TriNorVecPos[TriTable[ci][m]][2];
                        nvec[count*9+3] = TriNorVecPos[TriTable[ci][m+1]][0];
                        nvec[count*9+4] = TriNorVecPos[TriTable[ci][m+1]][1];
                        nvec[count*9+5] = TriNorVecPos[TriTable[ci][m+1]][2];
                        nvec[count*9+6] = TriNorVecPos[TriTable[ci][m+2]][0];
                        nvec[count*9+7] = TriNorVecPos[TriTable[ci][m+2]][1];
                        nvec[count*9+8] = TriNorVecPos[TriTable[ci][m+2]][2];

                    }
		    count++;
		}
	    }
	}
    }
}
