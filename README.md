# build and run
```bash
mkdir build
cd build
cmake ..
make
./benchmark
```
This runs a growing size of hashmaps, abseil and tessil hopscotch\_map, and measures the time taken to insert and find elements in the hashmaps. The results are written to stdout.
