#include <string>

namespace BankOcr {
    namespace detail {
        int RecognizeDigit(const std::string& line1, const std::string& line2, const std::string& line3);
        int RecognizeNumber(const std::string& line1, const std::string& line2, const std::string& line3);
    }
}
