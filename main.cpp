// #include <fstream>
// #include <limits>

// std::fstream& GotoLine(std::fstream& file, unsigned int num){
//     file.seekg(std::ios::beg);
//     for(int i=0; i < num - 1; ++i){
//         file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
//     }
//     return file;
// }

// int main(){
//     using namespace std;
//     fstream file("bla.txt");

//     GotoLine(file, 8);

//     string line8;
//     file >> line8;

//     cout << line8;
//     cin.get();
//     return 0;
// }