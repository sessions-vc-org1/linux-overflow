// The struct definition for a payment handler which keeps track of a client's payment Provider.
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>
#include <sqlite3.h>
#include <fstream>
#include "paymentHandler.h"

template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    auto size = static_cast<size_t>( size_s );
    std::unique_ptr<char[]> buf( new char[ size ] );
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}


PaymentHandler::PaymentHandler(void){
    currentProvider = PaymentProvider("American Express");
};

// Callback for SQLite (static class method)
int PaymentHandler::callback(void* data, int argc, char** argv, char** azColName) {
    std::string* result = static_cast<std::string*>(data);
    if (argv[0]) *result = argv[0];
    return 0;
}

std::string PaymentHandler::get_payload(char* input) {
    sqlite3* db;
    char* zErrMsg = 0;
    std::string payload = "";

    // Open in-memory DB
    if (sqlite3_open(":memory:", &db)) return "";

    // Create table and insert a string longer than 10 chars
    const std::string sql = string_format("CREATE TABLE Secrets(Val TEXT);" \
                      "INSERT INTO Secrets VALUES('{}');",input);

    const char *cstr = sql.c_str();

    sqlite3_exec(db, cstr, 0, 0, &zErrMsg);

    // Fetch it back
    sqlite3_exec(db, "SELECT Val FROM Secrets LIMIT 1;", PaymentHandler::callback, &payload, &zErrMsg);
    
    sqlite3_close(db);
    return payload;
}

std::string PaymentHandler::load_file_for_payload(const std::string& payload) {
    // Map known payloads to filenames
    std::string filePath;
    if (payload == "THIS_PAYLOAD_IS_DEFINITELY_TOO_LONG") {
        filePath = "samples/long_payload.txt";
    } else if (payload == "SHORT_PAYLOAD") {
        filePath = "samples/short_payload.txt";
    } else {
        filePath = "samples/default_payload.txt";
    }

    std::ifstream in(filePath, std::ios::in | std::ios::binary);
    if (!in) {
        return "";
    }
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return contents;
}

// Source - https://stackoverflow.com/a
// Posted by iFreilicht, modified by community. See post 'Timeline' for change history
// Retrieved 2026-01-22, License - CC BY-SA 4.0





// Backwards-compatible free function wrapper used by existing callers
std::string get_payload(char* input) {
    PaymentHandler handler;
    return handler.get_payload(input);
}

void PaymentHandler::get_input(char* text) {
            std::cout << "Input your payload: " << std::endl;
            std::cin >> text;
        }