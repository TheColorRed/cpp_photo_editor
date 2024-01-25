#include <array>
#include <map>
#include <regex>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

class CliArgs {
private:
  /** The original arguments passed to the program. */
  vector<string> vargs;
  /** The arguments converted to a map, excluding the input file and program name. */
  // vector<string> insertOrder;
  // map<string, vector<string>> args;
  map<string, bool> flags;
  vector<map<string, vector<string>>> args;

public:
  /** The input file. */
  string input;
  vector<string> output;

  CliArgs(char* argv[]) {
    for (int i = 0; argv[i] != NULL; i++) vargs.push_back(string(argv[i]));
    // remove the first argument (the program name)
    vargs.erase(vargs.begin());
  }

  void parse() {
    this->getInput();

    // Loop through the remaining arguments and add them to the map
    for (int i = 0; i < vargs.size(); i++) {
      string arg = vargs[i];
      if (arg.rfind("--", 0) == 0) {
        string key, value;
        if (arg == "--o") {
          key = arg.substr(1);
          value = vargs[i + 1];
          output.push_back(value);
        } else {
          key = arg.substr(2);
          value = vargs[i + 1];
          map<string, vector<string>> argMap;
          argMap[key] = vector<string>();
          // If the item after the key is another key/flag, then the value is empty.
          if (value.rfind("-", 0) == 0) {
            args.push_back(argMap);
          } else {
            argMap[key].push_back(value);
            args.push_back(argMap);
          }
        }
      } else if (arg.rfind("-", 0) == 0) {
        printf("Found flag %s\n", arg.c_str());
        string key = arg.substr(1);
        flags[key] = true;
        // insertOrder.push_back(key);
      }
    }
  }

  int size() {
    return args.size();
  }

  bool has(string key) {
    for (int i = 0; i < args.size(); i++) {
      auto arg = args[i];
      if (arg.find(key) != arg.end()) {
        return true;
      }
    }
    return false;
  }

  tuple<string, vector<string>> at(int index) {
    auto arg = args[index];
    return make_tuple(arg.begin()->first, arg.begin()->second);
  }

  bool getFlag(string key) {
    return flags[key];
  }

private:
  void getInput() {
    // Remove the input file from the vector and set it as the input
    string first = vargs[0];
    bool inputFound = fileExists(first);
    if (!inputFound) {
      printf("Could not find file %s\n", first.c_str());
      exit(1);
    }
    input = vargs[0];
    vargs.erase(vargs.begin());
  }

  bool fileExists(string path) {
    if (FILE* file = fopen(path.c_str(), "r")) {
      fclose(file);
      return true;
    } else {
      return false;
    }
  }
};