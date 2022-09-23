//char* first_numberstring(char* str)
//{
//    char const* digits = "0123456789";
//    size_t const n = str.find_first_of(digits);
//    if (n != std::string::npos)
//    {
//        std::size_t const m = str.find_first_not_of(digits, n);
//        return str.substr(n, m != std::string::npos ? m - n : m);
//    }
//    return std::string();
//}