#include <stdlib.h>

class RandomNumberGenerator
{
public:
    static int NumberBetween(int minVal, int maxVal)
    {
        //return _generator.Next(minVal, maxVal + 1);
        return rand() % (maxVal - minVal + 1) + minVal;

    }
private:
    //static Random _generator = new Random(Guid.NewGuid().GetHashCode());
};