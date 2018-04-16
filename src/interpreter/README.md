### How to Install Luna Interpreter

- make sure your current dir is `.../SER502-Spring2018-Team4/src/interpreter`, you can use `pwd` to check your current dir.
- create a new dir to build Luna Interpreter: `mkdir build`
- `cd` to `build` dir: `cd build`
- compile Luna interpreter: `cmake .. && make`, now executable Luna interpreter should be stored in `.../build/bin` dir.
- run Luna interpreter: `bin/luna`.
- (Optional) install Luna interpreter to your computer: `sudo make install`, now you can run Luna interpreter by using `luna`
- (Optional) run unit tests: `bin/luna_test` or `make test`.

