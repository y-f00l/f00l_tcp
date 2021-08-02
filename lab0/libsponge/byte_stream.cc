#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}
#include <iostream>
using namespace std;

ByteStream::ByteStream(const size_t capacity) :
    eof_f(false),
    end(false),
    cap(capacity),
    buffer(""),
    write_count(0),
    read_count(0)
    {}

size_t ByteStream::write(const string &data) {
    this -> eof_f = false;
    size_t remain = this -> remaining_capacity();
    size_t count = data.size() > remain ? remain : data.size();
    this -> buffer += data.substr(0, count);
    this -> write_count += count;
    return count;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    return this -> buffer.substr(0,len);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    this -> buffer.erase(0,len);
    this -> read_count += len;
    if(this -> buffer_empty() && this -> input_ended())
        this -> eof_f = true;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    size_t remain = this -> buffer_size();
    size_t count = len > remain ? remain : len;
    //this -> read_count += count;
    //cout << this -> read_count << endl;
    return peek_output(count);
}

void ByteStream::end_input() {
    this->end = true;
    if(this -> buffer_empty())
        this -> eof_f = true;
}

bool ByteStream::input_ended() const {
    return this -> end;
}

size_t ByteStream::buffer_size() const {
    return this -> buffer.size();
}

bool ByteStream::buffer_empty() const {
    return this -> buffer.empty();
}

bool ByteStream::eof() const {
    return this -> eof_f;
}

size_t ByteStream::bytes_written() const {
    return this -> write_count;
}

size_t ByteStream::bytes_read() const {
    return this -> read_count;
}

size_t ByteStream::remaining_capacity() const {
    return this -> cap - buffer.size();
}
