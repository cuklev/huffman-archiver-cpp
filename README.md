# huffman-archiver-cpp
Archiver using huffman coding written in C++


# Benchmarks

Here's a little table to compare it with lz4, a utility with similar speed.

|                                                 | none   | huff  | lz4   |
|-------------------------------------------------|--------|-------|-------|
| `base64 /dev/urandom | head -c 100000`          | 100kb  | 76kb  | 101kb |
| a tar archive of htmls with git commit hashes   | 103kb  | 60kb  | 23kb  |
| html of the wikipedia article about USA (UTF-8) | 1381kb | 947kb | 420kb |
| html of the wikipedia article about USA (ASCII) | 1372kb | 932kb | 414kb |

As you can see, lz4's results are usually better, but not as consistent.
