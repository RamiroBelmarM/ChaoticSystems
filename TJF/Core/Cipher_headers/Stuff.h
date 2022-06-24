void writeFileBytes(const char* filename, std::vector<unsigned char>& fileBytes){
    std::ofstream file(filename, std::ios::out|std::ios::binary);
    std::copy(fileBytes.cbegin(), fileBytes.cend(),
        std::ostream_iterator<unsigned char>(file));
    return;
}
unsigned int random_nonce(){
    thread_local static std::mt19937 mt{std::random_device{}()};
    thread_local static std::uniform_int_distribution<unsigned int> dist;
    using pick = std::uniform_int_distribution<unsigned int>::param_type;
    return dist(mt, pick(0, 4294967295));
}