#include <algorithm>
#include <iostream>
#include <vector>
int bruteForce(std::vector<int> heights,int size)
{
  int maxWater{0};
  int width{0},height{0},volume{0};
  for(int i=0;i<size;i++)
  {
    for(int j=i+1;j<size;j++)
    {
      width = j-i;
      height = std::min(heights[i],heights[j]);
      volume = width * height;
      maxWater= std::max(maxWater,volume);
    }
  }
  return maxWater;
}
int optimized(std::vector<int> heights, int size)
{
  int lp{0},rp={size-1},maxWater{0},width,ht,currentWater;
  while(lp<rp)
  {
    width = rp-lp;
    ht = std::min(heights[lp],heights[rp]);
    currentWater = width * ht;
    maxWater = std::max(maxWater, currentWater);
    heights[lp]<heights[rp]?lp++:rp--;
  }
  return maxWater;
}
int main()
{ 
  std::vector<int> heights = {1,8,6,2,5,4,8,3,7};
  std::cout<<"Max Volume of Water: "<<bruteForce(heights, heights.size())<<"\n";
  std::cout<<"Max Volume of Water: "<<optimized(heights, heights.size())<<"\n";
  return 0;
}