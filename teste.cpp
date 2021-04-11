#include <iostream>


int main(int argc, char** argv){
  std::string s = "scott>=tiger";
std::string delimiter = ">=";
std::string token = s.substr(0, s.find(delimiter)); // token is "scott"
s.substr(s.find(delimiter));
  return 0;
}