#include "fstruct_test.h"

#include "smgame/fstructs/fs_types.h"
#include "smgame/errors.h"
#include <iostream>
using namespace std;
using namespace smgame;
Test Hello()
{
	RandomFile f("./test_1.fs");
	auto& os = f.seekg(0);
	os << "hello world" << endl;
	os.flush();
}
